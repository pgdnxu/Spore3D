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

#ifndef _uObjMeshLoader_h_
#define _uObjMeshLoader_h_

#include "cMesh.h"
#include "uObjMtl.h"
#include "uFileUtils.h"
#include "uStringUtils.h"
#include "uDebug.h"

namespace Spore3D {
    
    class ObjMeshLoader {
    public:

        static bool loadMesh(const std::string &meshPath, const std::string &meshFileName, Mesh &mesh, ObjMtl &objMtl) {
            std::string cMeshPath = StringUtils::trimmed(meshPath);
            std::string cMeshFileName = StringUtils::trimmed(meshFileName);
            
            if (cMeshPath[cMeshPath.length()-1] != '/') {
                cMeshPath.append("/");
            }
            
            std::string meshPathName = cMeshPath + cMeshFileName;
            
            std::string meshContent;
            if (!FileUtils::readTextFile(meshPathName, meshContent)) {
                return false;
            }
            
            objMtl.setFilePath(cMeshPath);
            
            std::vector<std::string> lines;
            StringUtils::split(meshContent, '\n', lines);
            std::vector<std::string>::iterator itline = lines.begin();
            
            uint32 vindex = 0;
            ObjMtlInfo *currObjMtlInfo = nullptr;
            
            for (; itline != lines.end(); itline++) {
                Debug::log(*itline);
                
                std::string tLine = StringUtils::trimmed(*itline);
                
                if (tLine[0] != '#') {
                    std::vector<std::string> els;
                    StringUtils::split(tLine, ' ', els);
                    if (els.size() > 0) {
                        
                        std::string keyword = els[0];
                        
                        if ("mtllib" == keyword) {
                            //material
                            objMtl.setFileName(els[1]);
                        } else if ("usemtl" == keyword) {
                            if (nullptr != currObjMtlInfo) {
                                currObjMtlInfo->range.end = vindex;
                            }
                            currObjMtlInfo = &objMtl.objMtlInfoMap[els[1]];
                            currObjMtlInfo->range.begin = vindex + 1;
                        } else if ("vn" == keyword) {
                            //normals
                            mesh.normal.push_back(ObjMtl::genVec3WithLine(els));
                        } else if ("vt" == keyword) {
                            //texcoords
                            mesh.uv.push_back(ObjMtl::genVec2WithLine(els));
                        } else if ("v" == keyword) {
                            //verts
                            mesh.vertices.push_back(ObjMtl::genVec3WithLine(els));
                            vindex++;
                        } else if ("f" == keyword) {
                            //face
                            genIndexWithFaceData(mesh, els);
                        }
                    }
                }
            }
            
            return true;
        }
        
    private:
        static void genIndexWithFaceData(Mesh &mesh, std::vector<std::string> &v) {
            for (int i = 1; i < v.size(); i++) {
                std::vector<std::string> inds = StringUtils::split(v[i], '/');
                if (inds.size() == 1) {
                    if (inds[0].length() > 0) {
                        mesh.vertIndex.push_back(std::stoi(inds[0]));
                    }
                } else if (inds.size() == 2) {
                    if (inds[0].length() > 0) {
                        mesh.vertIndex.push_back(std::stoi(inds[0]));
                    }
                    if (inds[1].length() > 0) {
                        mesh.textureIndex.push_back(std::stoi(inds[1]));
                    }
                } else if (inds.size() >= 3) {
                    if (inds[0].length() > 0) {
                        mesh.vertIndex.push_back(std::stoi(inds[0]));
                    }
                    if (inds[1].length() > 0) {
                        mesh.textureIndex.push_back(std::stoi(inds[1]));
                    }
                    if (inds[2].length() > 0) {
                        mesh.normalIndex.push_back(std::stoi(inds[2]));
                    }
                }
            }
        }
        
    };
    
}


#endif /* uObjMeshLoader_h */
