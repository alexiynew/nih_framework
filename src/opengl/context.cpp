/// @file
/// @brief Window implementation for windows.
/// @author Fedorov Alexey
/// @date 11.09.2018

// =============================================================================
// MIT License
//
// Copyright (c) 2017-2018 Fedorov Alexey
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

#include <utility>

#include <opengl/context.hpp>

namespace framework::opengl
{
#pragma region context

context::context(context_settings settings) noexcept : m_settings(std::move(settings))
{}

context::~context() = default;

context_settings context::settings() const
{
    return m_settings;
}

#pragma endregion

#pragma region context_settings

context_settings& context_settings::double_buffered()
{
    m_double_buffered = true;
    return *this;
}

context_settings& context_settings::single_buffered()
{
    m_double_buffered = false;
    return *this;
}

context_settings& context_settings::version(utils::version version)
{
    m_version = version;
    return *this;
}

context_settings& context_settings::depth_bits(int32 bits)
{
    m_depth_bits = bits;
    return *this;
}

context_settings& context_settings::stencil_bits(int32 bits)
{
    m_stencil_bits = bits;
    return *this;
}

context_settings& context_settings::color_type(context_settings::color type)
{
    m_color_type = type;
    return *this;
}

context_settings& context_settings::samples_count(context_settings::samples count)
{
    m_samples_count = count;
    return *this;
}

bool context_settings::get_double_buffered() const
{
    return m_double_buffered;
}

bool context_settings::get_single_buffered() const
{
    return !m_double_buffered;
}

utils::version context_settings::get_version() const
{
    return m_version;
}

int32 context_settings::get_depth_bits() const
{
    return m_depth_bits;
}

int32 context_settings::get_stencil_bits() const
{
    return m_stencil_bits;
}

context_settings::color context_settings::get_color_type() const
{
    return m_color_type;
}

context_settings::samples context_settings::get_samples_count() const
{
    return m_samples_count;
}

#pragma endregion

} // namespace framework::opengl