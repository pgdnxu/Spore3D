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
        
        for (const auto &it : m_ChildernList) {
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
    : Component(name), m_Parent(nullptr), m_PositionHasChanged(false), m_RotationHasChanged(false) {
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
            m_RotationHasChanged = true;
            m_PositionHasChanged = true;
        }
    }
    
    bool Transform::addChild(Transform *child) {
        if (nullptr == child)
            return false;
        GameObject *go = child->gameObject;
        if (nullptr == go)
            return false;
        if (m_ChildrenIndexMap.find(go->toString()) != m_ChildrenIndexMap.end())
            return false;
        m_ChildernList.push_back(child);
        m_ChildrenIndexMap[go->toString()] = (uint32)(m_ChildernList.size()-1);
        return true;
    }
    
    void Transform::removeChild(const std::string &childName) {
        if (m_ChildrenIndexMap.find(childName) != m_ChildrenIndexMap.end()) {
            uint32 index = m_ChildrenIndexMap[childName];
            m_ChildrenIndexMap.erase(childName);
            m_ChildernList[index] = nullptr;
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
        for (const auto &it : m_ChildernList) {
            it->detachChildren();
        }
        m_ChildernList.clear();
        m_ChildrenIndexMap.clear();
    }
    
    Transform *Transform::find(const std::string &childName) {
        if (childName.length() <= 0) return nullptr;
        size_t index = childName.find('/');
        if (std::string::npos == index) {
            if (m_ChildrenIndexMap.find(childName) != m_ChildrenIndexMap.end()) {
                return getChild(m_ChildrenIndexMap[childName]);
            }
        } else {
            std::string currName = childName.substr(0, index);
            if (currName.length() > 0 && m_ChildrenIndexMap.find(currName) != m_ChildrenIndexMap.end()) {
                return getChild(m_ChildrenIndexMap[currName])->find(childName.substr(index + 1, childName.length()));
            }
        }
        return nullptr;
    }
    
    Transform *Transform::getChild(const uint32 index) {
        if (index >= getChildCount()) return nullptr;
        return m_ChildernList[index];
    }
    
    Mat4 Transform::getLocalToWorldMatrix(void) const {
        return Mat4::TransMat(getPosition()) * Mat4::RotMat(getRotation());
    }
    
    Mat4 Transform::getWorldToLocalMatrix(void) const {
        return Mat4::RotMat(getRotation().conjugate()) * Mat4::TransMat(-getPosition()) ;
    }
    
    Vec3 Transform::transformPoint(const Vec3 &point) const {
        return getWorldToLocalMatrix() * point;
    }
    
    Vec3 Transform::inverseTransformPoint(const Vec3 &point) const {
        return getLocalToWorldMatrix() * point;
    }
    
    Vec3 Transform::transformDirection(const Vec3 &dir) const {
        return Mat4::RotMat(getRotation().conjugate()) * dir;
    }
    
    Vec3 Transform::inverseTransformDirection(const Vec3 &dir) const {
        return Mat4::RotMat(getRotation()) * dir;
    }
    
    Component *Transform::getComponentInChildren(const ComponentTypeId typeId) const {
        Component *ret = getComponent(typeId);
        if (nullptr != ret) return ret;
        for (const auto &it : m_ChildernList) {
            if ((ret = it->getComponentInChildren(typeId)) != nullptr) break;
        }
        return ret;
    }
    
    Component *Transform::getComponentInChildren(const std::string &typeName) const {
        return getComponentInChildren(genTypeId(typeName));
    }
    
    void Transform::getComponentsInChildren(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        Component *rslt = getComponent(typeId);
        if (nullptr != rslt) componentList.push_back(rslt);
        for (const auto &it : m_ChildernList) {
            it->getComponentsInParent(typeId, componentList);
        }
    }
    
    void Transform::getComponentsInChildren(const std::string &typeName, std::vector<Component*> &componentList) const {
        getComponentsInChildren(genTypeId(typeName), componentList);
    }
    
    Component *Transform::getComponentInParent(const ComponentTypeId typeId) const {
        Component *ret = getComponent(typeId);
        if (nullptr != ret) return ret;
        if (nullptr != m_Parent) {
            return m_Parent->getComponentInParent(typeId);
        }
        return nullptr;
    }
    
    Component *Transform::getComponentInParent(const std::string &typeName) const  {
        return getComponentInParent(genTypeId(typeName));
    }
    
    void Transform::getComponentsInParent(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
        Component *rslt = getComponent(typeId);
        if (nullptr != rslt) componentList.push_back(rslt);
        if (nullptr != m_Parent) {
            m_Parent->getComponentsInParent(typeId, componentList);
        }
    }
    
    void Transform::getComponentsInParent(const std::string &typeName, std::vector<Component*> &componentList) const {
        return getComponentsInParent(genTypeId(typeName), componentList);
    }
    
    void Transform::setPosition(const Vec3 &position) {
        setLocalPosition(m_LocalPosition + m_Parent->transformDirection(position - getPosition()));
    }
    
    void Transform::setRotation(const Quaternion &rotation) {
        if (nullptr != m_Parent) {
            setLocalRotation(m_Parent->getRotation().inversed() * (rotation * getRotation()));
        } else {
            setLocalRotation(rotation * getLocalRotation());
        }
    }
    
    void Transform::setLocalPosition(const Vec3 &localPosition) {
        m_PositionHasChanged = true;
        m_LocalPosition = localPosition;
    }
    
    void Transform::setLocalRotation(const Quaternion &localRotation) {
        m_RotationHasChanged = true;
        m_LocalRotation = localRotation;
    }
    
    Vec3 Transform::getPosition(void) const {
        if (m_PositionHasChanged) {
            if (nullptr == m_Parent) {
                m_Position = m_LocalPosition;
            } else {
                m_Position = m_Parent->inverseTransformPoint(m_LocalPosition);
            }
            m_PositionHasChanged = false;
        }
        return m_Position;
    }
    
    Quaternion Transform::getRotation(void) const {
        if (m_RotationHasChanged) {
            if (nullptr == m_Parent) {
                m_Rotation = m_LocalRotation;
            } else {
                m_Rotation = m_Parent->getRotation() * m_LocalRotation;
            }
            m_RotationHasChanged = false;
        }
        return m_Rotation;
    }
    
    void Transform::translate(const Vec3 &translation, Space relativeTo) {
        if (Space::Self == relativeTo) {
            setLocalPosition(getLocalPosition() + translation);
        } else if (Space::World == relativeTo) {
            if (nullptr != m_Parent) {
                setLocalPosition(getLocalPosition() + m_Parent->transformDirection(translation));
            } else {
                setLocalPosition(getLocalPosition() + translation);
            }
        }
    }
    
    void Transform::translate(const float x, const float y, const float z, Space relativeTo) {
        translate(Vec3(x, y, z), relativeTo);
    }
    
    void Transform::translate(const Vec3 &translation, Transform *relativeTo) {
        if (nullptr == relativeTo) {
            // world space
            translate(translation, Space::World);
        } else {
            if (nullptr != m_Parent) {
                setLocalPosition(getLocalPosition() + m_Parent->transformDirection(relativeTo->inverseTransformDirection(translation)));
            } else {
                setLocalPosition(getLocalPosition() + relativeTo->inverseTransformDirection(translation));
            }
            
        }
    }
    
    void Transform::translate(const float x, const float y, const float z, Transform *relativeTo) {
        translate(Vec3(x, y, z), relativeTo);
    }
    
    void Transform::rotate(const Vec3 &eulerAngles, Space relativeTo) {
        if (Space::Self == relativeTo) {
            setLocalRotation(Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z) * getLocalRotation());
        } else if (Space::World == relativeTo) {
            if (nullptr != m_Parent) {
                setLocalRotation(m_Parent->getRotation().inversed() * (Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z) * getRotation()));
            } else {
                setLocalRotation(Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z) * getLocalRotation());
            }
        }
    }
    
    void Transform::rotate(const float xAngle, const float yAngle, const float zAngle, Space relativeTo) {
        rotate(Vec3(xAngle, yAngle, zAngle), relativeTo);
    }
    
    void Transform::rotate(const Vec3 &axis, const float angle, Space relativeTo) {
        Vec3 naxis(axis);
        naxis.normalize();
        if (Space::Self == relativeTo) {
            setLocalRotation((Mat4(getLocalRotation()) * Mat4::RotMat(naxis, angle)).getQuaternion());
        } else if (Space::World == relativeTo) {
            if (nullptr != m_Parent) {
                setLocalRotation((Mat4::RotMat(m_Parent->transformDirection(naxis), angle) * Mat4(getLocalRotation())).getQuaternion());
            } else {
                setLocalRotation((Mat4(getLocalRotation()) * Mat4::RotMat(naxis, angle)).getQuaternion());
            }
        }
    }
    
    void Transform::rotateAround(const Vec3 &point, const Vec3 &axis, float angle) {
        
    }
    
    void Transform::lookAt(const Vec3 &worldPosition, const Vec3 &worldUp) {
        
    }
    
    void Transform::lookAt(const Transform *target, const Vec3 &worldUp) {
        if (nullptr != target) {
            lookAt(target->getPosition(), worldUp);
        }
    }
}
