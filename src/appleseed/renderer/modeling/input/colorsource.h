
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

#ifndef APPLESEED_RENDERER_MODELING_INPUT_COLORSOURCE_H
#define APPLESEED_RENDERER_MODELING_INPUT_COLORSOURCE_H

// appleseed.renderer headers.
#include "renderer/global/global.h"
#include "renderer/modeling/input/source.h"

// appleseed.foundation headers.
#include "foundation/image/colorspace.h"

// Forward declarations.
namespace renderer      { class ColorEntity; }

namespace renderer
{

//
// Uniform source.
//

class ColorSource
  : public Source
{
  public:
    // Constructor.
    explicit ColorSource(const ColorEntity& color_entity);

    // Evaluate the source.
    virtual void evaluate_uniform(
        double&                 scalar);
    virtual void evaluate_uniform(
        foundation::Color3f&    linear_rgb,
        Alpha&                  alpha);
    virtual void evaluate_uniform(
        Spectrum&               spectrum,
        Alpha&                  alpha);

  private:
    const foundation::LightingConditions    m_lighting_conditions;

    double                                  m_scalar;
    Spectrum                                m_spectrum;
};


//
// ColorSource class implementation.
//

// Evaluate the source.
inline void ColorSource::evaluate_uniform(
    double&                 scalar)
{
    scalar = m_scalar;
}
inline void ColorSource::evaluate_uniform(
    foundation::Color3f&    linear_rgb,
    Alpha&                  alpha)
{
    linear_rgb =
        foundation::ciexyz_to_linear_rgb(
            foundation::spectrum_to_ciexyz<float>(
                m_lighting_conditions,
                m_spectrum));
    alpha.set(1.0f);
}
inline void ColorSource::evaluate_uniform(
    Spectrum&               spectrum,
    Alpha&                  alpha)
{
    spectrum = m_spectrum;
    alpha.set(1.0f);
}

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_INPUT_COLORSOURCE_H
