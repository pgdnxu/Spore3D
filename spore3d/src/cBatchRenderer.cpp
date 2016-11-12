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
        
        size_t *vertexNums = new size_t[rcb.size()+1];
        size_t vertexCount = 0;
        size_t vertIndexCount = 0;
        uint32 index = 1;
        vertexNums[0] = 0;
        
        Shader *currBatchShader = rcb.at(0)->getRenderer()->getMaterial()->getShader();
        if (nullptr == currBatchShader) {
            return;
        }
        currBatchShader->enable();
        
        Camera *camera = SceneManager::getInstance()->getActiveScene()->getMainCamera();
        if (nullptr == camera) {
            return;
        }
        
        Viewport vp = camera->getViewport();
        Color backgroundColor = camera->getBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        
        currBatchShader->setUniform("view_matrix", camera->gameObject->transform->getWorldToLocalMatrix());
        
        currBatchShader->setUniform("pr_matrix", Mat4::PerspectiveMat(60, vp.width, vp.height, 0, 1000));
        
        for (const auto &it : rcb) {
            vertexNums[index] = it->getMeshFilter()->getMesh()->vertices.size();
            vertexCount += vertexNums[index];
            vertIndexCount += it->getMeshFilter()->getMesh()->vertIndex.size();
            index++;
        }
        
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

        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[ElementArrayBuffer]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndexCount*sizeof(uint32), nullptr, GL_STATIC_DRAW);
        uint32 *vertIndexBufferOffset = (uint32*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        
        uint32 index2 = 0;
        uint32 lastBatchVertNum = 0;
        for (const auto &it : rcb) {
            lastBatchVertNum += uint32(vertexNums[index2++]);
            std::vector<uint32> &vertIndex = it->getMeshFilter()->getMesh()->vertIndex;
            for (uint32 i = 0; i < vertIndex.size(); i++) {
                *(vertIndexBufferOffset) = vertIndex[i] + lastBatchVertNum;
                vertIndexBufferOffset++;
            }
        }

        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glDrawElements(GL_TRIANGLES, GLsizei(vertIndexCount), GL_UNSIGNED_INT, nullptr);
        
        delete [] vertexNums;
    }
    
    void BatchRenderer::beginRender(void) {
        m_ArrayBufferOffset = 0;
    }
    
    void BatchRenderer::endRender(void) {
        glFlush();
    }
    
}
