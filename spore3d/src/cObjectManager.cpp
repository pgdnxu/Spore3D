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

#include "cObjectManager.h"
#include "cGameObject.h"
#include "uHash.h"

#include "cComponent.h"
#include "cTransform.h"

namespace Spore3D {
    
    ObjectManager *ObjectManager::getInstance() {
        static ObjectManager _instance;
        return &_instance;
    }
    
    ObjectManager::_ObjectCreate ObjectManager::_objectCreate;
    
    ObjectManager::_ObjectCreate::_ObjectCreate() {
        ObjectManager::getInstance();
    }
    
    void ObjectManager::init() {
        if (nullptr != m_DB) {
            delete m_DB;
        }
        m_DB = new ObjectManagerDB();

        registerAllComponentTypes();
    }
    
    Component *ObjectManager::addComponentWithComponentTypeId(const CObjectId objectId, const ComponentTypeId typeId) {
        CoreObject *obj = m_DB->mObjectMap[objectId];
        if (nullptr == obj) return nullptr;
        ComponentTypeInfoMap::iterator it = m_DB->mComponentTypeInfoMap.find(typeId);
        if (it == m_DB->mComponentTypeInfoMap.end())
            return nullptr;
        Component *cmp = getComponentByComponentTypeId(objectId, typeId);
        if (nullptr != cmp) {
            ((*(it->second.destructionMethod))(cmp));
        }
        cmp = static_cast<Component*>((*(it->second.creationMethod))(it->second.typeName));
        if (nullptr == cmp) return nullptr;
        cmp->init();
        cmp->gameObject = static_cast<GameObject*>(obj);
        m_DB->mComponentTypeToComponentMap[typeId][objectId] = cmp;
        
        return cmp;
    }
    
    Component *ObjectManager::getComponentByComponentTypeId(const CObjectId objectId, const ComponentTypeId typeId) {
        return m_DB->mComponentTypeToComponentMap[typeId][objectId];
    }
    
    Component *ObjectManager::addComponentWithComponentName(const CObjectId objectId, const std::string &componentName) {
        Hash typeId(componentName);
        return addComponentWithComponentTypeId(objectId, typeId.get());
    }
    
    Component *ObjectManager::getComponentByComponentName(const CObjectId objectId, const std::string &componentName) {
        Hash typeId(componentName);
        return getComponentByComponentTypeId(objectId, typeId.get());
    }

    void ObjectManager::registerComponentType(const ComponentTypeId typeId, const CreationMethod creationMethod, const DestructionMethod destructionMethod, const std::string &typeName) {
        ComponentTypeInfo &info = m_DB->mComponentTypeInfoMap[typeId];
        info.creationMethod = creationMethod;
        info.destructionMethod = destructionMethod;
        info.typeId = typeId;
        info.typeName = typeName;
        
    }
    
    void ObjectManager::registerAllComponentTypes() {
        Component::registerComponentTypes();
        Transform::registerComponentTypes();
    }
    
    Component *ObjectManager::createComponent(const ComponentTypeId typeId) {
        ComponentTypeInfoMap::iterator it = m_DB->mComponentTypeInfoMap.find(typeId);
        if (it == m_DB->mComponentTypeInfoMap.end())
            return nullptr;
        return static_cast<Component*>((*(it->second.creationMethod))(it->second.typeName));
    }
    
//    CoreObject *ObjectManager::createObject(const std::string &name) {
//        CoreObject *co = CoreObject::Create(name);
//        if (nullptr != co) {
//            co->init();
//            m_DB->mObjectMap[co->getInstanceId()] = co;
//        }
//        return co;
//    }
    
    GameObject *ObjectManager::createGameObject(const std::string &name) {
        GameObject *go = static_cast<GameObject*>(GameObject::Create(name));
        if (nullptr != go) {
            go->init();
            m_DB->mObjectMap[go->getInstanceId()] = go;
            go->addComponent<Transform>();
            go->transform = go->getComponent<Transform>();
        }
        return go;
    }
    
    void ObjectManager::destoryObject(CoreObject *co) {
        if (nullptr != co) {
            m_DB->mObjectMap.erase(co->getInstanceId());
            CoreObject::Destory(co);
        }
    }
    
}
