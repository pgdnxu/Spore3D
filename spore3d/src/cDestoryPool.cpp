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

#include "cDestoryPool.h"
#include "cObject.h"

namespace Spore3D {
    
    DestoryPool *DestoryPool::getInstance() {
        static DestoryPool _instance;
        return &_instance;
    }
    
    DestoryPool::_ObjectCreate DestoryPool::_objectCreate;
    
    DestoryPool::_ObjectCreate::_ObjectCreate() {
        DestoryPool::getInstance();
    }
    
    void DestoryPool::add(CoreObject *co) {
        if (nullptr != co) {
            m_ObjectDestoryPool.push_back(co);
        }
    }
    
    void DestoryPool::destoryAll(void) {
        std::vector<CoreObject*>::iterator it = m_ObjectDestoryPool.begin();
        for(; it != m_ObjectDestoryPool.end(); it++) {
            delete (*it);
        }
        m_ObjectDestoryPool.clear();
    }
    
}
