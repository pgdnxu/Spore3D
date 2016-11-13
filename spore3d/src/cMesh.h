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

#ifndef _cMesh_h_
#define _cMesh_h_

#include "cObject.h"
#include "uMath.h"

#include <vector>

namespace Spore3D {
    
    class Mesh : public CoreObject {
    public:
        Mesh(const std::string &name);
        virtual ~Mesh();
        
    public:
        std::vector<Vec3>   vertices;
        std::vector<Vec2>   uv;
        std::vector<Vec2>   uv2;
        std::vector<Vec3>   normal;
        
        std::vector<uint32> vertIndex;
        std::vector<uint32> textureIndex;
        std::vector<uint32> normalIndex;
        
    protected:
        virtual void deinit(void) override;
        virtual Mesh *clone(void) override;
        
        void clear(void);
    };
    
}

#endif /* _cMesh_h_ */
