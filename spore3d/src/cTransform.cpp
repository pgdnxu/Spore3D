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
    
    Transform::Transform(const std::string &name)
    : Component(name), m_Parent(nullptr){
    }
    
    Transform::~Transform() {
        
    }
    
    void Transform::setParent(Transform *) {
        
    }
    
    void Transform::setPosition(const Vec3 &position) {
        
    }
    
    void Transform::setRotation(const Quaternion &rotation) {
        
    }
    
    void Transform::setLocalPosition(const Vec3 &localPosition) {
        
    }
    
    void Transform::setLocalRotation(const Quaternion &localRotation) {
        
    }
    
    Vec3 Transform::getPosition() const {
        return m_Position;
    }
    
    Quaternion Transform::getRotation() const {
        return m_Rotation;
    }
    
    Vec3 Transform::getEulerAngle() const {
        return m_EulerAngle;
    }
    
    Vec3 Transform::getLocalPosition() const {
        return m_LocalPosition;
    }
    
    Quaternion Transform::getLocalRotation() const {
        return m_LocalRotation;
    }
    
    Vec3 Transform::getLocalEulerAngle() const {
        return m_LocalEulerAngle;
    }
    
}
