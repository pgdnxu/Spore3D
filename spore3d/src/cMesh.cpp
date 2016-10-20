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

#include "cMesh.h"

namespace Spore3D {
    
    CoreObject *Mesh::Create(const std::string &name) {
        return new Mesh(name);
    }
    
    void Mesh::Destory(CoreObject *cObject) {
        CoreObject::Destory(cObject);
    }
    
    void Mesh::init() {
        
    }
    
    void Mesh::deinit() {
        
    }
    
    Mesh::Mesh(const std::string &name) : Spore3D::CoreObject(name) {
        
    }
    
    Mesh::~Mesh() {
        
    }
    
}
