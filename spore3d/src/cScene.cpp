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

#include "cObject.h"
#include "cScene.h"

namespace Spore3D {
    
    Scene::~Scene() {
        unload();
    }
    
    std::vector<GameObject*> Scene::getRootGameObjects() const {
//        return m_RootGameObjectList;
        std::vector<GameObject*> ret;
        getRootGameObjects(ret);
        return ret;
    }
    
    void Scene::getRootGameObjects(std::vector<GameObject*> &rootGameObjectList) const {
//        rootGameObjectList = m_RootGameObjectList;
        for (const auto &it : m_RootGameObjectMap) {
            rootGameObjectList.push_back(it.second);
        }
    }
    
    size_t Scene::getRootCount(void) const {
        return m_RootGameObjectMap.size();
    }
    
    void Scene::unload(void) {
//        for (const auto &gameObject : m_RootGameObjectList) {
//            if (!gameObject->isDontDestroyOnLoad()) {
//                CoreObject::Destory(gameObject);
//            }
//        }
//        m_RootGameObjectIteratorMap.clear();
//        m_RootGameObjectList.clear();
        for (const auto &it : m_RootGameObjectMap) {
            if (!it.second->isDontDestroyOnLoad()) {
                CoreObject::Destory(it.second);
            }
        }
        m_RootGameObjectMap.clear();
    }
    
    void Scene::addRootGameObject(GameObject *gameObject) {
        if (nullptr != gameObject) {
//            m_RootGameObjectList.push_back(gameObject);
//            std::vector<GameObject*>::const_iterator last = m_RootGameObjectList.end();
//            m_RootGameObjectIteratorMap[gameObject->getInstanceId()] = --last;
            m_RootGameObjectMap[gameObject->getInstanceId()] = gameObject;
        }
    }
    void Scene::removeRootGameObject(GameObject *gameObject) {
        if (nullptr != gameObject) {
//            auto it = m_RootGameObjectIteratorMap.find(gameObject->getInstanceId());
//            if (it != m_RootGameObjectIteratorMap.end()) {
//                m_RootGameObjectList.erase(it->second);
//                m_RootGameObjectIteratorMap.erase(it);
//            }
            m_RootGameObjectMap.erase(gameObject->getInstanceId());
        }
    }
    
    bool Scene::isRootGameObject(GameObject *gameObject) const {
        if (nullptr == gameObject) return false;
        return m_RootGameObjectMap.find(gameObject->getInstanceId()) != m_RootGameObjectMap.end();
    }
    
}
