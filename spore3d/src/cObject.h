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

#ifndef _cObject_h_
#define _cObject_h_

#include <set>
#include <map>
#include <string>

#include "uTypes.h"
#include "uHash.h"


namespace Spore3D {
    
    class CoreObject {
    public:
        CObjectId getInstanceId(void) const { return m_InstanceID->get(); }
        std::string toString(void) const { return m_Name; }
        
        
        CoreObject(const std::string &name);
        virtual ~CoreObject() = 0;
        
        template<typename T> static T *Instantiate(T *object);
        static CoreObject *Instantiate(CoreObject*);
        static void Destory(CoreObject*);
    
    protected:
        virtual void deinit(void);
        virtual CoreObject *clone(void) = 0;
        
    private:
        std::string m_Name;
        Hash *m_InstanceID = nullptr;
        
        static uint32 _InstanceNumber;
    };
    
    typedef CoreObject* (*CreationMethod)(const std::string &);
    typedef void (*DestructionMethod)(CoreObject *);
    
    template<typename T>
    T *CoreObject::Instantiate(T *object) {
        return static_cast<T*>(CoreObject::Instantiate(static_cast<CoreObject*>(object)));
    }
    
}

#endif /* _cObject_h_ */
