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

#ifndef _cSceneManager_h_
#define _cSceneManager_h_

#include <string>
#include <vector>

#include "uTypes.h"

namespace Spore3D {
    
    class Scene;
    class GameObject;
    
    class SceneManager {
        
    public:
        static SceneManager *getInstance(void);
        
        Scene *createScene(const std::string&);
        Scene *getActiveScene(void) const;
        Scene *getSceneAt(const int32) const;
        Scene *getSceneByName(const std::string&) const;
        void moveGameObjectToScene(GameObject*, Scene*);
        bool setActiveScene(Scene*);
        bool unloadScene(const std::string&);
        bool unloadScene(Scene*);
        size_t getSceneCount(void) const { return m_SceneList.size(); }
        
        ~SceneManager() { /* TODO: deinit! */ }
        
    private:
        struct _ObjectCreate {
            
            _ObjectCreate();
            
        };
        static _ObjectCreate _objectCreate;
        
        SceneManager() : m_CurrActiveSceneIndex(-1) {}
        
//        int32 getSceneIndex(const Scene*) const;
//        int32 getSceneIndex(const std::string&) const;

        int32 m_CurrActiveSceneIndex;
        std::vector<Scene*> m_SceneList;
        
    };
    
}

#endif /* _cSceneManager_h_ */
