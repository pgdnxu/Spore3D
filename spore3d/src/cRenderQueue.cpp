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

#include "cRenderQueue.h"
#include "cObject.h"
#include "cRenderCommand.h"

namespace Spore3D {
    
    RenderQueue *RenderQueue::getInstance() {
        static RenderQueue _instance;
        return &_instance;
    }
    
    RenderQueue::_ObjectCreate RenderQueue::_objectCreate;
    
    RenderQueue::_ObjectCreate::_ObjectCreate() {
        RenderQueue::getInstance();
    }
    
    void RenderQueue::addCommand(RenderCommand *renderCommand) {
        m_CommandList.push_back(renderCommand);
    }
    
    void RenderQueue::render(void) {
        
        for (const auto &it : m_CommandList) {
            CoreObject::Destory(it);
        }
        m_CommandList.clear();
    }
    
}
