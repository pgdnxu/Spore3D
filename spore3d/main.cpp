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

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "uMath.h"
#include "cObject.h"
#include "uHash.h"
#include "cComponent.h"
#include "cObjectManager.h"
#include "cTransform.h"
#include "cGameObject.h"

#include <map>

int main(void)
{
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
    
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
