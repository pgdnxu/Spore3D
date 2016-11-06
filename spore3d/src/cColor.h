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

#ifndef _cColor_h_
#define _cColor_h_

#include <map>
#include "uTypes.h"
#include "uMath.h"

namespace Spore3D {
    
    struct Color32 {
        uint8 r, g, b, a;
        
        Color32(const uint8 r, const uint8 g, const uint8 b, const uint8 a)
        : r(r), g(g), b(b), a(a) {}
        Color32(const Color32 &color)
        : r(color.r), g(color.g), b(color.b), a(color.a) {}
        Color32 &operator=(const Color32 &color) {
            r = color.r;
            g = color.g;
            b = color.b;
            a = color.a;
            return *this;
        }
        
    };
    
    class Color {
    public:
        static const Color black;
        static const Color blue;
        static const Color clear;
        static const Color cyan;
        static const Color gray;
        static const Color green;
        static const Color grey;
        static const Color magenta;
        static const Color red;
        static const Color white;
        static const Color yellow;
        
    public:
        float r, g, b, a;
        
        Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
        Color(const float r, const float g, const float b, const float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}
        Color(const Color &color)
        : r(color.r), g(color.g), b(color.b), a(color.a) {}
        Color &operator=(const Color &color) {
            r = color.r;
            g = color.g;
            b = color.b;
            a = color.a;
            return *this;
        }
        Color(const Color32 &color)
        : r(color.r/255.0f), g(color.g/255.0f), b(color.b/255.0f), a(color.a/255.0f) {}
        
        Color gamma(void) const;
        float grayscale(void) const;
        float maxColorComponent(void) {return math::fmax(math::fmax(r, g), b);}
        
        static Color HSVtoRGB(const float H, const float S, const float V);
        static void RGBToHSV(const Color &color, float &H, float &S, float &V);
        
    private:
        struct _GammaTableInit {
            _GammaTableInit();
        };
        static _GammaTableInit _gammaTableInit;
        static std::map<uint8, float> _GammaTable;
    };
    
}

#endif /* _cColor_h_ */
