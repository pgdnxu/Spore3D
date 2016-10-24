// *********************************************************************
//     ____                       _____ ____
//    / ___| _ __   ___  _ __ ___|___ /|  _ \  ___ ___  _ __ ___
//    \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |/ __/ _ \| '_ ` _ \
//     ___) | |_) | (_) | | |  __/___) | |_| | (_| (_) | | | | | |
//    |____/| .__/ \___/|_|  \___|____/|____(_)___\___/|_| |_| |_|
//          |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
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
    
    CoreObject::~CoreObject() {
        delete m_InstanceID;
        m_InstanceID = nullptr;
    }
    
    CoreObject::CoreObject(const std::string &name) : m_Name(name) {
        if (nullptr == m_InstanceID) {
            std::string tname(m_Name);
            m_InstanceID = new Hash(tname.append("_").append(std::to_string(_InstanceNumber++)));
        }
    }
    
}
