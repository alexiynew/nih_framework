
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

#include <chrono>
#include <thread>

#include <common/utils.hpp>
#include <common/version.hpp>
#include <graphics/opengl/gl.hpp>
#include <system/window.hpp>
#include <unit_test/suite.hpp>

class context_test : public framework::unit_test::suite
{
public:
    context_test() : suite("context_test")
    {
        add_test([this]() { main_loop(); }, "main_loop");
    }

private:
    void main_loop()
    {
        using framework::float32;
        using framework::graphics::context_settings;
        using framework::system::window;
        using framework::utils::random_numbers;

        using namespace framework::graphics::opengl::details;

        window::set_application_name("GL Test");

        framework::graphics::opengl::init();

        window main_window({640, 480}, "Context test");
        auto context = main_window.context();

        TEST_ASSERT(context != nullptr, "No graphic context.");
        TEST_ASSERT(context->valid(), "Graphic context is invalid.");

        const context_settings& settings = context->settings();
        TEST_ASSERT(settings.api_type() == context_settings::graphic_api::opengl, "Wrong context settings");
        TEST_ASSERT(settings.version() == framework::utils::version(3, 0), "Wrong context settings");
        TEST_ASSERT(settings.depth_bits() == 24, "Wrong context settings");
        TEST_ASSERT(settings.stencil_bits() == 8, "Wrong context settings");
        TEST_ASSERT(settings.antialiasing_level() == context_settings::antialiasing::best, "Wrong context settings");

        context->make_current();

        TEST_ASSERT(context->is_current(), "Can't make graphic context current.");

        main_window.show();

        const float32 max_total_time = 1000;
        float32 total_time           = 0;

        while (main_window.visible() && total_time < max_total_time) {
            main_window.process_events();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            context->swap_buffers();

            std::this_thread::sleep_for(std::chrono::milliseconds(16));

            total_time += 16;
        }
    }
};

int main()
{
    return run_tests(context_test());
}