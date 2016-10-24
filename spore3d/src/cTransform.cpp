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

namespace Spore3D {
    
    CoreObject *Transform::_alloc_obj(const std::string &name) {
        return new Transform(name);
    }
    
    void Transform::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(Transform::TypeId(), Transform::_alloc_obj, nullptr, TRANSFORM_TYPE_NAME);
    }
    
    Transform *Transform::clone(void) {
        //TODO :
        return nullptr;
    }
    
    Transform *Transform::cloneFromGameObject(void) {
        Transform *newTransform = new Transform(toString());
        
        newTransform->m_Parent = nullptr;
        newTransform->m_Position = m_Position;
        newTransform->m_Rotation = m_Rotation;
        newTransform->m_EulerAngle = m_EulerAngle;
        newTransform->m_LocalPosition = m_LocalPosition;
        newTransform->m_LocalRotation = m_LocalRotation;
        newTransform->m_LocalEulerAngle = m_LocalEulerAngle;
        
        //TODO: child
        
        return newTransform;
    }
    
    void Transform::deinit(void) {
        Component::deinit();
    }
    
    ComponentTypeId Transform::TypeId(void) {
        static Hash _componentTypeId(TRANSFORM_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Transform::Transform(const std::string &name)
    : Component(name), m_Parent(nullptr){
        m_ComponentTypeId = TypeId();
    }
    
    Transform::~Transform() {
        
    }
    
    
}
