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
    
    const int32 LNF = -1;
    
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
        if (glIsProgram(m_ProgramID))
            glUseProgram(m_ProgramID);
    }
    
    void Shader::disable(void) {
        glUseProgram(0);
    }
    
    void Shader::reload(void) {
        glLinkProgram(m_ProgramID);
        m_UniformLocationCache.clear();
    }
    
    int32 Shader::getUniformLocation(const std::string &uniformName) {
        if (m_UniformLocationCache.find(uniformName) == m_UniformLocationCache.end()) {
            int32 location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
            if (LNF != location) {
                m_UniformLocationCache[uniformName] = location;
            }
            return location;
        }
        return m_UniformLocationCache[uniformName];
    }
    
    void Shader::setUniform(const std::string &uniformName, const float value) {
        int32 location = getUniformLocation(uniformName);
        if (LNF != location) {
            glUniform1f(location, value);
        }
    }
    
    void Shader::setUniform(const std::string &uniformName, const Vec2 &value) {
        int32 location = getUniformLocation(uniformName);
        if (LNF != location) {
            glUniform2f(location, value.x, value.y);
        }
        
    }
    
    void Shader::setUniform(const std::string &uniformName, const Vec3 &value) {
        int32 location = getUniformLocation(uniformName);
        if (LNF != location) {
            glUniform3f(location, value.x, value.y, value.z);
        }
    }
    
    void Shader::setUniform(const std::string &uniformName, const Vec4 &value) {
        int32 location = getUniformLocation(uniformName);
        if (LNF != location) {
            glUniform4f(location, value.x, value.y, value.z, value.w);
        }
    }
    
    void Shader::setUniform(const std::string &uniformName, const Mat4 &value) {
        int32 location = getUniformLocation(uniformName);
        if (LNF != location) {
            glUniformMatrix4fv(location, 1, GL_FALSE, value.s);
        }
    }
    
}
