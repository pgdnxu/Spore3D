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

#ifndef _uDebug_h_
#define _uDebug_h_

#include <iostream>
#include <string>
#include <ctime>

#define _DEBUG

namespace Spore3D {
    
    class Debug {
    public:
        static void log(const std::string &msg) {
#ifdef _DEBUG
            char tmp[64];
            time_t t = time(0);
            strftime(tmp,sizeof(tmp),"[%Y-%m-%d,%H:%M:%S] ",localtime(&t));
            std::cout<<tmp<<msg<<std::endl;
#endif
        }
        
        static void err(const std::string &msg) {
#ifdef _DEBUG
            log(std::string("[ERROR] ").append(msg));
#endif
        }
    };
    
}

#endif /* _uDebug_h_ */
