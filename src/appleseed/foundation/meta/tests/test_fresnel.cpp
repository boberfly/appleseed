
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
#include "foundation/image/spectrum.h"
#include "foundation/math/fresnel.h"
#include "foundation/utility/iostreamop.h"
#include "foundation/utility/test.h"

using namespace foundation;

FOUNDATION_TEST_SUITE(Foundation_Math_Fresnel)
{
    FOUNDATION_TEST_CASE(SchlickFresnelReflection_GivenCosThetaIsZero_ReturnsOne)
    {
        const Spectrum31f NormalReflectance(42.0f);

        const Spectrum31f result = schlick_fresnel_reflection(NormalReflectance, 0.0);

        FOUNDATION_EXPECT_EQ(Spectrum31f(1.0f), result);
    }

    FOUNDATION_TEST_CASE(SchlickFresnelReflection_GivenCosThetaIsOne_ReturnsNormalReflectance)
    {
        const Spectrum31f NormalReflectance(42.0f);

        const Spectrum31f result = schlick_fresnel_reflection(NormalReflectance, 1.0);

        FOUNDATION_EXPECT_EQ(NormalReflectance, result);
    }
}
