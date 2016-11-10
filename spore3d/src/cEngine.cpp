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

#include "cEngine.h"
#include "uDebug.h"
#include "glfwWindow.h"
#include "cObjectManager.h"
#include "cDestoryPool.h"
#include "cSceneManager.h"
#include "cScene.h"
#include "cGameObject.h"
#include "cCamera.h"
#include "cTransform.h"
#include "uMath.h"
#include "cShaderManager.h"
#include "cMeshFilter.h"
#include "cMesh.h"
#include "uObjMtl.h"
#include "uObjMeshLoader.h"

namespace Spore3D {
    
    Engine *Engine::getInstance() {
        static Engine _instance;
        return &_instance;
    }
    
    Engine::_ObjectCreate Engine::_objectCreate;
    
    Engine::_ObjectCreate::_ObjectCreate() {
        Engine::getInstance();
    }
    
    Engine::Engine() : m_MainWindow(nullptr) {
    }
    
    Engine::~Engine() {
        
    }
    
    void Engine::deinit(void) {
        delete m_MainWindow;
        m_MainWindow = nullptr;
        
        SceneManager::getInstance()->unloadAllScenes();
        m_MainScene = nullptr;
        
        ShaderManager::getInstance()->deinit();
        
        DestoryPool::getInstance()->destoryAll();
    }
    
    void Engine::proc(void) {
        
    }
    
    int Engine::run(int argc, char *argv[]) {
        if (nullptr == m_MainWindow) return -1;
        
        while(!m_MainWindow->closed()) {
            proc();
            m_MainWindow->update();
            DestoryPool::getInstance()->destoryAll();
        }
        
        deinit();
        
        return 0;
    }
    
    bool Engine::init(const char *name, int width, int height) {
        if (nullptr == m_MainWindow) {
            m_MainWindow = new GlfwWindow(name , width, height);
            if (nullptr == m_MainWindow) {
                Debug::err("Engine init failed: MainWindow is NULL.");
                return false;
            }
        }
        
        if (!ObjectManager::getInstance()->init()) {
            Debug::err("Engine init failed: ObjectManager init failed.");
            return false;
        }
        
        // init root scene
        m_MainScene = SceneManager::getInstance()->createScene("MainScene");
        if (nullptr == m_MainScene) {
            Debug::err("Engine init failed: RootScene is NULL.");
            return false;
        }
        if (!SceneManager::getInstance()->setActiveScene(m_MainScene)) {
            Debug::err("Engine init failed: set active scene failed.");
            return false;
        }
        
        // init main camera
        GameObject *mainCamera = new GameObject("MainCameraObject");
        mainCamera->addComponent<Camera>();
        mainCamera->getComponent<Transform>()->setPosition(Vec3(20,20,20)).lookAt(Vec3(0,0,0), Vec3::Up);
        m_MainScene->addRootGameObject(mainCamera);
        
        
        //test code
        GameObject *warrior = new GameObject("Warrior");
        Mesh *mesh = new Spore3D::Mesh("chr_sword");
        ObjMtl om;
        ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/chr_sword", "chr_sword.obj", *mesh, om);
        warrior->addComponent<MeshFilter>()->setMesh(mesh);
        m_MainScene->addRootGameObject(warrior);
        
        return true;
    }
}
