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

#ifndef _cComponent_h_
#define _cComponent_h_

#include <vector>

#include "uTypes.h"
#include "cObject.h"
#include "cGameObject.h"

namespace Spore3D {
    
    class Transform;
    class ObjectManager;
    
    const std::string COMPONENT_TYPE_NAME = "Component";
    
    struct ComponentTypeInfo{
        CreationMethod      creationMethod;
        DestructionMethod   destructionMethod;
        ComponentTypeId     typeId;
        std::string         typeName;
    };
    
    class Component : public CoreObject {
        friend GameObject;
        friend ObjectManager;
    public:
        
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        ComponentTypeId getTypeId(void) { return m_ComponentTypeId; }
        
        virtual void deinit(void) override;
        
        template<typename T>
        T *getComponent(void) const {
            return nullptr == gameObject ? nullptr : gameObject->getComponent<T>();
        }
        Component *getComponent(const std::string &typeName) const {
            return nullptr == gameObject ? nullptr : gameObject->getComponent(typeName);
        }
        Component *getComponent(const ComponentTypeId typeId) const {
            return nullptr == gameObject ? nullptr : gameObject->getComponent(typeId);
        }
        template<typename T>
        void getComponents(std::vector<Component*> &componentList) const {
            if (nullptr != gameObject) {
                gameObject->getComponents<T>(componentList);
            }
        }
        
        void getComponents(const std::string &typeName, std::vector<Component*> &componentList) const {
            if (nullptr != gameObject) {
                gameObject->getComponents(typeName, componentList);
            }
        }
        
        void getComponents(const ComponentTypeId typeId, std::vector<Component*> &componentList) const {
            if (nullptr != gameObject) {
                gameObject->getComponents(typeId, componentList);
            }
        }
        
        virtual Component *getComponentInChildren(const ComponentTypeId) const;
        virtual Component *getComponentInChildren(const std::string&) const;
        
        virtual void getComponentsInChildren(const ComponentTypeId, std::vector<Component*>&) const;
        virtual void getComponentsInChildren(const std::string&, std::vector<Component*>&) const;
        
        virtual Component *getComponentInParent(const ComponentTypeId) const;
        virtual Component *getComponentInParent(const std::string&) const;
        
        virtual void getComponentsInParent(const ComponentTypeId, std::vector<Component*>&) const;
        virtual void getComponentsInParent(const std::string&, std::vector<Component*>&) const;
        
        
        GameObject *gameObject;
        Transform *transform;
    protected:
        Component(const std::string&);
        virtual ~Component();
        virtual Component *clone(void) override;
        virtual Component *cloneFromGameObject(void);
        
        ComponentTypeId m_ComponentTypeId;
        static ComponentTypeId genTypeId(const std::string&);
        
    private:
        static CoreObject *_alloc_obj(const std::string&);

    };
    
}

#endif /* _cComponent_h_ */
