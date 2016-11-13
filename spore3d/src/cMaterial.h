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

#ifndef _cMaterial_h_
#define _cMaterial_h_

#include "cObject.h"
#include "cShader.h"
#include "cTexture.h"
#include "uDebug.h"

namespace Spore3D {
    
    class Material : public CoreObject {
    public:
        Material(const std::string &);
        virtual ~Material();
        
        void setShader(Shader*);
        Shader *getShader(void) const;
        
        void setTexture(Texture*);
        Texture *getTexture(void) const;
        
        bool operator==(const Material &material) {
            return (m_Shader->getInstanceId() == material.getShader()->getInstanceId())
            && (m_Texture->getInstanceId() == material.getTexture()->getInstanceId());
        }
        
    protected:
        virtual void deinit(void) override;
        virtual Material *clone(void) override;
        
    private:
                Shader *m_Shader;
                Texture *m_Texture;
    };
    
}

#endif /* cMaterial_h */
