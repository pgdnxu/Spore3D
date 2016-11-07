// *********************************************************************
//             ____                       _____ ____
//            / ___| _ __   ___  _ __ ___|___ /|  _ \
//            \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |
//             ___) | |_) | (_) | | |  __/___) | |_| |
//            |____/| .__/ \___/|_|  \___|____/|____/
//                  |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
//      -- github.com/pgdnxu/Spore3D
//  --------------------------------------------------------------------
//
//  Copyright (C) 2016 Shannon Xu
//
//  This software is distributed under the terms of the MIT License.
//  A copy of the license may be obtained at: https://opensource.org/licenses/MIT
//
// .--. --. -.. -. .. -. ..-. --.-. --. -- .- .. .-.. .-.-.- -.-. --- --

#ifndef _cBounds_h_
#define _cBounds_h_

#include "uMath.h"
#include "cRay.h"

namespace Spore3D {
    
    /* axially aligned bounding box */
    class Bounds {
    public:
        
        Bounds(const Vec3 &center, const Vec3 &size);
        
        Vec3 getMin(void) const { return m_Min; }
        Vec3 getMax(void) const { return m_Max; }
        Vec3 getExtents(void) const { return m_Extents; }
        Vec3 getSize(void) const { return m_Size; }
        Vec3 getCenter(void) const { return m_Center; }
        
        bool isEmpty(void) const;
        Vec3 closestPoint(const Vec3&) const;
        bool contains(const Vec3&) const;
        void encapsulate(const Vec3&);
        void expand(const float amount);
        bool intersectRay(const Ray&);
        bool interset(const Bounds&) const;
        void setMinMax(const Vec3&, const Vec3&);
        float sqrDistance(const Vec3&);
        
    private:
        Vec3 m_Min;
        Vec3 m_Max;
        Vec3 m_Extents;
        Vec3 m_Size;
        Vec3 m_Center;
    };
    
}

#endif /* _cBounds_h_ */
