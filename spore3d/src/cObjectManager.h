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

#ifndef _cObjectManager_h_
#define _cObjectManager_h_

#include <map>
#include <vector>

#include "uTypes.h"
#include "cObject.h"


namespace Spore3D {
    
    class Component;
    struct ComponentTypeInfo;
    class CoreObject;
    class GameObject;
    
    typedef std::map<CObjectId, CoreObject*> ObjectMap;
    typedef std::map<ComponentTypeId, ComponentTypeInfo> ComponentTypeInfoMap;
    typedef std::map<CObjectId, Component*> ObjectComponentMap;
    typedef std::map<ComponentTypeId, ObjectComponentMap> ComponentMap;
    
    struct ObjectManagerDB {
        ObjectMap               mObjectMap;
        ComponentTypeInfoMap    mComponentTypeInfoMap;
        ComponentMap            mComponentTypeToComponentMap;
    };
    
    class ObjectManager {
        
    public:
        static ObjectManager *getInstance();
        
        void registerComponentType(const ComponentTypeId, const CreationMethod, const DestructionMethod, const std::string&);
        
        Component *addComponentWithComponentTypeId(const CObjectId, const ComponentTypeId);
        Component *getComponentByComponentTypeId(const CObjectId, const ComponentTypeId);
        Component *addComponentWithComponentName(const CObjectId, const std::string&);
        Component *getComponentByComponentName(const CObjectId, const std::string&);
    
        void removeComponentByComponentTypeId(const CObjectId, const ComponentTypeId);
        void removeComponentByComponentName(const CObjectId, const std::string&);
        void removeComponentByObjectId(const CObjectId);
        
        void addGameObject(GameObject*);
        void removeGameObject(const CObjectId);
        
        void init();
    private:
        struct _ObjectCreate {
            
            _ObjectCreate();
        
        };
        static _ObjectCreate _objectCreate;
        
        ObjectManagerDB *m_DB;
        ObjectManager() : m_DB(nullptr) {};
        
        Component *createComponent(const ComponentTypeId);
        
        static void registerAllComponentTypes();
        
    };
    
}

#endif /* _cObjectManager_h_ */
