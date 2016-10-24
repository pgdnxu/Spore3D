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

#include "cComponent.h"
#include "cObjectManager.h"
#include "cGameObject.h"

namespace Spore3D {
    
    CoreObject *Component::_alloc_obj(const std::string& name) {
        return new Component(name);
    }

    void Component::registerComponentTypes() {
        ObjectManager::getInstance()->registerComponentType(Component::getComponentTypeId(), Component::_alloc_obj, nullptr, COMPONENT_TYPE_NAME);
    }
    
    void Component::deinit() {
        ObjectManager::getInstance()->removeComponentByComponentTypeId(gameObject->getInstanceId(), getComponentTypeId());
        gameObject = nullptr;
    }
    
    Component::Component(const std::string &name)
    : CoreObject(name), gameObject(nullptr), transform(nullptr) {
        m_ComponentTypeId = getComponentTypeId();
    }
    
    Component::~Component() {
        
    }
    
    ComponentTypeId	Component::getComponentTypeId(void) {
        static Hash _componentTypeId(COMPONENT_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Component *Component::clone() {
        //TODO : implementation
        return nullptr;
    }
    
}
