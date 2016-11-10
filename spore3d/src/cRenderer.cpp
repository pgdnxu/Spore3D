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

#include "cRenderer.h"
#include "uDebug.h"
#include "cRenderCommand.h"
#include "uTypes.h"
#include "cTransform.h"
#include "cRenderQueue.h"
#include "cMeshFilter.h"

namespace Spore3D {
    
    CoreObject *Renderer::_alloc_obj(const std::string &name) {
        return new Renderer(name);
    }
    
    void Renderer::registerComponentTypes(void) {
        ObjectManager::getInstance()->registerComponentType(Renderer::TypeId(), Renderer::_alloc_obj, nullptr, RENDERER_TYPE_NAME);
    }
    
    ComponentTypeId Renderer::TypeId(void) {
        static Hash _componentTypeId(RENDERER_TYPE_NAME);
        return _componentTypeId.get();
    }
    
    void Renderer::deinit(void) {
        
    }
    
    Renderer::Renderer(const std::string &name)
    : Component(name) {
        m_ComponentTypeId = TypeId();
    }
    
    Renderer::~Renderer() {
        Debug::log("Renderer::~Renderer()"+toString());
    }
    
    void Renderer::setShader(Shader *shader) {
        m_Shader = shader;
    }
    
    Shader *Renderer::getShader(void) const {
        return m_Shader;
    }
    
    void Renderer::setTexture(Texture *texture) {
        m_Texture = texture;
    }
    
    Texture *Renderer::getTexture(void) const {
        return m_Texture;
    }
    
    void Renderer::render(void) {
        Transform *transform = gameObject->transform;
        if (nullptr != transform) {
            for (uint32 index = 0; index < transform->getChildCount(); index++) {
                Transform *child = transform->getChild(index);
                if (nullptr != child) {
                    Renderer *cr = child->gameObject->getComponent<Renderer>();
                    if (nullptr != cr) {
                        cr->render();
                    }
                }
            }

            RenderQueue::getInstance()->addCommand(new RenderCommand(this, getComponent<MeshFilter>()));
        }
    }
}
