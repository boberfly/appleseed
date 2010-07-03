
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
#include "foundation/math/cdf.h"
#include "foundation/math/fp.h"
#include "foundation/utility/test.h"

FOUNDATION_TEST_SUITE(Foundation_Math_CDF)
{
    using namespace foundation;
    using namespace std;

    typedef CDF<int, double> CDF;

    FOUNDATION_TEST_CASE(Empty_GivenCDFInInitialState_ReturnsTrue)
    {
        CDF cdf;

        FOUNDATION_EXPECT_TRUE(cdf.empty());
    }

    FOUNDATION_TEST_CASE(Valid_GivenCDFInInitialState_ReturnsFalse)
    {
        CDF cdf;

        FOUNDATION_EXPECT_FALSE(cdf.valid());
    }

    FOUNDATION_TEST_CASE(Empty_GivenCDFWithOneItem_ReturnsFalse)
    {
        CDF cdf;
        cdf.insert(1, 0.5);

        FOUNDATION_EXPECT_FALSE(cdf.empty());
    }

    FOUNDATION_TEST_CASE(Valid_GivenCDFWithOneItemWithPositiveWeight_ReturnsTrue)
    {
        CDF cdf;
        cdf.insert(1, 0.5);

        FOUNDATION_EXPECT_TRUE(cdf.valid());
    }

    FOUNDATION_TEST_CASE(Valid_GivenCDFWithOneItemWithZeroWeight_ReturnsFalse)
    {
        CDF cdf;
        cdf.insert(1, 0.0);

        FOUNDATION_EXPECT_FALSE(cdf.valid());
    }

    FOUNDATION_TEST_CASE(Clear_GivenCDFWithOneItem_RemovesItem)
    {
        CDF cdf;
        cdf.insert(1, 0.5);
        cdf.clear();

        FOUNDATION_EXPECT_TRUE(cdf.empty());
    }

    FOUNDATION_TEST_CASE(Clear_GivenCDFWithOneItem_MakesCDFInvalid)
    {
        CDF cdf;
        cdf.insert(1, 0.5);
        cdf.clear();

        FOUNDATION_EXPECT_FALSE(cdf.valid());
    }

    FOUNDATION_TEST_CASE(Sample_GivenCDFWithOneItemWithPositiveWeight_ReturnsItem)
    {
        CDF cdf;
        cdf.insert(1, 0.5);
        cdf.prepare();

        const CDF::ItemWeightPair result = cdf.sample(0.5);

        FOUNDATION_EXPECT_EQ(1, result.first);
        FOUNDATION_EXPECT_FEQ(1.0, result.second);
    }

    struct Fixture
    {
        CDF m_cdf;

        Fixture()
        {
            m_cdf.insert(1, 0.4);
            m_cdf.insert(2, 1.6);
            m_cdf.prepare();
        }
    };

    FOUNDATION_TEST_CASE_WITH_FIXTURE(Sample_GivenInputEqualToZero_ReturnsItems1, Fixture)
    {
        const CDF::ItemWeightPair result = m_cdf.sample(0.0);

        FOUNDATION_EXPECT_EQ(1, result.first);
        FOUNDATION_EXPECT_FEQ(0.2, result.second);
    }

    FOUNDATION_TEST_CASE_WITH_FIXTURE(Sample_GivenInputEqualTo0_2_ReturnsItems2, Fixture)
    {
        const CDF::ItemWeightPair result = m_cdf.sample(0.2);

        FOUNDATION_EXPECT_EQ(2, result.first);
        FOUNDATION_EXPECT_FEQ(0.8, result.second);
    }

    FOUNDATION_TEST_CASE_WITH_FIXTURE(Sample_GivenInputNearOne_ReturnsItem2, Fixture)
    {
        const CDF::ItemWeightPair result = m_cdf.sample(0.99);

        FOUNDATION_EXPECT_EQ(2, result.first);
        FOUNDATION_EXPECT_FEQ(0.8, result.second);
    }

    FOUNDATION_TEST_CASE_WITH_FIXTURE(Sample_GivenInputOneUlpBeforeOne_ReturnsItem2, Fixture)
    {
        const double almost_one = shift(1.0, -1);
        const CDF::ItemWeightPair result = m_cdf.sample(almost_one);

        FOUNDATION_EXPECT_EQ(2, result.first);
        FOUNDATION_EXPECT_FEQ(0.8, result.second);
    }

    FOUNDATION_TEST_CASE(2D_CDF_Exploration)
    {
        CDF child[2];

        child[0].insert(1, 0.3);
        child[0].insert(2, 0.7);
        child[0].prepare();

        child[1].insert(3, 0.1);
        child[1].insert(4, 0.4);
        child[1].prepare();

        CDF parent;
        parent.insert(0, child[0].weight());
        parent.insert(1, child[1].weight());
        parent.prepare();

        const double x = 0.3;   // will choose child[0]
        const double y = 0.6;   // will choose value 2

        const CDF::ItemWeightPair u = parent.sample(x);
        const CDF::ItemWeightPair v = child[u.first].sample(y);

        const int value = v.first;
        const double prob = u.second * v.second;

        FOUNDATION_EXPECT_EQ(2, value);
        FOUNDATION_EXPECT_FEQ(0.7 * (2.0 / 3), prob);
    }
}
