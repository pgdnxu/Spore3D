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

#include "cRenderCommand.h"
#include "uDebug.h"

namespace Spore3D {

    RenderCommand::RenderCommand(Renderer *renderer, MeshFilter *meshFilter, Transform *transform)
    : Spore3D::CoreObject("RenderCommand"), m_MeshFilter(meshFilter), m_Renderer(renderer), m_Transform(transform){
        
    }

    RenderCommand::~RenderCommand() {
//        Debug::log("RenderCommand::~RenderCommand()"+toString());
    }
    
    void RenderCommand::deinit(void) {
        m_MeshFilter = nullptr;
        m_Renderer = nullptr;
    }
    
    RenderCommand *RenderCommand::clone(void) {
        return new RenderCommand(m_Renderer, m_MeshFilter, m_Transform);
    }
    
}
