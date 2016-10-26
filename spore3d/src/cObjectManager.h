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
    
    typedef std::map<CObjectId, GameObject*> ObjectMap;
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
        static ObjectManager *getInstance(void);
        
        void registerComponentType(const ComponentTypeId, const CreationMethod, const DestructionMethod, const std::string&);
        
        bool        addComponentWithComponent(const CObjectId, Component*);
        Component   *addComponentWithComponentTypeId(const CObjectId, const ComponentTypeId);
        Component   *addComponentWithComponentName(const CObjectId, const std::string&);
        Component   *getComponentByComponentTypeId(const CObjectId, const ComponentTypeId) const;
        Component   *getComponentByComponentName(const CObjectId, const std::string&) const;
        std::vector<Component*> getAllComponents(const CObjectId) const;
        std::vector<GameObject*> getAllObjects(const ComponentTypeId) const;
        
        void removeComponentByComponentTypeId(const CObjectId, const ComponentTypeId);
        void removeComponentByComponentName(const CObjectId, const std::string&);
        void removeComponentByObjectId(const CObjectId);
        
        void addGameObject(GameObject*);
        void removeGameObject(const CObjectId);
        
        void init(void);
    private:
        struct _ObjectCreate {
            
            _ObjectCreate();
        
        };
        static _ObjectCreate _objectCreate;
        
        ObjectManagerDB *m_DB;
        ObjectManager() : m_DB(nullptr) {};
        
        Component *createComponent(const ComponentTypeId);
        
        static void registerAllComponentTypes(void);
        
    };
    
}

#endif /* _cObjectManager_h_ */
