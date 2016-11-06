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

#include "cObject.h"
#include "cDestoryPool.h"

namespace Spore3D {
    
    const std::string CoreObject::NO_NAME = "no_name";
    
    uint32 CoreObject::_InstanceNumber = 0;
    
    void CoreObject::deinit(void) {
        
    }
    
    CoreObject *CoreObject::Instantiate(CoreObject *cObject) {
        if (nullptr != cObject)
            return cObject->clone();
        return nullptr;
    }
    
    void CoreObject::Destory(CoreObject *cObject) {
        if (nullptr != cObject) {
            DestoryPool::getInstance()->add(cObject);
            cObject->deinit();
        }
    }
    
    void CoreObject::DontDestroyOnLoad(CoreObject *cObject) {
        if (nullptr != cObject) {
            cObject->m_DontDestroyOnLoad = true;
        }
    }
    
    CoreObject::~CoreObject() {
        delete m_InstanceID;
        m_InstanceID = nullptr;
    }
    
    CoreObject::CoreObject(const std::string &name)
    : m_Name(name), m_DontDestroyOnLoad(false) {
        if (nullptr == m_InstanceID) {
            std::string tname(m_Name);
            m_InstanceID = new Hash(tname.append("_").append(std::to_string(_InstanceNumber++)));
        }
    }
    
}
