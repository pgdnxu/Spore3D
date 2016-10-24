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
    
    void Mesh::deinit(void) {
        clear();
    }
    
    Mesh::Mesh(const std::string &name) : Spore3D::CoreObject(name) {
        
    }
    
    Mesh::~Mesh() {
        
    }
    
    Mesh *Mesh::clone(void) {
        Mesh *newMesh = new Mesh(toString());
        
        newMesh->vertices = vertices;
        newMesh->uv = uv;
        newMesh->uv2 = uv2;
        newMesh->normal = normal;
        newMesh->vertIndex = vertIndex;
        newMesh->textureIndex = textureIndex;
        newMesh->normalIndex = normalIndex;
        
        return newMesh;
    }
    
    void Mesh::clear(void) {
        vertices.clear();
        uv.clear();
        uv2.clear();
        normal.clear();
        
        vertIndex.clear();
        textureIndex.clear();
        normalIndex.clear();
    }
}
