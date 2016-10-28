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
#include "cComponent.h"
#include "cObjectManager.h"
#include "cGameObject.h"

namespace Spore3D {
    
    CoreObject *Component::_alloc_obj(const std::string& name) {
        return new Component(name);
    }

    void Component::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(Component::TypeId(), Component::_alloc_obj, nullptr, COMPONENT_TYPE_NAME);
    }
    
    void Component::deinit(void) {
        gameObject = nullptr;
    }
    
    Component::Component(const std::string &name)
    : CoreObject(name), gameObject(nullptr), transform(nullptr) {
        m_ComponentTypeId = TypeId();
    }
    
    Component::~Component() {
        
    }
    
    ComponentTypeId Component::genTypeId(const std::string &typeName) {
        Hash _componentTypeId(typeName);
        return _componentTypeId.get();
    }
    
    ComponentTypeId	Component::TypeId(void) {
        static ComponentTypeId _cmpTypeId = genTypeId(COMPONENT_TYPE_NAME);
        return _cmpTypeId;
    }
    
    Component *Component::clone(void) {
        return nullptr;
    }
    
    Component *Component::cloneFromGameObject(void) {
        return nullptr;
    }
    
    Component *Component::getComponentInChildren(const ComponentTypeId typeId) const {
        return nullptr == gameObject ? nullptr : gameObject->getComponentInChildren(typeId);
    }
    
    Component *Component::getComponentInChildren(const std::string &typeName) const {
        return nullptr == gameObject ? nullptr : gameObject->getComponentInChildren(typeName);
    }
    
    void Component::getComponentsInChildren(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        if (nullptr != gameObject) {
            gameObject->getComponentsInChildren(typeId, componentList);
        }
    }
    
    void Component::getComponentsInChildren(const std::string &typeName, std::vector<Component*> &componentList) const {
        if (nullptr != gameObject) {
            gameObject->getComponentsInChildren(typeName, componentList);
        }
    }
    
    Component *Component::getComponentInParent(const ComponentTypeId typeId) const {
        return nullptr == gameObject ? nullptr : gameObject->getComponentInParent(typeId);
    }
    
    Component *Component::getComponentInParent(const std::string &typeName) const {
        return nullptr == gameObject ? nullptr : gameObject->getComponentInParent(typeName);
    }
    
    void Component::getComponentsInParent(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        if (nullptr != gameObject) {
            gameObject->getComponentsInParent(typeId, componentList);
        }
    }
    
    void Component::getComponentsInParent(const std::string &typeName, std::vector<Component*> &compoentList) const {
        if (nullptr != gameObject) {
            gameObject->getComponentsInParent(typeName, compoentList);
        }
    }
    
}
