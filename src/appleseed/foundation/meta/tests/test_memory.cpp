
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
#include "foundation/utility/memory.h"
#include "foundation/utility/test.h"

// Standard headers.
#include <vector>

using namespace foundation;
using namespace std;

FOUNDATION_TEST_SUITE(Foundation_Utility_Memory)
{
    FOUNDATION_TEST_CASE(Align_GivenZero_ReturnsZero)
    {
        FOUNDATION_EXPECT_EQ(0, align(0, 4));
    }

    FOUNDATION_TEST_CASE(Align_GivenUnalignedValue_ReturnsAlignedValue)
    {
        FOUNDATION_EXPECT_EQ(16, align(13, 4));
    }

    FOUNDATION_TEST_CASE(Align_GivenAlignedValue_ReturnsInputValue)
    {
        FOUNDATION_EXPECT_EQ(16, align(16, 4));
    }

    FOUNDATION_TEST_CASE(ClearReleaseMemory_GivenVectorWithThousandElements_ClearsVector)
    {
        vector<int> v(1000);

        clear_release_memory(v);

        FOUNDATION_EXPECT_TRUE(v.empty());
    }

    FOUNDATION_TEST_CASE(ClearReleaseMemory_GivenVectorWithThousandElements_ResetsVectorCapacityToDefaultValue)
    {
        vector<int> v;
        const size_t default_capacity = v.capacity();

        v.resize(1000);

        clear_release_memory(v);

        FOUNDATION_EXPECT_EQ(default_capacity, v.capacity());
    }

    FOUNDATION_TEST_CASE(ClearKeepMemory_GivenVectorWithThousandElements_ClearsVector)
    {
        vector<int> v(1000);

        clear_keep_memory(v);

        FOUNDATION_EXPECT_TRUE(v.empty());
    }

    FOUNDATION_TEST_CASE(ClearReleaseMemory_GivenVectorWithThousandElements_RetainsVectorCapacity)
    {
        vector<int> v(1000);

        const size_t old_capacity = v.capacity();

        clear_keep_memory(v);

        FOUNDATION_EXPECT_EQ(old_capacity, v.capacity());
    }
}
