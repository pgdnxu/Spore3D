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

#ifndef _cTexture_h_
#define _cTexture_h_

#include <OpenGL/gl3.h>
#include "cObject.h"

namespace Spore3D {

    class PngData;
    class TextureManager;
    
    class Texture : public CoreObject {
        friend TextureManager;
    public:
        Texture(const std::string &name, GLenum target);
        virtual ~Texture();
        
        void enable(void) const;
        void disable(void) const;
        
        PngData *getData(void) const { return m_Data; }
        
    protected:
        virtual void deinit(void) override;
        virtual Texture *clone(void) override;
        
    private:
        void setData(PngData*);
        
        GLuint m_TextureId;
        GLenum m_Target;
        PngData *m_Data;
    };
    
}

#endif /* _cTexture_h_ */
