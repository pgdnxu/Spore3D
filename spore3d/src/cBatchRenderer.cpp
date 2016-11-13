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

#include "cBatchRenderer.h"
#include "cRenderCommand.h"
#include "cCamera.h"
#include "cSceneManager.h"
#include "cMeshFilter.h"
#include "cTransform.h"
#include "cMesh.h"
#include "uMath.h"
#include "uDebug.h"
#include "cScene.h"
#include "cShader.h"
#include "cRenderer.h"
#include "cMaterial.h"
#include "cColor.h"

#include <vector>

namespace Spore3D {
    
    BatchRenderer *BatchRenderer::getInstance() {
        static BatchRenderer _instance;
        return &_instance;
    }
    
    BatchRenderer::_ObjectCreate BatchRenderer::_objectCreate;
    
    BatchRenderer::_ObjectCreate::_ObjectCreate() {
        BatchRenderer::getInstance();
    }
    
    void BatchRenderer::init(void) {
        glGenVertexArrays(NumVAOs, m_VAOs);
        glBindVertexArray(m_VAOs[Triangles]);
        glGenBuffers(NumBuffers, m_Buffers);
    }
    
    void BatchRenderer::renderBatch(const RenderCommandBatch &rcb) {
        
        size_t vertexCount = 0;
        size_t vertIndexCount = 0;
        size_t texCoodIndexCount = 0;
        uint32 index = 1;
        
        
        Shader *currBatchShader = rcb.at(0)->getRenderer()->getMaterial()->getShader();
        if (nullptr == currBatchShader) return;
        currBatchShader->enable();
        
        Texture *currBatchTexture = rcb.at(0)->getRenderer()->getMaterial()->getTexture();
        if (nullptr == currBatchTexture) return;
        currBatchTexture->enable();
        
        Camera *camera = SceneManager::getInstance()->getActiveScene()->getMainCamera();
        if (nullptr == camera) return;
        
        size_t *vertexNums = new size_t[rcb.size()+1];
        vertexNums[0] = 0;
        
        Color backgroundColor = camera->getBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        
        
        
        currBatchShader->setUniform("view_matrix", camera->gameObject->transform->getWorldToLocalMatrix());
        
        currBatchShader->setUniform("pr_matrix", Mat4::PerspectiveMat(camera->getFOV(), camera->getWidth(), camera->getHeight(), camera->getNear(), camera->getFar()));
        
        currBatchShader->setUniform("ColorRamp", 0);
        glActiveTexture(GL_TEXTURE0 + 0);
        
        for (const auto &it : rcb) {
            vertexNums[index] = it->getMeshFilter()->getMesh()->vertices.size();
            vertexCount += vertexNums[index];
            vertIndexCount += it->getMeshFilter()->getMesh()->vertIndex.size();
            texCoodIndexCount += it->getMeshFilter()->getMesh()->textureIndex.size();
            index++;
        }
 
        
        //array buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[ArrayBuffer]);
        glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(Vec3), nullptr, GL_STATIC_DRAW);
        
        float *vertexBufferOffset = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        
        for (const auto &it : rcb) {
            std::vector<Vec3> &vertices = it->getMeshFilter()->getMesh()->vertices;
            for (uint32 i = 0; i < vertices.size(); i++) {
                
                Vec3 vertix = it->getTransform()->transformPoint(vertices.at(i));

                vertexBufferOffset[0] = vertix.x;
                vertexBufferOffset[1] = vertix.y;
                vertexBufferOffset[2] = vertix.z;
                
                vertexBufferOffset += 3;
            }
        }
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        //element array buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[ElementArrayBuffer]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndexCount*sizeof(uint32), nullptr, GL_STATIC_DRAW);
        uint32 *vertIndexBufferOffset = (uint32*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        
        uint32 index2 = 0;
        uint32 lastBatchVertNum = 0;
        for (const auto &it : rcb) {
            lastBatchVertNum += uint32(vertexNums[index2++]);
            std::vector<uint32> &vertIndex = it->getMeshFilter()->getMesh()->vertIndex;
            for (uint32 i = 0; i < vertIndex.size(); i++) {
                *(vertIndexBufferOffset++) = vertIndex[i] + lastBatchVertNum;
            }
        }
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        
        //texture cood buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TexCoodBuffer]);
        glBufferData(GL_ARRAY_BUFFER, texCoodIndexCount*sizeof(float), nullptr, GL_STATIC_DRAW);
        float *texCoodIndexBufferOffset = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        
        for (const auto &it : rcb) {
            uint32 dd = 0;
            float cc = 0.0f;
            Mesh *mesh = it->getMeshFilter()->getMesh();
            std::vector<uint32> textureIndex = mesh->textureIndex;
            for (uint32 i = 0; i < textureIndex.size(); i++) {
                *(texCoodIndexBufferOffset++) = mesh->uv.at(textureIndex.at(i)).x;
//                *(texCoodIndexBufferOffset++) = cc;
//                dd++;
//                if (dd%3==0) {
//                    cc+=0.01;
//                }
//                std::cout<<textureIndex.at(i)<<":"<<mesh->uv.at(textureIndex.at(i)).x<<std::endl;
            }
        }
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, GLsizei(vertIndexCount), GL_UNSIGNED_INT, nullptr);
        
        delete [] vertexNums;
    }
    
    void BatchRenderer::beginRender(void) {
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_FRONT);
    }
    
    void BatchRenderer::endRender(void) {
        glFlush();
    }
    
}
