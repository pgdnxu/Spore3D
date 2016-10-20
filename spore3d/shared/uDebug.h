// *********************************************************************
//     ____                       _____ ____
//    / ___| _ __   ___  _ __ ___|___ /|  _ \  ___ ___  _ __ ___
//    \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |/ __/ _ \| '_ ` _ \
//     ___) | |_) | (_) | | |  __/___) | |_| | (_| (_) | | | | | |
//    |____/| .__/ \___/|_|  \___|____/|____(_)___\___/|_| |_| |_|
//          |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
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
    
    char tmp[64];
    
    class Debug {
    public:
        static void log(const std::string &msg) {
#ifdef _DEBUG
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
