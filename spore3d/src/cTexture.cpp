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

#include "cTexture.h"
#include "uDebug.h"
#include "uPng.h"

namespace Spore3D {
    
    Texture::Texture(const std::string &name, GLenum target) : CoreObject(name), m_Target(target), m_Data(nullptr) {
        glGenTextures(1, &m_TextureId);
    }
    
    Texture::~Texture() {
        delete m_Data;
        m_Data = nullptr;
    }
    
    void Texture::deinit(void) {
        disable();
        glDeleteTextures(1, &m_TextureId);
    }
    
    Texture *Texture::clone(void) {
        //TODO : deep copy
        Texture *newTexture = new Texture(toString(), m_Target);
        newTexture->m_TextureId = m_TextureId;
        newTexture->m_Data = m_Data;
        return newTexture;
    }
    
    void Texture::enable(void) const {
        if (glIsTexture(m_TextureId))
            glBindTexture(m_Target, m_TextureId);
    }
    void Texture::disable(void) const {
        glBindTexture(m_Target, 0);
    }
    
    void Texture::setData(PngData *pngData) {
        if (nullptr == pngData) return;
        m_Data = pngData;
//        glActiveTexture(<#GLenum texture#>)
        enable();
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage1D(m_Target, 0, GL_RGBA8, pngData->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngData->data);
        disable();
    }
}
