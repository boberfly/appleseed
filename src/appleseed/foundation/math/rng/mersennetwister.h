
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

#ifndef APPLESEED_FOUNDATION_MATH_RNG_MERSENNETWISTER_H
#define APPLESEED_FOUNDATION_MATH_RNG_MERSENNETWISTER_H

// appleseed.foundation headers.
#include "foundation/core/concepts.h"
#include "foundation/platform/types.h"

// Standard headers.
#include <cstddef>

//
// On Windows, define FOUNDATIONDLL to __declspec(dllexport) when building the DLL
// and to __declspec(dllimport) when building an application using the DLL.
// Other platforms don't use this export mechanism and the symbol FOUNDATIONDLL is
// defined to evaluate to nothing.
//

#ifndef FOUNDATIONDLL
#ifdef _WIN32
#ifdef APPLESEED_FOUNDATION_EXPORTS
#define FOUNDATIONDLL __declspec(dllexport)
#else
#define FOUNDATIONDLL __declspec(dllimport)
#endif
#else
#define FOUNDATIONDLL
#endif
#endif

namespace foundation
{

//
// Mersenne-Twister random number generator.
//

class FOUNDATIONDLL MersenneTwister
  : public NonCopyable
{
  public:
    // Constructors, seeds the generator.
    explicit MersenneTwister(uint32 seed = 5489UL);
    MersenneTwister(uint32 init_key[], int key_length);

    // Generates a full-range 32-bit random number.
    uint32 rand_uint32();

  private:
    // Period parameters.
    static const int N = 624;
    static const int M = 397;
    static const uint32 MATRIX_A   = 0x9908b0dfUL;  // constant vector a
    static const uint32 UPPER_MASK = 0x80000000UL;  // most significant w-r bits
    static const uint32 LOWER_MASK = 0x7fffffffUL;  // least significant r bits

    uint32  mt[N];  // state vector
    int     mti;    // current index in state vector

    // Initialize the state vector with a seed.
    void init_state(uint32 seed);

    // Update the state vector.
    void update_state();
};


//
// MersenneTwister class implementation.
//

// Generates a full-range 32-bit random number.
inline uint32 MersenneTwister::rand_uint32()
{
    if (mti >= N)
        update_state();

    uint32 y = mt[mti++];

    // Tempering.
    y ^= (y >> 11);
    y ^= (y << 7)  & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_MATH_RNG_MERSENNETWISTER_H
