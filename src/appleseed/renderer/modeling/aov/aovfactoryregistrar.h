
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2017 Esteban Tovagliari, The appleseedhq Organization
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

#ifndef APPLESEED_RENDERER_MODELING_AOV_AOVFACTORYREGISTRAR_H
#define APPLESEED_RENDERER_MODELING_AOV_AOVFACTORYREGISTRAR_H

// appleseed.renderer headers.
#include "renderer/modeling/entity/entityfactoryregistrar.h"

// appleseed.foundation headers.
#include "foundation/utility/api/apiarray.h"
#include "foundation/utility/autoreleaseptr.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Forward declarations.
namespace foundation    { class SearchPaths; }
namespace renderer      { class IAOVFactory; }

namespace renderer
{

//
// An array of AOV factories.
//

APPLESEED_DECLARE_APIARRAY(AOVFactoryArray, IAOVFactory*);


//
// AOV factory registrar.
//

class APPLESEED_DLLSYMBOL AOVFactoryRegistrar
  : public EntityFactoryRegistrar
{
  public:
    typedef IAOVFactory FactoryType;
    typedef AOVFactoryArray FactoryArrayType;

    // Constructor.
    explicit AOVFactoryRegistrar(
        const foundation::SearchPaths& search_paths = foundation::SearchPaths());

    // Destructor.
    ~AOVFactoryRegistrar();

    // Reinitialize the registrar; load plugins found in provided search paths.
    void reinitialize(const foundation::SearchPaths& search_paths);

    // Retrieve the registered factories.
    FactoryArrayType get_factories() const;

    // Lookup a factory by name.
    const FactoryType* lookup(const char* name) const;

  private:
    struct Impl;
    Impl* impl;

    // Register a factory.
    void register_factory(foundation::auto_release_ptr<FactoryType> factory);
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_AOV_AOVFACTORYREGISTRAR_H
