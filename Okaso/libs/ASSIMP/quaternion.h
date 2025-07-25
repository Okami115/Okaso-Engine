/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2025, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
----------------------------------------------------------------------
*/

/** @file quaternion.h
 *  @brief Quaternion structure, including operators when compiling in C++
 */
#pragma once
#ifndef AI_QUATERNION_H_INC
#define AI_QUATERNION_H_INC

#include "defs.h"

#ifdef __cplusplus

#ifdef __GNUC__
#   pragma GCC system_header
#endif

// Forward declarations
template <typename TReal> class aiVector3t;
template <typename TReal> class aiMatrix3x3t;
template <typename TReal> class aiMatrix4x4t;

// ---------------------------------------------------------------------------
/**
 *  @brief  This class represents a quaternion as a 4D vector.
 */
template <typename TReal>
class aiQuaterniont {
public:
    aiQuaterniont() AI_NO_EXCEPT : w(1.0), x(), y(), z() {}
    aiQuaterniont(TReal pw, TReal px, TReal py, TReal pz)
        : w(pw), x(px), y(py), z(pz) {}

    /**
     *  @brief  Construct from rotation matrix. Result is undefined if the matrix is not orthonormal.
     */
    explicit aiQuaterniont( const aiMatrix3x3t<TReal>& pRotMatrix);

    /** Construct from euler angles */
    aiQuaterniont( TReal roty, TReal rotz, TReal rotx);

    /** Construct from an axis-angle pair */
    aiQuaterniont( aiVector3t<TReal> axis, TReal angle);

    /** Construct from a normalized quaternion stored in a vec3 */
    explicit aiQuaterniont( aiVector3t<TReal> normalized);

    /** Returns a matrix representation of the quaternion */
    aiMatrix3x3t<TReal> GetMatrix() const;

    bool operator== (const aiQuaterniont& o) const;
    bool operator!= (const aiQuaterniont& o) const;

    // transform vector by matrix
    aiQuaterniont& operator *= (const aiMatrix4x4t<TReal>& mat);

    bool Equal(const aiQuaterniont &o, TReal epsilon = ai_epsilon) const;

    /**
     *  @brief  Will normalize the quaternion representation.
     */
    aiQuaterniont& Normalize();

    /**
     *  @brief  Will compute the quaternion conjugate. The result will be stored in the instance.
     */
    aiQuaterniont& Conjugate();

    /**
     *  @brief  Rotate a point by this quaternion
     */
    aiVector3t<TReal> Rotate(const aiVector3t<TReal>& in) const;

    /**
     *  @brief Multiply two quaternions
     *  @param  two   The other quaternion.
     *  @return The result of the multiplication.
     */
    aiQuaterniont operator * (const aiQuaterniont& two) const;

    /**
     * @brief Performs a spherical interpolation between two quaternions and writes the result into the third.
     * @param pOut Target object to received the interpolated rotation.
     * @param pStart Start rotation of the interpolation at factor == 0.
     * @param pEnd End rotation, factor == 1.
     * @param pFactor Interpolation factor between 0 and 1. Values outside of this range yield undefined results.
     */
    static void Interpolate( aiQuaterniont& pOut, const aiQuaterniont& pStart,
        const aiQuaterniont& pEnd, TReal pFactor);

    //! w,x,y,z components of the quaternion
    TReal w, x, y, z;
} ;

using aiQuaternion = aiQuaterniont<ai_real>;

#else

struct aiQuaternion {
    ai_real w, x, y, z;
};

#endif

#endif // AI_QUATERNION_H_INC
