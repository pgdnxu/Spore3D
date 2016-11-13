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

#ifndef _uPng_h_
#define _uPng_h_

#include <string>
#include <cstdio>

#include <png.h>
#include <zlib.h>

#include "uTypes.h"

namespace Spore3D {
    
    struct PngData {
        uint32 width;
        uint32 height;
        int32 bitDepth;
        int32 colorType;
        uint8 *data;
        uint32 dataSize;
        
        PngData() : data(nullptr), dataSize(0) {}
        ~PngData() { delete [] data; data = nullptr;}
    };
    
    class PngReader {
    public:
        
        static uint32 getRowBytes(uint32 width){
            if((width * 3) % 4 == 0){
                return width * 3;
            }else{
                return ((width * 3) / 4 + 1) * 4;
            }
        }
        
        static PngData *read(const std::string &filePath) {
            png_structp png_ptr;
            png_infop info_ptr;
            FILE *fp;
            
            PngData *rpd = new PngData();
            if (nullptr == rpd) return nullptr;
            
            if ((fp = fopen(filePath.c_str(), "rb")) == nullptr) {
                delete rpd;
                return nullptr;
            }
            
            png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if (nullptr == png_ptr) {
                fclose(fp);
                delete rpd;
                return nullptr;
            }
            
            info_ptr = png_create_info_struct(png_ptr);
            if (nullptr == info_ptr) {
                fclose(fp);
                png_destroy_read_struct(&png_ptr, nullptr, nullptr);
                delete rpd;
                return nullptr;
            }
            
            if (setjmp(png_jmpbuf(png_ptr))) {
                /* Free all of the memory associated with the png_ptr and info_ptr */
                png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
                fclose(fp);
                /* If we get here, we had a problem reading the file */
                delete rpd;
                return nullptr;
            }
            
            png_init_io(png_ptr, fp);
            
            png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

            png_get_bKGD(nullptr, nullptr, nullptr);
            png_get_IHDR(png_ptr, info_ptr, &rpd->width, &rpd->height, &rpd->bitDepth, &rpd->colorType, nullptr, nullptr, nullptr);
            
            png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
            uint32 rowBytes = getRowBytes(rpd->width);
            
            if (rpd->colorType == PNG_COLOR_TYPE_RGB) {
                rpd->dataSize = rowBytes * rpd->height;
            } else if (rpd->colorType == PNG_COLOR_TYPE_RGBA) {
                rpd->dataSize = rpd->width * rpd->height * 4;
            } else{
                png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
                fclose(fp);
                delete rpd;
                return nullptr;
            }
            
            rpd->data = (uint8*)malloc(rpd->dataSize);
            
            for (uint32 i = 0; i < rpd->height; i++) {
                if (PNG_COLOR_TYPE_RGB == rpd->colorType) {
                    memcpy(rpd->data + rowBytes * i, row_pointers[i], rpd->width * 3);
                } else if (PNG_COLOR_TYPE_RGBA == rpd->colorType) {
                    memcpy(rpd->data + rpd->width * i * 4, row_pointers[i], rpd->width * 4);
                }
            }
            
            png_destroy_read_struct(&png_ptr, &info_ptr, 0);
            fclose(fp);
            return rpd;
        }
    };
    
}

#endif /* _uPng_h_ */
