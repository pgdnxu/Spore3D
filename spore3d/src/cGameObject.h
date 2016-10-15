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

#ifndef _cGameObject_h_
#define _cGameObject_h_

#include "cObject.h"
#include "uTypes.h"
#include "cObjectManager.h"
#include "cComponent.h"

namespace Spore3D {
    
    class GameObject : public CoreObject {
    public:
        template<typename T>
        Component *addComponent() {
            return ObjectManager::getInstance()->addComponentWithComponentTypeId(this->getInstanceId(), T::getComponentTypeId());
        }
        
        template<typename T>
        Component *getComponent() const {
            return ObjectManager::getInstance()->getComponentByComponentTypeId(this->getInstanceId(), T::getComponentTypeId());
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
        
        static CoreObject *Create(const std::string&);
        
        virtual void init();
        virtual void deinit();
        
    protected:
        GameObject(const std::string&);
        virtual ~GameObject();
    };
    
}

#endif /* _cGameObject_h_ */
