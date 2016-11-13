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
#include "cRenderer.h"
#include "cShader.h"
#include "cMaterial.h"
#include "cRenderQueue.h"
#include "cBatchRenderer.h"
#include "cTexture.h"
#include "cTextureManager.h"

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
        Scene *currActiveScene = SceneManager::getInstance()->getActiveScene();
        if (nullptr != currActiveScene) {
            currActiveScene->update();
            currActiveScene->render();
        }
        RenderQueue::getInstance()->render();
    }
    
    int Engine::run(int argc, char *argv[]) {
        if (nullptr == m_MainWindow) return -1;
        BatchRenderer::getInstance()->init();
        while(!m_MainWindow->closed()) {
            m_MainWindow->clear();
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
        Camera *camera = mainCamera->addComponent<Camera>();
        Viewport vp = Viewport(0, 0, m_MainWindow->getWidth(), m_MainWindow->getHeight());
        camera->setFOV(60)->setHeight(vp.height)->setWidth(vp.width)->setFar(1000)->setNear(0);
        camera->setViewport(vp);
        camera->setBackgroundColor(Color::black);
        glViewport(vp.x, vp.y, vp.width*2, vp.height*2);
        mainCamera->transform->setPosition(Vec3(0,40,-50)).lookAt(Vec3(0,0,0), Vec3::Up);
        m_MainScene->addRootGameObject(mainCamera);
        
        
        //test code
        GameObject *warrior = new GameObject("Warrior");
        Mesh *mesh = new Spore3D::Mesh("chr_sword");
        ObjMtl om;
        ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/chr_sword", "chr_sword.obj", *mesh, om);
        warrior->addComponent<MeshFilter>()->setMesh(mesh);
        warrior->transform->setPosition(Vec3(0,0,-20));
        m_MainScene->addRootGameObject(warrior);
        Renderer *renderer = warrior->addComponent<Renderer>();
        ShaderManager::getInstance()->setPath("/Users/shannonxu/projects/spore3d/spore3d/shaders/");
        Shader *shader = ShaderManager::getInstance()->getShader("default");
        Material *material = new Material("dfltMaterial");
        material->setShader(shader);
        Texture *texture = TextureManager::getInstance()->getTexture("/Users/shannonxu/Desktop/chr_sword", "chr_sword.png");
        material->setTexture(texture);
        renderer->setMaterial(material);

        GameObject *terrain = new GameObject("Terrain");
        Mesh *meshT = new Spore3D::Mesh("monu9");
        ObjMtl omT;
        ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/monu9", "monu9.obj", *meshT, omT);
        terrain->addComponent<MeshFilter>()->setMesh(meshT);
        terrain->transform->setPosition(Vec3(0,0,30));
        m_MainScene->addRootGameObject(terrain);
        Renderer *rendererT = terrain->addComponent<Renderer>();
        ShaderManager::getInstance()->setPath("/Users/shannonxu/projects/spore3d/spore3d/shaders/");
//        Shader *shader = ShaderManager::getInstance()->getShader("default");
        Material *materialT = new Material("dfltMaterialT");
        materialT->setShader(shader);
        Texture *textureT = TextureManager::getInstance()->getTexture("/Users/shannonxu/Desktop/monu9", "monu9.png");
        materialT->setTexture(textureT);
        rendererT->setMaterial(materialT);
        
        
        for (int i = 0; i < 25; i++) {
            GameObject *warriorClone = CoreObject::Instantiate(warrior);
            warriorClone->transform->setPosition(Vec3((i%5)*20-40,0,(i/5+1)*20-10));
            m_MainScene->addRootGameObject(warriorClone);
        }
        
        warrior->transform->setRotation(Quaternion(0, 180, 0));
        
        return true;
    }
}
