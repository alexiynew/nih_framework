#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <unit_test/suite.hpp>

class custom_exception
{};

/// @name Test to fail
/// @{
class should_fail_test_assert : public framework::unit_test::suite
{
public:
    should_fail_test_assert() : suite("should_fail_test_assert")
    {
        add_test([this]() { test_assert(); }, "test_assert");
    }

private:
    void test_assert()
    {
        TEST_ASSERT(false, "Test assert message.");
    }
};

class should_fail_test_fail : public framework::unit_test::suite
{
public:
    should_fail_test_fail() : suite("should_fail_test_fail")
    {
        add_test([this]() { test_fail(); }, "test_fail");
    }

private:
    void test_fail()
    {
        TEST_FAIL("Test fail message.");
    }
};

class should_fail_test_std_exception : public framework::unit_test::suite
{
public:
    should_fail_test_std_exception() : suite("should_fail_test_std_exception")
    {
        add_test([this]() { test_std_exception(); }, "test_std_exception");
    }

private:
    [[noreturn]] void test_std_exception() { throw std::runtime_error("Test exception"); }
};

class should_fail_test_any_exception : public framework::unit_test::suite
{
public:
    should_fail_test_any_exception() : suite("should_fail_test_any_exception")
    {
        add_test([this]() { test_any_exception(); }, "test_any_exception");
    }

private:
    [[noreturn]] void test_any_exception() { throw custom_exception(); }
};
/// @}

/// @name Test to pass
/// @{
class should_pass_test : public framework::unit_test::suite
{
public:
    should_pass_test() : suite("should_pass_test")
    {
        add_test([this]() { test_assert(); }, "test_assert");
    }

private:
    void test_assert()
    {
        TEST_ASSERT(true, "Test assert message.");
    }
};
/// @}

/// @name Test to run tests
/// @{
class test_for_test : public framework::unit_test::suite
{
public:
    test_for_test() : suite("test_for_test")
    {
        add_test([this]() { should_fail(); }, "should_fail");
        add_test([this]() { should_pass(); }, "should_pass");
    }

private:
    void should_fail()

    {
        std::vector<std::unique_ptr<framework::unit_test::suite>> tests;

        tests.emplace_back(std::make_unique<should_fail_test_assert>());
        tests.emplace_back(std::make_unique<should_fail_test_fail>());
        tests.emplace_back(std::make_unique<should_fail_test_std_exception>());
        tests.emplace_back(std::make_unique<should_fail_test_any_exception>());

        for (auto& test : tests) {
            run_suite(*test);

            std::stringstream error_stream;
            error_stream << "Test [" << test->name() << "] should fail.";
            TEST_ASSERT(!test->is_succeeded(), error_stream.str().c_str());
        }
    }

    void should_pass()
    {
        should_pass_test should_pass;

        run_suite(should_pass);

        TEST_ASSERT(should_pass.is_succeeded(), "This test should pass.");
    }

    void run_suite(framework::unit_test::suite& test)
    {
        std::streambuf* buffer = std::cout.rdbuf();
        std::cout.rdbuf(nullptr);

        try {
            test.run();
        } catch (...) {
        }

        std::cout.rdbuf(buffer);
        std::cout << std::setw(0);
    }
};
/// @}

int main()
{
    return run_tests(test_for_test());
}