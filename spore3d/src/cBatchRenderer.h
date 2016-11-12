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

#ifndef _cBatchRenderer_h_
#define _cBatchRenderer_h_

#include <OpenGL/gl3.h>
#include <vector>

#include "uTypes.h"
#include "uDebug.h"

namespace Spore3D {
    
    class RenderCommand;
    
    typedef std::vector<RenderCommand*> RenderCommandBatch;
    
    class BatchRenderer {
        
        enum VAO_IDs {Triangles, NumVAOs};
        enum Buffer_IDs {ArrayBuffer, ElementArrayBuffer, NumBuffers};
        
    public:
        static BatchRenderer *getInstance(void);
        
        void init(void);
        
        void renderBatch(const RenderCommandBatch&);
        void beginRender(void);
        void endRender(void);
        
    private:
        struct _ObjectCreate {
            _ObjectCreate();
        };
        static _ObjectCreate _objectCreate;
        
        BatchRenderer() : m_ArrayBufferOffset(0) {}
        
        GLuint m_VAOs[NumVAOs];
        GLuint m_Buffers[NumBuffers];
        
        GLuint m_ArrayBufferOffset;
    };
}

#endif /* _cBatchRenderer_h_ */
