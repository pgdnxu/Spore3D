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
    class Transform;
    
    
    class RenderCommand : public CoreObject {
    public:
        virtual ~RenderCommand();
        RenderCommand(Renderer*, MeshFilter*, Transform*);
        
        MeshFilter *getMeshFilter(void) const { return m_MeshFilter; }
        Renderer *getRenderer(void) const { return m_Renderer; }
        Transform *getTransform(void) const { return m_Transform; }
        
    protected:
        virtual void deinit(void) override;
        virtual RenderCommand *clone(void) override;
        
    private:
        MeshFilter *m_MeshFilter;
        Renderer *m_Renderer;
        Transform *m_Transform;
    };
    
}

#endif /* _cRenderCommand_h_ */
