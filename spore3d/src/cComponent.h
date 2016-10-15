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

#ifndef _cComponent_h_
#define _cComponent_h_

#include "uTypes.h"
#include "cObject.h"

namespace Spore3D {
    
    class GameObject;
    class ObjectManager;
    
    const std::string COMPONENT_TYPE_NAME = "Component";
    
    struct ComponentTypeInfo{
        CreationMethod      creationMethod;
        DestructionMethod   destructionMethod;
        ComponentTypeId     typeId;
        std::string         typeName;
    };
    
    class Component : public CoreObject {
        friend ObjectManager;
    
    public:
        static CoreObject *Create(const std::string&);
        static void Destory(CoreObject *component);
        
        static void registerComponentTypes();
        
        virtual void init();
        virtual void deinit();

        static ComponentTypeId getComponentTypeId(void);
    
        GameObject *gameObject;
    
    protected:
        Component(const std::string&);
        virtual ~Component();
    };
    
}

#endif /* _cComponent_h_ */
