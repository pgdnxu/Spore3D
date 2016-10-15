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

namespace Spore3D {
    
    CoreObject *Component::Create(const std::string &name) {
        return new Component(name);
    }
    
    void Component::Destory(CoreObject *component) {
        CoreObject::Destory(component);
    }
    
    void Component::init() {
        CoreObject::init();
    }

    void Component::registerComponentTypes() {
        ObjectManager::getInstance()->registerComponentType(Component::getComponentTypeId(), Component::Create, Component::Destory, COMPONENT_TYPE_NAME);
    }
    
    void Component::deinit() {
        CoreObject::deinit();
    }
    
    Component::Component(const std::string &name) : CoreObject(name) {

    }
    
    Component::~Component() {
        
    }
    
    ComponentTypeId	Component::getComponentTypeId(void) {
        static Hash _componentTypeId(COMPONENT_TYPE_NAME);
        return _componentTypeId.get();
    }
    
}
