
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

#ifndef APPLESEED_RENDERER_GLOBAL_GLOBALLOGGER_H
#define APPLESEED_RENDERER_GLOBAL_GLOBALLOGGER_H

// appleseed.foundation headers.
#include "foundation/core/concepts.h"
#include "foundation/utility/log.h"

//
// On Windows, define RENDERERDLL to __declspec(dllexport) when building the DLL
// and to __declspec(dllimport) when building an application using the DLL.
// Other platforms don't use this export mechanism and the symbol RENDERERDLL is
// defined to evaluate to nothing.
//

#ifndef RENDERERDLL
#ifdef _WIN32
#ifdef APPLESEED_RENDERER_EXPORTS
#define RENDERERDLL __declspec(dllexport)
#else
#define RENDERERDLL __declspec(dllimport)
#endif
#else
#define RENDERERDLL
#endif
#endif

namespace renderer
{

//
// A globally accessible logger.
//

RENDERERDLL foundation::Logger& global_logger();


//
// Utility macros to write a message to the global logger.
//

#define RENDERER_LOG(category, ...)                     \
    do {                                                \
        renderer::global_logger().write(                \
            category,                                   \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

#define RENDERER_LOG_INFO(...)                          \
    do {                                                \
        renderer::global_logger().write(                \
            foundation::LogMessage::Info,               \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

#define RENDERER_LOG_DEBUG(...)                         \
    do {                                                \
        renderer::global_logger().write(                \
            foundation::LogMessage::Debug,              \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

#define RENDERER_LOG_WARNING(...)                       \
    do {                                                \
        renderer::global_logger().write(                \
            foundation::LogMessage::Warning,            \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

#define RENDERER_LOG_ERROR(...)                         \
    do {                                                \
        renderer::global_logger().write(                \
            foundation::LogMessage::Error,              \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

#define RENDERER_LOG_FATAL(...)                         \
    do {                                                \
        renderer::global_logger().write(                \
            foundation::LogMessage::Fatal,              \
            __FILE__,                                   \
            __LINE__,                                   \
            __VA_ARGS__);                               \
    } while (0)

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_GLOBAL_GLOBALLOGGER_H
