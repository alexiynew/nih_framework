
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

#include <cstdint>
#include <sstream>

#include <common/utils.hpp>
#include <unit_test/suite.hpp>

class RandomNumbersTest : public framework::unit_test::Suite
{
public:
    RandomNumbersTest()
        : Suite("RandomNumbersTest")
    {
        add_test([this]() { generate_random_numbers(); }, "generate_random_numbers");
    }

private:
    void generate_random_numbers()
    {
        using namespace framework::utils;

        const auto no_numbers = random_numbers<float>(-1000.0f, 1000.0f, 0);
        TEST_ASSERT(no_numbers.size() == 0, "Wrond numbers count.");

        const auto numbers = random_numbers<int>(0, 0, 1000);
        TEST_ASSERT(numbers.size() == 1000, "Wrond numbers count.");

        for (auto i : numbers) {
            TEST_ASSERT(i == 0, "Wrong number in the sequence.");
        }

        for (auto i : random_numbers<double>(0.0, 1.0, 10)) {
            TEST_ASSERT(i >= 0.0 && i <= 1.0, "Wrong number in the sequence.");
        }

        for (auto i : random_numbers<std::uint16_t>(0xFFFF, 0, 1000)) {
            TEST_ASSERT(i >= 0 && i <= 0xFFFF, "Wrong number in the sequence.");
        }
    }
};

class ReadValueFromBufferTest : public framework::unit_test::Suite
{
public:
    ReadValueFromBufferTest()
        : Suite("ReadValueFromBufferTest")
    {
        add_test([this]() { read_big_endian_value_from_buffer(); }, "read_big_endian_value_from_buffer");
        add_test([this]() { read_little_endian_value_from_buffer(); }, "read_little_endian_value_from_buffer");
        add_test([this]() { read_big_endian_value_from_stream(); }, "read_big_endian_value_from_stream");
        add_test([this]() { read_little_endian_value_from_stream(); }, "read_little_endian_value_from_stream");
        add_test([this]() { read_big_endian_struct_from_buffer(); }, "read_big_endian_struct_from_buffer");
        add_test([this]() { read_little_endian_struct_from_buffer(); }, "read_little_endian_struct_from_buffer");
        add_test([this]() { read_big_endian_struct_from_stream(); }, "read_big_endian_struct_from_stream");
        add_test([this]() { read_little_endian_struct_from_stream(); }, "read_little_endian_struct_from_stream");
    }

private:

    class membuf : public std::basic_streambuf<char> {
    public:
      membuf(const std::uint8_t *p, std::size_t l) {
        setg((char*)p, (char*)p, (char*)p + l);
      }
    };

    class memstream : public std::istream
    {
    public:
        memstream(const std::uint8_t* p, size_t l)
            : std::istream(&_buffer)
            , _buffer(p, l)
        {
            rdbuf(&_buffer);
        }

    private:
        membuf _buffer;
    };

    void read_big_endian_value_from_buffer()
    {
        using namespace framework::utils;

        char buffer1[] = {0x1};
        char buffer2[] = {0x1, 0x0};
        char buffer3[] = {0x1, 0x0, 0x0, 0x0};

        char value1  = big_endian_value<char>(buffer1);
        short value2 = big_endian_value<short>(buffer2);
        int value3   = big_endian_value<int>(buffer3);

        TEST_ASSERT(value1 == 0x01, "Wrong value");
        TEST_ASSERT(value2 == 0x0100, "Wrong value");
        TEST_ASSERT(value3 == 0x01000000, "Wrong value");
    }

    void read_little_endian_value_from_buffer()
    {
        using namespace framework::utils;

        char buffer1[] = {0x1};
        char buffer2[] = {0x1, 0x0};
        char buffer3[] = {0x1, 0x0, 0x0, 0x0};

        char value1  = little_endian_value<char>(buffer1);
        short value2 = little_endian_value<short>(buffer2);
        int value3   = little_endian_value<int>(buffer3);

        TEST_ASSERT(value1 == 0x01, "Wrong value");
        TEST_ASSERT(value2 == 0x0001, "Wrong value");
        TEST_ASSERT(value3 == 0x00000001, "Wrong value");
    }

    void read_big_endian_value_from_stream()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};
        memstream stream(buffer, size(buffer));

        char value1  = big_endian_value<char>(stream);
        short value2 = big_endian_value<short>(stream);
        int value3   = big_endian_value<int>(stream);

        TEST_ASSERT(value1 == 0x01, "Wrong value");
        TEST_ASSERT(value2 == 0x0100, "Wrong value");
        TEST_ASSERT(value3 == 0x01000000, "Wrong value");
    }

    void read_little_endian_value_from_stream()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};
        memstream stream(buffer, size(buffer));

        char value1  = little_endian_value<char>(stream);
        short value2 = little_endian_value<short>(stream);
        int value3   = little_endian_value<int>(stream);

        TEST_ASSERT(value1 == 0x01, "Wrong value");
        TEST_ASSERT(value2 == 0x0001, "Wrong value");
        TEST_ASSERT(value3 == 0x00000001, "Wrong value");
    }

    void read_big_endian_struct_from_buffer()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};

        struct S {
            char v1;
            short v2;
            int v3;
        };

        S s = big_endian_value<S>(buffer);

        TEST_ASSERT(s.v1== 0x01, "Wrong value");
        TEST_ASSERT(s.v2== 0x0100, "Wrong value");
        TEST_ASSERT(s.v3== 0x01000000, "Wrong value");
    }

    void read_little_endian_struct_from_buffer()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};

        struct S {
            char v1;
            short v2;
            int v3;
        };

        S s = little_endian_value<S>(buffer);

        TEST_ASSERT(s.v1 == 0x01, "Wrong value");
        TEST_ASSERT(s.v2 == 0x0001, "Wrong value");
        TEST_ASSERT(s.v3 == 0x00000001, "Wrong value");
    }

    void read_big_endian_struct_from_stream()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};
        memstream stream(buffer, size(buffer));

        struct S {
            char v1;
            short v2;
            int v3;
        };

        S s = big_endian_value<S>(stream);

        TEST_ASSERT(s.v1== 0x01, "Wrong value");
        TEST_ASSERT(s.v2== 0x0100, "Wrong value");
        TEST_ASSERT(s.v3== 0x01000000, "Wrong value");
    }

    void read_little_endian_struct_from_stream()
    {
        using namespace framework::utils;

        std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};
        memstream stream(buffer, size(buffer));

        struct S {
            char v1;
            short v2;
            int v3;
        };

        S s = little_endian_value<S>(stream);

        TEST_ASSERT(s.v1 == 0x01, "Wrong value");
        TEST_ASSERT(s.v2 == 0x0001, "Wrong value");
        TEST_ASSERT(s.v3 == 0x00000001, "Wrong value");
    }

    //void read_little_endian_value_tuple()
    //{
    //    using namespace framework::utils;

    //    std::uint8_t buffer[] = {0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};

    //    memstream stream(buffer, size(buffer));

    //    auto [value1, value2, value3] = little_endian_values_tuple<char, short, int>(stream);

    //    TEST_ASSERT(value1 == 0x01, "Wrong value");
    //    TEST_ASSERT(value2 == 0x0001, "Wrong value");
    //    TEST_ASSERT(value3 == 0x00000001, "Wrong value");
    //}
};

/*
class format_string_test : public framework::unit_test::Suite
{
public:
    format_string_test() : Suite("format_string_test")
    {
        add_test([this]() { type_foramting(); }, "type_formating");
    }

private:
    void type_foramting()
    {
        using framework::utils::format;

        TEST_ASSERT(format("{0}", 1) == "1", "Wrong number formating.");

        TEST_ASSERT(format("{0}", 1.123456789) == "1.12346", "Wrong floating-point number formating.");

        TEST_ASSERT(format("{0}", "string") == "string", "Wrong string formating.");

        TEST_ASSERT(format("{{{0}}}", "string") == "{string}", "Wrong braces formating.");
        TEST_ASSERT(format("{0}}}", "string") == "string}", "Wrong braces formating.");
        TEST_ASSERT(format("{{{0}", "string") == "{string", "Wrong braces formating.");

        // ERROR_TEST(make_string("{{0}}}", "string"), "Single '}' in format string");
        // ERROR_TEST(make_string("{{{0}}", "string"), "Single '}' in format string");
        // ERROR_TEST(make_string("0}}}", "string"), "Single '}' in format string");
        // ERROR_TEST(make_string("{{{0", "string"), "'}' expected");
    }
};
*/

int main()
{
    return run_tests(RandomNumbersTest(), ReadValueFromBufferTest());
}
