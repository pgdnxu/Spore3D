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

#include "cSceneManager.h"
#include "cScene.h"

namespace Spore3D {
    
    SceneManager *SceneManager::getInstance() {
        static SceneManager _instance;
        return &_instance;
    }
    
    SceneManager::_ObjectCreate SceneManager::_objectCreate;
    
    SceneManager::_ObjectCreate::_ObjectCreate() {
        SceneManager::getInstance();
    }
    
    Scene *SceneManager::createScene(const std::string &sceneName) {
        if (nullptr != getSceneByName(sceneName)) return nullptr;
        Scene *newScene = new Scene(sceneName);
        if (nullptr != newScene) m_SceneList.push_back(newScene);
        return newScene;
    }
    
    Scene *SceneManager::getActiveScene(void) const {
//        return nullptr;
        return m_SceneList.at(m_CurrActiveSceneIndex);
    }
    
    Scene *SceneManager::getSceneAt(const int32 index) const {
        if (index >= 0 && index < getSceneCount())
            return m_SceneList.at(index);
        return nullptr;
    }
    
    Scene *SceneManager::getSceneByName(const std::string &sceneName) const {
        for (const auto &it : m_SceneList) {
            if (it->getName() == sceneName) return it;
        }
        return nullptr;
    }
    
    void SceneManager::moveGameObjectToScene(GameObject *gameObject, Scene *scene) {
        if (nullptr == gameObject) return;
    }
    
    bool SceneManager::setActiveScene(Scene *scene) {
        if (nullptr == scene) return false;
        return true;
    }
    
    bool SceneManager::unloadScene(const std::string &sceneName) {
        return unloadScene(getSceneByName(sceneName));
        
    }
    
    bool SceneManager::unloadScene(Scene *scene) {
        if (nullptr == scene) return false;
        auto it = m_SceneList.begin();
        for (;it != m_SceneList.end(); it++) {
            if (*it == scene) break;
        }
        if (it != m_SceneList.end()) {
            m_SceneList.erase(it);
            (*it)->unload();
            return true;
        }
        return false;
    }
    
//    int32 SceneManager::getSceneIndex(const Scene *scene) const {
//        if (nullptr == scene) return -1;
//        return getSceneIndex(scene->getName());
//    }
//    
//    int32 SceneManager::getSceneIndex(const std::string &sceneName) const {
//        int32 index = -1;
//        for (const auto &it : m_SceneList) {
//            ++index;
//            if (it->getName() == sceneName) break;
//        }
//        return index;
//    }
    
}
