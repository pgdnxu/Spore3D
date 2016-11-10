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

#ifndef _cRenderer_h_
#define _cRenderer_h_

#include "cComponent.h"

namespace Spore3D {
    
    const std::string RENDERER_TYPE_NAME = "Renderer";
    
    class Shader;
    class Texture;
    
    class Renderer : public Component {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        virtual void deinit(void) override;
    
        void render(void);
        
        void setShader(Shader*);
        Shader *getShader(void) const;
        
        void setTexture(Texture*);
        Texture *getTexture(void) const;
        
    protected:
        Renderer(const std::string&);
        virtual ~Renderer();
    private:
        static CoreObject *_alloc_obj(const std::string&);
        
        Shader *m_Shader;
        Texture *m_Texture;
    };
    
}

#endif /* _cRenderer_h_ */
