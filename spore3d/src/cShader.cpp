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

#include "cShader.h"

namespace Spore3D {
    
    Shader::Shader(const std::string &name, const GLuint programId)
    : CoreObject(name), m_ProgramID(programId) {
        
    }
    
    Shader::~Shader() {
        
    }
    
    void Shader::deinit(void) {
        glDeleteProgram(m_ProgramID);
    }
    
    Shader *Shader::clone(void) {
        return new Shader(toString(), m_ProgramID);
    }
    
    void Shader::enable(void) {
        if (glIsShader(m_ProgramID))
            glUseProgram(m_ProgramID);
    }
    
    void Shader::disable(void) {
        glUseProgram(0);
    }
    
}
