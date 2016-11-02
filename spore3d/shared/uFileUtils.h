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

#ifndef _uFileUtils_h_
#define _uFileUtils_h_

#include <string>
#include <vector>

#include "uTypes.h"
#include "uDebug.h"

namespace Spore3D {
    
    struct _ReadFileInfo {
        char *buffer;
        std::size_t fileLen;
        
        _ReadFileInfo():buffer(nullptr), fileLen(0) {}
        
        bool operator==(const _ReadFileInfo &rfi) {
            return buffer == rfi.buffer && fileLen == rfi.fileLen;
        }
        bool operator!=(const _ReadFileInfo &rfi) {
            return !(*this == rfi);
        }
    };
    
    static _ReadFileInfo NullRFI;
    
    class FileUtils {
    public:
        static std::vector<uint8> readBinFile(const std::string &filePath) {
            std::vector<uint8> ret;
            readBinFile(filePath, ret);
            return ret;
        }
        
        static bool readBinFile(const std::string &filePath, std::vector<uint8> &buffer) {
            _ReadFileInfo rfInfo = _readFileData(filePath.c_str(), "rb");
            if (rfInfo != NullRFI) {
                buffer.reserve(rfInfo.fileLen);
                std::copy(rfInfo.buffer, rfInfo.buffer + rfInfo.fileLen, std::back_inserter(buffer));
                _deInitRFI(rfInfo);
                return true;
            }
            return false;
        }
        
        static std::string readTextFile(const std::string &filePath) {
            std::string ret;
            readTextFile(filePath, ret);
            return ret;
        }
        
        static bool readTextFile(const std::string &filePath, std::string &buffer) {
            _ReadFileInfo rfInfo = _readFileData(filePath.c_str(), "rt");
            if (rfInfo != NullRFI) {
                buffer.assign(rfInfo.buffer, rfInfo.fileLen);
                _deInitRFI(rfInfo);
                return true;
            }
            return false;
        }

    private:
        
        static void _deInitRFI(_ReadFileInfo &rfi) {
            delete [] rfi.buffer;
            rfi.fileLen = 0;
            rfi.buffer = nullptr;
        }
        
        static uint32 _getFileLength(FILE *file) {
            
            uint32 flen = 0;
            if (nullptr == file) return 0;
            
            fseek(file, 0, SEEK_END);
            flen = uint32(ftell(file));
            fseek(file, 0, SEEK_SET);
            
            return flen;
            
        }
        
        static _ReadFileInfo _readFileData(const char *filePath, const char *mode) {
            
            _ReadFileInfo rfInfo;
            
            if (nullptr == filePath || nullptr == mode) {
                return NullRFI;
            }
            
            FILE *fd = fopen(filePath, mode);
            if (nullptr == fd) {
                Debug::err(std::string("open file: ").append(filePath).append(" failed."));
                return NullRFI;
            }
            
            std::size_t flen = _getFileLength(fd);
            
//            assert(flen < 10 * 1024 * 1024);
            
            char *buffer = new char[flen];
            if (nullptr == buffer) {
                Debug::err(std::string("file: ").append(filePath).append(" size to large. out of memory."));
                return NullRFI;
            }
            
            if (flen != fread(buffer, 1, flen, fd)) {
                Debug::err(std::string("read file: ").append(filePath).append(" failed."));
                delete [] buffer;
                return NullRFI;
            }
            
            fclose(fd);
            
            rfInfo.buffer = buffer;
            rfInfo.fileLen = flen;
            
            return rfInfo;
        }
    };
    
}

#endif /* _uFileUtils_h_ */
