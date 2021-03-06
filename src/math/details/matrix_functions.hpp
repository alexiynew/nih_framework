/// @file
/// @brief Contains matrix functions.
/// @author Fedorov Alexey
/// @date 05.07.2017

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

#ifndef FRAMEWORK_MATH_DETAILS
#error You should include math/math.hpp instead of matrix_functions.hpp
#endif

#ifndef FRAMEWORK_MATH_DETAILS_MATRIX_FUNCTIONS_HPP
#define FRAMEWORK_MATH_DETAILS_MATRIX_FUNCTIONS_HPP

#include <common/types.hpp>
#include <math/details/matrix_functions_details.hpp>
#include <math/details/matrix_type.hpp>

namespace framework
{
namespace math
{
/// @addtogroup math_matrix_functions
/// @{

/// @name transpose
/// @{

/// @brief Calculate the transpose of a matrix.
///
/// @param value Specifies the matrix of which to take the transpose.
///
/// @return The transpose of the matrix.
template <uint32 C, uint32 R, typename T>
inline matrix<R, C, T> transpose(const matrix<C, R, T>& value)
{
    return matrix_functions_details::transpose(value);
}
/// @}

/// @name component_wise_multiplication
/// @{

/// @brief Perform a component-wise multiplication of two matrices.
///
/// @param lhs Specifies the first matrix multiplicand.
/// @param rhs Specifies the second matrix multiplicand.
///
/// @return The component-wise multiplication of two matrices.
template <uint32 C, uint32 R, typename T>
inline matrix<C, R, T> component_wise_multiplication(const matrix<C, R, T>& lhs, const matrix<C, R, T>& rhs)
{
    matrix<C, R, T> temp{lhs};

    for (uint32 i = 0; i < C; ++i) {
        temp[i] *= rhs[i];
    }

    return temp;
}
/// @}

/// @name outer_product
/// @{

/// @brief Calculate the outer product of a pair of vectors.
///
/// @param lhs Specifies the parameter to be treated as a column vector.
/// @param rhs Specifies the parameter to be treated as a row vector.
///
/// @return The outer product of a pair of vectors.
template <uint32 C, uint32 R, typename T>
inline matrix<C, R, T> outer_product(const vector<R, T>& lhs, const vector<C, T>& rhs)
{
    return matrix_functions_details::outer_product(lhs, rhs);
}
/// @}

/// @name determinant
/// @{

/// @brief Calculate the determinant of a matrix.
///
/// @param value Specifies the matrix of which to take the determinant.
///
/// @return The determinant of the matrix.
template <uint32 C, uint32 R, typename T>
inline T determinant(const matrix<C, R, T>& value)
{
    return matrix_functions_details::determinant(value);
}
/// @}

/// @name inverse
/// @{

/// @brief Calculate the inverse of a matrix.
///
/// The values in the returned matrix are undefined if matrix is singular or poorly-conditioned (nearly singular).
///
/// @param value Specifies the matrix of which to take the inverse.
///
/// @return The inverse of a matrix.
template <uint32 C, uint32 R, typename T>
inline matrix<C, R, T> inverse(const matrix<C, R, T>& value)
{
    return matrix_functions_details::inverse(value);
}
/// @}

/// @name affine_inverse
/// @{

/// @brief Calculate the inverse of a affine matrix.
///
/// The values in the returned matrix are undefined if matrix contains not affine transformations,
/// or matrix is singular or poorly-conditioned (nearly singular).
///
/// @param value Specifies the matrix of which to take the inverse.
///
/// @return The inverse of a matrix.
template <uint32 C, uint32 R, typename T>
inline matrix<C, R, T> affine_inverse(const matrix<C, R, T>& value)
{
    return matrix_functions_details::affine_inverse(value);
}
/// @}

/// @name inverse_transpose
/// @{

/// @brief Calculate the inverse-transpose of a matrix.
///
/// The values in the returned matrix are undefined if matrix is singular or poorly-conditioned (nearly singular).
///
/// @param value Specifies the matrix of which to take the inverse.
///
/// @return The matrix which is equivalent to `transpose(inverse(matrix))`.
template <uint32 C, uint32 R, typename T>
inline matrix<C, R, T> inverse_transpose(const matrix<C, R, T>& value)
{
    return matrix_functions_details::inverse_transpose(value);
}
/// @}

/// @}

} // namespace math

} // namespace framework

#endif
