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

#ifndef _cRenderQueue_h_
#define _cRenderQueue_h_

#include <vector>

namespace Spore3D {
    
    class RenderCommand;
    
    class RenderQueue {
    public:
        static RenderQueue *getInstance(void);
    
        void addCommand(RenderCommand*);
        void render(void);
    private:
        struct _ObjectCreate {
            _ObjectCreate();
        };
        static _ObjectCreate _objectCreate;
        
        std::vector<RenderCommand*> m_CommandList;
    };
    
}

#endif /* _cRenderQueue_h_ */
