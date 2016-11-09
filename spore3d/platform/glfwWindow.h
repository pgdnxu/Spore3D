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

#ifndef _glfwWindow_h_
#define _glfwWindow_h_

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

namespace Spore3D {
    
    class GlfwWindow {
        
        friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        
        friend struct GLFWwindow;
        
    private:
        const char *m_Title;
        int m_Width, m_Height;
        GLFWwindow *m_Window;
        
        bool m_Keys[MAX_KEYS];
        bool m_MouseButtons[MAX_BUTTONS];
        double m_mx, m_my;
        
    public:
        GlfwWindow(const char *name, int width, int height);
        ~GlfwWindow();
        bool closed() const;
        void update();
        void clear() const;
        
        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }
        
        void updateSize(int width, int height) {
            m_Width = width;
            m_Height = height;
        }
        
        bool isKeyPressed(unsigned int keycode) const;
        bool isMouseButtonPressed(unsigned int button) const;
        void getMousePosition(double& x, double& y) const;
    private:
        bool init();
    };
    
}

#endif /* _glfwWindow_h_ */
