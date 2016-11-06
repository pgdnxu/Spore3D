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

#include "cObjectManager.h"
#include "cGameObject.h"
#include "uHash.h"

#include "cComponent.h"
#include "cTransform.h"
#include "cMeshFilter.h"
#include "cCamera.h"

namespace Spore3D {
    
    ObjectManager *ObjectManager::getInstance() {
        static ObjectManager _instance;
        return &_instance;
    }
    
    ObjectManager::_ObjectCreate ObjectManager::_objectCreate;
    
    ObjectManager::_ObjectCreate::_ObjectCreate() {
        ObjectManager::getInstance();
    }
    
    void ObjectManager::init(void) {
        if (nullptr != m_DB) {
            delete m_DB;
        }
        m_DB = new ObjectManagerDB();

        registerAllComponentTypes();
    }
    
    bool ObjectManager::addComponentWithComponent(const CObjectId objectId, Component *component) {
        if (nullptr == component) return false;
        if (m_DB->mObjectMap.find(objectId) == m_DB->mObjectMap.end()) return nullptr;
        if (m_DB->mComponentTypeInfoMap.find(component->getTypeId()) == m_DB->mComponentTypeInfoMap.end()) return false;
        component->gameObject = m_DB->mObjectMap[objectId];
        component->transform = component->gameObject->transform;
        m_DB->mComponentTypeToComponentMap[component->getTypeId()][objectId].push_back(component);
        return true;
    }
    
    Component *ObjectManager::addComponentWithComponentTypeId(const CObjectId objectId, const ComponentTypeId typeId) {
        if (m_DB->mObjectMap.find(objectId) == m_DB->mObjectMap.end()) return nullptr;
//        ComponentTypeInfoMap::iterator it = m_DB->mComponentTypeInfoMap.find(typeId);
        auto it = m_DB->mComponentTypeInfoMap.find(typeId);
        if (it == m_DB->mComponentTypeInfoMap.end()) return nullptr;
        Component *cmp = static_cast<Component*>((*(it->second->creationMethod))(it->second->typeName));
        if (nullptr == cmp) return nullptr;
        cmp->gameObject = m_DB->mObjectMap[objectId];
        cmp->transform = cmp->gameObject->transform;
        m_DB->mComponentTypeToComponentMap[typeId][objectId].push_back(cmp);
        return cmp;
    }
    
    Component *ObjectManager::addComponentWithComponentTypeName(const CObjectId objectId, const std::string &typeName) {
        Hash typeId(typeName);
        return addComponentWithComponentTypeId(objectId, typeId.get());
    }
    
    void ObjectManager::getComponentByComponentTypeId(const CObjectId objectId, const ComponentTypeId typeId, std::vector<Component *> &componentList) const {
        if (m_DB->mObjectMap.find(objectId) == m_DB->mObjectMap.end()) return;
        if (m_DB->mComponentTypeToComponentMap.find(typeId) == m_DB->mComponentTypeToComponentMap.end()) return;
        componentList = m_DB->mComponentTypeToComponentMap[typeId][objectId];
    }
    
    void ObjectManager::getComponentByComponentTypeName(const CObjectId objectId, const std::string &typeName, std::vector<Component *> &componentList) const {
        return getComponentByComponentTypeId(objectId, Component::genTypeId(typeName), componentList);
    }
    
    void ObjectManager::getComponents(const CObjectId objectId, std::vector<Component*> &componentList) const {
        if (m_DB->mObjectMap.find(objectId) == m_DB->mObjectMap.end()) return;
        for (const auto &it : m_DB->mComponentTypeToComponentMap) {
            if (it.second.find(objectId) != it.second.end()) {
                componentList.insert(componentList.end(), it.second.at(objectId).begin(), it.second.at(objectId).end());
            }
        }
    }
    void ObjectManager::getGameObjects(const ComponentTypeId typeId, std::vector<GameObject*> &gameObjectList) const {
        if (m_DB->mComponentTypeToComponentMap.find(typeId) == m_DB->mComponentTypeToComponentMap.end()) return;
        for (const auto &it : m_DB->mComponentTypeToComponentMap.at(typeId)) {
            gameObjectList.push_back(m_DB->mObjectMap.at(it.first));
        }
    }
    
    void ObjectManager::removeComponentByComponentTypeId(const CObjectId objectId, const ComponentTypeId typeId) {
        m_DB->mComponentTypeToComponentMap[typeId].erase(objectId);
    }
    
    void ObjectManager::removeComponentByComponentTypeName(const CObjectId objectId, const std::string& typeName) {
        Hash typeId(typeName);
        return removeComponentByComponentTypeId(objectId, typeId.get());
    }
    
    void ObjectManager::removeComponentByObjectId(const CObjectId objectId) {
        if (m_DB->mObjectMap.find(objectId) == m_DB->mObjectMap.end()) return;
        for (auto &it : m_DB->mComponentTypeToComponentMap) {
            if (it.second.find(objectId) != it.second.end()) {
                for (const auto &c : it.second.at(objectId)) {
                    CoreObject::Destory(c);
                }
                it.second.erase(objectId);
            }
        }
    }
    
    void ObjectManager::addGameObject(GameObject *gameObject) {
        if (nullptr != gameObject) {
            m_DB->mObjectMap[gameObject->getInstanceId()] = gameObject;
        }
    }
    
    void ObjectManager::removeGameObject(const CObjectId objectId) {
        removeComponentByObjectId(objectId);
        m_DB->mObjectMap.erase(objectId);
    }
    
    void ObjectManager::registerComponentType(const ComponentTypeId typeId, const CreationMethod creationMethod, const DestructionMethod destructionMethod, const std::string &typeName) {
//        ComponentTypeInfo &info = m_DB->mComponentTypeInfoMap[typeId];
//        info.creationMethod = creationMethod;
//        info.destructionMethod = destructionMethod;
//        info.typeId = typeId;
//        info.typeName = typeName;
        
        ComponentTypeInfo *newComponentTypeInfo =new ComponentTypeInfo();
        newComponentTypeInfo->creationMethod = creationMethod;
        newComponentTypeInfo->destructionMethod = destructionMethod;
        newComponentTypeInfo->typeId = typeId;
        newComponentTypeInfo->typeName = typeName;
        m_DB->mComponentTypeInfoMap[typeId] = newComponentTypeInfo;
        
    }
    
    void ObjectManager::registerAllComponentTypes(void) {
        Component::registerComponentTypes();
        Transform::registerComponentTypes();
        MeshFilter::registerComponentTypes();
//        Camera::registerComponentTypes();
    }
    
    Component *ObjectManager::createComponent(const ComponentTypeId typeId) {
//        ComponentTypeInfoMap::iterator it = m_DB->mComponentTypeInfoMap.find(typeId);
        auto it = m_DB->mComponentTypeInfoMap.find(typeId);
        if (it == m_DB->mComponentTypeInfoMap.end())
            return nullptr;
        return static_cast<Component*>((*(it->second->creationMethod))(it->second->typeName));
    }
    
}
