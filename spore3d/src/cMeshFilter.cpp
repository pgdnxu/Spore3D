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

#include <memory>
#include "cMeshFilter.h"
#include "cObjectManager.h"
#include "cMesh.h"
#include "cGameObject.h"
#include "uDebug.h"

namespace Spore3D {
    
    CoreObject *MeshFilter::_alloc_obj(const std::string &name) {
        return new MeshFilter(name);
    }
    
    void MeshFilter::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(MeshFilter::TypeId(), MeshFilter::_alloc_obj, nullptr, MESHFILTER_TYPE_NAME);
    }
    
    ComponentTypeId MeshFilter::TypeId(void) {
        static Hash _componentTypeId(MESHFILTER_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    MeshFilter *MeshFilter::clone(void) {
        MeshFilter *newMeshFilter = cloneFromGameObject();
        GameObject *relGameObject = nullptr;
        if (nullptr != gameObject) {
            relGameObject = gameObject->cloneFromComponent(getTypeId());
            ObjectManager::getInstance()->addComponentWithComponent(relGameObject->getInstanceId(), newMeshFilter);
        }
        
        return newMeshFilter;
    }
    
    MeshFilter *MeshFilter::cloneFromGameObject(void) {
        Debug::log("MeshFilter *MeshFilter::cloneFromGameObject(void)");
        
        MeshFilter *newMeshFilter = new MeshFilter(toString());
        
        newMeshFilter->m_Mesh = nullptr;
        newMeshFilter->m_SharedMesh = getSharedPtrMesh();
        
        return newMeshFilter;
    }
    
    void MeshFilter::deinit(void) {
        Destory(m_Mesh);
        Component::deinit();
    }
    
    MeshFilter::MeshFilter(const std::string &name)
    : Component(name), m_Mesh(nullptr), m_SharedMesh(nullptr) {
        m_ComponentTypeId = TypeId();
    }
    
    MeshFilter::~MeshFilter() {
        Debug::log("MeshFilter::~MeshFilter() "+toString());
    }
    
    Mesh *MeshFilter::getMesh(void) {
        if (nullptr == m_Mesh) {
            if (nullptr == m_SharedMesh) return nullptr;
            m_Mesh = Instantiate<Mesh>(m_SharedMesh.get());
        }
        return m_Mesh;
    }
    
    void MeshFilter::setMesh(Mesh *mesh) {
        if (nullptr == m_Mesh && nullptr == m_SharedMesh) {
            m_Mesh = mesh;
        }
    }
    std::shared_ptr<Mesh> MeshFilter::getSharedPtrMesh(void) {
        if (m_SharedMesh == nullptr) {
            if (nullptr == m_Mesh) return nullptr;
            Mesh *copy = Instantiate<Mesh>(m_Mesh);
            m_SharedMesh = std::shared_ptr<Mesh>(copy, Destory);
        }
        return m_SharedMesh;
    }
    Mesh *MeshFilter::getSharedMesh() {
        return getSharedPtrMesh().get();
    };
}
