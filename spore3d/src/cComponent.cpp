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
    
    ComponentTypeId	Component::TypeId(void) {
        static Hash _componentTypeId(COMPONENT_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Component *Component::clone(void) {
        return nullptr;
    }
    
    Component *Component::cloneFromGameObject(void) {
        return nullptr;
    }
    
}
