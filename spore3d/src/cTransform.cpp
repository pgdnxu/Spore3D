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

#include "cTransform.h"
#include "cObjectManager.h"

#include <iostream>

namespace Spore3D {
    
    CoreObject *Transform::Create(const std::string &name) {
        return new Transform(name);
    }
    
    void Transform::Destory(CoreObject* transform) {
        Component::Destory(transform);
    }
    
    void Transform::registerComponentTypes() {
        ObjectManager::getInstance()->registerComponentType(Transform::getComponentTypeId(), Transform::Create, Transform::Destory, TRANSFORM_TYPE_NAME);
    }
    
    void Transform::init() {
        Component::init();
    }
    
    void Transform::deinit() {

    }
    
    ComponentTypeId Transform::getComponentTypeId(void) {
        static Hash _componentTypeId(TRANSFORM_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Transform::Transform(const std::string &name) : Component(name) {
    }
    
    Transform::~Transform() {
        
    }
    
}
