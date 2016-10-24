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

#ifndef _uHash_h_
#define _uHash_h_

#include <string>
#include "uTypes.h"

#define INVALID_HASH    0xffffffff
#define HASH_INIT       0x811c9dc5
#define HASH_PRIME      0x01000193
#define CONVERT_BACKSLASH
#define CASE_INSENSITIVE

namespace Spore3D {
    
    class Hash {
    public:
        Hash() : m_HashValue(INVALID_HASH) {}
        
        Hash(uint32 hashValue) : m_HashValue(hashValue) {}
        
        Hash(const char *pString) {
            m_HashValue = makeHash(pString);
        }
        
        Hash(const std::string &string) {
            m_HashValue = makeHash(string.c_str());
        }
        
        Hash(const Hash &h) : m_HashValue(h.m_HashValue) {}
        
        Hash &operator=(const Hash &h) {
            m_HashValue = h.m_HashValue;
            return *this;
        }
        
        void set(const uint32 hashValue) {
            m_HashValue = hashValue;
        }
        
        uint32 get(void) const {
            return m_HashValue;
        }
        
        bool isValid(void) const {
            return INVALID_HASH != m_HashValue;
        }
        
        operator unsigned int() {
            return m_HashValue;
        }
        
        bool operator<(const Hash &h) const {
            return m_HashValue < h.m_HashValue;
        }
        
        bool operator>(const Hash &h) const {
            return m_HashValue > h.m_HashValue;
        }
        
        bool operator<=(const Hash &h) const {
            return m_HashValue <= h.m_HashValue;
        }
        
        bool operator>=(const Hash &h) const {
            return m_HashValue >= h.m_HashValue;
        }
        
        bool operator==(const Hash &h) const {
            return m_HashValue == h.m_HashValue;
        }
        
        bool operator!=(const Hash &h) const {
            return m_HashValue != h.m_HashValue;
        }
        
    private:
        uint32 makeHash(const char *pString) {
            if (!pString || !pString[0])
                return INVALID_HASH;
            
            const unsigned char* strOffset = (const unsigned char*)pString;
            uint32 hash = HASH_INIT;
            
            while (*strOffset)
            {
                hash *= HASH_PRIME;
                
                char c = *strOffset++;
                
#ifdef CONVERT_BACKSLASH
                if (c == '\\')
                {
                    c = '/';
                }
#endif
                
#ifdef CASE_INSENSITIVE
                if ((c >= 'a') && (c <= 'z'))
                {
                    c -= 'a' - 'A';
                }
#endif
                hash ^= (uint32)c;
            }
            return hash;
        }
        
        uint32 m_HashValue;
    };
    
}

#endif /* _uHash_h_ */
