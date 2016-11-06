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

#ifndef _uObjMtl_h_
#define _uObjMtl_h_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "uTypes.h"
#include "uMath.h"
#include "uFileUtils.h"
#include "uStringUtils.h"

namespace Spore3D {
    
    struct ObjMtlTextureRange {
        uint32 begin;
        uint32 end;
        ObjMtlTextureRange() : begin(0), end(0) {}
    };
    
    struct ObjMtlInfo {
        std::string mtlName;
        uint8       illum;
        Vec3        Ka;
        Vec3        Kd;
        Vec3        Ks;
        std::string map_Kd;
        ObjMtlTextureRange range;
    };
    
    typedef std::map<std::string, ObjMtlInfo> ObjMtlInfoMap;
    
    class ObjMtl {
    public:
        ObjMtl() {}
        
        ObjMtl(const std::string &mtlFilePath, const std::string &mtlFileName) {
            setFilePath(mtlFilePath);
            setFileName(mtlFileName);
        }
      
        void setFilePath(const std::string &path) {
            m_MtlFilePath = path;
            StringUtils::trim(m_MtlFilePath);
            if (m_MtlFilePath[m_MtlFilePath.length()-1] != '/') {
                m_MtlFilePath.append("/");
            }
        }
        
        void setFileName(const std::string &name) {
            m_MtlFileName = name;
            StringUtils::trim(m_MtlFileName);
        }
        
        bool load(void) {
            objMtlInfoMap.clear();
            
            std::string content = FileUtils::readTextFile(m_MtlFilePath+m_MtlFileName);
            if (content.length() <= 0) {
                return false;
            }
            
            std::vector<std::string> lines;
            StringUtils::split(content, '\n', lines);
            
            ObjMtlInfo *currOMI = nullptr;
            
//            std::vector<std::string>::iterator itline = lines.begin();
            auto itline = lines.begin();
            for (;itline != lines.end(); itline++) {
                std::string tLine = StringUtils::trimmed(*itline);
                if (tLine[0] != '#') {
                    std::vector<std::string> els;
                    StringUtils::split(tLine, ' ', els);
                    if (els.size() > 0) {
                        std::string keyword = els[0];
                        if ("newmtl" == keyword) {
                            currOMI = &objMtlInfoMap[els[1]];
                            currOMI->mtlName = els[1];
                        }
                        if (nullptr != currOMI) {
                            if ("illum" == keyword) {
                                currOMI->illum = std::stoi(els[1]);
                            } else if ("Ka" == keyword) {
                                currOMI->Ka = genVec3WithLine(els);
                            } else if ("Kd" == keyword) {
                                currOMI->Kd = genVec3WithLine(els);
                            } else if ("Ks" == keyword) {
                                currOMI->Ks = genVec3WithLine(els);
                            } else if ("map_Kd" == keyword) {
                                currOMI->map_Kd = els[1];
                            }
                        }
                    }
                }
            }
            return true;
        }
        
        ObjMtlInfoMap objMtlInfoMap;
        
        
        static Vec2 genVec2WithLine(std::vector<std::string> &v) {
            Vec2 rv;
            if (v.size() >= 3) {
                rv.x = std::stof(v[1]);
                rv.y = std::stof(v[2]);
            }
            return rv;
        }
        
        static Vec3 genVec3WithLine(std::vector<std::string> &v) {
            Vec3 rv;
            if (v.size() >= 4) {
                rv.x = std::stof(v[1]);
                rv.y = std::stof(v[2]);
                rv.z = std::stof(v[3]);
            }
            return rv;
        }
        
    private:
        std::string m_MtlFilePath;
        std::string m_MtlFileName;
        
        
    };
    
}

#endif /* uObjMtl_h */
