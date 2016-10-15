// *********************************************************************
//     ____                       _____ ____
//    / ___| _ __   ___  _ __ ___|___ /|  _ \  ___ ___  _ __ ___
//    \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |/ __/ _ \| '_ ` _ \
//     ___) | |_) | (_) | | |  __/___) | |_| | (_| (_) | | | | | |
//    |____/| .__/ \___/|_|  \___|____/|____(_)___\___/|_| |_| |_|
//          |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
//  --------------------------------------------------------------------
//
//  Copyright (C) 2016 Shannon Xu
//
//  This software is distributed under the terms of the MIT License.
//  A copy of the license may be obtained at: https://opensource.org/licenses/MIT
//
// .--. --. -.. -. .. -. ..-. --.-. --. -- .- .. .-.. .-.-.- -.-. --- --

#ifndef _cTransform_h_
#define _cTransform_h_

#include "cComponent.h"

namespace Spore3D {

    class ObjectManager;
    
    const std::string TRANSFORM_TYPE_NAME = "Transform";
    
    class Transform : public Component {
        friend ObjectManager;
        
    public:
        static CoreObject *Create(const std::string&);
        static void Destory(CoreObject*);
        
        static void registerComponentTypes();
        
        virtual void init();
        virtual void deinit();
        
        static ComponentTypeId getComponentTypeId(void);
        
    protected:
        Transform(const std::string&);
        virtual ~Transform();
        
    };
    
}

#endif /* _cTransform_h_ */
