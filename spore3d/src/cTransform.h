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

#ifndef _cTransform_h_
#define _cTransform_h_

#include <vector>
#include <map>

#include "cComponent.h"
#include "uMath.h"
#include "uTypes.h"

namespace Spore3D {
    
    const std::string TRANSFORM_TYPE_NAME = "Transform";
    
    enum Space{
        Self,
        World
    };
    
    class Transform : public Component {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        virtual void deinit(void) override;
        
        virtual Component *getComponentInChildren(const ComponentTypeId) const override;
        virtual Component *getComponentInChildren(const std::string&) const override;
        
        virtual void getComponentsInChildren(const ComponentTypeId, std::vector<Component*>&) const override;
        virtual void getComponentsInChildren(const std::string&, std::vector<Component*>&) const override;
        
        virtual Component *getComponentInParent(const ComponentTypeId) const override;
        virtual Component *getComponentInParent(const std::string&) const override;
        
        virtual void getComponentsInParent(const ComponentTypeId, std::vector<Component*>&) const override;
        virtual void getComponentsInParent(const std::string&, std::vector<Component*>&) const override;
        
        void setParent(Transform *parent) { setParent(parent, true); }
        void setParent(Transform *parent, bool worldPositionStays);
        Transform *getParent() const { return m_Parent; }
        
        void setPosition(const Vec3&);
        void setRotation(const Quaternion&);
        void setLocalPosition(const Vec3&);
        void setLocalRotation(const Quaternion&);
        
        Vec3 getPosition(void) const;
        Quaternion getRotation(void) const;
        
        Vec3 getEulerAngle(void) const { return m_EulerAngle; }
        Vec3 getLocalPosition(void) const { return m_LocalPosition; }
        Quaternion getLocalRotation(void) const { return m_LocalRotation; }
        Vec3 getLocalEulerAngle(void) const { return m_LocalEulerAngle; }
        Vec3 getForward(void) const { return Mat4(m_Rotation) * Vec3::forward; }
        Vec3 getUp(void) const { return Mat4(m_Rotation) * Vec3::up; }
        Vec3 getRight(void) const { return Mat4(m_Rotation) * Vec3::right; }
        
        Mat4 getLocalToWorldMatrix(void) const;
        Mat4 getWorldToLocalMatrix(void) const;
        Vec3 transformPoint(const Vec3&) const;
        Vec3 inverseTransformPoint(const Vec3&) const;
        Vec3 transformDirection(const Vec3&) const;
        Vec3 inverseTransformDirection(const Vec3&) const;
        
        bool addChild(Transform*);
        void removeChild(const std::string&);
        void removeChild(Transform*);
        void removeFromParent(void);
        uint32 getChildCount(void) const { return (uint32)m_ChildernList.size(); };
        void detachChildren(void);
        Transform *find(const std::string&);
        Transform *getChild(const uint32);
        
        bool hasChanged() const { return m_PositionHasChanged || m_RotationHasChanged; }
        
        void translate(const Vec3 &translation, Space relativeTo = Space::Self);
        void translate(const float x, const float y, const float z, Space relativeTo = Space::Self);
        void translate(const Vec3 &translation, Transform *relativeTo);
        void translate(const float x, const float y, const float z, Transform *relativeTo);
        
        void rotate(const Vec3 &eulerAngles, Space relativeTo = Space::Self);
        void rotate(const float xAngle, const float yAngle, const float zAngle, Space relativeTo = Space::Self);
        void rotate(const Vec3 &axis, const float angle, Space relativeTo = Space::Self);
        
        void rotateAround(const Vec3 &point, const Vec3 &axis, const float angle);
        
        void lookAt(const Transform *target);
        void lookAt(const Transform *target, const Vec3 &worldUp = Vec3::up);
        void lookAt(const Vec3 &worldPosition);
        void lookAt(const Vec3 &worldPosition, const Vec3 &worldUp = Vec3::up);
        
    protected:
        Transform(const std::string&);
        virtual ~Transform();
        virtual Transform *clone(void) override;
        virtual Transform *cloneFromGameObject(void) override;
        
    private:
        mutable bool m_PositionHasChanged;
        mutable bool m_RotationHasChanged;
        
        Transform *m_Parent;
        
        mutable Vec3 m_Position;
        mutable Quaternion m_Rotation;
        Vec3 m_EulerAngle;
        
        Vec3 m_LocalPosition;
        Quaternion m_LocalRotation;
        Vec3 m_LocalEulerAngle;
        
        void positionChanged(void);
        void rotationChanged(void);
        
        static CoreObject *_alloc_obj(const std::string&);
        
        std::map<std::string, uint32> m_ChildrenIndexMap;
        std::vector<Transform*> m_ChildernList;
        
    };
    
}

#endif /* _cTransform_h_ */
