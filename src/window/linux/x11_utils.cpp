#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

#include <window/linux/x11_utils.hpp>

using namespace framework;

namespace {

/// Client message source
constexpr int32 message_source_application = 1;

const std::string net_supporting_wm_check_atom_name  = u8"_NET_SUPPORTING_WM_CHECK";
const std::string net_supported_atom_name            = u8"_NET_SUPPORTED";
const std::string net_wm_state_atom_name             = u8"_NET_WM_STATE";
const std::string net_wm_bypass_compositor_atom_name = u8"_NET_WM_BYPASS_COMPOSITOR";
const std::string net_active_window_atom_name        = u8"_NET_ACTIVE_WINDOW";
const std::string wm_state_atom_name                 = u8"WM_STATE";
const std::string net_wm_name_atom_name              = u8"_NET_WM_NAME";
const std::string net_wm_icon_name_atom_name         = u8"_NET_WM_ICON_NAME";
const std::string utf8_string_atom_name              = u8"UTF8_STRING";

enum net_wm_state_action
{
    remove = 0,
    add    = 1
};

enum bypass_compositor_state
{
    no_preferences = 0,
    disabled       = 1
};

inline bool have_utf8_support()
{
#ifdef X_HAVE_UTF8_STRING
    return true;
#else
    return false;
#endif
}

template <typename ValueType, typename DataType>
std::vector<ValueType> values_from_array(const DataType* data, uint64 count)
{
    std::vector<ValueType> values(count);

    for (uint64 i = 0; i < count; ++i) {
        values[i] = *(reinterpret_cast<const ValueType*>(data + i));
    }

    return values;
}

template <typename PropertyType>
std::vector<PropertyType> get_window_property(Display* display, Window window, Atom property, Atom type)
{
    const int64 max_items_count = 1024;

    Atom actual_type    = None;
    int32 actual_format = 0;
    uint64 items_count  = 0;
    uint64 bytes_after  = 0;
    uint8* data         = nullptr;

    int32 result = XGetWindowProperty(display,
                                      window,
                                      property,
                                      0,
                                      max_items_count,
                                      False,
                                      type,
                                      &actual_type,
                                      &actual_format,
                                      &items_count,
                                      &bytes_after,
                                      &data);

    if (result != Success || actual_type != type || items_count == 0 || data == nullptr) {
        if (data) {
            XFree(data);
        }
        return std::vector<PropertyType>();
    }

    std::vector<PropertyType> values;
    switch (actual_format) {
        case 8: values = values_from_array<PropertyType>(reinterpret_cast<uint8*>(data), items_count); break;
        case 16: values = values_from_array<PropertyType>(reinterpret_cast<uint16*>(data), items_count); break;
        case 32: values = values_from_array<PropertyType>(reinterpret_cast<uint32*>(data), items_count); break;
    };

    XFree(data);

    return values;
}

bool is_ewmh_compliant(const x11_server* server)
{
    const Atom net_supporting_wm_check = server->get_atom(net_supporting_wm_check_atom_name);
    const Atom net_supported           = server->get_atom(net_supported_atom_name);

    if (net_supported == None || net_supporting_wm_check == None) {
        return false;
    }

    const auto root_window = server->default_root_window();

    auto root = get_window_property<Window>(server->display(), root_window, net_supporting_wm_check, XA_WINDOW);

    if (root.empty() || root[0] == None) {
        return false;
    }

    auto child = get_window_property<Window>(server->display(), root[0], net_supporting_wm_check, XA_WINDOW);

    if (child.empty() || child[0] == None) {
        return false;
    }

    return root[0] == child[0];
}

std::vector<Atom> get_window_state(const x11_server* server, Window window)
{
    Atom net_wm_state = server->get_atom(net_wm_state_atom_name);
    if (net_wm_state == None) {
        return std::vector<Atom>();
    }

    return get_window_property<Atom>(server->display(), window, net_wm_state, XA_ATOM);
}

bool window_change_state(const x11_server* server,
                         Window window,
                         net_wm_state_action action,
                         const std::vector<std::string>& state_atom_names)
{
    if (!utils::ewmh_supported() || state_atom_names.empty()) {
        return false;
    }

    Atom net_wm_state = server->get_atom(net_wm_state_atom_name);

    if (net_wm_state == None) {
        return false;
    }

    std::array<Atom, 2> state_atoms;
    state_atoms[0] = (state_atom_names.size() > 0 ? server->get_atom(state_atom_names[0]) : None);
    state_atoms[1] = (state_atom_names.size() > 1 ? server->get_atom(state_atom_names[1]) : None);

    return utils::send_client_message(server,
                                      window,
                                      net_wm_state,
                                      action,
                                      state_atoms[0],
                                      state_atoms[1],
                                      message_source_application);
}

void bypass_compositor_set_state(const x11_server* server, Window window, bypass_compositor_state state)
{
    if (!utils::ewmh_supported()) {
        return;
    }

    Atom net_wm_bypass_compositor = server->get_atom(net_wm_bypass_compositor_atom_name);
    if (net_wm_bypass_compositor == None) {
        return;
    }

    XChangeProperty(server->display(),
                    window,
                    net_wm_bypass_compositor,
                    XA_CARDINAL,
                    32,
                    PropModeReplace,
                    reinterpret_cast<const unsigned char*>(&state),
                    1);
}

XTextProperty create_text_property(Display* display, const std::string& string)
{
    XTextProperty text_property = {};

    std::vector<char> temp(string.size() + 1);
    std::strcpy(temp.data(), string.c_str());
    char* data = temp.data();

    if (have_utf8_support()) {
        Xutf8TextListToTextProperty(display, &data, 1, XUTF8StringStyle, &text_property);
    } else {
        XmbTextListToTextProperty(display, &data, 1, XStdICCTextStyle, &text_property);
    }

    return text_property;
}

std::string create_string(Display* display, const XTextProperty& text_property)
{
    if (text_property.value == nullptr || text_property.format != 8) {
        return "";
    }

    char** list = nullptr;
    int count   = 0;
    if (have_utf8_support()) {
        Xutf8TextPropertyToTextList(display, &text_property, &list, &count);
    } else {
        XmbTextPropertyToTextList(display, &text_property, &list, &count);
    }

    if (list == nullptr) {
        return "";
    }

    std::string string(*list);

    XFreeStringList(list);

    return string;
}

} // namespace

namespace framework {

namespace utils {

bool ewmh_supported()
{
    static bool supported = is_ewmh_compliant(x11_server::connect().get());
    return supported;
}

bool send_client_message(const x11_server* server, Window window, Atom message_type, const std::vector<int64>& data)
{
    XEvent event               = {0};
    event.type                 = ClientMessage;
    event.xclient.window       = window;
    event.xclient.message_type = message_type;
    event.xclient.format       = 32;

    const int max_size = sizeof(event.xclient.data.l) / sizeof(long);

    for (size_t i = 0; i < data.size() && i < max_size; ++i) {
        event.xclient.data.l[i] = data[i];
    }

    Status result = XSendEvent(server->display(),
                               server->default_root_window(),
                               False,
                               SubstructureNotifyMask | SubstructureRedirectMask,
                               &event);

    return result != 0;
}

bool window_has_state(const x11_server* server, Window window, const std::string& state_atom_name)
{
    if (!ewmh_supported()) {
        return false;
    }

    const Atom net_wm_state_atom = server->get_atom(state_atom_name);

    if (net_wm_state_atom == None) {
        return false;
    }

    const auto state = ::get_window_state(server, window);

    for (auto atom : state) {
        if (atom == net_wm_state_atom) {
            return true;
        }
    }

    return false;
}

bool window_add_state(const x11_server* server, Window window, const std::vector<std::string>& state_atom_names)
{
    return ::window_change_state(server, window, ::net_wm_state_action::add, state_atom_names);
}

bool window_remove_state(const framework::x11_server* server,
                         Window window,
                         const std::vector<std::string>& state_atom_names)
{
    return ::window_change_state(server, window, ::net_wm_state_action::remove, state_atom_names);
}

bool activate_window(const x11_server* server, Window window, Time lastInputTime)
{
    if (!ewmh_supported()) {
        return false;
    }

    Atom net_active_window = server->get_atom(net_active_window_atom_name, false);
    if (net_active_window == None) {
        return false;
    }

    Window active_window = server->currently_active_window();
    if (window == active_window) {
        return true;
    }

    return send_client_message(server,
                               window,
                               net_active_window,
                               message_source_application,
                               lastInputTime,
                               active_window);
}

void bypass_compositor_desable(const x11_server* server, Window window)
{
    ::bypass_compositor_set_state(server, window, bypass_compositor_state::disabled);
}

void bypass_compositor_reset(const x11_server* server, Window window)
{
    ::bypass_compositor_set_state(server, window, bypass_compositor_state::no_preferences);
}

CARD32 get_window_wm_state(const x11_server* server, Window window)
{
    Atom net_wm_state = server->get_atom(wm_state_atom_name);

    auto state = get_window_property<CARD32>(server->display(), window, net_wm_state, net_wm_state);

    if (state.empty()) {
        return WithdrawnState;
    }

    return state[0];
}

void set_window_name(const x11_server* server, Window window, const std::string& title)
{
    Atom net_wm_name      = server->get_atom(net_wm_name_atom_name);
    Atom net_wm_icon_name = server->get_atom(net_wm_icon_name_atom_name);
    Atom utf8_string      = server->get_atom(utf8_string_atom_name);

    if (ewmh_supported() && net_wm_name != None && net_wm_icon_name != None && utf8_string != None) {
        XChangeProperty(server->display(),
                        window,
                        net_wm_name,
                        utf8_string,
                        8,
                        PropModeReplace,
                        reinterpret_cast<const uint8*>(title.c_str()),
                        static_cast<int32>(title.size()));

        XChangeProperty(server->display(),
                        window,
                        net_wm_icon_name,
                        utf8_string,
                        8,
                        PropModeReplace,
                        reinterpret_cast<const uint8*>(title.c_str()),
                        static_cast<int32>(title.size()));
    }

    XTextProperty text_property = create_text_property(server->display(), title);

    if (text_property.value != nullptr) {
        XSetWMName(server->display(), window, &text_property);
        XSetWMIconName(server->display(), window, &text_property);
        XFree(text_property.value);
    }
}

std::string get_window_name(const x11_server* server, Window window)
{
    Atom net_wm_name      = server->get_atom(net_wm_name_atom_name);
    Atom net_wm_icon_name = server->get_atom(net_wm_icon_name_atom_name);
    Atom utf8_string      = server->get_atom(utf8_string_atom_name);

    if (ewmh_supported() && net_wm_name != None && net_wm_icon_name != None && utf8_string != None) {
        std::vector<uint8> data = get_window_property<uint8>(server->display(), window, net_wm_name, utf8_string);

        if (data.empty()) {
            data = get_window_property<uint8>(server->display(), window, net_wm_icon_name, utf8_string);
        }

        if (!data.empty()) {
            return std::string(reinterpret_cast<char*>(data.data()), data.size());
        }
    }

    XTextProperty text_property = {};

    if (XGetWMName(server->display(), window, &text_property) == 0) {
        XGetWMIconName(server->display(), window, &text_property);
    }

    if (text_property.value != nullptr) {
        std::string title = create_string(server->display(), text_property);
        XFree(text_property.value);
        return title;
    }

    return "";
}

} // namespace utils

} // namespace framework