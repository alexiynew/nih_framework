/// @file
/// @brief Describes interface for all window implementations.
/// @author Fedorov Alexey
/// @date 05.04.2017

// =============================================================================
// MIT License
//
// Copyright (c) 2017-2019 Fedorov Alexey
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// =============================================================================

#ifndef FRAMEWORK_SYSTEM_DETAILS_WINDOW_IMPLEMENTATION_HPP
#define FRAMEWORK_SYSTEM_DETAILS_WINDOW_IMPLEMENTATION_HPP

#include <memory>
#include <string>

#include <system/context_settings.hpp>

#include <system/inc/window_position.hpp>
#include <system/inc/window_size.hpp>

#include <system/details/event_handler.hpp>

namespace framework::system::details
{
class window_implementation
{
public:
    static void set_application_name(const std::string& name);

    window_implementation();

    virtual ~window_implementation();

    window_implementation(const window_implementation&) = delete;
    window_implementation& operator=(const window_implementation&) = delete;

    window_implementation(window_implementation&&) = default;
    window_implementation& operator=(window_implementation&&) = default;

    void set_event_handler(const details::event_handler* handler);

    /// @name actions
    /// @{
    virtual void show()           = 0;
    virtual void hide()           = 0;
    virtual void focus()          = 0;
    virtual void process_events() = 0;

    virtual void iconify()              = 0;
    virtual void maximize()             = 0;
    virtual void switch_to_fullscreen() = 0;
    virtual void restore()              = 0;
    virtual void make_current()         = 0;
    virtual void swap_buffers()         = 0;
    /// @}

    /// @name setters
    /// @{
    virtual void set_size(window_size)         = 0;
    virtual void set_position(window_position) = 0;

    virtual void set_max_size(window_size) = 0;
    virtual void set_min_size(window_size) = 0;

    virtual void set_resizable(bool) = 0;

    virtual void set_title(const std::string& title) = 0;
    /// @}

    /// @name getters
    /// @{
    virtual window_position position() const = 0;
    virtual window_size size() const         = 0;

    virtual window_size max_size() const = 0;
    virtual window_size min_size() const = 0;

    virtual std::string title() const = 0;
    /// @}

    /// @name state
    /// @{
    virtual bool fullscreen() const = 0;
    virtual bool iconified() const  = 0;
    virtual bool maximized() const  = 0;
    virtual bool resizable() const  = 0;
    virtual bool visible() const    = 0;
    virtual bool focused() const    = 0;
    /// @}

protected:
    static std::string application_name;

    const details::event_handler* m_event_handler = nullptr;
};

// @brief Fabric function to make platform dependent implementation
std::unique_ptr<window_implementation> create_implementation(window_size size,
                                                             const std::string& title,
                                                             const context_settings& settings);

} // namespace framework::system::details

#endif