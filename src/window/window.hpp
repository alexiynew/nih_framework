/// @file
/// @brief Window interface class.
/// @author Fedorov Alexey
/// @date 04.04.2017

#ifndef FRAMEWORK_WINDOW_WINDOW_HPP
#define FRAMEWORK_WINDOW_WINDOW_HPP

#include <common/common_types.hpp>
#include <memory>

namespace framework {

class window
{
public:
    class implementation;

    struct size_t
    {
        int32 width;
        int32 height;
    };

    struct position_t
    {
        int32 x;
        int32 y;
    };

    window();
    ~window();

    window(const window&) = delete;
    window& operator=(const window&) = delete;

    /// @name actions
    /// @{
    void show();
    void hide();
    void focus();
    void process_events();

    void minimize();
    void maximize();
    void to_full_screen();
    void restore();
    /// @}

    /// @name setters
    /// @{
    void set_size(size_t size);
    void set_position(position_t position);

    void set_max_size(size_t max_size);
    void set_min_size(size_t min_size);

    void set_title(const std::string& title);
    /// @}

    /// @name getters
    /// @{
    position_t position();
    size_t size();

    size_t max_size();
    size_t min_size();

    std::string title();

    bool full_screen();
    bool minimized();
    bool maximized();
    bool resizable();
    bool visible();
    bool focused();
    /// @}

private:
    std::unique_ptr<implementation> m_implementation;
};
} // namespace framework

#endif
