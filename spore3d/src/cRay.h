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

#ifndef _cRay_h_
#define _cRay_h_

#include "uMath.h"

namespace Spore3D {
    
    class Ray {
    public:
        Ray(const Vec3 &origin, const Vec3 &direction);
        Vec3 getDirection(void) const { return m_Direction; }
        Vec3 getOrigin(void) const { return m_Origin; }
        void setDirection(const Vec3&);
        void setOrigin(const Vec3&);
        
    private:
        Vec3 m_Direction;
        Vec3 m_Origin;
        
    };
    
}

#endif /* _cRay_h_ */
