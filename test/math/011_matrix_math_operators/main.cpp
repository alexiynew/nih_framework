#include <math/math.hpp>
#include <unit_test/suite.hpp>

#include "unit_test/assertions.hpp"

using namespace framework::math;

class matrix_operators_test : public test::suite
{
public:
    matrix_operators_test()
        : suite("matrix_operators_test")
    {
        add_test([this]() { unary_minus_operator(); }, "unary_minus_operator");
        add_test([this]() { unary_plus_operator(); }, "unary_plus_operator");
        add_test([this]() { add_assign_operator(); }, "add_assign_operator");
        add_test([this]() { subtract_assign_operator(); }, "subtract_assign_operator");
        add_test([this]() { multiplies_assign_operator(); }, "multiplies_assign_operator");
        add_test([this]() { divides_assign_operator(); }, "divides_assign_operator");
        add_test([this]() { add_operator(); }, "add_operator");
        add_test([this]() { subtract_operator(); }, "subtract_operator");
        add_test([this]() { multiply_with_scalar_operator(); }, "multiply_with_scalar_operator");
        add_test([this]() { multiply_with_vector_operator(); }, "multiply_with_vector_operator");
        add_test([this]() { multiply_with_matrix_operator(); }, "multiply_with_matrix_operator");
        add_test([this]() { divide_operator(); }, "divide_operator");
    }

private:
    void unary_minus_operator()
    {
        TEST_ASSERT(-matrix44 == Matrix4x4F(-1), "Matrix4x4 unary subtract failed.");
        TEST_ASSERT(-matrix43 == Matrix4x3F(-1), "Matrix4x3 unary subtract failed.");
        TEST_ASSERT(-matrix42 == Matrix4x2F(-1), "Matrix4x2 unary subtract failed.");
        TEST_ASSERT(-matrix34 == Matrix3x4F(-1), "Matrix3x4 unary subtract failed.");
        TEST_ASSERT(-matrix33 == Matrix3x3F(-1), "Matrix3x3 unary subtract failed.");
        TEST_ASSERT(-matrix32 == Matrix3x2F(-1), "Matrix3x2 unary subtract failed.");
        TEST_ASSERT(-matrix24 == Matrix2x4F(-1), "Matrix2x4 unary subtract failed.");
        TEST_ASSERT(-matrix23 == Matrix2x3F(-1), "Matrix2x3 unary subtract failed.");
        TEST_ASSERT(-matrix22 == Matrix2x2F(-1), "Matrix2x2 unary subtract failed.");
    }

    void unary_plus_operator()
    {
        TEST_ASSERT(+matrix44 == Matrix4x4F(1), "Matrix4x4 unary add operator failed.");
        TEST_ASSERT(+matrix43 == Matrix4x3F(1), "Matrix4x3 unary add operator failed.");
        TEST_ASSERT(+matrix42 == Matrix4x2F(1), "Matrix4x2 unary add operator failed.");
        TEST_ASSERT(+matrix34 == Matrix3x4F(1), "Matrix3x4 unary add operator failed.");
        TEST_ASSERT(+matrix33 == Matrix3x3F(1), "Matrix3x3 unary add operator failed.");
        TEST_ASSERT(+matrix32 == Matrix3x2F(1), "Matrix3x2 unary add operator failed.");
        TEST_ASSERT(+matrix24 == Matrix2x4F(1), "Matrix2x4 unary add operator failed.");
        TEST_ASSERT(+matrix23 == Matrix2x3F(1), "Matrix2x3 unary add operator failed.");
        TEST_ASSERT(+matrix22 == Matrix2x2F(1), "Matrix2x2 unary add operator failed.");
    }

    void add_assign_operator()
    {
        Matrix4x4F temp44;
        Matrix4x3F temp43;
        Matrix4x2F temp42;
        Matrix3x4F temp34;
        Matrix3x3F temp33;
        Matrix3x2F temp32;
        Matrix2x4F temp24;
        Matrix2x3F temp23;
        Matrix2x2F temp22;

        temp44 += matrix44;
        temp43 += matrix43;
        temp42 += matrix42;
        temp34 += matrix34;
        temp33 += matrix33;
        temp32 += matrix32;
        temp24 += matrix24;
        temp23 += matrix23;
        temp22 += matrix22;

        TEST_ASSERT(temp44 == Matrix4x4F(2), "Matrix4x4 add_assign operator failed.");
        TEST_ASSERT(temp43 == Matrix4x3F(2), "Matrix4x3 add_assign operator failed.");
        TEST_ASSERT(temp42 == Matrix4x2F(2), "Matrix4x2 add_assign operator failed.");
        TEST_ASSERT(temp34 == Matrix3x4F(2), "Matrix3x4 add_assign operator failed.");
        TEST_ASSERT(temp33 == Matrix3x3F(2), "Matrix3x3 add_assign operator failed.");
        TEST_ASSERT(temp32 == Matrix3x2F(2), "Matrix3x2 add_assign operator failed.");
        TEST_ASSERT(temp24 == Matrix2x4F(2), "Matrix2x4 add_assign operator failed.");
        TEST_ASSERT(temp23 == Matrix2x3F(2), "Matrix2x3 add_assign operator failed.");
        TEST_ASSERT(temp22 == Matrix2x2F(2), "Matrix2x2 add_assign operator failed.");

        temp44 += 1;
        temp43 += 1;
        temp42 += 1;
        temp34 += 1;
        temp33 += 1;
        temp32 += 1;
        temp24 += 1;
        temp23 += 1;
        temp22 += 1;

        const Matrix4x4F result44 = {3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3};
        const Matrix4x3F result43 = {3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1};
        const Matrix4x2F result42 = {3, 1, 1, 3, 1, 1, 1, 1};
        const Matrix3x4F result34 = {3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1};
        const Matrix3x3F result33 = {3, 1, 1, 1, 3, 1, 1, 1, 3};
        const Matrix3x2F result32 = {3, 1, 1, 3, 1, 1};
        const Matrix2x4F result24 = {3, 1, 1, 1, 1, 3, 1, 1};
        const Matrix2x3F result23 = {3, 1, 1, 1, 3, 1};
        const Matrix2x2F result22 = {3, 1, 1, 3};

        TEST_ASSERT(temp44 == result44, "Matrix4x4 add_assign operator failed.");
        TEST_ASSERT(temp43 == result43, "Matrix4x3 add_assign operator failed.");
        TEST_ASSERT(temp42 == result42, "Matrix4x2 add_assign operator failed.");
        TEST_ASSERT(temp34 == result34, "Matrix3x4 add_assign operator failed.");
        TEST_ASSERT(temp33 == result33, "Matrix3x3 add_assign operator failed.");
        TEST_ASSERT(temp32 == result32, "Matrix3x2 add_assign operator failed.");
        TEST_ASSERT(temp24 == result24, "Matrix2x4 add_assign operator failed.");
        TEST_ASSERT(temp23 == result23, "Matrix2x3 add_assign operator failed.");
        TEST_ASSERT(temp22 == result22, "Matrix2x2 add_assign operator failed.");
    }

    void subtract_assign_operator()
    {
        Matrix4x4F temp44(2);
        Matrix4x3F temp43(2);
        Matrix4x2F temp42(2);
        Matrix3x4F temp34(2);
        Matrix3x3F temp33(2);
        Matrix3x2F temp32(2);
        Matrix2x4F temp24(2);
        Matrix2x3F temp23(2);
        Matrix2x2F temp22(2);

        temp44 -= matrix44;
        temp43 -= matrix43;
        temp42 -= matrix42;
        temp34 -= matrix34;
        temp33 -= matrix33;
        temp32 -= matrix32;
        temp24 -= matrix24;
        temp23 -= matrix23;
        temp22 -= matrix22;

        TEST_ASSERT(temp44 == matrix44, "Matrix4x4 subtract_assign operator failed.");
        TEST_ASSERT(temp43 == matrix43, "Matrix4x3 subtract_assign operator failed.");
        TEST_ASSERT(temp42 == matrix42, "Matrix4x2 subtract_assign operator failed.");
        TEST_ASSERT(temp34 == matrix34, "Matrix3x4 subtract_assign operator failed.");
        TEST_ASSERT(temp33 == matrix33, "Matrix3x3 subtract_assign operator failed.");
        TEST_ASSERT(temp32 == matrix32, "Matrix3x2 subtract_assign operator failed.");
        TEST_ASSERT(temp24 == matrix24, "Matrix2x4 subtract_assign operator failed.");
        TEST_ASSERT(temp23 == matrix23, "Matrix2x3 subtract_assign operator failed.");
        TEST_ASSERT(temp22 == matrix22, "Matrix2x2 subtract_assign operator failed.");

        temp44 -= 1;
        temp43 -= 1;
        temp42 -= 1;
        temp34 -= 1;
        temp33 -= 1;
        temp32 -= 1;
        temp24 -= 1;
        temp23 -= 1;
        temp22 -= 1;

        const Matrix4x4F result44 = {0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0};
        const Matrix4x3F result43 = {0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1};
        const Matrix4x2F result42 = {0, -1, -1, 0, -1, -1, -1, -1};
        const Matrix3x4F result34 = {0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0, -1};
        const Matrix3x3F result33 = {0, -1, -1, -1, 0, -1, -1, -1, 0};
        const Matrix3x2F result32 = {0, -1, -1, 0, -1, -1};
        const Matrix2x4F result24 = {0, -1, -1, -1, -1, 0, -1, -1};
        const Matrix2x3F result23 = {0, -1, -1, -1, 0, -1};
        const Matrix2x2F result22 = {0, -1, -1, 0};

        TEST_ASSERT(temp44 == result44, "Matrix4x4 subtract_assign operator failed.");
        TEST_ASSERT(temp43 == result43, "Matrix4x3 subtract_assign operator failed.");
        TEST_ASSERT(temp42 == result42, "Matrix4x2 subtract_assign operator failed.");
        TEST_ASSERT(temp34 == result34, "Matrix3x4 subtract_assign operator failed.");
        TEST_ASSERT(temp33 == result33, "Matrix3x3 subtract_assign operator failed.");
        TEST_ASSERT(temp32 == result32, "Matrix3x2 subtract_assign operator failed.");
        TEST_ASSERT(temp24 == result24, "Matrix2x4 subtract_assign operator failed.");
        TEST_ASSERT(temp23 == result23, "Matrix2x3 subtract_assign operator failed.");
        TEST_ASSERT(temp22 == result22, "Matrix2x2 subtract_assign operator failed.");
    }

    void multiplies_assign_operator()
    {
        Matrix4x4F temp44(2);
        Matrix4x3F temp43(2);
        Matrix4x2F temp42(2);
        Matrix3x4F temp34(2);
        Matrix3x3F temp33(2);
        Matrix3x2F temp32(2);
        Matrix2x4F temp24(2);
        Matrix2x3F temp23(2);
        Matrix2x2F temp22(2);

        temp44 *= Matrix4x4F(2);
        temp43 *= Matrix4x4F(2);
        temp42 *= Matrix4x4F(2);
        temp34 *= Matrix3x3F(2);
        temp33 *= Matrix3x3F(2);
        temp32 *= Matrix3x3F(2);
        temp24 *= Matrix2x2F(2);
        temp23 *= Matrix2x2F(2);
        temp22 *= Matrix2x2F(2);

        TEST_ASSERT(temp44 == Matrix4x4F(4), "Matrix4x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp43 == Matrix4x3F(4), "Matrix4x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp42 == Matrix4x2F(4), "Matrix4x2 multiplies_assign operator failed.");
        TEST_ASSERT(temp34 == Matrix3x4F(4), "Matrix3x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp33 == Matrix3x3F(4), "Matrix3x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp32 == Matrix3x2F(4), "Matrix3x2 multiplies_assign operator failed.");
        TEST_ASSERT(temp24 == Matrix2x4F(4), "Matrix2x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp23 == Matrix2x3F(4), "Matrix2x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp22 == Matrix2x2F(4), "Matrix2x2 multiplies_assign operator failed.");

        temp44 *= 10;
        temp43 *= 10;
        temp42 *= 10;
        temp34 *= 10;
        temp33 *= 10;
        temp32 *= 10;
        temp24 *= 10;
        temp23 *= 10;
        temp22 *= 10;

        TEST_ASSERT(temp44 == Matrix4x4F(40), "Matrix4x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp43 == Matrix4x3F(40), "Matrix4x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp42 == Matrix4x2F(40), "Matrix4x2 multiplies_assign operator failed.");
        TEST_ASSERT(temp34 == Matrix3x4F(40), "Matrix3x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp33 == Matrix3x3F(40), "Matrix3x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp32 == Matrix3x2F(40), "Matrix3x2 multiplies_assign operator failed.");
        TEST_ASSERT(temp24 == Matrix2x4F(40), "Matrix2x4 multiplies_assign operator failed.");
        TEST_ASSERT(temp23 == Matrix2x3F(40), "Matrix2x3 multiplies_assign operator failed.");
        TEST_ASSERT(temp22 == Matrix2x2F(40), "Matrix2x2 multiplies_assign operator failed.");
    }

    void divides_assign_operator()
    {
        Matrix4x4F temp44(20);
        Matrix4x3F temp43(20);
        Matrix4x2F temp42(20);
        Matrix3x4F temp34(20);
        Matrix3x3F temp33(20);
        Matrix3x2F temp32(20);
        Matrix2x4F temp24(20);
        Matrix2x3F temp23(20);
        Matrix2x2F temp22(20);

        temp44 /= 10;
        temp43 /= 10;
        temp42 /= 10;
        temp34 /= 10;
        temp33 /= 10;
        temp32 /= 10;
        temp24 /= 10;
        temp23 /= 10;
        temp22 /= 10;

        TEST_ASSERT(temp44 == Matrix4x4F(2), "Matrix4x4 divides_assign operator failed.");
        TEST_ASSERT(temp43 == Matrix4x3F(2), "Matrix4x3 divides_assign operator failed.");
        TEST_ASSERT(temp42 == Matrix4x2F(2), "Matrix4x2 divides_assign operator failed.");
        TEST_ASSERT(temp34 == Matrix3x4F(2), "Matrix3x4 divides_assign operator failed.");
        TEST_ASSERT(temp33 == Matrix3x3F(2), "Matrix3x3 divides_assign operator failed.");
        TEST_ASSERT(temp32 == Matrix3x2F(2), "Matrix3x2 divides_assign operator failed.");
        TEST_ASSERT(temp24 == Matrix2x4F(2), "Matrix2x4 divides_assign operator failed.");
        TEST_ASSERT(temp23 == Matrix2x3F(2), "Matrix2x3 divides_assign operator failed.");
        TEST_ASSERT(temp22 == Matrix2x2F(2), "Matrix2x2 divides_assign operator failed.");
    }

    void add_operator()
    {
        const Matrix4x4F temp44 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x3F temp43 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x2F temp42 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x4F temp34 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x3F temp33 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x2F temp32 = {1, 1, 1, 1, 1, 1};
        const Matrix2x4F temp24 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix2x3F temp23 = {1, 1, 1, 1, 1, 1};
        const Matrix2x2F temp22 = {1, 1, 1, 1};

        const Matrix4x4F result44 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x3F result43 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x2F result42 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x4F result34 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x3F result33 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x2F result32 = {2, 2, 2, 2, 2, 2};
        const Matrix2x4F result24 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix2x3F result23 = {2, 2, 2, 2, 2, 2};
        const Matrix2x2F result22 = {2, 2, 2, 2};

        TEST_ASSERT(temp44 + 1.0f == result44, "Matrix4x4 add operator failed.");
        TEST_ASSERT(temp43 + 1.0f == result43, "Matrix4x3 add operator failed.");
        TEST_ASSERT(temp42 + 1.0f == result42, "Matrix4x2 add operator failed.");
        TEST_ASSERT(temp34 + 1.0f == result34, "Matrix3x4 add operator failed.");
        TEST_ASSERT(temp33 + 1.0f == result33, "Matrix3x3 add operator failed.");
        TEST_ASSERT(temp32 + 1.0f == result32, "Matrix3x2 add operator failed.");
        TEST_ASSERT(temp24 + 1.0f == result24, "Matrix2x4 add operator failed.");
        TEST_ASSERT(temp23 + 1.0f == result23, "Matrix2x3 add operator failed.");
        TEST_ASSERT(temp22 + 1.0f == result22, "Matrix2x2 add operator failed.");

        TEST_ASSERT(1.0f + temp44 == result44, "Matrix4x4 add operator failed.");
        TEST_ASSERT(1.0f + temp43 == result43, "Matrix4x3 add operator failed.");
        TEST_ASSERT(1.0f + temp42 == result42, "Matrix4x2 add operator failed.");
        TEST_ASSERT(1.0f + temp34 == result34, "Matrix3x4 add operator failed.");
        TEST_ASSERT(1.0f + temp33 == result33, "Matrix3x3 add operator failed.");
        TEST_ASSERT(1.0f + temp32 == result32, "Matrix3x2 add operator failed.");
        TEST_ASSERT(1.0f + temp24 == result24, "Matrix2x4 add operator failed.");
        TEST_ASSERT(1.0f + temp23 == result23, "Matrix2x3 add operator failed.");
        TEST_ASSERT(1.0f + temp22 == result22, "Matrix2x2 add operator failed.");

        TEST_ASSERT(temp44 + temp44 == result44, "Matrix4x4 add operator failed.");
        TEST_ASSERT(temp43 + temp43 == result43, "Matrix4x3 add operator failed.");
        TEST_ASSERT(temp42 + temp42 == result42, "Matrix4x2 add operator failed.");
        TEST_ASSERT(temp34 + temp34 == result34, "Matrix3x4 add operator failed.");
        TEST_ASSERT(temp33 + temp33 == result33, "Matrix3x3 add operator failed.");
        TEST_ASSERT(temp32 + temp32 == result32, "Matrix3x2 add operator failed.");
        TEST_ASSERT(temp24 + temp24 == result24, "Matrix2x4 add operator failed.");
        TEST_ASSERT(temp23 + temp23 == result23, "Matrix2x3 add operator failed.");
        TEST_ASSERT(temp22 + temp22 == result22, "Matrix2x2 add operator failed.");
    }

    void subtract_operator()
    {
        const Matrix4x4F temp44 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x3F temp43 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x2F temp42 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x4F temp34 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x3F temp33 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x2F temp32 = {2, 2, 2, 2, 2, 2};
        const Matrix2x4F temp24 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix2x3F temp23 = {2, 2, 2, 2, 2, 2};
        const Matrix2x2F temp22 = {2, 2, 2, 2};

        const Matrix4x4F result44 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x3F result43 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x2F result42 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x4F result34 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x3F result33 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x2F result32 = {1, 1, 1, 1, 1, 1};
        const Matrix2x4F result24 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix2x3F result23 = {1, 1, 1, 1, 1, 1};
        const Matrix2x2F result22 = {1, 1, 1, 1};

        TEST_ASSERT(temp44 - 1.0f == result44, "Matrix4x4 subtract operator failed.");
        TEST_ASSERT(temp43 - 1.0f == result43, "Matrix4x3 subtract operator failed.");
        TEST_ASSERT(temp42 - 1.0f == result42, "Matrix4x2 subtract operator failed.");
        TEST_ASSERT(temp34 - 1.0f == result34, "Matrix3x4 subtract operator failed.");
        TEST_ASSERT(temp33 - 1.0f == result33, "Matrix3x3 subtract operator failed.");
        TEST_ASSERT(temp32 - 1.0f == result32, "Matrix3x2 subtract operator failed.");
        TEST_ASSERT(temp24 - 1.0f == result24, "Matrix2x4 subtract operator failed.");
        TEST_ASSERT(temp23 - 1.0f == result23, "Matrix2x3 subtract operator failed.");
        TEST_ASSERT(temp22 - 1.0f == result22, "Matrix2x2 subtract operator failed.");

        TEST_ASSERT(2.0f - temp44 == Matrix4x4F(0), "Matrix4x4 subtract operator failed.");
        TEST_ASSERT(2.0f - temp43 == Matrix4x3F(0), "Matrix4x3 subtract operator failed.");
        TEST_ASSERT(2.0f - temp42 == Matrix4x2F(0), "Matrix4x2 subtract operator failed.");
        TEST_ASSERT(2.0f - temp34 == Matrix3x4F(0), "Matrix3x4 subtract operator failed.");
        TEST_ASSERT(2.0f - temp33 == Matrix3x3F(0), "Matrix3x3 subtract operator failed.");
        TEST_ASSERT(2.0f - temp32 == Matrix3x2F(0), "Matrix3x2 subtract operator failed.");
        TEST_ASSERT(2.0f - temp24 == Matrix2x4F(0), "Matrix2x4 subtract operator failed.");
        TEST_ASSERT(2.0f - temp23 == Matrix2x3F(0), "Matrix2x3 subtract operator failed.");
        TEST_ASSERT(2.0f - temp22 == Matrix2x2F(0), "Matrix2x2 subtract operator failed.");

        TEST_ASSERT(temp44 - temp44 == Matrix4x4F(0), "Matrix4x4 subtract operator failed.");
        TEST_ASSERT(temp43 - temp43 == Matrix4x3F(0), "Matrix4x3 subtract operator failed.");
        TEST_ASSERT(temp42 - temp42 == Matrix4x2F(0), "Matrix4x2 subtract operator failed.");
        TEST_ASSERT(temp34 - temp34 == Matrix3x4F(0), "Matrix3x4 subtract operator failed.");
        TEST_ASSERT(temp33 - temp33 == Matrix3x3F(0), "Matrix3x3 subtract operator failed.");
        TEST_ASSERT(temp32 - temp32 == Matrix3x2F(0), "Matrix3x2 subtract operator failed.");
        TEST_ASSERT(temp24 - temp24 == Matrix2x4F(0), "Matrix2x4 subtract operator failed.");
        TEST_ASSERT(temp23 - temp23 == Matrix2x3F(0), "Matrix2x3 subtract operator failed.");
        TEST_ASSERT(temp22 - temp22 == Matrix2x2F(0), "Matrix2x2 subtract operator failed.");
    }

    void multiply_with_scalar_operator()
    {
        const Matrix4x4F temp44 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x3F temp43 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix4x2F temp42 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x4F temp34 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x3F temp33 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix3x2F temp32 = {1, 1, 1, 1, 1, 1};
        const Matrix2x4F temp24 = {1, 1, 1, 1, 1, 1, 1, 1};
        const Matrix2x3F temp23 = {1, 1, 1, 1, 1, 1};
        const Matrix2x2F temp22 = {1, 1, 1, 1};

        const Matrix4x4F result44 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x3F result43 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix4x2F result42 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x4F result34 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x3F result33 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix3x2F result32 = {2, 2, 2, 2, 2, 2};
        const Matrix2x4F result24 = {2, 2, 2, 2, 2, 2, 2, 2};
        const Matrix2x3F result23 = {2, 2, 2, 2, 2, 2};
        const Matrix2x2F result22 = {2, 2, 2, 2};

        TEST_ASSERT(temp44 * 2.0f == result44, "Matrix4x4 multiply with scalar operator failed.");
        TEST_ASSERT(temp43 * 2.0f == result43, "Matrix4x3 multiply with scalar operator failed.");
        TEST_ASSERT(temp42 * 2.0f == result42, "Matrix4x2 multiply with scalar operator failed.");
        TEST_ASSERT(temp34 * 2.0f == result34, "Matrix3x4 multiply with scalar operator failed.");
        TEST_ASSERT(temp33 * 2.0f == result33, "Matrix3x3 multiply with scalar operator failed.");
        TEST_ASSERT(temp32 * 2.0f == result32, "Matrix3x2 multiply with scalar operator failed.");
        TEST_ASSERT(temp24 * 2.0f == result24, "Matrix2x4 multiply with scalar operator failed.");
        TEST_ASSERT(temp23 * 2.0f == result23, "Matrix2x3 multiply with scalar operator failed.");
        TEST_ASSERT(temp22 * 2.0f == result22, "Matrix2x2 multiply with scalar operator failed.");

        TEST_ASSERT(2.0f * temp44 == result44, "Matrix4x4 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp43 == result43, "Matrix4x3 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp42 == result42, "Matrix4x2 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp34 == result34, "Matrix3x4 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp33 == result33, "Matrix3x3 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp32 == result32, "Matrix3x2 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp24 == result24, "Matrix2x4 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp23 == result23, "Matrix2x3 multiply with scalar operator failed.");
        TEST_ASSERT(2.0f * temp22 == result22, "Matrix2x2 multiply with scalar operator failed.");
    }

    void multiply_with_vector_operator()
    {
        // clang-format off
        Matrix4x4F temp44 = {
            1, 2, 3, 4,
            1, 2, 3, 4,
            1, 2, 3, 4,
            1, 2, 3, 4
        };
        // clang-format on

        Matrix4x3F temp43(temp44);
        Matrix4x2F temp42(temp44);
        Matrix3x4F temp34(temp44);
        Matrix3x3F temp33(temp44);
        Matrix3x2F temp32(temp44);
        Matrix2x4F temp24(temp44);
        Matrix2x3F temp23(temp44);
        Matrix2x2F temp22(temp44);

        Vector4F vector4(1, 2, 3, 4);
        Vector3F vector3(1, 2, 3);
        Vector2F vector2(1, 2);

        TEST_ASSERT(vector4 * temp44 == Vector4F(30, 30, 30, 30), "Matrix4x4 multiply with vector operator failed.");
        TEST_ASSERT(vector3 * temp43 == Vector4F(14, 14, 14, 14), "Matrix4x3 multiply with vector operator failed.");
        TEST_ASSERT(vector2 * temp42 == Vector4F(5, 5, 5, 5), "Matrix4x2 multiply with vector operator failed.");

        TEST_ASSERT(vector4 * temp34 == Vector3F(30, 30, 30), "Matrix3x4 multiply with vector operator failed.");
        TEST_ASSERT(vector3 * temp33 == Vector3F(14, 14, 14), "Matrix3x3 multiply with vector operator failed.");
        TEST_ASSERT(vector2 * temp32 == Vector3F(5, 5, 5), "Matrix3x2 multiply with vector operator failed.");

        TEST_ASSERT(vector4 * temp24 == Vector2F(30, 30), "Matrix2x4 multiply with vector operator failed.");
        TEST_ASSERT(vector3 * temp23 == Vector2F(14, 14), "Matrix2x3 multiply with vector operator failed.");
        TEST_ASSERT(vector2 * temp22 == Vector2F(5, 5), "Matrix2x2 multiply with vector operator failed.");

        TEST_ASSERT(temp44 * vector4 == Vector4F(10, 20, 30, 40), "Matrix4x4 multiply with vector operator failed.");
        TEST_ASSERT(temp43 * vector4 == Vector3F(10, 20, 30), "Matrix4x3 multiply with vector operator failed.");
        TEST_ASSERT(temp42 * vector4 == Vector2F(10, 20), "Matrix4x2 multiply with vector operator failed.");

        TEST_ASSERT(temp34 * vector3 == Vector4F(6, 12, 18, 24), "Matrix3x4 multiply with vector operator failed.");
        TEST_ASSERT(temp33 * vector3 == Vector3F(6, 12, 18), "Matrix3x3 multiply with vector operator failed.");
        TEST_ASSERT(temp32 * vector3 == Vector2F(6, 12), "Matrix3x2 multiply with vector operator failed.");

        TEST_ASSERT(temp24 * vector2 == Vector4F(3, 6, 9, 12), "Matrix2x4 multiply with vector operator failed.");
        TEST_ASSERT(temp23 * vector2 == Vector3F(3, 6, 9), "Matrix2x3 multiply with vector operator failed.");
        TEST_ASSERT(temp22 * vector2 == Vector2F(3, 6), "Matrix2x2 multiply with vector operator failed.");
    }

    void multiply_with_matrix_operator()
    {
        const Matrix4x4F temp44 = {1, 2, 3, 4, 4, 1, 2, 3, 3, 4, 1, 2, 2, 3, 4, 1};
        const Matrix4x3F temp43 = {1, 2, 3, 3, 1, 2, 2, 3, 1, 1, 2, 3};
        const Matrix4x2F temp42 = {1, 2, 2, 1, 1, 2, 2, 1};
        const Matrix3x4F temp34 = {1, 2, 3, 4, 4, 1, 2, 3, 3, 4, 1, 2};
        const Matrix3x3F temp33 = {1, 2, 3, 3, 1, 2, 2, 3, 1};
        const Matrix3x2F temp32 = {1, 2, 2, 1, 1, 2};
        const Matrix2x4F temp24 = {1, 2, 3, 4, 4, 1, 2, 3};
        const Matrix2x3F temp23 = {1, 2, 3, 3, 1, 2};
        const Matrix2x2F temp22 = {1, 2, 2, 1};

        const Matrix4x4F result44x44 = {26, 28, 26, 20, 20, 26, 28, 26, 26, 20, 26, 28, 28, 26, 20, 26};
        const Matrix3x4F result44x34 = {26, 28, 26, 20, 20, 26, 28, 26, 26, 20, 26, 28};
        const Matrix2x4F result44x24 = {26, 28, 26, 20, 20, 26, 28, 26};

        const Matrix4x3F result43x44 = {17, 21, 22, 14, 21, 25, 19, 17, 24, 20, 21, 19};
        const Matrix3x3F result43x34 = {17, 21, 22, 14, 21, 25, 19, 17, 24};
        const Matrix2x3F result43x24 = {17, 21, 22, 14, 21, 25};

        const Matrix4x2F result42x44 = {16, 14, 14, 16, 16, 14, 14, 16};
        const Matrix3x2F result42x34 = {16, 14, 14, 16, 16, 14};
        const Matrix2x2F result42x24 = {16, 14, 14, 16};

        const Matrix4x4F result34x43 = {18, 16, 10, 16, 13, 15, 13, 19, 17, 11, 13, 19, 18, 16, 10, 16};
        const Matrix3x4F result34x33 = {18, 16, 10, 16, 13, 15, 13, 19, 17, 11, 13, 19};
        const Matrix2x4F result34x23 = {18, 16, 10, 16, 13, 15, 13, 19};

        const Matrix4x3F result33x43 = {13, 13, 10, 10, 13, 13, 13, 10, 13, 13, 13, 10};
        const Matrix3x3F result33x33 = {13, 13, 10, 10, 13, 13, 13, 10, 13};
        const Matrix2x3F result33x23 = {13, 13, 10, 10, 13, 13};

        const Matrix4x2F result32x43 = {8, 10, 7, 11, 9, 9, 8, 10};
        const Matrix3x2F result32x33 = {8, 10, 7, 11, 9, 9};
        const Matrix2x2F result32x23 = {8, 10, 7, 11};

        const Matrix4x4F result24x42 = {9, 4, 7, 10, 6, 5, 8, 11, 9, 4, 7, 10, 6, 5, 8, 11};
        const Matrix3x4F result24x32 = {9, 4, 7, 10, 6, 5, 8, 11, 9, 4, 7, 10};
        const Matrix2x4F result24x22 = {9, 4, 7, 10, 6, 5, 8, 11};

        const Matrix4x3F result23x42 = {7, 4, 7, 5, 5, 8, 7, 4, 7, 5, 5, 8};
        const Matrix3x3F result23x32 = {7, 4, 7, 5, 5, 8, 7, 4, 7};
        const Matrix2x3F result23x22 = {7, 4, 7, 5, 5, 8};

        const Matrix4x2F result22x42 = {5, 4, 4, 5, 5, 4, 4, 5};
        const Matrix3x2F result22x32 = {5, 4, 4, 5, 5, 4};
        const Matrix2x2F result22x22 = {5, 4, 4, 5};

        TEST_ASSERT(temp44 * temp44 == result44x44, "Matrix4x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp44 * temp34 == result44x34, "Matrix4x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp44 * temp24 == result44x24, "Matrix4x4 multiply with matrix operator failed.");

        TEST_ASSERT(temp43 * temp44 == result43x44, "Matrix4x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp43 * temp34 == result43x34, "Matrix4x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp43 * temp24 == result43x24, "Matrix4x3 multiply with matrix operator failed.");

        TEST_ASSERT(temp42 * temp44 == result42x44, "Matrix4x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp42 * temp34 == result42x34, "Matrix4x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp42 * temp24 == result42x24, "Matrix4x2 multiply with matrix operator failed.");

        TEST_ASSERT(temp34 * temp43 == result34x43, "Matrix3x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp34 * temp33 == result34x33, "Matrix3x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp34 * temp23 == result34x23, "Matrix3x4 multiply with matrix operator failed.");

        TEST_ASSERT(temp33 * temp43 == result33x43, "Matrix3x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp33 * temp33 == result33x33, "Matrix3x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp33 * temp23 == result33x23, "Matrix3x3 multiply with matrix operator failed.");

        TEST_ASSERT(temp32 * temp43 == result32x43, "Matrix3x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp32 * temp33 == result32x33, "Matrix3x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp32 * temp23 == result32x23, "Matrix3x2 multiply with matrix operator failed.");

        TEST_ASSERT(temp24 * temp42 == result24x42, "Matrix2x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp24 * temp32 == result24x32, "Matrix2x4 multiply with matrix operator failed.");
        TEST_ASSERT(temp24 * temp22 == result24x22, "Matrix2x4 multiply with matrix operator failed.");

        TEST_ASSERT(temp23 * temp42 == result23x42, "Matrix2x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp23 * temp32 == result23x32, "Matrix2x3 multiply with matrix operator failed.");
        TEST_ASSERT(temp23 * temp22 == result23x22, "Matrix2x3 multiply with matrix operator failed.");

        TEST_ASSERT(temp22 * temp42 == result22x42, "Matrix2x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp22 * temp32 == result22x32, "Matrix2x2 multiply with matrix operator failed.");
        TEST_ASSERT(temp22 * temp22 == result22x22, "Matrix2x2 multiply with matrix operator failed.");
    }

    void divide_operator()
    {
        const Matrix4x4F temp44 = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix4x3F temp43 = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix4x2F temp42 = {10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix3x4F temp34 = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix3x3F temp33 = {10, 10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix3x2F temp32 = {10, 10, 10, 10, 10, 10};
        const Matrix2x4F temp24 = {10, 10, 10, 10, 10, 10, 10, 10};
        const Matrix2x3F temp23 = {10, 10, 10, 10, 10, 10};
        const Matrix2x2F temp22 = {10, 10, 10, 10};

        const Matrix4x4F result44 = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix4x3F result43 = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix4x2F result42 = {5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix3x4F result34 = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix3x3F result33 = {5, 5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix3x2F result32 = {5, 5, 5, 5, 5, 5};
        const Matrix2x4F result24 = {5, 5, 5, 5, 5, 5, 5, 5};
        const Matrix2x3F result23 = {5, 5, 5, 5, 5, 5};
        const Matrix2x2F result22 = {5, 5, 5, 5};

        TEST_ASSERT(temp44 / 2.0f == result44, "Matrix4x4 divide operator failed.");
        TEST_ASSERT(temp43 / 2.0f == result43, "Matrix4x3 divide operator failed.");
        TEST_ASSERT(temp42 / 2.0f == result42, "Matrix4x2 divide operator failed.");
        TEST_ASSERT(temp34 / 2.0f == result34, "Matrix3x4 divide operator failed.");
        TEST_ASSERT(temp33 / 2.0f == result33, "Matrix3x3 divide operator failed.");
        TEST_ASSERT(temp32 / 2.0f == result32, "Matrix3x2 divide operator failed.");
        TEST_ASSERT(temp24 / 2.0f == result24, "Matrix2x4 divide operator failed.");
        TEST_ASSERT(temp23 / 2.0f == result23, "Matrix2x3 divide operator failed.");
        TEST_ASSERT(temp22 / 2.0f == result22, "Matrix2x2 divide operator failed.");

        TEST_ASSERT(50.0f / temp44 == result44, "Matrix4x4 divide operator failed.");
        TEST_ASSERT(50.0f / temp43 == result43, "Matrix4x3 divide operator failed.");
        TEST_ASSERT(50.0f / temp42 == result42, "Matrix4x2 divide operator failed.");
        TEST_ASSERT(50.0f / temp34 == result34, "Matrix3x4 divide operator failed.");
        TEST_ASSERT(50.0f / temp33 == result33, "Matrix3x3 divide operator failed.");
        TEST_ASSERT(50.0f / temp32 == result32, "Matrix3x2 divide operator failed.");
        TEST_ASSERT(50.0f / temp24 == result24, "Matrix2x4 divide operator failed.");
        TEST_ASSERT(50.0f / temp23 == result23, "Matrix2x3 divide operator failed.");
        TEST_ASSERT(50.0f / temp22 == result22, "Matrix2x2 divide operator failed.");
    }

    const Matrix4x4F matrix44;
    const Matrix4x3F matrix43;
    const Matrix4x2F matrix42;
    const Matrix3x4F matrix34;
    const Matrix3x3F matrix33;
    const Matrix3x2F matrix32;
    const Matrix2x4F matrix24;
    const Matrix2x3F matrix23;
    const Matrix2x2F matrix22;
};


int main()
{
    return run_tests(matrix_operators_test());
}