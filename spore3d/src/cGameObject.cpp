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

#include "cGameObject.h"
#include "cTransform.h"
#include "uDebug.h"

namespace Spore3D {

    GameObject::GameObject(const std::string &name, std::vector<Component*> &componentList)
    : CoreObject(name), transform(nullptr), m_CurrScene(nullptr) {
        for (const auto &component : componentList) {
            addComponent(component);
        }
    }
    
    GameObject::GameObject(const std::string &name, bool isRaw)
    : CoreObject(name), transform(nullptr), m_CurrScene(nullptr) {
        ObjectManager::getInstance()->addGameObject(this);
        if (!isRaw)
            this->transform = static_cast<Transform*>(this->addComponent<Transform>());
        
    }
    
    GameObject::~GameObject() {
        Debug::log("GameObject::~GameObject() "+toString());
    }
    
    void GameObject::deinit(void) {
        ObjectManager::getInstance()->removeGameObject(getInstanceId());
    }
    
    GameObject *GameObject::clone(void) {
        return cloneFromComponent(Component::TypeId());
    }
    
    GameObject *GameObject::cloneFromComponent(ComponentTypeId typeId) {
        GameObject *newObject = _clone();
        if (nullptr == newObject) return nullptr;
        std::vector<Component*> cmpList;
        ObjectManager::getInstance()->getComponents(getInstanceId(), cmpList);
        for (const auto &it : cmpList) {
            if (it->getTypeId() != typeId) {
                Component *newCmp = it->cloneFromGameObject();
                if(!ObjectManager::getInstance()->addComponentWithComponent(newObject->getInstanceId(), newCmp)) {
                    std::string errStr = "clone GameObject:";
                    errStr.append(newObject->toString()).append("<").append(std::to_string(newObject->getInstanceId())).append("> failed. [clone Component failed.]");
                    Debug::err(errStr);
                }
            }
        }
        newObject->transform = newObject->getComponent<Transform>();
        return newObject;
    }
    
    GameObject *GameObject::_clone(void) {
        GameObject *rawGameObject = new GameObject(toString()+"_clone", true);
        return rawGameObject;
    }
    
    Component *GameObject::getComponentInChildren(const ComponentTypeId typeId) const {
        return nullptr == transform ? nullptr : transform->getComponentInChildren(typeId);
    }
    
    Component *GameObject::getComponentInChildren(const std::string &typeName) const {
        return nullptr == transform ? nullptr : transform->getComponentInChildren(typeName);
    }
    
    void GameObject::getComponentsInChildren(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        if (nullptr != transform) {
            transform->getComponentsInChildren(typeId, componentList);
        }
        
    }
    
    void GameObject::getComponentsInChildren(const std::string &typeName, std::vector<Component*> &componentList) const {
        if (nullptr != transform) {
            transform->getComponentsInChildren(typeName, componentList);
        }
    }
    
    Component *GameObject::getComponentInParent(const ComponentTypeId typeId) const {
        return nullptr == transform ? nullptr : transform->getComponentInParent(typeId);
    }
    
    Component *GameObject::getComponentInParent(const std::string &typeName) const {
        return nullptr == transform ? nullptr : transform->getComponentInParent(typeName);
    }
    
    
    void GameObject::getComponentsInParent(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        if (nullptr != transform) {
            transform->getComponentsInParent(typeId, componentList);
        }
    }
    
    void GameObject::getComponentsInParent(const std::string &typeName, std::vector<Component*> &componentList) const {
        if (nullptr != transform) {
            transform->getComponentsInParent(typeName, componentList);
        }
    }
    
    GameObject *GameObject::Find(const std::string&) {
        return nullptr;
    }
    
    bool GameObject::isActiveInHierarchy(void) const {
        if (nullptr == transform) return false;
        Transform *parent = transform->getParent();
        if (nullptr != parent && nullptr != parent->gameObject) {
            return m_ActiveSelf && parent->gameObject->isActiveInHierarchy();
        }
        return m_ActiveSelf;
    }
    
    void GameObject::testUpdate(void) {
        if (toString() == "Warrior") {
            Quaternion q = transform->getRotation();
            transform->setRotation(Quaternion(0, q.eulerAngle().y+5, 0));
        } else if (toString() == "Warrior_clone") {
            if (getInstanceId()%3==0) {
                Quaternion q = transform->getRotation();
                transform->setRotation(Quaternion(0, q.eulerAngle().y-2, 0));
            } else if (getInstanceId()%3==1) {
                Quaternion q = transform->getRotation();
                transform->setRotation(Quaternion(0, q.eulerAngle().y+1, 0));
            }
        }
    }
}
