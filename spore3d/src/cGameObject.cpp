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
    
    GameObject::GameObject(const std::string &name, bool isRaw) : CoreObject(name), transform(nullptr) {
        ObjectManager::getInstance()->addGameObject(this);
        if (!isRaw)
            this->transform = static_cast<Transform*>(this->addComponent<Transform>());
        
    }
    
    GameObject::~GameObject() {
        Debug::log("GameObject::~GameObject()");
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
        std::vector<Component*> cmpList = ObjectManager::getInstance()->getAllComponents(getInstanceId());
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
        return newObject;
    }
    
    GameObject *GameObject::_clone(void) {
        GameObject *rawGameObject = new GameObject(toString(), true);
        return rawGameObject;
    }
}
