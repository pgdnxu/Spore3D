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

#ifndef _cRenderCommand_h_
#define _cRenderCommand_h_

#include "cObject.h"

namespace Spore3D {
    
    class MeshFilter;
    class Renderer;
    
    class RenderCommand : public CoreObject {
    public:
        virtual ~RenderCommand();
        RenderCommand(Renderer*, MeshFilter*);
        
        MeshFilter *getMeshFilter(void) const;
        Renderer *getRenderer(void) const;
        
    protected:
        virtual void deinit(void) override;
        virtual RenderCommand *clone(void) override;
        
    private:
        MeshFilter *m_MeshFilter;
        Renderer *m_Renderer;
    };
    
}

#endif /* _cRenderCommand_h_ */
