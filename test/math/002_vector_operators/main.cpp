#include <math/math.hpp>
#include <unit_test/test.hpp>

using namespace framework::math;

class vector_operators_test : public test::suite
{
public:
    vector_operators_test()
        : suite("vector_operators_test")
    {
        add_test([this]() { assign_operator(); }, "assign_operator");
        add_test([this]() { access_operator(); }, "access_operator");
        add_test([this]() { data_access(); }, "data_access");
        add_test([this]() { unary_minus_operator(); }, "unary_minus_operator");
        add_test([this]() { unary_plus_operator(); }, "unary_plus_operator");
        add_test([this]() { plus_operator(); }, "plus_operator");
        add_test([this]() { minus_operator(); }, "minus_operator");
        add_test([this]() { multiply_operator(); }, "multiply_operator");
        add_test([this]() { divide_operator(); }, "divide_operator");
    }

private:
    void assign_operator()
    {
        const Vector4D v4d(1.1, 2.2, 3.3, 4);
        const Vector3F v3f(5.5f, 6.6f, 7.7f);
        const Vector2I v2i(1, 2.0);

        Vector4D v4d_result;
        Vector3F v3f_result;
        Vector2I v2i_result;

        Vector4I v4i_result;
        Vector3D v3d_result;
        Vector2F v2f_result;

        v4d_result = v4d;
        v3f_result = v3f;
        v2i_result = v2i;

        v4i_result = v4d;
        v3d_result = v3f;
        v2f_result = v2i;

        ASSERT_MSG(v4i_result == Vector4I(1, 2, 3, 4), "Assign to vector4i failed.");
        ASSERT_MSG(v4d_result == Vector4D(1.1, 2.2, 3.3, 4), "Assign to vector4d failed.");

        ASSERT_MSG(v3d_result == Vector3D(double(5.5f), double(6.6f), double(7.7f)), "Assign to vector3d failed.");
        ASSERT_MSG(v3f_result == Vector3F(5.5f, 6.6f, 7.7f), "Assign to vector3f failed.");

        ASSERT_MSG(v2f_result == Vector2F(1, 2), "Assign to vector2f failed.");
        ASSERT_MSG(v2i_result == Vector2I(1, 2.0), "Assign to vector2i failed.");
    }

    void access_operator()
    {
        const Vector4D v4d(1.1, 2.2, 3.3, 4.4);
        const Vector3F v3f(5.5f, 6.6f, 7.7f);
        const Vector2I v2i(1, 2);

        // clang-format off
        ASSERT_MSG(almost_equal(v4d[0], 1.1) &&
                   almost_equal(v4d[1], 2.2) &&
                   almost_equal(v4d[2], 3.3) &&
                   almost_equal(v4d[3], 4.4),
                   "Access to vector4d filed.");

        ASSERT_MSG(almost_equal(v3f[0], 5.5f) &&
                   almost_equal(v3f[1], 6.6f) &&
                   almost_equal(v3f[2], 7.7f),
                   "Access to vector3f failed.");

        ASSERT_MSG(v2i[0] == 1 && v2i[1] == 2, "Access to vector2i failed.");
        // clang-format on
    }

    void data_access()
    {
        const Vector4D v4d(1.1, 2.2, 3.3, 4.4);
        const Vector3F v3f(5.5f, 6.6f, 7.7f);
        const Vector2I v2i(1, 2);

        const double* double_pointer = v4d.data();
        const float* float_pointer   = v3f.data();
        const int* int_pointer       = v2i.data();

        // clang-format off
        ASSERT_MSG(almost_equal(double_pointer[0], 1.1) &&
                   almost_equal(double_pointer[1], 2.2) &&
                   almost_equal(double_pointer[2], 3.3) &&
                   almost_equal(double_pointer[3], 4.4),
                   "Access to data of vector4d filed.");

        ASSERT_MSG(almost_equal(float_pointer[0], 5.5f) &&
                   almost_equal(float_pointer[1], 6.6f) &&
                   almost_equal(float_pointer[2], 7.7f),
                   "Access to data of vector3f failed.");

        ASSERT_MSG(int_pointer[0] == 1 && int_pointer[1] == 2, "Access to data of vector2i failed.");
        // clang-format on
    }

    void unary_minus_operator()
    {
        const Vector4D v4d(1.4);
        const Vector3F v3f(2.4f);
        const Vector2I v2i(3);

        ASSERT_MSG(-v4d == Vector4D(-1.4, -1.4, -1.4, -1.4), "Inverse of vector4d failed.");
        ASSERT_MSG(-v3f == Vector3F(-2.4f, -2.4f, -2.4f), "Inverse of vector3f failed.");
        ASSERT_MSG(-v2i == Vector2I(-3, -3), "Inverse of vector2i failed.");
    }

    void unary_plus_operator()
    {
        const Vector4D v4d(1.4);
        const Vector3F v3f(2.4f);
        const Vector2I v2i(3);

        ASSERT_MSG(+v4d == Vector4D(1.4, 1.4, 1.4, 1.4), "Unary plus of vector4d failed.");
        ASSERT_MSG(+v3f == Vector3F(2.4f, 2.4f, 2.4f), "Unary plus of vector3f failed.");
        ASSERT_MSG(+v2i == Vector2I(3, 3), "Unary plus of vector2i failed.");
    }

    void plus_operator()
    {
        const Vector4D v4d(1.0);
        const Vector3F v3f(1.0f);
        const Vector2I v2i(1);

        TEST_ASSERT(v4d + v4d == Vector4D(2.0), "Plus operator failed.");
        TEST_ASSERT(v4d + 1.0 == Vector4D(2.0), "Plus operator failed.");
        TEST_ASSERT(1.0 + v4d == Vector4D(2.0), "Plus operator failed.");

        TEST_ASSERT(v3f + v3f == Vector3F(2.0f), "Plus operator failed.");
        TEST_ASSERT(v3f + 1.0f == Vector3F(2.0f), "Plus operator failed.");
        TEST_ASSERT(1.0f + v3f == Vector3F(2.0f), "Plus operator failed.");

        TEST_ASSERT(v2i + v2i == Vector2I(2), "Plus operator failed.");
        TEST_ASSERT(v2i + 1 == Vector2I(2), "Plus operator failed.");
        TEST_ASSERT(1 + v2i == Vector2I(2), "Plus operator failed.");
    }

    void minus_operator()
    {
        const Vector4D v4d(1.0);
        const Vector3F v3f(1.0f);
        const Vector2I v2i(1);

        TEST_ASSERT(v4d - v4d == Vector4D(0.0), "Minus operator failed.");
        TEST_ASSERT(v4d - 1.0 == Vector4D(0.0), "Minus operator failed.");
        TEST_ASSERT(1.0 - v4d == Vector4D(0.0), "Minus operator failed.");

        TEST_ASSERT(v3f - v3f == Vector3F(0.0f), "Minus operator failed.");
        TEST_ASSERT(v3f - 1.0f == Vector3F(0.0f), "Minus operator failed.");
        TEST_ASSERT(1.0f - v3f == Vector3F(0.0f), "Minus operator failed.");

        TEST_ASSERT(v2i - v2i == Vector2I(0), "Minus operator failed.");
        TEST_ASSERT(v2i - 1 == Vector2I(0), "Minus operator failed.");
        TEST_ASSERT(1 - v2i == Vector2I(0), "Minus operator failed.");
    }

    void multiply_operator()
    {
        const Vector4D v4d(2.0);
        const Vector3F v3f(2.0f);
        const Vector2I v2i(2);

        TEST_ASSERT(v4d * v4d == Vector4D(4.0), "Multiply operator failed.");
        TEST_ASSERT(v4d * 2.0 == Vector4D(4.0), "Multiply operator failed.");
        TEST_ASSERT(2.0 * v4d == Vector4D(4.0), "Multiply operator failed.");

        TEST_ASSERT(v3f * v3f == Vector3F(4.0f), "Multiply operator failed.");
        TEST_ASSERT(v3f * 2.0f == Vector3F(4.0f), "Multiply operator failed.");
        TEST_ASSERT(2.0f * v3f == Vector3F(4.0f), "Multiply operator failed.");

        TEST_ASSERT(v2i * v2i == Vector2I(4), "Multiply operator failed.");
        TEST_ASSERT(v2i * 2 == Vector2I(4), "Multiply operator failed.");
        TEST_ASSERT(2 * v2i == Vector2I(4), "Multiply operator failed.");
    }

    void divide_operator()
    {
        const Vector4D v4d(2.0);
        const Vector3F v3f(2.0f);
        const Vector2I v2i(2);

        TEST_ASSERT(v4d / v4d == Vector4D(1.0), "Divide operator failed.");
        TEST_ASSERT(v4d / 2.0 == Vector4D(1.0), "Divide operator failed.");
        TEST_ASSERT(2.0 / v4d == Vector4D(1.0), "Divide operator failed.");

        TEST_ASSERT(v3f / v3f == Vector3F(1.0f), "Divide operator failed.");
        TEST_ASSERT(v3f / 2.0f == Vector3F(1.0f), "Divide operator failed.");
        TEST_ASSERT(2.0f / v3f == Vector3F(1.0f), "Divide operator failed.");

        TEST_ASSERT(v2i / v2i == Vector2I(1), "Divide operator failed.");
        TEST_ASSERT(v2i / 2 == Vector2I(1), "Divide operator failed.");
        TEST_ASSERT(2 / v2i == Vector2I(1), "Divide operator failed.");
    }
};

class bool_vector_operators_test : public test::suite
{
public:
    bool_vector_operators_test()
        : suite("bool_vector_operators_test")
    {
        add_test([this]() { assign_operator(); }, "assign_operator");
        add_test([this]() { access_operator(); }, "access_operator");
        add_test([this]() { data_access(); }, "data_access");
    }

private:
    void assign_operator()
    {
        const Vector4B v4b(true, false, true, false);
        const Vector3B v3b(true, false, true);
        const Vector2B v2b(true, false);

        const Vector4D v4d(-1.1, 0.0, 3.3, 0.0);
        const Vector3F v3f(5.5f, 0.0, -7.7f);
        const Vector2I v2i(1, 0);

        Vector4B v4b_result;
        Vector3B v3b_result;
        Vector2B v2b_result;

        v4b_result = v4b;
        v3b_result = v3b;
        v2b_result = v2b;

        ASSERT_MSG(v4b_result == v4b, "Assign to vector4b failed.");
        ASSERT_MSG(v3b_result == v3b, "Assign to vector3b failed.");
        ASSERT_MSG(v2b_result == v2b, "Assign to vector2b failed.");

        v4b_result = v4d;
        v3b_result = v3f;
        v2b_result = v2i;

        ASSERT_MSG(v4b_result == v4b, "Assign to vector4b failed.");
        ASSERT_MSG(v3b_result == v3b, "Assign to vector3b failed.");
        ASSERT_MSG(v2b_result == v2b, "Assign to vector2b failed.");
    }

    void access_operator()
    {
        const Vector4B v4b(true, false, true, false);
        const Vector3B v3b(true, false, true);
        const Vector2B v2b(true, false);

        ASSERT_MSG(v4b[0] && !v4b[1] && v4b[2] && !v4b[3], "Access to vector4b failed.");
        ASSERT_MSG(v3b[0] && !v3b[1] && v3b[2], "Access to vector3b failed.");
        ASSERT_MSG(v2b[0] && !v2b[1], "Access to vector2b failed.");
    }

    void data_access()
    {
        const Vector4B v4b(true, false, true, false);
        const Vector3B v3b(true, false, true);
        const Vector2B v2b(true, false);

        const bool* bool4 = v4b.data();
        const bool* bool3 = v3b.data();
        const bool* bool2 = v2b.data();

        ASSERT_MSG(bool4[0] && !bool4[1] && bool4[2] && !bool4[3], "Access to data of vector4b failed.");
        ASSERT_MSG(bool3[0] && !bool3[1] && bool3[2], "Access to data of vector3b failed.");
        ASSERT_MSG(bool2[0] && !bool2[1], "Access to data of vector2b failed.");
    }
};

int main()
{
    return run_tests(vector_operators_test(), bool_vector_operators_test());
}
