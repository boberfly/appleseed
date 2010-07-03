
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
#include "foundation/image/color.h"
#include "foundation/image/image.h"
#include "foundation/image/tile.h"
#include "foundation/utility/iostreamop.h"
#include "foundation/utility/test.h"

FOUNDATION_TEST_SUITE(Foundation_Image_Image)
{
    using namespace foundation;

    FOUNDATION_TEST_CASE(Constructor_CreatesBlankImage)
    {
        Image image(2, 1, 1, 1, 3, PixelFormatFloat);

        Color3f c00; image.tile(0, 0).get_pixel(0, 0, c00);
        Color3f c10; image.tile(1, 0).get_pixel(0, 0, c10);

        FOUNDATION_EXPECT_EQ(Color3f(0.0), c00);
        FOUNDATION_EXPECT_EQ(Color3f(0.0), c10);
    }

    FOUNDATION_TEST_CASE(CopyConstructor_GivenVirginSourceImage_CreatesBlankImage)
    {
        Image source(2, 1, 1, 1, 3, PixelFormatFloat);
        Image copy(source);

        Color3f c00; copy.tile(0, 0).get_pixel(0, 0, c00);
        Color3f c10; copy.tile(1, 0).get_pixel(0, 0, c10);

        FOUNDATION_EXPECT_EQ(Color3f(0.0), c00);
        FOUNDATION_EXPECT_EQ(Color3f(0.0), c10);
    }
}
