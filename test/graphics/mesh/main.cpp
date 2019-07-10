
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
#include <gl/gl.hpp>
#include <graphics/mesh.hpp>
#include <system/window.hpp>
#include <unit_test/suite.hpp>

class mesh_test : public framework::unit_test::suite
{
public:
    mesh_test() : suite("mesh_test")
    {
        add_test([this]() { main_loop(); }, "main_loop");
    }

private:
    void main_loop()
    {
        using namespace framework;

        using framework::float32;
        using framework::graphics::mesh;
        using framework::system::window;
        using framework::utils::random_numbers;

        window::set_application_name("GL mesh Test");

        window main_window({640, 480}, "GL mesh test");

        main_window.make_current();

        main_window.show();

        const float32 max_total_time = 1000;
        float32 total_time           = 0;

        while (main_window.visible() && total_time < max_total_time) {
            main_window.process_events();

            gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            gl::glClear(GL_COLOR_BUFFER_BIT);

            main_window.swap_buffers();

            std::this_thread::sleep_for(std::chrono::milliseconds(16));

            total_time += 16;
        }

        TEST_FAIL("Not implemented.");
    }
};

int main()
{
    return run_tests(mesh_test());
}
