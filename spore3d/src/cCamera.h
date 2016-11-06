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

#ifndef _cCamera_h_
#define _cCamera_h_

#include <vector>

#include "cBehaviour.h"
#include "uTypes.h"

namespace Spore3D {
    
    const std::string CAMERA_TYPE_NAME = "Camera";
    
    class Camera : public Behaviour {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        static std::vector<Camera*> allCameras(void);
        static uint32 allCamerasCount(void);
        //TODO : static Camera *current(void);
        //TODO : static Gamera *main(void);
        
    protected:
        Camera(const std::string&);
        virtual ~Camera();
        virtual Camera *clone(void) override;
        virtual Camera *cloneFromGameObject(void) override;
        
    private:
        static CoreObject *_alloc_obj(const std::string&);
    };
    
}

#endif /* _cCamera_h_ */
