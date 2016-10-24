// *********************************************************************
//     ____                       _____ ____
//    / ___| _ __   ___  _ __ ___|___ /|  _ \  ___ ___  _ __ ___
//    \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |/ __/ _ \| '_ ` _ \
//     ___) | |_) | (_) | | |  __/___) | |_| | (_| (_) | | | | | |
//    |____/| .__/ \___/|_|  \___|____/|____(_)___\___/|_| |_| |_|
//          |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
//  --------------------------------------------------------------------
//
//  Copyright (C) 2016 Shannon Xu
//
//  This software is distributed under the terms of the MIT License.
//  A copy of the license may be obtained at: https://opensource.org/licenses/MIT
//
// .--. --. -.. -. .. -. ..-. --.-. --. -- .- .. .-.. .-.-.- -.-. --- --

#ifndef _cMeshFilter_h_
#define _cMeshFilter_h_

#include "cComponent.h"

namespace Spore3D {
    
    class Mesh;
    
    static const std::string MESHFILTER_TYPE_NAME = "MeshFilter";
    
    class MeshFilter : public Component {
    public:
        static void registerComponentTypes(void);
        static ComponentTypeId TypeId(void);
        
        virtual void deinit(void);
    
        Mesh *getMesh(void) const;
        void setMesh(Mesh*);
        std::shared_ptr<Mesh> getSharedMesh();
        
    protected:
        MeshFilter(const std::string&);
        virtual ~MeshFilter();
        virtual MeshFilter *clone(void);
        virtual MeshFilter *cloneFromGameObject(void);
        
    private:
        static CoreObject *_alloc_obj(const std::string&);
        
        Mesh *m_Mesh;
        std::shared_ptr<Mesh> m_SharedMesh;
    };
    
}

#endif /* _cMeshFilter_h_ */