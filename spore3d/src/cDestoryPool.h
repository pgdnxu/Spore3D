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

#ifndef _cDestoryPool_h_
#define _cDestoryPool_h_

#include <vector>

namespace Spore3D {
    
    class CoreObject;
    
    class DestoryPool {
    public:
        static DestoryPool *getInstance();
        
        void add(CoreObject *co);
        void destoryAll();
        
    private:
        struct _ObjectCreate {
            
            _ObjectCreate();
            
        };
        static _ObjectCreate _objectCreate;
        std::vector<CoreObject*> m_ObjectDestoryPool;
    };
}

#endif /* _cDestoryPool_h_ */
