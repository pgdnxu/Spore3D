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

#ifndef _cEngine_h_
#define _cEngine_h_

namespace Spore3D {
    
    class GlfwWindow;
    class Scene;
    
    class Engine {
    public:
        static Engine *getInstance(void);

        bool init(const char *name, int width, int height);
        int run(int argc, char *argv[]);
        
    private:
        struct _ObjectCreate {
            _ObjectCreate();
        };
        static _ObjectCreate _objectCreate;
        Engine();
        ~Engine();
        
        void proc(void);
        void deinit(void);
        
        GlfwWindow *m_MainWindow;
        Scene *m_MainScene;
    };
    
}

#endif /* _cEngine_h_ */
