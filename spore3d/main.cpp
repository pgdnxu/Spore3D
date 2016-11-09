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

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <map>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "uMath.h"
#include "cObject.h"
#include "uHash.h"
#include "cComponent.h"
#include "cObjectManager.h"
#include "cTransform.h"
#include "cGameObject.h"
#include "uPng.h"
#include "uObjMtl.h"
#include "uObjMeshLoader.h"
#include "uStringUtils.h"
#include "cDestoryPool.h"
#include "uDebug.h"
#include "cMeshFilter.h"
#include "cCamera.h"
#include "cSceneManager.h"
#include "cScene.h"
#include "cColor.h"
#include "cBounds.h"
#include "cShader.h"
#include "cShaderManager.h"

#include "glfwWindow.h"

#include "cEngine.h"

void transformTest2() {
    using namespace std;
    using namespace Spore3D;
    ObjectManager::getInstance()->init();
    GameObject *go1 = new GameObject("go1");
    GameObject *go2 = new GameObject("go2");
    GameObject *go3 = new GameObject("go3");
    Transform *t1 = go1->getComponent<Transform>();
    if (nullptr == t1) {
        Debug::err("go1 has no transform.");
        return;
    }
    
    Transform *t2 = go2->getComponent<Transform>();
    if (nullptr == t2) {
        Debug::err("go2 has no transform.");
        return;
    }
    
    Transform *t3 = go3->getComponent<Transform>();
    if (nullptr == t3) {
        Debug::err("go3 has no transform.");
        return;
    }
    
    //=======================================================
    
    t1->setLocalPosition(Vec3(1,1,1));
    t2->setLocalPosition(Vec3(1,2,1));
    t3->setLocalPosition(Vec3(1,1,3));
    
    t2->setParent(t1, false);
    t3->setParent(t2, false);
    
    t3->setLocalPosition(Vec3(2,3,4));
    t3->setLocalRotation(Quaternion(11, 22, 33));
    t1->setRotation(Quaternion(10, 20, 30));
    t3->setRotation(Quaternion(30, 20, 10));
    t2->setLocalRotation(Quaternion(10, 20, 30));
    t1->translate(Vec3(1,2,3), t3);
    
    cout<<t3->getRotation()<<endl;
    cout<<t3->getLocalRotation()<<endl;
    t1->rotate(Vec3(3,4,5), 43, Space::World);
    t3->rotate(Vec3(3,4,5), 43, Space::Self);
    
    cout<<t3->getRotation()<<endl;
    cout<<t3->getLocalRotation()<<endl;
    
    t2->rotate(Vec3(23,1,-0.32), 879.34f, Space::World);
    cout<<t2->getRotation()<<endl;
    cout<<t3->getRotation()<<endl;
    cout<<t3->getLocalRotation()<<endl;
    
    t2->setPosition(Vec3(1,2,3));
    cout<<t2->getLocalPosition()<<endl;
    
    cout<<t2->transformDirection(Vec3(1,2,3))<<endl;
    
    t3->rotateAround(Vec3(12,32,45), Vec3(23,4,1), 123);
    
    t3->lookAt(Vec3(24, 5, 23), Vec3(0, 1, 0));
    
    cout<<t3->getLocalToWorldMatrix()<<endl;
    cout<<t3->getWorldToLocalMatrix()<<endl;
    cout<<t3->getPosition()<<endl;
    cout<<t3->getLocalPosition()<<endl;
    cout<<t3->getRotation()<<endl;
    cout<<t3->getLocalRotation()<<endl;
//    
//    cout<<t3->getUp()<<endl;
//    cout<<t3->getRight()<<endl;
//    cout<<t3->getForward()<<endl;
    
    //=======================================================
    CoreObject::Destory(go1);
    CoreObject::Destory(go2);
    CoreObject::Destory(go3);
    DestoryPool::getInstance()->destoryAll();
}

void transformTest() {
    using namespace std;
    using namespace Spore3D;
    ObjectManager::getInstance()->init();
    GameObject *go1 = new GameObject("go1");
    GameObject *go2 = new GameObject("go2");
    GameObject *go3 = new GameObject("go3");
    
    //--------------------------------------------
    
    Transform *t1 = go1->getComponent<Transform>();
    if (nullptr == t1) {
        Debug::err("go1 has no transform.");
        return;
    }
    
    Transform *t2 = go2->getComponent<Transform>();
    if (nullptr == t2) {
        Debug::err("go2 has no transform.");
        return;
    }
    
    Transform *t3 = go3->getComponent<Transform>();
    if (nullptr == t3) {
        Debug::err("go3 has no transform.");
        return;
    }
    
//    t1->setPosition(Vec3(10, 10, 0));
    t1->setLocalPosition(Vec3(10, 10, 0));
    
//    t2->setPosition(Vec3(20, 20, 0));
    t2->setLocalPosition(Vec3(20, 20, 0));
    
    t2->setLocalRotation(Quaternion(0, 0, 90));
//    t1->setRotation(Quaternion::eulerAngle(0, 0, 0));
    
//    cout<<Quaternion::eulerAngle(degToRad(33), degToRad(44), degToRad(55))<<endl;
    
//    cout<<t1->getRotation()<<endl;
    
//    cout<<t2->getWorldToLocalMatrix()<<endl;
//    cout<<t2->getLocalToWorldMatrix()<<endl;
    
//    t1->setParent(t2, true);
    t1->setLocalRotation(Quaternion(10, 20, 30));
    t1->setParent(t2);
    
    t3->setLocalPosition(Vec3(15.234, 13, 11));
    t3->setLocalRotation(Quaternion(10, 20, 30));
    t3->setParent(t1, false);
    
//    cout<<t3->getLocalRotation()<<endl;
    t3->rotate(Vec3(10, 10, 10), Space::World);
    t3->translate(Vec3(12.3,34.5,-20), Space::World);
    t3->rotate(Vec3(1,2,3), -785, Space::World);
    t3->rotate(Vec3(1,2,3), -785, Space::World);
    
    t3->rotateAround(Vec3(23, -12.3, 2), Vec3(2, 3, 0), 10);
//    cout<<t3->getLocalPosition()<<endl;
//    t3->translate(Vec3(1,1,1), Space::World);
    
//    cout<<t1->getPosition()<<endl;
//    cout<<t1->getLocalPosition()<<endl;
//    cout<<t2->getRotation()<<endl;
//    cout<<t1->getLocalRotation()<<endl;
//    cout<<t1->getRotation()<<endl;
    
    cout<<t3->getPosition()<<endl;
    cout<<t3->getLocalPosition()<<endl;
//    cout<<t1->getRotation()<<endl;
    cout<<t3->getRotation()<<endl;
    cout<<t3->getLocalRotation()<<endl;
    
    //--------------------------------------------
    
    CoreObject::Destory(go1);
    CoreObject::Destory(go2);
    CoreObject::Destory(go3);
    DestoryPool::getInstance()->destoryAll();
}

void cloneTest() {

    using namespace std;
    using namespace Spore3D;
    
    ObjectManager::getInstance()->init();
    
    Spore3D::Mesh *mesh = new Spore3D::Mesh("chr_sword");
    Spore3D::ObjMtl om;
    Spore3D::ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/chr_sword", "chr_sword.obj", *mesh, om);
    
    GameObject *go = new GameObject("sprite1");
    if (nullptr != go) {
        go->addComponent<MeshFilter>();
        cout<<go->toString()<<endl;
        Transform *t = go->getComponent<Transform>();
        if (t != nullptr) {
            cout<<t->toString()<<endl;
        }
        MeshFilter *c = go->getComponent<MeshFilter>();
        if (c != nullptr) {
            cout<<c->toString()<<endl;
        }
        c->getMesh();
        c->setMesh(mesh);
        c->getSharedMesh();
        
        GameObject *go2 = CoreObject::Instantiate<GameObject>(go);
        c = (MeshFilter*)(go2->getComponent<MeshFilter>());
        if (c != nullptr) {
            cout<<c->toString()<<endl;
        }
        
        cout<<go->getInstanceId()<<endl;
        cout<<go2->getInstanceId()<<endl;
        
        MeshFilter *nmf = CoreObject::Instantiate<MeshFilter>(go2->getComponent<MeshFilter>());
        
//        t->setRotation(Quaternion(degToRad(90), 0, 0));
        cout<<t->getRight()<<endl;
        cout<<t->getUp()<<endl;
        cout<<t->getForward()<<endl;
        
        CoreObject::Destory(go);
        CoreObject::Destory(go2);
        CoreObject::Destory(nmf->gameObject);
    }
    
    
    DestoryPool::getInstance()->destoryAll();
}

void ObjectManagerTest() {
    using namespace std;
    using namespace Spore3D;
    ObjectManager *om = ObjectManager::getInstance();
    om->init();
    
    GameObject *go = new GameObject("sprite1");
    if (nullptr != go) {
        go->addComponent("Component");
        cout<<go->toString()<<endl;
        Transform *t = (Transform*)(go->getComponent<Transform>());
        if (t != nullptr) {
            cout<<t->toString()<<endl;
        }
        Component *c = (Component*)(go->getComponent<Component>());
        if (c != nullptr) {
            cout<<c->toString()<<endl;
        }
        CoreObject::Destory(go);
        t = (Transform*)(go->getComponent<Transform>());
        if (nullptr == t) {
            cout<<"go destory transform"<<endl;
        }
    }
    DestoryPool::getInstance()->destoryAll();
}

void QuaternionTest() {
    using namespace std;
    using namespace Spore3D;
    
//    Quaternion a = Quaternion::eulerAngle(degToRad(10), degToRad(20), degToRad(30));
//    cout<<degToRad(10)<<", "<<degToRad(20)<<", "<<degToRad(30)<<endl;
//    Vec3 aa = a.eulerAngle();
//    cout<<aa.x<<", "<<aa.y<<", "<<aa.z<<endl;
}

void PrTest() {
    using namespace std;
    using namespace Spore3D;
    Vec4 aa = Mat4::PerspectiveMat(0, 100, 0, 100, 50, 100)*Vec4(50,50,10,1);
    cout<<aa.x<<", "<<aa.y<<", "<<aa.z<<", "<<aa.w<<endl;
    cout<<aa.x/aa.w<<", "<<aa.y/aa.w<<", "<<aa.z/aa.w<<", "<<aa.w/aa.w<<endl;
    if (aa.x/aa.w == 0) cout<<"oops."<<endl;
}

void ObjMtlTest() {
    Spore3D::ObjMtl *om = new Spore3D::ObjMtl("/Users/shannonxu/Desktop/chr_sword", "chr_sword.mtl");
    om->load();
    Spore3D::ObjMtlInfoMap::iterator it = om->objMtlInfoMap.begin();
    for (; it != om->objMtlInfoMap.end(); it++) {
        std::cout<<it->second.mtlName<<std::endl;
        std::cout<<it->second.illum<<std::endl;
        std::cout<<it->second.Ka<<std::endl;
        std::cout<<it->second.Kd<<std::endl;
        std::cout<<it->second.Ks<<std::endl;
        std::cout<<it->second.map_Kd<<std::endl;
        
    }
}

void ObjMeshLoaderTest() {
//    Spore3D::Mesh *mesh = static_cast<Spore3D::Mesh*>(Spore3D::Mesh::Create("chr_sword"));
    Spore3D::Mesh *mesh = new Spore3D::Mesh("chr_sword");
    Spore3D::ObjMtl om;
    Spore3D::ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/chr_sword", "chr_sword.obj", *mesh, om);
    Spore3D::Mesh::Destory(mesh);
}

void ColorTest() {
    using namespace Spore3D;
    using namespace std;
    Color a(0.65,0.11,0.23);
//    Color g = Color::HSVtoRGB(123, 0.3, 0.5);
    Color g;
    Color::RGBToHSV(a, g.r, g.g, g.b);
    cout<<g.r<<"  "<<g.g<<"  "<<g.b<<endl;
//    cout<<a.grayscale()<<endl;
    
}

void ShaderTest() {
    using namespace Spore3D;
    
    ShaderManager::getInstance()->setPath("/Users/shannonxu/projects/spore3d/spore3d/shaders/default");
    
    ShaderManager::getInstance()->getShader("default");
}

int main(int argc, char *argv[])
{
//    ColorTest();
//    transformTest2();
//    transformTest();
//    cloneTest();
//    ObjectManagerTest();
//    QuaternionTest();
//    PrTest();
//    ObjMtlTest();
//    ObjMeshLoaderTest();
    
    
    
    if (!Spore3D::Engine::getInstance()->init("Spore3D test", 800, 600)) {
        return -1;
    }
    
    ShaderTest();
    
    return Spore3D::Engine::getInstance()->run(argc, argv);

}
