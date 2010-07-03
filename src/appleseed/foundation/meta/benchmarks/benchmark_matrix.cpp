
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// appleseed.foundation headers.
#include "foundation/math/matrix.h"
#include "foundation/math/vector.h"
#include "foundation/utility/benchmark.h"

FOUNDATION_BENCHMARK_SUITE(Foundation_Math_Matrix44)
{
    using namespace foundation;

    template <typename T>
    struct Fixture
    {
        Matrix<T, 4, 4> m_lhs, m_rhs;
        Matrix<T, 4, 4> m_result_mat;
        Vector<T, 4>    m_vec;
        Vector<T, 4>    m_result_vec;

        Fixture()
        {
            // A 4x4 invertible matrix.
            const T mat_val[] =
            {
                 -7,  22, -55, -94,
                 87, -56,   0, -62,
                 97, -73,  -4, -83,
                -10,  62, -82,  80
            };

            m_lhs = Matrix<T, 4, 4>(mat_val);
            m_rhs = transpose(m_lhs);
            m_vec = Vector<T, 4>(2, -24, 66, 13);
        }
    };

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(SinglePrecisionMatrixMatrixMultiplication, Fixture<float>)
    {
        m_result_mat = m_lhs * m_rhs;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(DoublePrecisionMatrixMatrixMultiplication, Fixture<double>)
    {
        m_result_mat = m_lhs * m_rhs;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(SinglePrecisionMatrixVectorMultiplication, Fixture<float>)
    {
        m_result_vec = m_lhs * m_vec;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(DoublePrecisionMatrixVectorMultiplication, Fixture<double>)
    {
        m_result_vec = m_lhs * m_vec;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(SinglePrecisionVectorMatrixMultiplication, Fixture<float>)
    {
        m_result_vec = m_vec * m_rhs;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(DoublePrecisionVectorMatrixMultiplication, Fixture<double>)
    {
        m_result_vec = m_vec * m_rhs;
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(SinglePrecisionMatrixInversion, Fixture<float>)
    {
        m_result_mat = inverse(m_lhs);
    }

    FOUNDATION_BENCHMARK_CASE_WITH_FIXTURE(DoublePrecisionMatrixInversion, Fixture<double>)
    {
        m_result_mat = inverse(m_lhs);
    }
}
