
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

#ifndef APPLESEED_STUDIO_RENDERING_IRENDERWIDGET_H
#define APPLESEED_STUDIO_RENDERING_IRENDERWIDGET_H

// appleseed.foundation headers.
#include "foundation/core/concepts.h"
#include "foundation/image/color.h"

// Standard headers.
#include <cstddef>

// Forward declarations.
namespace renderer      { class Frame; }

namespace appleseed {
namespace studio {

class IRenderWidget
  : public foundation::NonCopyable
{
  public:
    virtual void clear(
        const foundation::Color4f&  color) = 0;

    virtual void highlight_region(
        const size_t                x,
        const size_t                y,
        const size_t                width,
        const size_t                height) = 0;

    virtual void blit_tile(
        const renderer::Frame&      frame,
        const size_t                tile_x,
        const size_t                tile_y) = 0;

    virtual void blit_frame(
        const renderer::Frame&      frame) = 0;
};

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_RENDERING_IRENDERWIDGET_H
