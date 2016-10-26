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

#ifndef _cComponent_h_
#define _cComponent_h_

#include "uTypes.h"
#include "cObject.h"

namespace Spore3D {
    
    class GameObject;
    class Transform;
    
    static const std::string COMPONENT_TYPE_NAME = "Component";
    
    struct ComponentTypeInfo{
        CreationMethod      creationMethod;
        DestructionMethod   destructionMethod;
        ComponentTypeId     typeId;
        std::string         typeName;
    };
    
    class Component : public CoreObject {
        friend GameObject;
    public:
        
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        ComponentTypeId getTypeId(void) { return m_ComponentTypeId; }
        
        virtual void deinit(void);
    
        GameObject *gameObject;
        Transform *transform;
        
        virtual Component *cloneFromGameObject(void);
        
    protected:
        Component(const std::string&);
        virtual ~Component();
        virtual Component *clone(void);
        
        ComponentTypeId m_ComponentTypeId;
        
    private:
        static CoreObject *_alloc_obj(const std::string&);
    };
    
}

#endif /* _cComponent_h_ */
