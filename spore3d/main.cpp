// *********************************************************************
//     ____                       _____ ____
//    / ___| _ __   ___  _ __ ___|___ /|  _ \  ___ ___  _ __ ___
//    \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |/ __/ _ \| '_ ` _ \
//     ___) | |_) | (_) | | |  __/___) | |_| | (_| (_) | | | | | |
//    |____/| .__/ \___/|_|  \___|____/|____(_)___\___/|_| |_| |_|
//          |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
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



void ObjectManagerTest() {
    using namespace std;
    using namespace Spore3D;
    ObjectManager *om = ObjectManager::getInstance();
    om->init();
    
    GameObject *go = (GameObject*)(om->createGameObject("sprite1"));
    go->addComponent("Component");
    if (go != nullptr) {
        cout<<go->toString()<<endl;
        Transform *t = (Transform*)(go->getComponent<Transform>());
        if (t != nullptr) {
            cout<<t->toString()<<endl;
        }
        Component *c = (Component*)(go->getComponent<Component>());
        if (c != nullptr) {
            cout<<c->toString()<<endl;
        }
    }
}

void QuaternionTest() {
    using namespace std;
    using namespace Spore3D;
    
    Quaternion a = Quaternion::eulerAngle(degToRad(10), degToRad(20), degToRad(30));
    cout<<degToRad(10)<<", "<<degToRad(20)<<", "<<degToRad(30)<<endl;
    Vec3 aa = a.eulerAngle();
    cout<<aa.x<<", "<<aa.y<<", "<<aa.z<<endl;
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
    Spore3D::Mesh *mesh = static_cast<Spore3D::Mesh*>(Spore3D::Mesh::Create("chr_sword"));
    Spore3D::ObjMtl om;
    Spore3D::ObjMeshLoader::loadMesh("/Users/shannonxu/Desktop/chr_sword", "chr_sword.obj", *mesh, om);
    Spore3D::Mesh::Destory(mesh);
}

int main(void)
{
    
//    ObjectManagerTest();
//    QuaternionTest();
//    PrTest();
//    ObjMtlTest();
    ObjMeshLoaderTest();
    
    
    Spore3D::PngData *pd = Spore3D::PngReader::read("/Users/shannonxu/Desktop/chr_sword/chr_sword.png");
    if (nullptr == pd) {
        return -1;
    }
    
    
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
//    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    
    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
    int cn = 0;
    while(cn < pd->width)
    {
        glClearColor(pd->data[cn*4]/255.0f, pd->data[cn*4+1]/255.0f, pd->data[cn*4+2]/255.0f, pd->data[cn*4+3]/255.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
        cn++;
//        sleep(1);
    }
    
    glfwTerminate();
    return 0;
}
