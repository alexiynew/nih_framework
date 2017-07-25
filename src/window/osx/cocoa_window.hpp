/// @file
/// @brief Window implementation for osx.
/// @author Fedorov Alexey
/// @date 19.04.2017

#ifndef FRAMEWORK_WINDOW_OSX_COCOA_WINDOW_HPP
#define FRAMEWORK_WINDOW_OSX_COCOA_WINDOW_HPP

#include <window/window_implementation.hpp>

#import "Cocoa/Cocoa.h"

namespace framework {

class cocoa_window final : public window_implementation
{
public:
    cocoa_window();
    ~cocoa_window() override;

    void show() override;
    void hide() override;

private:
    NSAutoreleasePool* pool;
    NSWindow* window;
};
}

#endif
