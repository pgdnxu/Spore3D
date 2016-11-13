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

#include "cScene.h"
#include "cObject.h"
#include "cRenderer.h"
#include "cCamera.h"

namespace Spore3D {
    
    Scene::~Scene() {
        unload();
    }
    
    std::vector<GameObject*> Scene::getRootGameObjects() const {
        std::vector<GameObject*> ret;
        getRootGameObjects(ret);
        return ret;
    }
    
    void Scene::getRootGameObjects(std::vector<GameObject*> &rootGameObjectList) const {
        for (const auto &it : m_RootGameObjectMap) {
            rootGameObjectList.push_back(it.second);
        }
    }
    
    size_t Scene::getRootCount(void) const {
        return m_RootGameObjectMap.size();
    }
    
    void Scene::unload(void) {
        for (const auto &it : m_RootGameObjectMap) {
            if (!it.second->isDontDestroyOnLoad()) {
                CoreObject::Destory(it.second);
            }
        }
        m_RootGameObjectMap.clear();
        m_MainCamera = nullptr;
    }
    
    void Scene::setMainCamera(Camera *camera) {
        if (nullptr == camera) return;
        if (camera->isEnable()) {
            m_MainCamera = camera;
        }
    }
    
    void Scene::addRootGameObject(GameObject *gameObject) {
        if (nullptr != gameObject) {
            if (nullptr == m_MainCamera) {
                setMainCamera(gameObject->getComponent<Camera>());
            }
            m_RootGameObjectMap[gameObject->getInstanceId()] = gameObject;
        }
    }
    void Scene::removeRootGameObject(GameObject *gameObject) {
        if (nullptr != gameObject) {
            m_RootGameObjectMap.erase(gameObject->getInstanceId());
            Camera *camera = gameObject->getComponent<Camera>();
            if (nullptr != camera) {
                if (nullptr == m_MainCamera || m_MainCamera->getInstanceId() == camera->getInstanceId()) {
                    m_MainCamera = nullptr;
                    for (const auto &it : m_RootGameObjectMap) {
                        setMainCamera(it.second->getComponent<Camera>());
                        if (nullptr != m_MainCamera) break;
                    }
                }
            }
        }
    }
    
    bool Scene::isRootGameObject(GameObject *gameObject) const {
        if (nullptr == gameObject) return false;
        return m_RootGameObjectMap.find(gameObject->getInstanceId()) != m_RootGameObjectMap.end();
    }
    
    void Scene::render(void) {
        for (const auto &it : m_RootGameObjectMap) {
            Renderer *renderer = it.second->getComponent<Renderer>();
            if (nullptr != renderer) {
                renderer->render();
            }
        }
    }
    
    void Scene::update(void) {
        for (const auto &it : m_RootGameObjectMap) {
            it.second->testUpdate();
        }
    }
    
}
