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

namespace Spore3D {
    
    uint32 CoreObject::_InstanceNumber = 0;
    
    CoreObject *CoreObject::Create(const std::string &name) {
        return new CoreObject(name);
    }
    
    void CoreObject::Destory(CoreObject *cObject) {
        if (nullptr != cObject) {
            cObject->deinit();
            delete cObject;
        }
    }
    
    CObjectId CoreObject::getInstanceId() const {
        return m_InstanceID->get();
    }
    
    std::string CoreObject::toString() const {
        return m_Name;
    }
    
    void CoreObject::init() {
        if (nullptr == m_InstanceID) {
            std::string tname(m_Name);
            m_InstanceID = new Hash(tname.append("_").append(std::to_string(_InstanceNumber++)));
        }
    }
    
    void CoreObject::deinit() {
        delete m_InstanceID;
        m_InstanceID = nullptr;
    }
    
    CoreObject::~CoreObject() {
        
    }
    
    CoreObject::CoreObject(const std::string &name) : m_Name(name) {

    }
    
}
