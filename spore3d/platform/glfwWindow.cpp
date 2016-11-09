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

namespace Spore3D {
    
    void window_resize(GLFWwindow *window, int width, int height);
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    
    GlfwWindow::GlfwWindow(const char *title, int width, int height) {
        m_Title = title;
        m_Width = width;
        m_Height = height;
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
    
    bool GlfwWindow::init()
    {
        
//        Spore3D::PngData *pd = Spore3D::PngReader::read("/Users/shannonxu/Desktop/chr_sword/chr_sword.png");
//        if (nullptr == pd) {
//            return -1;
//        }
        
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
        
        
//        std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
//        std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
//        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
//        std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        
        //    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
        
        /* Loop until the user closes the window */
        //    while (!glfwWindowShouldClose(window))
//        int cn = 0;
//        while(cn < pd->width)
//        {
//            glClearColor(pd->data[cn*4]/255.0f, pd->data[cn*4+1]/255.0f, pd->data[cn*4+2]/255.0f, pd->data[cn*4+3]/255.0f);
//            /* Render here */
//            glClear(GL_COLOR_BUFFER_BIT);
//            
//            /* Swap front and back buffers */
//            glfwSwapBuffers(window);
//            
//            /* Poll for and process events */
//            glfwPollEvents();
//            cn++;
//            //        sleep(1);
//        }
        
//        glfwTerminate();
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
    }
    
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        win->m_MouseButtons[button] = action != GLFW_RELEASE;
    }
    
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
        GlfwWindow *win = (GlfwWindow*)glfwGetWindowUserPointer(window);
        win->m_mx = xpos;
        win->m_my = ypos;
    }
}
