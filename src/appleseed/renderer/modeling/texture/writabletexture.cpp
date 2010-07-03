
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

// Interface header.
#include "writabletexture.h"

// appleseed.renderer headers.
#include "renderer/modeling/texture/texture.h"

// appleseed.foundation headers.
#include "foundation/image/canvasproperties.h"
#include "foundation/image/colorspace.h"
#include "foundation/image/tile.h"
#include "foundation/platform/thread.h"
#include "foundation/utility/searchpaths.h"

using namespace boost;
using namespace foundation;
using namespace std;

namespace renderer
{

namespace
{

    //
    // Writable texture.
    //

    class WritableTexture
      : public Texture
    {
      public:
        // Constructor.
        WritableTexture(
            const char*         name,
            const ParamArray&   params,
            const SearchPaths&  search_paths)
          : Texture(params)
          , m_name(name)
          , m_props_defined(false)
        {
        }

        // Delete this instance.
        virtual void release()
        {
            delete this;
        }

        // Return a string identifying the model of this texture.
        virtual const char* get_model() const
        {
            return WritableTextureFactory::get_model();
        }

        // Return the name of this texture.
        virtual const char* get_name() const
        {
            return m_name.c_str();
        }

        // Return the color space of the texture.
        virtual ColorSpace get_color_space() const
        {
            // todo: implement.
            return ColorSpaceLinearRGB;
        }

        // Access canvas properties.
        virtual const CanvasProperties& properties()
        {
            mutex::scoped_lock lock(m_mutex);

            if (!m_props_defined)
            {
                set_canvas_properties();
                m_props_defined = true;
            }

            return m_props;
        }

        // Load a given tile.
        virtual Tile* load_tile(
            const size_t    tile_x,
            const size_t    tile_y)
        {
            mutex::scoped_lock lock(m_mutex);

            // todo: create a blank tile, or get the tile from the texture.
            return new Tile(
                32,
                32,
                4,
                PixelFormatFloat);
        }

        // Unload a given tile.
        virtual void unload_tile(
            const size_t    tile_x,
            const size_t    tile_y,
            Tile*           tile)
        {
            mutex::scoped_lock lock(m_mutex);

            // todo: store the tile into the texture.
        }

      private:
        const string        m_name;
        mutable mutex       m_mutex;
        bool                m_props_defined;
        CanvasProperties    m_props;

        // Set canvas properties.
        void set_canvas_properties()
        {
            // todo: open texture file and set canvas properties.
        }
    };

}   // anonymous namespace


//
// WritableTextureFactory class implementation.
//

// Return a string identifying this texture model.
const char* WritableTextureFactory::get_model()
{
    return "2d_texture";
}

// Create a new writable texture.
auto_release_ptr<Texture> WritableTextureFactory::create(
    const char*         name,
    const ParamArray&   params,
    const SearchPaths&  search_paths)
{
    return
        auto_release_ptr<Texture>(
            new WritableTexture(name, params, search_paths));
}

}   // namespace renderer
