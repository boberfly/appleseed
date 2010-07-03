
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
#include "memory.h"

// Standard headers.
#include <cstdlib>

using namespace std;

namespace foundation
{

//
// Memory-alignment related functions implementation.
//

// Allocate memory on a specified alignment boundary.
void* aligned_malloc(const size_t size, const size_t alignment)
{
    assert(size > 0);
    assert(alignment > 0);
    assert(is_pow2(alignment));

    // Compute the total number of bytes of memory we need to allocate.
    const size_t total_size = size + sizeof(void*) + (alignment - 1);

    // Allocate the memory.
    void** const unaligned_ptr = reinterpret_cast<void**>(malloc(total_size));
    if (!unaligned_ptr)
        return 0;

    // Compute the next aligned address.
    void** const aligned_ptr = align(unaligned_ptr + 1, alignment);

    // Store the address of the unaligned memory block.
    *(aligned_ptr - 1) = unaligned_ptr;

    return aligned_ptr;
}

// Free a block of memory that was allocated with aligned_malloc().
void aligned_free(void* aligned_ptr)
{
    assert(aligned_ptr);

    // Retrieve the address of the unaligned memory block.
    void* unaligned_ptr = *(reinterpret_cast<void**>(aligned_ptr) - 1);

    // Deallocate the memory.
    free(unaligned_ptr);
}

}   // namespace foundation
