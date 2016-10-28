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

#ifndef _cBehaviour_h_
#define _cBehaviour_h_

#include "cComponent.h"

namespace Spore3D {
    
    class Behaviour : public Component {
    public:
        void setEnable(const bool enable) { m_Enable = enable; }
    protected:
    protected:
        Behaviour(const std::string &name) : Component(name) {}
    private:
        bool m_Enable;
    };
    
}


#endif /* _cBehaviour_h_ */
