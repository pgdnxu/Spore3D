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
            return static_cast<T*>(ObjectManager::getInstance()->addComponentWithComponentTypeId(getInstanceId(), T::TypeId()));
        }
        
        Component *addComponent(const std::string &typeName) {
            return ObjectManager::getInstance()->addComponentWithComponentTypeName(getInstanceId(), typeName);
        }
        
        Component *addComponent(const ComponentTypeId typeId) {
            return ObjectManager::getInstance()->addComponentWithComponentTypeId(getInstanceId(), typeId);
        }
        
        template<typename T>
        void getComponents(std::vector<Component*> &componentList) const {
            ObjectManager::getInstance()->getComponentByComponentTypeId(getInstanceId(), T::TypeId(), componentList);
        }
        
        void getComponents(const std::string &typeName, std::vector<Component*> &componentList) const {
            ObjectManager::getInstance()->getComponentByComponentTypeName(getInstanceId(), typeName, componentList);
        }
        
        void getComponents(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
            ObjectManager::getInstance()->getComponentByComponentTypeId(getInstanceId(), typeId, componentList);
        }
        
        template<typename T>
        T *getComponent(void) const {
            std::vector<Component*> componentList;
            getComponents<T>(componentList);
            return componentList.empty() ? nullptr : static_cast<T*>(componentList.front());
        }
        
        Component *getComponent(const std::string &typeName) const {
            std::vector<Component*> componentList;
            getComponents(typeName, componentList);
            return componentList.empty() ? nullptr : componentList.front();
        }
        
        Component *getComponent(const ComponentTypeId typeId) const {
            std::vector<Component*> componentList;
            getComponents(typeId, componentList);
            return componentList.empty() ? nullptr : componentList.front();
        }
        
        
        Component *getComponentInChildren(const ComponentTypeId) const;
        Component *getComponentInChildren(const std::string&) const;
        
        void getComponentsInChildren(const ComponentTypeId, std::vector<Component*>&) const;
        void getComponentsInChildren(const std::string&, std::vector<Component*>&) const;
        
        Component *getComponentInParent(const ComponentTypeId) const;
        Component *getComponentInParent(const std::string&) const;
        
        void getComponentsInParent(const ComponentTypeId, std::vector<Component*>&) const;
        void getComponentsInParent(const std::string&, std::vector<Component*>&) const;
        
        GameObject(const std::string&, bool isRaw = false);
        
        virtual void deinit(void) override;
        
        Transform *transform;
        
    protected:
        virtual ~GameObject();
        virtual GameObject *clone(void) override;
        virtual GameObject *cloneFromComponent(const ComponentTypeId);
        
    private:
        GameObject *_clone(void);
    };
    
}

#endif /* _cGameObject_h_ */
