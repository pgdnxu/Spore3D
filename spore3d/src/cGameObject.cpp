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

#include "cGameObject.h"
#include "cTransform.h"
#include "uDebug.h"

namespace Spore3D {
    
    GameObject::GameObject(const std::string &name) : CoreObject(name), transform(nullptr) {
        ObjectManager::getInstance()->addGameObject(this);
    }
    
    GameObject::~GameObject() {
        Debug::log("GameObject::~GameObject()");
    }
    
    void GameObject::deinit() {
        ObjectManager::getInstance()->removeGameObject(getInstanceId());
    }
}
