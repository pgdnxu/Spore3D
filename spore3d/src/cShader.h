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

#ifndef _cShader_h_
#define _cShader_h_

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "cObject.h"

namespace Spore3D {
    
    class Shader : public CoreObject {
        
    public:
        Shader(const std::string&,const GLuint);
        virtual ~Shader();
        
        void enable(void);
        void disable(void);
        
    protected:
        GLuint m_ProgramID;
        
        virtual void deinit(void) override;
        virtual Shader *clone(void) override;
        
    };
    
}

#endif /* _cShader_h_ */
