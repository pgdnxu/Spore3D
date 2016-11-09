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

#ifndef _cShaderManager_h_
#define _cShaderManager_h_

#include <map>
#include <string>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "uTypes.h"



namespace Spore3D {
    
    class Shader;
    
    struct ShaderConfig {
        std::string name;
        GLenum type;
    };
    
    class ShaderManager {
    public:
        static ShaderManager *getInstance(void);
        
        Shader *getShader(const std::string&);
        
        std::string getPath(void) const;
        void setPath(const std::string&);
        
        void deinit(void);
    private:
        struct _ObjectCreate {
            _ObjectCreate();
        };
        static _ObjectCreate _objectCreate;
        ShaderManager() {}
    
        Shader *loadShader(const std::string&);
        
        std::map<std::string, Shader*> m_ShaderMap;
        
        std::string m_CurrPath;
        
        static GLenum getShaderType(const std::string&);
    };
    
    
}

#endif /* _cShaderManager_h_ */
