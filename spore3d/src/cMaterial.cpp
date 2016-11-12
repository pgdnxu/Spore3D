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

#include "cMaterial.h"

namespace Spore3D {
    
    Material::Material(const std::string &name)
    : CoreObject(name) {
        
    }
    
    Material::~Material() {
        
    }
    
    void Material::deinit(void) {
        m_Texture = nullptr;
        m_Shader = nullptr;
    }
    
    Material *Material::clone(void) {
        Material *ret = new Material(toString());
        ret->m_Shader = m_Shader;
        ret->m_Texture = m_Texture;
        return ret;
    }
    
    void Material::setShader(Shader *shader) {
        m_Shader = shader;
    }
    
    Shader *Material::getShader(void) const {
        return m_Shader;
    }
    
    void Material::setTexture(Texture *texture) {
        m_Texture = texture;
    }
    
    Texture *Material::getTexture(void) const {
        return m_Texture;
    }
}
