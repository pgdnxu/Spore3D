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

#ifndef _cGameObject_h_
#define _cGameObject_h_

#include "cObject.h"
#include "uTypes.h"
#include "cObjectManager.h"

namespace Spore3D {
    
    class Component;
    class Transform;
    class MeshFilter;
    
    class GameObject : public CoreObject {
        friend ObjectManager;
        friend Component;
        friend Transform;
        friend MeshFilter;
    public:
        template<typename T>
        T *addComponent(void) {
            return static_cast<T*>(ObjectManager::getInstance()->addComponentWithComponentTypeId(this->getInstanceId(), T::TypeId()));
        }
        
        template<typename T>
        T *getComponent(void) const {
            return static_cast<T*>(ObjectManager::getInstance()->getComponentByComponentTypeId(this->getInstanceId(), T::TypeId()));
        }
        
        Component *addComponent(const std::string &componentName) {
            return ObjectManager::getInstance()->addComponentWithComponentName(this->getInstanceId(), componentName);
        }
        
        Component *getComponent(const std::string &componentName) const {
            return ObjectManager::getInstance()->getComponentByComponentName(this->getInstanceId(), componentName);
        }
        
        Component *addComponent(const ComponentTypeId componentTypeId) {
            return ObjectManager::getInstance()->addComponentWithComponentTypeId(this->getInstanceId(), componentTypeId);
        }
        
        Component *getComponent(const ComponentTypeId componentTypeId) const {
            return ObjectManager::getInstance()->getComponentByComponentTypeId(this->getInstanceId(), componentTypeId);
        }
        
        GameObject(const std::string&, bool isRaw = false);
        
        virtual void deinit(void);
        
        Transform *transform;
        
    protected:
        virtual ~GameObject();
        virtual GameObject *clone(void);
        virtual GameObject *cloneFromComponent(ComponentTypeId);
        
    private:
        GameObject *_clone(void);
    };
    
}

#endif /* _cGameObject_h_ */
