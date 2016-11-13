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

#include "cTextureManager.h"
#include "cObject.h"
#include "cTexture.h"
#include "uStringUtils.h"
#include "uDebug.h"
#include "uPng.h"

namespace Spore3D {
    
    TextureManager *TextureManager::getInstance() {
        static TextureManager _instance;
        return &_instance;
    }
    
    TextureManager::_ObjectCreate TextureManager::_objectCreate;
    
    TextureManager::_ObjectCreate::_ObjectCreate() {
        TextureManager::getInstance();
    }
    
    Texture *TextureManager::getTexture(const std::string &path, const std::string &fileName) {
        if (fileName.empty()) {
            Debug::err("getTexture failed. (fileName if empty)");
            return nullptr;
        }
        std::string tPath = path;
        StringUtils::trim(tPath);
        StringUtils::appendSlash(tPath);
        std::string keyPath = tPath+StringUtils::trimmed(fileName);
        
        if (m_TextureMap.find(keyPath) != m_TextureMap.end()) {
            return m_TextureMap[keyPath];
        }
        
        PngData *pngData = PngReader::read("/Users/shannonxu/Desktop/chr_sword/chr_sword.png");
        if (nullptr == pngData) {
            Debug::err("getTexture failed. (read PNG failed.)");
            return nullptr;
        }
        
        Texture *newTexture = new Texture(fileName, GL_TEXTURE_1D);
        if (nullptr == newTexture) {
            Debug::err("getTexture failed. (init Texture failed.)");
            delete pngData;
            return nullptr;
        }
        
        newTexture->setData(pngData);
        m_TextureMap[keyPath] = newTexture;
        
        return newTexture;
    }
    
    void TextureManager::deinit(void) {
        for (const auto &it : m_TextureMap) {
            CoreObject::Destory(it.second);
        }
        m_TextureMap.clear();
    }
}
