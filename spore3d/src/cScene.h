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
#ifndef _cScene_h_
#define _cScene_h_

#include "cObject.h"

namespace Spore3D {
    
    class SceneManager;
    
    class Scene : public CoreObject {
        friend SceneManager;
    public:
        Scene(const std::string&);
        virtual ~Scene() = 0;
    protected:
        virtual void deinit(void) override;
        virtual Scene *clone(void) override;
    };
    
}

#endif /* _cScene_h_ */
