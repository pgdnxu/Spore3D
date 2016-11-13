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

#include "glfwWindow.h"

//test code
#include "uDebug.h"
#include "cSceneManager.h"
#include "cCamera.h"
#include "cTransform.h"
#include "cScene.h"
#include "uMath.h"

namespace Spore3D {
    
    void window_resize(GLFWwindow *window, int width, int height);
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    
    GlfwWindow::GlfwWindow(const char *title, int width, int height)
    : startToRotate(false), m_Title(title), m_Width(width), m_Height(height) {
        if (!init()) {
            glfwTerminate();
        }
        
        for (int i = 0; i < MAX_KEYS; i++)
            m_Keys[i] = false;
        for (int i = 0; i < MAX_BUTTONS; i++)
            m_MouseButtons[i] = false;
        
    }
    
    GlfwWindow::~GlfwWindow() {
        glfwTerminate();
    }
    
    void GlfwWindow::update() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
    
    bool GlfwWindow::init() {

        /* Initialize the library */
        if (!glfwInit())
            return -1;
        
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        
        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
        if (!m_Window)
        {
            glfwTerminate();
            return -1;
        }
        
        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, window_resize);
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
        glfwSetCursorPosCallback(m_Window, cursor_position_callback);
        
        return true;

    }
    
    bool GlfwWindow::closed() const {
        return glfwWindowShouldClose(m_Window) == 1;
    }
    
    void GlfwWindow::clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    bool GlfwWindow::isKeyPressed(unsigned int keycode) const {
        if (keycode >= MAX_KEYS)
            return false;
        return m_Keys[keycode];
    }
    
    bool GlfwWindow::isMouseButtonPressed(unsigned int button) const {
        if (button >= MAX_BUTTONS)
            return false;
        return m_MouseButtons[button];
    }
    
    void GlfwWindow::getMousePosition(double& x, double& y) const{
        x = m_mx;
        y = m_my;
    }
    
    void window_resize(GLFWwindow *window, int width, int height) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        glViewport(0, 0, width, height);
        win->updateSize(width, height);
    }
    
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        win->m_Keys[key] = action != GLFW_RELEASE;
        if (win->m_Keys[key]) {
            Scene *currScene = SceneManager::getInstance()->getActiveScene();
            Camera *currCamera = nullptr;
            if (nullptr != currScene) {
                currCamera = currScene->getMainCamera();
            }
            if (nullptr != currCamera) {
                if ('W' == key) {
//                    Debug::log("w");
                    Vec3 nf = currCamera->transform->getForward();
                    currCamera->transform->translate(nf.normalized()*10,Space::World);
                } else if ('S' == key) {
                    Vec3 nb = currCamera->transform->getForward();
                    currCamera->transform->translate(-nb.normalized()*10,Space::World);
//                    Debug::log("s");
                } else if ('D' == key) {
                    Vec3 nr = currCamera->transform->getRight();
                    currCamera->transform->translate(nr.normalized()*10,Space::World);
//                    Debug::log("d");
                } else if ('A' == key) {
                    Vec3 nl = currCamera->transform->getRight();
                    currCamera->transform->translate(-nl.normalized()*10,Space::World);
//                    Debug::log("a");
                }
            }
        }
    }
    
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        win->m_MouseButtons[button] = action != GLFW_RELEASE;
        if (!win->startToRotate) {
            win->startToRotate = true;
        } else {
            win->startToRotate = false;
        }
    }
    
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        
        if (win->startToRotate) {
            Scene *currScene = SceneManager::getInstance()->getActiveScene();
            Camera *currCamera = nullptr;
            if (nullptr != currScene) {
                currCamera = currScene->getMainCamera();
            }
            if (nullptr != currCamera) {
            
                Vec3 r = currCamera->transform->getRotation().eulerAngle();
                float nrx = math::clamp(-(ypos-win->m_my)/5+r.x,-179,179);
                float nry = math::clamp(-(xpos-win->m_mx)/5+r.y,-179,179);
                
                currCamera->transform->setRotation(Quaternion(nrx, nry,0));
            
            }
        }
        win->m_mx = xpos;
        win->m_my = ypos;
    }
}
