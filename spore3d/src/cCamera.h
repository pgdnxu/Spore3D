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

#ifndef _cCamera_h_
#define _cCamera_h_

#include <vector>

#include "cBehaviour.h"
#include "uTypes.h"
#include "cColor.h"
#include "uMath.h"


namespace Spore3D {
    
    const std::string CAMERA_TYPE_NAME = "Camera";
    
    enum CameraClearFlags {
        Skybox,
        SolidColor,
        Depth,
        Nothing
    };
    
    struct Viewport {
        float x;
        float y;
        float width;
        float height;
        Viewport() : x(0.f), y(0.f), width(0.f), height(0.f) {}
        Viewport(const float x, const float y, const float width, const float height)
        :x(x), y(y), width(width), height(height) {}
    };
    
    class Camera : public Behaviour {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        static std::vector<Camera*> allCameras(void);
        static uint32 allCamerasCount(void);
        //TODO : static Camera *current(void);
        //TODO : static Gamera *main(void);
        
        CameraClearFlags clearFlags;
        
        void setBackgroundColor(const Color &color) {
            m_BackgroundColor = color;
        }
        Color getBackgroundColor(void) const {
            return m_BackgroundColor;
        }
        
        Mat4 getCameraToWorldMatrix(void) const;
        void setViewport(const Viewport &viewport) { m_Viewport = viewport;  };
        Viewport getViewport(void) { return m_Viewport; }
        
        Camera *setFOV(const float fov) { m_FOV = fov; return this; }
        Camera *setWidth(const float width) { m_Width = width; return this; }
        Camera *setHeight(const float height) { m_Height = height; return this; }
        Camera *setNear(const float near) { m_Near = near; return this; }
        Camera *setFar(const float far) { m_Far = far; return this; }
        float getFOV(void) const { return m_FOV; }
        float getWidth(void) const { return m_Width; }
        float getHeight(void) const { return m_Height; }
        float getNear(void) const { return m_Near; }
        float getFar(void) const { return m_Far; }
        
    protected:
        Camera(const std::string&);
        virtual ~Camera();
        virtual Camera *clone(void) override;
        virtual Camera *cloneFromGameObject(void) override;
        
    private:
        static CoreObject *_alloc_obj(const std::string&);
        
        Color m_BackgroundColor;
        
        Viewport m_Viewport;
        
        float m_FOV;
        float m_Width;
        float m_Height;
        float m_Near;
        float m_Far;
    };
    
}

#endif /* _cCamera_h_ */
