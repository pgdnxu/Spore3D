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

#ifndef _cTextureManager_h_
#define _cTextureManager_h_

#include <map>
#include <string>

namespace Spore3D {
    
    class Texture;
    
    class TextureManager {
    public:
        static TextureManager *getInstance(void);
        
        Texture *getTexture(const std::string&, const std::string&);
        
        void deinit(void);
    private:
        struct _ObjectCreate {
            _ObjectCreate();
        };
        static _ObjectCreate _objectCreate;
        
        std::map<std::string, Texture*> m_TextureMap;
    };
    
}

#endif /* _cTextureManager_h_ */
