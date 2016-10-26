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

#include <iostream>

#include "cTransform.h"
#include "cObjectManager.h"
#include "cGameObject.h"

namespace Spore3D {
    
    CoreObject *Transform::_alloc_obj(const std::string &name) {
        return new Transform(name);
    }
    
    void Transform::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(Transform::TypeId(), Transform::_alloc_obj, nullptr, TRANSFORM_TYPE_NAME);
    }
    
    Transform *Transform::clone(void) {
        
        Transform *newTransform = cloneFromGameObject();
        GameObject *relGameObject = nullptr;
        if (nullptr != gameObject) {
            relGameObject = gameObject->cloneFromComponent(getTypeId());
            ObjectManager::getInstance()->addComponentWithComponent(relGameObject->getInstanceId(), newTransform);
        }
        
        return newTransform;
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
        
        for (const auto &it : m_ChilderList) {
            Transform *newChild = Instantiate<Transform>(it);
            newTransform->addChild(newChild);
        }
        
        return newTransform;
    }
    
    void Transform::deinit(void) {
        if (nullptr != m_Parent) {
            m_Parent->removeChild(this);
        }
        Component::deinit();
    }
    
    ComponentTypeId Transform::TypeId(void) {
        static Hash _componentTypeId(TRANSFORM_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Transform::Transform(const std::string &name)
    : Component(name), m_Parent(nullptr), hasChanged(false) {
        m_ComponentTypeId = TypeId();
    }
    
    Transform::~Transform() {
        
    }
    
    void Transform::setParent(Transform *parent, bool worldPositionStays) {
        if (nullptr == parent)
            return;
        m_Parent = parent;
        parent->addChild(this);
        if (worldPositionStays) {
            setLocalPosition(parent->transformPoint(getLocalPosition()));
            setLocalRotation((parent->getRotation()).conjugate() * getLocalRotation());
        } else {
            setPosition(Mat4::TransMat(parent->getPosition())*Mat4::RotMat(parent->getRotation())*m_Position);
            setRotation(getRotation() * parent->getRotation());
        }
    }
    
    bool Transform::addChild(Transform *child) {
        if (nullptr == child)
            return false;
        GameObject *go = child->gameObject;
        if (nullptr == go)
            return false;
        if (m_ChildreIndexMap.find(go->toString()) != m_ChildreIndexMap.end())
            return false;
        m_ChilderList.push_back(child);
        m_ChildreIndexMap[go->toString()] = (uint32)(m_ChilderList.size()-1);
        return true;
    }
    
    void Transform::removeChild(const std::string &childName) {
        if (m_ChildreIndexMap.find(childName) != m_ChildreIndexMap.end()) {
            uint32 index = m_ChildreIndexMap[childName];
            m_ChildreIndexMap.erase(childName);
            m_ChilderList[index] = nullptr;
        }
    }
    
    void Transform::removeChild(Transform *child) {
        if (nullptr == child)
            return;
        GameObject *go = child->gameObject;
        if (nullptr != go) {
            removeChild(go->toString());
        }
    }
    
    void Transform::removeFromParent() {
        if (nullptr == m_Parent)
            return;
        m_Parent->removeChild(this);
        m_Parent = nullptr;
    }
    
    void Transform::detachChildren(void) {
        for (const auto &it : m_ChilderList) {
            it->detachChildren();
        }
        m_ChilderList.clear();
        m_ChildreIndexMap.clear();
    }
    
    Transform *Transform::find(const std::string &childName) {
        if (m_ChildreIndexMap.find(childName) != m_ChildreIndexMap.end()) {
            return getChild(m_ChildreIndexMap[childName]);
        }
        return nullptr;
    }
    
    Transform *Transform::getChild(const uint32 index) {
        if (index >= getChildCount()) return nullptr;
        return m_ChilderList[index];
    }
    
    Mat4 Transform::getLocalToWorldMatrix(void) const {
        return Mat4::RotMat(m_Rotation) * Mat4::TransMat(m_Position);
    }
    
    Mat4 Transform::getWorldToLocalMatrix(void) const {
        return Mat4::RotMat(m_Rotation.conjugate()) * Mat4::TransMat(-m_Position);
    }
    
    Vec3 Transform::transformPoint(const Vec3 &point) const {
        return getWorldToLocalMatrix() * point;
    }
    
    Vec3 Transform::inverseTransformPoint(const Vec3 &point) const {
        return getLocalToWorldMatrix() * point;
    }
    
    Vec3 Transform::transformDirection(const Vec3 &dir) const {
        return Mat4::RotMat(m_Rotation.conjugate()) * dir;
    }
    
    Vec3 Transform::inverseTransformDirection(const Vec3 &dir) const {
        return Mat4::RotMat(m_Rotation) * dir;
    }
    
}
