
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
#include "defaultproject.h"

// appleseed.renderer headers.
#include "renderer/api/camera.h"
#include "renderer/api/frame.h"
#include "renderer/api/project.h"
#include "renderer/api/scene.h"

// appleseed.foundation headers.
#include "foundation/math/transform.h"

using namespace foundation;
using namespace std;

namespace renderer
{

//
// DefaultProjectFactory class implementation.
//

// Create a new instance of the default project.
auto_release_ptr<Project> DefaultProjectFactory::create()
{
    // Create a project.
    auto_release_ptr<Project> project(ProjectFactory::create("default"));

    // Add default configurations to the project.
    project->add_default_configurations();

    // Create a scene.
    auto_ptr<Scene> scene(new Scene());

    //
    // Camera.
    //

    {
        // Create a pinhole camera.
        ParamArray params;
        params.insert("film_dimensions", "0.036 0.024");
        params.insert("focal_length", "0.035");
        auto_release_ptr<Camera> camera(
            PinholeCameraFactory::create(
                "camera",
                params,
                Transformd(Matrix4d::identity())));

        // Attach the camera to the scene.
        scene->set_camera(camera);
    }

    //
    // Frame.
    //

    {
        // Create a frame.
        ParamArray params;
        params.insert("camera", scene->get_camera()->get_name());
        params.insert("resolution", "512 512");
        params.insert("color_space", "srgb");
        auto_ptr<Frame> frame(
            new Frame("beauty", params));

        // Attach the frame to the project.
        project->set_frame(frame);
    }

    // Attach the scene to the project.
    project->set_scene(scene);

    // Return the newly created project.
    return project;
}

}   // namespace renderer
