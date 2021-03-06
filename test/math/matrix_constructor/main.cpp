
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

#include <math/math.hpp>
#include <unit_test/suite.hpp>

using ::framework::math::matrix2x2f;
using ::framework::math::matrix2x3f;
using ::framework::math::matrix2x4f;
using ::framework::math::matrix3x2f;
using ::framework::math::matrix3x3f;
using ::framework::math::matrix3x4f;
using ::framework::math::matrix4x2f;
using ::framework::math::matrix4x3f;
using ::framework::math::matrix4x4f;

using ::framework::math::matrix2f;
using ::framework::math::matrix3f;
using ::framework::math::matrix4f;

using ::framework::math::vector2d;
using ::framework::math::vector2f;
using ::framework::math::vector2i;
using ::framework::math::vector3d;
using ::framework::math::vector3f;
using ::framework::math::vector3i;
using ::framework::math::vector4d;
using ::framework::math::vector4f;
using ::framework::math::vector4i;

using ::framework::float32;

class matrix_test : public framework::unit_test::suite
{
public:
    matrix_test() : suite("matrix_test")
    {
        add_test([this]() { size_check(); }, "size_check");
        add_test([this]() { default_constructor(); }, "default_constructor");
        add_test([this]() { copy_constructor(); }, "copy_constructor");
        add_test([this]() { one_argument_constructor(); }, "one_argument_constructor");
        add_test([this]() { const_pointer_constructor(); }, "const_pointer_constructor");
        add_test([this]() { pointer_constructor(); }, "pointer_constructor");
        add_test([this]() { matrix4x4_constructors(); }, "matrix4x4_constructors");
        add_test([this]() { matrix4x3_constructors(); }, "matrix4x3_constructors");
        add_test([this]() { matrix4x2_constructors(); }, "matrix4x2_constructors");
        add_test([this]() { matrix3x4_constructors(); }, "matrix3x4_constructors");
        add_test([this]() { matrix3x3_constructors(); }, "matrix3x3_constructors");
        add_test([this]() { matrix3x2_constructors(); }, "matrix3x2_constructors");
        add_test([this]() { matrix2x4_constructors(); }, "matrix2x4_constructors");
        add_test([this]() { matrix2x3_constructors(); }, "matrix2x3_constructors");
        add_test([this]() { matrix2x2_constructors(); }, "matrix2x2_constructors");
    }

private:
    void size_check()
    {
        constexpr matrix2x2f matrix22;
        constexpr matrix2x3f matrix23;
        constexpr matrix2x4f matrix24;

        constexpr matrix3x2f matrix32;
        constexpr matrix3x3f matrix33;
        constexpr matrix3x4f matrix34;

        constexpr matrix4x2f matrix42;
        constexpr matrix4x3f matrix43;
        constexpr matrix4x4f matrix44;

        static_assert(sizeof(matrix22) == sizeof(float32) * 2 * 2 && matrix22.size() == 2,
                      "Matrix2x2 size check failed.");
        static_assert(sizeof(matrix23) == sizeof(float32) * 2 * 3 && matrix23.size() == 2,
                      "Matrix2x3 size check failed.");
        static_assert(sizeof(matrix24) == sizeof(float32) * 2 * 4 && matrix24.size() == 2,
                      "Matrix2x4 size check failed.");
        static_assert(sizeof(matrix32) == sizeof(float32) * 3 * 2 && matrix32.size() == 3,
                      "Matrix3x2 size check failed.");
        static_assert(sizeof(matrix33) == sizeof(float32) * 3 * 3 && matrix33.size() == 3,
                      "Matrix3x3 size check failed.");
        static_assert(sizeof(matrix34) == sizeof(float32) * 3 * 4 && matrix34.size() == 3,
                      "Matrix3x4 size check failed.");
        static_assert(sizeof(matrix42) == sizeof(float32) * 4 * 2 && matrix42.size() == 4,
                      "Matrix4x2 size check failed.");
        static_assert(sizeof(matrix43) == sizeof(float32) * 4 * 3 && matrix43.size() == 4,
                      "Matrix4x3 size check failed.");
        static_assert(sizeof(matrix44) == sizeof(float32) * 4 * 4 && matrix44.size() == 4,
                      "Matrix4x4 size check failed.");
    }

    void default_constructor()
    {
        constexpr matrix2x2f matrix22;
        constexpr matrix2x3f matrix23;
        constexpr matrix2x4f matrix24;

        constexpr matrix3x2f matrix32;
        constexpr matrix3x3f matrix33;
        constexpr matrix3x4f matrix34;

        constexpr matrix4x2f matrix42;
        constexpr matrix4x3f matrix43;
        constexpr matrix4x4f matrix44;

        // clang-format off
        TEST_ASSERT(matrix22 == matrix2x2f(
            1, 0,
            0, 1
        ), "Matrix2x2 default constructor failed.");

        TEST_ASSERT(matrix23 == matrix2x3f(
            1, 0, 0,
            0, 1, 0
        ), "Matrix2x3 default constructor failed.");

        TEST_ASSERT(matrix24 == matrix2x4f(
            1, 0, 0, 0,
            0, 1, 0, 0
        ), "Matrix2x4 default constructor failed.");

        TEST_ASSERT(matrix32 == matrix3x2f(
            1, 0,
            0, 1,
            0, 0
        ), "Matrix3x2 default constructor failed.");

        TEST_ASSERT(matrix33 == matrix3x3f(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        ), "Matrix3x3 default constructor failed.");

        TEST_ASSERT(matrix34 == matrix3x4f(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0
        ), "Matrix3x4 default constructor failed.");

        TEST_ASSERT(matrix42 == matrix4x2f(
            1, 0,
            0, 1,
            0, 0,
            0, 0
        ), "Matrix4x2 default constructor failed.");

        TEST_ASSERT(matrix43 == matrix4x3f(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1,
            0, 0, 0
        ), "Matrix4x3 default constructor failed.");

        TEST_ASSERT(matrix44 == matrix4x4f(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ), "Matrix4x4 default constructor failed.");
        // clang-format on
    }

    void copy_constructor()
    {
        constexpr matrix2x2f matrix22;
        constexpr matrix2x3f matrix23;
        constexpr matrix2x4f matrix24;

        constexpr matrix3x2f matrix32;
        constexpr matrix3x3f matrix33;
        constexpr matrix3x4f matrix34;

        constexpr matrix4x2f matrix42;
        constexpr matrix4x3f matrix43;
        constexpr matrix4x4f matrix44;

        constexpr matrix2x2f matrix22_2 = matrix22;
        constexpr matrix2x3f matrix23_2 = matrix23;
        constexpr matrix2x4f matrix24_2 = matrix24;

        constexpr matrix3x2f matrix32_2 = matrix32;
        constexpr matrix3x3f matrix33_2 = matrix33;
        constexpr matrix3x4f matrix34_2 = matrix34;

        constexpr matrix4x2f matrix42_2 = matrix42;
        constexpr matrix4x3f matrix43_2 = matrix43;
        constexpr matrix4x4f matrix44_2 = matrix44;

        TEST_ASSERT(matrix22 == matrix22_2, "Matrix2x2 copy constructor failed.");
        TEST_ASSERT(matrix23 == matrix23_2, "Matrix2x3 copy constructor failed.");
        TEST_ASSERT(matrix24 == matrix24_2, "Matrix2x4 copy constructor failed.");

        TEST_ASSERT(matrix32 == matrix32_2, "Matrix3x2 copy constructor failed.");
        TEST_ASSERT(matrix33 == matrix33_2, "Matrix3x3 copy constructor failed.");
        TEST_ASSERT(matrix34 == matrix34_2, "Matrix3x4 copy constructor failed.");

        TEST_ASSERT(matrix42 == matrix42_2, "Matrix4x2 copy constructor failed.");
        TEST_ASSERT(matrix43 == matrix43_2, "Matrix4x3 copy constructor failed.");
        TEST_ASSERT(matrix44 == matrix44_2, "Matrix4x4 copy constructor failed.");
    }

    void one_argument_constructor()
    {
        constexpr matrix2x2f matrix22;
        constexpr matrix2x3f matrix23;
        constexpr matrix2x4f matrix24;

        constexpr matrix3x2f matrix32;
        constexpr matrix3x3f matrix33;
        constexpr matrix3x4f matrix34;

        constexpr matrix4x2f matrix42;
        constexpr matrix4x3f matrix43;
        constexpr matrix4x4f matrix44;

        TEST_ASSERT(matrix22 == matrix2x2f(1), "Matrix2x2 one argument constructor failed.");
        TEST_ASSERT(matrix23 == matrix2x3f(1), "Matrix2x3 one argument constructor failed.");
        TEST_ASSERT(matrix24 == matrix2x4f(1), "Matrix2x4 one argument constructor failed.");

        TEST_ASSERT(matrix32 == matrix3x2f(1), "Matrix3x2 one argument constructor failed.");
        TEST_ASSERT(matrix33 == matrix3x3f(1), "Matrix3x3 one argument constructor failed.");
        TEST_ASSERT(matrix34 == matrix3x4f(1), "Matrix3x4 one argument constructor failed.");

        TEST_ASSERT(matrix42 == matrix4x2f(1), "Matrix4x2 one argument constructor failed.");
        TEST_ASSERT(matrix43 == matrix4x3f(1), "Matrix4x3 one argument constructor failed.");
        TEST_ASSERT(matrix44 == matrix4x4f(1), "Matrix4x4 one argument constructor failed.");
    }

    void const_pointer_constructor()
    {
        const float32 data4[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
        const float32 data3[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};
        const float32 data2[] = {0, 1, 0, 1, 0, 1, 0, 1};

        const matrix4x4f m44(data4);
        const matrix3x4f m34(data4);
        const matrix2x4f m24(data4);

        const matrix4x3f m43(data3);
        const matrix3x3f m33(data3);
        const matrix2x3f m23(data3);

        const matrix4x2f m42(data2);
        const matrix3x2f m32(data2);
        const matrix2x2f m22(data2);

        const vector4f tmp4f = {0, 1, 2, 3};
        const vector3f tmp3f = {0, 1, 2};
        const vector2f tmp2f = {0, 1};

        TEST_ASSERT(m44 == matrix4x4f(tmp4f, tmp4f, tmp4f, tmp4f), "Matrix4x4 from pointer constructor failed.");
        TEST_ASSERT(m34 == matrix3x4f(tmp4f, tmp4f, tmp4f), "Matrix3x4 from pointer constructor failed.");
        TEST_ASSERT(m24 == matrix2x4f(tmp4f, tmp4f), "Matrix2x4 from pointer constructor failed.");

        TEST_ASSERT(m43 == matrix4x3f(tmp3f, tmp3f, tmp3f, tmp3f), "Matrix4x3 from pointer constructor failed.");
        TEST_ASSERT(m33 == matrix3x3f(tmp3f, tmp3f, tmp3f), "Matrix3x3 from pointer constructor failed.");
        TEST_ASSERT(m23 == matrix2x3f(tmp3f, tmp3f), "Matrix2x3 from pointer constructor failed.");

        TEST_ASSERT(m42 == matrix4x2f(tmp2f, tmp2f, tmp2f, tmp2f), "Matrix4x3 from pointer constructor.");
        TEST_ASSERT(m32 == matrix3x2f(tmp2f, tmp2f, tmp2f), "Matrix3x3 from pointer constructor.");
        TEST_ASSERT(m22 == matrix2x2f(tmp2f, tmp2f), "Matrix2x3 from pointer constructor.");
    }

    void pointer_constructor()
    {
        float32 data4[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
        float32 data3[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};
        float32 data2[] = {0, 1, 0, 1, 0, 1, 0, 1};

        const matrix4x4f m44(data4);
        const matrix3x4f m34(data4);
        const matrix2x4f m24(data4);

        const matrix4x3f m43(data3);
        const matrix3x3f m33(data3);
        const matrix2x3f m23(data3);

        const matrix4x2f m42(data2);
        const matrix3x2f m32(data2);
        const matrix2x2f m22(data2);

        const vector4f tmp4f = {0, 1, 2, 3};
        const vector3f tmp3f = {0, 1, 2};
        const vector2f tmp2f = {0, 1};

        TEST_ASSERT(m44 == matrix4x4f(tmp4f, tmp4f, tmp4f, tmp4f), "Matrix4x4 from pointer constructor failed.");
        TEST_ASSERT(m34 == matrix3x4f(tmp4f, tmp4f, tmp4f), "Matrix3x4 from pointer constructor failed.");
        TEST_ASSERT(m24 == matrix2x4f(tmp4f, tmp4f), "Matrix2x4 from pointer constructor failed.");

        TEST_ASSERT(m43 == matrix4x3f(tmp3f, tmp3f, tmp3f, tmp3f), "Matrix4x3 from pointer constructor failed.");
        TEST_ASSERT(m33 == matrix3x3f(tmp3f, tmp3f, tmp3f), "Matrix3x3 from pointer constructor failed.");
        TEST_ASSERT(m23 == matrix2x3f(tmp3f, tmp3f), "Matrix2x3 from pointer constructor failed.");

        TEST_ASSERT(m42 == matrix4x2f(tmp2f, tmp2f, tmp2f, tmp2f), "Matrix4x3 from pointer constructor.");
        TEST_ASSERT(m32 == matrix3x2f(tmp2f, tmp2f, tmp2f), "Matrix3x3 from pointer constructor.");
        TEST_ASSERT(m22 == matrix2x2f(tmp2f, tmp2f), "Matrix2x3 from pointer constructor.");
    }

    void matrix4x4_constructors()
    {
        // clang-format off
        const matrix4x4f m1 = {
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f
        };

        const matrix4x4f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4),
            vector4f(1, 2, 3, 4)
        };

        const matrix4x4f m3 = {
            vector3f(1, 2, 3), 4,
            vector3d(1, 2, 3), 4,
            vector3i(1, 2, 3), 4,
            vector3f(1, 2, 3), 4
        };

        const matrix4x4f m4 = {
            1, vector3f(2, 3, 4),
            1, vector3d(2, 3, 4),
            1, vector3i(2, 3, 4),
            1, vector3f(2, 3, 4)
        };

        const matrix4x4f m5 = {
            vector2f(1, 2), vector2f(3, 4),
            vector2d(1, 2), vector2d(3, 4),
            vector2i(1, 2), vector2i(3, 4),
            vector2f(1, 2), vector2f(3, 4)
        };

        const matrix4x4f m6 = {
            vector2f(1, 2), 3, 4,
            vector2d(1, 2), 3, 4,
            vector2i(1, 2), 3, 4,
            vector2f(1, 2), 3, 4
        };

        const matrix4x4f m7 = {
            1, vector2f(2, 3), 4,
            1, vector2d(2, 3), 4,
            1, vector2i(2, 3), 4,
            1, vector2f(2, 3), 4
        };

        const matrix4x4f m8 = {
            1, 2, vector2f(3, 4),
            1, 2, vector2d(3, 4),
            1, 2, vector2i(3, 4),
            1, 2, vector2f(3, 4)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m6, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m7, "Matrix4x4f constructor failed.");
        TEST_ASSERT(m1 == m8, "Matrix4x4f constructor failed.");
    }

    void matrix4x3_constructors()
    {
        // clang-format off
        const matrix4x3f m1 = {
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f
        };

        const matrix4x3f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4),
            vector4f(1, 2, 3, 4)
        };

        const matrix4x3f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3),
            vector3i(1, 2, 3),
            vector3f(1, 2, 3)
        };

        const matrix4x3f m4 = {
            vector2f(1, 2), 3,
            vector2d(1, 2), 3,
            vector2i(1, 2), 3,
            vector2f(1, 2), 3
        };

        const matrix4x3f m5 = {
            1, vector2f(2, 3),
            1, vector2d(2, 3),
            1, vector2i(2, 3),
            1, vector2f(2, 3)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix4x3f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix4x3f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix4x3f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix4x3f constructor failed.");
    }

    void matrix4x2_constructors()
    {
        // clang-format off
        const matrix4x2f m1 = {
            1.0f, 2.0f,
            1.0f, 2.0f,
            1.0f, 2.0f,
            1.0f, 2.0f
        };

        const matrix4x2f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4),
            vector4f(1, 2, 3, 4)
        };

        const matrix4x2f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3),
            vector3i(1, 2, 3),
            vector3f(1, 2, 3)
        };

        const matrix4x2f m4 = {
            vector2f(1, 2),
            vector2d(1, 2),
            vector2i(1, 2),
            vector2f(1, 2)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix4x2f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix4x2f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix4x2f constructor failed.");
    }

    void matrix3x4_constructors()
    {
        // clang-format off
        const matrix3x4f m1 = {
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f
        };

        const matrix3x4f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4)
        };

        const matrix3x4f m3 = {
            vector3f(1, 2, 3), 4,
            vector3d(1, 2, 3), 4,
            vector3i(1, 2, 3), 4
        };

        const matrix3x4f m4 = {
            1, vector3f(2, 3, 4),
            1, vector3d(2, 3, 4),
            1, vector3i(2, 3, 4)
        };

        const matrix3x4f m5 = {
            vector2f(1, 2), vector2f(3, 4),
            vector2d(1, 2), vector2d(3, 4),
            vector2i(1, 2), vector2i(3, 4)
        };

        const matrix3x4f m6 = {
            vector2f(1, 2), 3, 4,
            vector2d(1, 2), 3, 4,
            vector2i(1, 2), 3, 4
        };

        const matrix3x4f m7 = {
            1, vector2f(2, 3), 4,
            1, vector2d(2, 3), 4,
            1, vector2i(2, 3), 4
        };

        const matrix3x4f m8 = {
            1, 2, vector2f(3, 4),
            1, 2, vector2d(3, 4),
            1, 2, vector2i(3, 4)\
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m6, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m7, "Matrix3x4f constructor failed.");
        TEST_ASSERT(m1 == m8, "Matrix3x4f constructor failed.");
    }

    void matrix3x3_constructors()
    {
        // clang-format off
        const matrix3x3f m1 = {
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f
        };

        const matrix3x3f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4)
        };

        const matrix3x3f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3),
            vector3i(1, 2, 3)
        };

        const matrix3x3f m4 = {
            vector2f(1, 2), 3,
            vector2d(1, 2), 3,
            vector2i(1, 2), 3
        };

        const matrix3x3f m5 = {
            1, vector2f(2, 3),
            1, vector2d(2, 3),
            1, vector2i(2, 3)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix3x3f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix3x3f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix3x3f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix3x3f constructor failed.");
    }

    void matrix3x2_constructors()
    {
        // clang-format off
        const matrix3x2f m1 = {
            1.0f, 2.0f,
            1.0f, 2.0f,
            1.0f, 2.0f
        };

        const matrix3x2f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4),
            vector4i(1, 2, 3, 4)
        };

        const matrix3x2f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3),
            vector3i(1, 2, 3)
        };

        const matrix3x2f m4 = {
            vector2f(1, 2),
            vector2d(1, 2),
            vector2i(1, 2)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix3x2f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix3x2f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix3x2f constructor failed.");
    }

    void matrix2x4_constructors()
    {
        // clang-format off
        const matrix2x4f m1 = {
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f
        };

        const matrix2x4f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4)
        };

        const matrix2x4f m3 = {
            vector3f(1, 2, 3), 4,
            vector3d(1, 2, 3), 4
        };

        const matrix2x4f m4 = {
            1, vector3f(2, 3, 4),
            1, vector3d(2, 3, 4)
        };

        const matrix2x4f m5 = {
            vector2f(1, 2), vector2f(3, 4),
            vector2d(1, 2), vector2d(3, 4)
        };

        const matrix2x4f m6 = {
            vector2f(1, 2), 3, 4,
            vector2d(1, 2), 3, 4
        };

        const matrix2x4f m7 = {
            1, vector2f(2, 3), 4,
            1, vector2d(2, 3), 4
        };

        const matrix2x4f m8 = {
            1, 2, vector2f(3, 4),
            1, 2, vector2d(3, 4)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m6, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m7, "Matrix2x4f constructor failed.");
        TEST_ASSERT(m1 == m8, "Matrix2x4f constructor failed.");
    }

    void matrix2x3_constructors()
    {
        // clang-format off
        const matrix2x3f m1 = {
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f
        };

        const matrix2x3f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4)
        };

        const matrix2x3f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3)
        };

        const matrix2x3f m4 = {
            vector2f(1, 2), 3,
            vector2d(1, 2), 3
        };

        const matrix2x3f m5 = {
            1, vector2f(2, 3),
            1, vector2d(2, 3)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix2x3f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix2x3f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix2x3f constructor failed.");
        TEST_ASSERT(m1 == m5, "Matrix2x3f constructor failed.");
    }

    void matrix2x2_constructors()
    {
        // clang-format off
        const matrix2x2f m1 = {
            1.0f, 2.0f,
            1.0f, 2.0f
        };

        const matrix2x2f m2 = {
            vector4f(1, 2, 3, 4),
            vector4d(1, 2, 3, 4)
        };

        const matrix2x2f m3 = {
            vector3f(1, 2, 3),
            vector3d(1, 2, 3)
        };

        const matrix2x2f m4 = {
            vector2f(1, 2),
            vector2d(1, 2)
        };
        // clang-format on

        TEST_ASSERT(m1 == m2, "Matrix2x2f constructor failed.");
        TEST_ASSERT(m1 == m3, "Matrix2x2f constructor failed.");
        TEST_ASSERT(m1 == m4, "Matrix2x2f constructor failed.");
    }
};

class matrix_from_matrix_test : public framework::unit_test::suite
{
public:
    matrix_from_matrix_test() : suite("matrix_from_matrix_test")
    {
        add_test([this]() { matrix4x4_constructors(); }, "matrix4x4_constructors");
        add_test([this]() { matrix4x3_constructors(); }, "matrix4x3_constructors");
        add_test([this]() { matrix4x2_constructors(); }, "matrix4x2_constructors");
        add_test([this]() { matrix3x4_constructors(); }, "matrix3x4_constructors");
        add_test([this]() { matrix3x3_constructors(); }, "matrix3x3_constructors");
        add_test([this]() { matrix3x2_constructors(); }, "matrix3x2_constructors");
        add_test([this]() { matrix2x4_constructors(); }, "matrix2x4_constructors");
        add_test([this]() { matrix2x3_constructors(); }, "matrix2x3_constructors");
        add_test([this]() { matrix2x2_constructors(); }, "matrix2x2_constructors");

        // clang-format off
        matrix44 = {
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix43 = {
            0, 1, 2,
            0, 1, 2,
            0, 1, 2,
            0, 1, 2
        };

        matrix42 = {
            0, 1,
            0, 1,
            0, 1,
            0, 1
        };

        matrix34 = {
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix33 = {
            0, 1, 2,
            0, 1, 2,
            0, 1, 2
        };

        matrix32 = {
            0, 1,
            0, 1,
            0, 1
        };

        matrix24 = {
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix23 = {
            0, 1, 2,
            0, 1, 2
        };

        matrix22 = {
            0, 1,
            0, 1
        };
        // clang-format on
    }

private:
    void matrix4x4_constructors()
    {
        TEST_ASSERT(matrix4f(matrix44) == matrix4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix4x4 from Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix4f(matrix43) == matrix4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 1),
                    "Matrix4x4 from Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix4f(matrix42) == matrix4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1),
                    "Matrix4x4 from Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix4f(matrix34) == matrix4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix4f(matrix33) == matrix4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix4f(matrix32) == matrix4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix4f(matrix24) == matrix4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 0, 1, 0, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix4f(matrix23) == matrix4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix4f(matrix22) == matrix4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
                    "Matrix4x4 from Matrix2x2 constructor failed.");
    }

    void matrix4x3_constructors()
    {
        TEST_ASSERT(matrix4x3f(matrix44) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix4x3 form Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix43) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix4x3 form Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix42) == matrix4x3f(0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0),
                    "Matrix4x3 form Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix4x3f(matrix34) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 0, 0),
                    "Matrix4x3 form Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix33) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 0, 0),
                    "Matrix4x3 form Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix32) == matrix4x3f(0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0),
                    "Matrix4x3 form Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix4x3f(matrix24) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 0, 1, 0, 0, 0),
                    "Matrix4x3 form Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix23) == matrix4x3f(0, 1, 2, 0, 1, 2, 0, 0, 1, 0, 0, 0),
                    "Matrix4x3 form Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix4x3f(matrix22) == matrix4x3f(0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0),
                    "Matrix4x3 form Matrix2x2 constructor failed.");
    }

    void matrix4x2_constructors()
    {
        TEST_ASSERT(matrix4x2f(matrix44) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 1),
                    "Matrix4x2 from Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix43) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 1),
                    "Matrix4x2 from Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix42) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 1),
                    "Matrix4x2 from Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix4x2f(matrix34) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 0),
                    "Matrix4x2 from Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix33) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 0),
                    "Matrix4x2 from Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix32) == matrix4x2f(0, 1, 0, 1, 0, 1, 0, 0),
                    "Matrix4x2 from Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix4x2f(matrix24) == matrix4x2f(0, 1, 0, 1, 0, 0, 0, 0),
                    "Matrix4x2 from Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix23) == matrix4x2f(0, 1, 0, 1, 0, 0, 0, 0),
                    "Matrix4x2 from Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix4x2f(matrix22) == matrix4x2f(0, 1, 0, 1, 0, 0, 0, 0),
                    "Matrix4x2 from Matrix2x2 constructor failed.");
    }

    void matrix3x4_constructors()
    {
        TEST_ASSERT(matrix3x4f(matrix44) == matrix3x4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix3x4 from Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix43) == matrix3x4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0),
                    "Matrix3x4 from Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix42) == matrix3x4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0),
                    "Matrix3x4 from Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix3x4f(matrix34) == matrix3x4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix3x4 from Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix33) == matrix3x4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0),
                    "Matrix3x4 from Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix32) == matrix3x4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0),
                    "Matrix3x4 from Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix3x4f(matrix24) == matrix3x4f(0, 1, 2, 3, 0, 1, 2, 3, 0, 0, 1, 0),
                    "Matrix3x4 from Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix23) == matrix3x4f(0, 1, 2, 0, 0, 1, 2, 0, 0, 0, 1, 0),
                    "Matrix3x4 from Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix3x4f(matrix22) == matrix3x4f(0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0),
                    "Matrix3x4 from Matrix2x2 constructor failed.");
    }

    void matrix3x3_constructors()
    {
        TEST_ASSERT(matrix3f(matrix44) == matrix3f(0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix3x3 from Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix3f(matrix43) == matrix3f(0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix3x3 from Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix3f(matrix42) == matrix3f(0, 1, 0, 0, 1, 0, 0, 1, 1),
                    "Matrix3x3 from Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix3f(matrix34) == matrix3f(0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix3x3 from Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix3f(matrix33) == matrix3f(0, 1, 2, 0, 1, 2, 0, 1, 2),
                    "Matrix3x3 from Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix3f(matrix32) == matrix3f(0, 1, 0, 0, 1, 0, 0, 1, 1),
                    "Matrix3x3 from Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix3f(matrix24) == matrix3f(0, 1, 2, 0, 1, 2, 0, 0, 1),
                    "Matrix3x3 from Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix3f(matrix23) == matrix3f(0, 1, 2, 0, 1, 2, 0, 0, 1),
                    "Matrix3x3 from Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix3f(matrix22) == matrix3f(0, 1, 0, 0, 1, 0, 0, 0, 1),
                    "Matrix3x3 from Matrix2x2 constructor failed.");
    }

    void matrix3x2_constructors()
    {
        TEST_ASSERT(matrix3x2f(matrix44) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix43) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix42) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix3x2f(matrix34) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix33) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix32) == matrix3x2f(0, 1, 0, 1, 0, 1),
                    "Matrix3x2 from Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix3x2f(matrix24) == matrix3x2f(0, 1, 0, 1, 0, 0),
                    "Matrix3x2 from Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix23) == matrix3x2f(0, 1, 0, 1, 0, 0),
                    "Matrix3x2 from Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix3x2f(matrix22) == matrix3x2f(0, 1, 0, 1, 0, 0),
                    "Matrix3x2 from Matrix2x2 constructor failed.");
    }

    void matrix2x4_constructors()
    {
        TEST_ASSERT(matrix2x4f(matrix44) == matrix2x4f(0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix2x4 form Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix43) == matrix2x4f(0, 1, 2, 0, 0, 1, 2, 0),
                    "Matrix2x4 form Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix42) == matrix2x4f(0, 1, 0, 0, 0, 1, 0, 0),
                    "Matrix2x4 form Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix2x4f(matrix34) == matrix2x4f(0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix2x4 form Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix33) == matrix2x4f(0, 1, 2, 0, 0, 1, 2, 0),
                    "Matrix2x4 form Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix32) == matrix2x4f(0, 1, 0, 0, 0, 1, 0, 0),
                    "Matrix2x4 form Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix2x4f(matrix24) == matrix2x4f(0, 1, 2, 3, 0, 1, 2, 3),
                    "Matrix2x4 form Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix23) == matrix2x4f(0, 1, 2, 0, 0, 1, 2, 0),
                    "Matrix2x4 form Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix2x4f(matrix22) == matrix2x4f(0, 1, 0, 0, 0, 1, 0, 0),
                    "Matrix2x4 form Matrix2x2 constructor failed.");
    }

    void matrix2x3_constructors()
    {
        TEST_ASSERT(matrix2x3f(matrix44) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix43) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix42) == matrix2x3f(0, 1, 0, 0, 1, 0),
                    "Matrix2x3 form Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix2x3f(matrix34) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix33) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix32) == matrix2x3f(0, 1, 0, 0, 1, 0),
                    "Matrix2x3 form Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix2x3f(matrix24) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix23) == matrix2x3f(0, 1, 2, 0, 1, 2),
                    "Matrix2x3 form Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix2x3f(matrix22) == matrix2x3f(0, 1, 0, 0, 1, 0),
                    "Matrix2x3 form Matrix2x2 constructor failed.");
    }

    void matrix2x2_constructors()
    {
        TEST_ASSERT(matrix2f(matrix44) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix4x4 constructor failed.");
        TEST_ASSERT(matrix2f(matrix43) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix4x3 constructor failed.");
        TEST_ASSERT(matrix2f(matrix42) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix4x2 constructor failed.");

        TEST_ASSERT(matrix2f(matrix34) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix3x4 constructor failed.");
        TEST_ASSERT(matrix2f(matrix33) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix3x3 constructor failed.");
        TEST_ASSERT(matrix2f(matrix32) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix3x2 constructor failed.");

        TEST_ASSERT(matrix2f(matrix24) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix2x4 constructor failed.");
        TEST_ASSERT(matrix2f(matrix23) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix2x3 constructor failed.");
        TEST_ASSERT(matrix2f(matrix22) == matrix2f(0, 1, 0, 1), "Matrix2x2 form Matrix2x2 constructor failed.");
    }

    matrix4x4f matrix44;
    matrix4x3f matrix43;
    matrix4x2f matrix42;

    matrix3x4f matrix34;
    matrix3x3f matrix33;
    matrix3x2f matrix32;

    matrix2x4f matrix24;
    matrix2x3f matrix23;
    matrix2x2f matrix22;
};

int main()
{
    return run_tests(matrix_test(), matrix_from_matrix_test());
}
