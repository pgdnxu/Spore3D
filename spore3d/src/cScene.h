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
#ifndef _cScene_h_
#define _cScene_h_

#include <vector>
#include <string>
#include <map>

#include "cGameObject.h"
#include "uTypes.h"

namespace Spore3D {
    
    class SceneManager;
    class Camera;
    
    class Scene {
        friend SceneManager;
    public:
        Scene(const std::string &name) : m_Name(name),m_MainCamera(nullptr) {}
        
        std::vector<GameObject*> getRootGameObjects() const;
        void getRootGameObjects(std::vector<GameObject*>&) const;
        bool isRootGameObject(GameObject*) const;
        size_t getRootCount(void) const;
        
        bool isLoaded(void) const { return m_IsLoaded; }
        void unload(void);
        
        void addRootGameObject(GameObject*);
        void removeRootGameObject(GameObject*);
        
        const std::string &getName(void) const { return m_Name; }
        
        void render(void);
        
        Camera *getMainCamera(void) { return m_MainCamera; }
        
        void update(void);
        
    private:
        bool m_IsLoaded;

        Camera *m_MainCamera;
        
        std::map<CObjectId, GameObject*> m_RootGameObjectMap;
        std::string m_Name;
        ~Scene();
        
        void setMainCamera(Camera*);
    };
    
}

#endif /* _cScene_h_ */
