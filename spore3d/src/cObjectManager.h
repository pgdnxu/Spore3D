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
    typedef std::map<ComponentTypeId, ComponentTypeInfo*> ComponentTypeInfoMap;
    typedef std::map<CObjectId, std::vector<Component*>> ObjectComponentMap;
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
        Component   *addComponentWithComponentTypeName(const CObjectId, const std::string&);
        void        getComponentByComponentTypeId(const CObjectId, const ComponentTypeId, std::vector<Component*>&) const;
        void        getComponentByComponentTypeName(const CObjectId, const std::string&, std::vector<Component*>&) const;
        
        void getComponents(const CObjectId, std::vector<Component*>&) const;
        void getGameObjects(const ComponentTypeId, std::vector<GameObject*>&) const;
        
        void removeComponentByComponentTypeId(const CObjectId, const ComponentTypeId);
        void removeComponentByComponentTypeName(const CObjectId, const std::string&);
        void removeComponentByObjectId(const CObjectId);
        
        void addGameObject(GameObject*);
        void removeGameObject(const CObjectId);
        
        Component *createComponent(const ComponentTypeId);
        
        void init(void);
        ~ObjectManager() { /* TODO : deinit! */ delete m_DB; }
    private:
        struct _ObjectCreate {
            
            _ObjectCreate();
        
        };
        static _ObjectCreate _objectCreate;
        
        ObjectManagerDB *m_DB;
        ObjectManager() : m_DB(nullptr) {};
        
        static void registerAllComponentTypes(void);
        
    };
    
}

#endif /* _cObjectManager_h_ */
