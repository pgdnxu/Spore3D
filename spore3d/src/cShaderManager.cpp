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

#include "cShaderManager.h"
#include "uStringUtils.h"
#include "uFileUtils.h"
#include "uDebug.h"
#include "pugixml.hpp"
#include "cShader.h"

namespace Spore3D {
    
    static const char* CONF_NODE_SHADER = "shader";
    static const char* CONF_NODE_SNODE = "snode";
    static const char* CONF_NODE_NAME = "name";
    static const char* CONF_NODE_TYPE = "type";
    
    static const std::string SHADER_TYPE_VERTEX = "VERTEX_SHADER";
    static const std::string SHADER_TYPE_FRAGMENT = "FRAGMENT_SHADER";
    static const std::string SHADER_TYPE_TESS_EVALUATION = "TESS_EVALUATION_SHADER";
    static const std::string SHADER_TYPE_TESS_CONTROL = "TESS_CONTROL_SHADER";
    static const std::string SHADER_TYPE_GEOMETRY = "GEOMETRY_SHADER";
    
    ShaderManager *ShaderManager::getInstance() {
        static ShaderManager _instance;
        return &_instance;
    }
    
    ShaderManager::_ObjectCreate ShaderManager::_objectCreate;
    
    ShaderManager::_ObjectCreate::_ObjectCreate() {
        ShaderManager::getInstance();
    }

    std::string ShaderManager::getCurrPath(void) const {
        return m_CurrPath;
    }
    void ShaderManager::setCurrPath(const std::string &path) {
        m_CurrPath = StringUtils::trimmed(path);
        if (m_CurrPath.at(m_CurrPath.length()-1) != '/') {
            m_CurrPath.append("/");
        }
    }
    
    Shader *ShaderManager::loadShader(const std::string &shaderName) {
        GLint rslt;
        bool hasVertShader = false;
        bool hasFragShader = false;
        std::string confPath = m_CurrPath + shaderName + ".conf";

        std::map<GLenum, std::vector<ShaderConfig>> configMap;
        pugi::xml_document doc;
        if (doc.load_file(confPath.c_str(), pugi::parse_default, pugi::encoding_utf8)) {
            pugi::xml_node rootNode = doc.child(CONF_NODE_SHADER);
            
            for (pugi::xml_node snode = rootNode.child(CONF_NODE_SNODE);
                 snode;
                 snode = rootNode.next_sibling(CONF_NODE_SNODE)) {
                pugi::xml_node nameNode = snode.child(CONF_NODE_NAME);
                pugi::xml_node typeNode = snode.child(CONF_NODE_TYPE);
                
                std::string name = nameNode.first_child().value();
                std::string type = typeNode.first_child().value();
                
                GLenum stype = getShaderType(type);
                ShaderConfig config;
                config.type = stype;
                config.name = name;
                configMap[stype].push_back(config);
                
                if (GL_VERTEX_SHADER == stype) hasVertShader = true;
                if (GL_FRAGMENT_SHADER == stype) hasFragShader = true;
            }
            
            if (!hasVertShader) {
                Debug::err("Load shader failed :"+shaderName+" has no vertex shader.");
                return nullptr;
            }
            
            if (!hasFragShader) {
                Debug::err("Load shader failed :"+shaderName+" has no fragment shader.");
                return nullptr;
            }
            
            std::vector<GLuint> shaderIdList;
            for (const auto &it : configMap) {
                uint32 index = 0;
                const char *srcList[it.second.size()];
                for (const auto &conf : it.second) {
                    std::string filePath = m_CurrPath + conf.name;
                    std::string shaderSrc;
                    FileUtils::readTextFile(filePath, shaderSrc);
                    if (shaderSrc.empty()) {
                        Debug::err("Load shader failed : read "+conf.name+" failed.");
                        return nullptr;
                    }
                    srcList[index++] = shaderSrc.c_str();
                }
                
                GLuint shaderId = glCreateShader(it.first);
                glShaderSource(shaderId, 1, srcList, nullptr);
                glCompileShader(shaderId);
                
                glGetShaderiv(shaderId, GL_COMPILE_STATUS, &rslt);
                if (GL_FALSE == rslt) {
#ifdef _DEBUG
                    int length;
                    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
                    std::vector<GLchar> error(length);
                    glGetShaderInfoLog(shaderId, length, &length, &error[0]);
                    Debug::err(&error[0]);
#endif /* _DEBUG */
                    
                    return nullptr;
                }
                shaderIdList.push_back(shaderId);
            }
            
            GLuint programId = glCreateProgram();
            for (const auto &it : shaderIdList) {
                glAttachShader(programId, it);
            }
            glLinkProgram(programId);
            glGetProgramiv(programId, GL_LINK_STATUS, &rslt);
            if (GL_FALSE == rslt) {
#ifdef _DEBUG
                int length;
                glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
                std::vector<GLchar> error(length);
                glGetProgramInfoLog(programId, length, &length, &error[0]);
                Debug::err(&error[0]);
#endif /* _DEBUG */
                return nullptr;
            }
            
            Shader *newShader = new Shader(shaderName, programId);
            for (const auto &it : shaderIdList) {
                glDeleteShader(it);
            }
            return newShader;
        } else {
            Debug::err("Load shader config:"+confPath+" failed.");
        }
        return nullptr;
    }
    
    Shader *ShaderManager::getShader(const std::string &shaderName) {
        const auto &it = m_ShaderMap.find(shaderName);
        if (it != m_ShaderMap.end())
            return it->second;
        else {
            Shader *newShader = loadShader(shaderName);
            if (nullptr != newShader)
                m_ShaderMap[shaderName] = newShader;
            return newShader;
        }
    }
    
    GLenum ShaderManager::getShaderType(const std::string &type) {
        GLenum ret = 0;
        if (type == SHADER_TYPE_VERTEX) {
            ret = GL_VERTEX_SHADER;
        } else if (type == SHADER_TYPE_FRAGMENT) {
            ret = GL_FRAGMENT_SHADER;
        } else if (type == SHADER_TYPE_TESS_EVALUATION) {
            ret = GL_TESS_CONTROL_SHADER;
        } else if (type == SHADER_TYPE_TESS_CONTROL) {
            ret = GL_TESS_EVALUATION_SHADER;
        } else if (type == SHADER_TYPE_GEOMETRY) {
            ret = GL_GEOMETRY_SHADER;
        }
        return ret;
    }
    
}
