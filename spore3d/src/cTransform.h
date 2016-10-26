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
    
    static const std::string TRANSFORM_TYPE_NAME = "Transform";
    
    class Transform : public Component {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        virtual void deinit(void);
        
        void setParent(Transform *parent) { setParent(parent, false); }
        void setParent(Transform *parent, bool worldPositionStays);
        Transform *getParent() const { return m_Parent; }
        
        void setPosition(const Vec3 &position) { m_Position = position; hasChanged = true; }
        void setRotation(const Quaternion &rotation) { m_Rotation = rotation; m_EulerAngle = m_Rotation.eulerAngle(); hasChanged = true; }
        void setLocalPosition(const Vec3 &localPosition) { m_LocalPosition = localPosition; hasChanged = true; }
        void setLocalRotation(const Quaternion &localRotation) { m_LocalRotation = localRotation; m_LocalEulerAngle = m_LocalRotation.eulerAngle(); hasChanged = true; }
        
        Vec3 getPosition(void) const { return m_Position; }
        Quaternion getRotation(void) const { return m_Rotation; }
        Vec3 getEulerAngle(void) const { return m_EulerAngle; }
        Vec3 getLocalPosition(void) const { return m_LocalPosition; }
        Quaternion getLocalRotation(void) const { return m_LocalRotation; }
        Vec3 getLocalEulerAngle(void) const { return m_LocalEulerAngle; }
        Vec3 getForward(void) const { return Mat4(m_Rotation) * Vec3(0, 0, 1); }
        Vec3 getUp(void) const { return Mat4(m_Rotation) * Vec3(0, 1, 0); }
        Vec3 getRight(void) const { return Mat4(m_Rotation) * Vec3(1, 0, 0); }
        
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
        uint32 getChildCount(void) const { return (uint32)m_ChilderList.size(); };
        void detachChildren(void);
        Transform *find(const std::string&);
        Transform *getChild(const uint32);
        
        bool hasChanged;
    protected:
        Transform(const std::string&);
        virtual ~Transform();
        virtual Transform *clone(void);
        virtual Transform *cloneFromGameObject(void);
        
    private:
        Transform *m_Parent;
        
        Vec3 m_Position;
        Quaternion m_Rotation;
        Vec3 m_EulerAngle;
        
        Vec3 m_LocalPosition;
        Quaternion m_LocalRotation;
        Vec3 m_LocalEulerAngle;
        
        static CoreObject *_alloc_obj(const std::string&);
        
        std::map<std::string, uint32> m_ChildreIndexMap;
        std::vector<Transform*> m_ChilderList;
    };
    
}

#endif /* _cTransform_h_ */
