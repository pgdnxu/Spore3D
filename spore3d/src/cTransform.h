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

#ifndef _cTransform_h_
#define _cTransform_h_

#include "cComponent.h"
#include "uMath.h"

namespace Spore3D {

    class ObjectManager;
    
    const std::string TRANSFORM_TYPE_NAME = "Transform";
    
    class Transform : public Component {
        friend ObjectManager;
        
    public:
        static CoreObject *Create(const std::string&);
        static void Destory(CoreObject*);
        static void registerComponentTypes();
        static ComponentTypeId getComponentTypeId(void);
        
        virtual void init();
        virtual void deinit();
        
        
        void setParent(Transform *);
        
        void setPosition(const Vec3&);
        void setRotation(const Quaternion&);
        void setLocalPosition(const Vec3&);
        void setLocalRotation(const Quaternion&);
        
        Vec3 getPosition() const;
        Quaternion getRotation() const;
        Vec3 getEulerAngle() const;
        
        Vec3 getLocalPosition() const;
        Quaternion getLocalRotation() const;
        Vec3 getLocalEulerAngle() const;
        
        
    private:
        Transform(const std::string&);
        virtual ~Transform();
        
        Transform *m_Parent;
        
        Vec3 m_Position;
        Quaternion m_Rotation;
        Vec3 m_EulerAngle;
        
        Vec3 m_LocalPosition;
        Quaternion m_LocalRotation;
        Vec3 m_LocalEulerAngle;
        
    };
    
}

#endif /* _cTransform_h_ */
