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

#include "cCamera.h"
#include "cTransform.h"

namespace Spore3D {
    
    CoreObject *Camera::_alloc_obj(const std::string& name) {
        return new Camera(name);
    }
    
    void Camera::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(Camera::TypeId(), Camera::_alloc_obj, nullptr, CAMERA_TYPE_NAME);
    }
    
    ComponentTypeId Camera::TypeId(void) {
        static Hash _componentTypeId(CAMERA_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    Camera::Camera(const std::string &name)
    : Behaviour(name), clearFlags(Nothing) {
        m_ComponentTypeId = TypeId();
    }
    
    Camera::~Camera() {
        
    }
    
    Camera *Camera::clone(void) {
        return nullptr;
    }
    
    Camera *Camera::cloneFromGameObject(void) {
        return nullptr;
    }
    
    std::vector<Camera*> Camera::allCameras(void) {
        std::vector<Camera*> ret;
        return ret;
    }
    
    uint32 Camera::allCamerasCount(void) {
        return 0;
    }
    
    Mat4 Camera::getCameraToWorldMatrix(void) const {
        if (nullptr != gameObject) {
            Transform *transform = gameObject->getComponent<Transform>();
            if (nullptr != transform) {
                return transform->getLocalToWorldMatrix();
            }
        }
        return Mat4(math::NO_INIT);
    }
    
}
