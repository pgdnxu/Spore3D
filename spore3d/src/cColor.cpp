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

#include "cColor.h"
#include <iostream>

namespace Spore3D {
    
    const Color Color::black(0, 0, 0);
    const Color Color::blue(0, 0, 1);
    const Color Color::clear(0, 0, 0, 0);
    const Color Color::cyan(0, 1, 1);
    const Color Color::gray(0.5, 0.5, 0.5);
    const Color Color::green(0, 1, 0);
    const Color Color::grey(0.5, 0.5, 0.5);
    const Color Color::magenta(1, 0, 1);
    const Color Color::red(1, 0, 0);
    const Color Color::white(1, 1, 1);
    const Color Color::yellow(1, 0.92, 0.016);
    
    std::map<uint8, float> Color::_GammaTable;
    
    Color::_GammaTableInit Color::_gammaTableInit;
    
    Color::_GammaTableInit::_GammaTableInit() {
        float fPrecompensation = 1/2.2f;
        for (uint16 i = 0; i <= 255; i++) {
            _GammaTable[uint8(i)] = powf(i / 255.0f, fPrecompensation);
        }
    }
    
    Color Color::gamma(void) const {
        Color ret(_GammaTable[uint8(r*255+0.5)],_GammaTable[uint8(g*255+0.5)],_GammaTable[uint8(b*255+0.5)]);
        return ret;
    }
    
    float Color::grayscale(void) const {
        return r*0.299 + g*0.587 + b*0.114;
    }

    Color Color::HSVtoRGB(const float H, const float S, const float V) {
        Color ret;
        int32 h = int32(H/60) % 6;
        float f = H/60 - h;
        float p = V * (1 - S);
        float q = V * (1 - f * S);
        float t = V * (1 - (1 - f) * S);
        switch(h) {
            case 0:
                ret = Color(V, t, p);
                break;
            case 1:
                ret = Color(q, V, p);
                break;
            case 2:
                ret = Color(p, V, t);
                break;
            case 3:
                ret = Color(p, q, V);
                break;
            case 4:
                ret = Color(t, p, V);
                break;
            case 5:
                ret = Color(V, p, q);
                break;
        }
        return ret;
    }
    
    void Color::RGBToHSV(const Color &color, float &H, float &S, float &V) {
        float max = math::fmax(math::fmax(color.r, color.g), color.b);
        float min = math::fmin(math::fmin(color.r, color.g), color.b);
        float diff = max-min;
        if (color.r == max) H = (color.g-color.b) / diff;
        if (color.g == max) H = 2 + (color.b-color.r) / diff;
        if (color.b == max) H = 4 + (color.r-color.g) / diff;
        H = H < 0 ? H*60+360 : H*60;
        H /= 360.f;
        V = max;
        S = diff/max;
    }
    
    Color Color::lerp(const Color &lcolor, const Color &rcolor, const float t) {
        Color diff = rcolor - lcolor;
        return Color(lcolor.r+diff.r/t, lcolor.g+diff.r/t, lcolor.b+diff.b/t, lcolor.a);
    }
    
}
