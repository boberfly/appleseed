
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2015 Francois Beaune, The appleseedhq Organization
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

#ifndef APPLESEED_SHARED_APPLICATION_COMMANDLINEHANDLERBASE_H
#define APPLESEED_SHARED_APPLICATION_COMMANDLINEHANDLERBASE_H

// appleseed.shared headers.
#include "dllsymbol.h"

// appleseed.foundation headers.
#include "foundation/core/concepts/noncopyable.h"

// Forward declarations.
namespace appleseed     { namespace shared { class SuperLogger; } }
namespace foundation    { class CommandLineParser; }

namespace appleseed {
namespace shared {

//
// Base class for command line handlers.
//

class SHAREDDLL CommandLineHandlerBase
  : public foundation::NonCopyable
{
  public:
    // Constructor.
    explicit CommandLineHandlerBase(const char* application_name);

    // Destructor.
    virtual ~CommandLineHandlerBase();

    // Add all the default command line options.
    void add_default_options();

    // Add individual default command line options.
    void add_help_option();
    void add_version_option();
    void add_system_option();
    void add_message_verbosity_option();
    void add_message_coloring_option();
    void add_display_options_option();

    // Parse the application's command line.
    // This method may reconfigure the logger (to enable message coloring, for instance).
    virtual void parse(
        const int       argc,
        const char*     argv[],
        SuperLogger&    logger);

  protected:
    // This method must be implemented to emit usage instructions to the logger.
    virtual void print_program_usage(
        const char*     program_name,
        SuperLogger&    logger) const = 0;

    // Access the command line parser object.
    foundation::CommandLineParser& parser();
    const foundation::CommandLineParser& parser() const;

  private:
    struct Impl;
    Impl* impl;

    void print_version_information(SuperLogger& logger) const;
    static void print_system_information(SuperLogger& logger);
};

}       // namespace shared
}       // namespace appleseed

#endif  // !APPLESEED_SHARED_APPLICATION_COMMANDLINEHANDLERBASE_H
