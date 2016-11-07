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

#include "cBounds.h"

namespace Spore3D {
    
    Bounds::Bounds(const Vec3 &center, const Vec3 &size) {
        m_Center = center;
        m_Size = size;
        m_Extents = size / 2;
        m_Min = Vec3(center.x-m_Extents.x, center.y-m_Extents.y, center.z-m_Extents.z);
        m_Max = Vec3(center.x+m_Extents.x, center.y+m_Extents.y, center.z+m_Extents.z);
    }
    
    Vec3 Bounds::closestPoint(const Vec3 &point) const {
        if (contains(point)) return point;
        Vec3 ret(math::NO_INIT);
        
        if (point.x < m_Min.x) {
            ret.x = m_Min.x;
        } else if (point.x > m_Max.x) {
            ret.x = m_Max.x;
        } else {
            ret.x = point.x;
        }
        
        if (point.y < m_Min.y) {
            ret.y = m_Min.y;
        } else if (point.y > m_Max.y) {
            ret.y = m_Max.y;
        } else {
            ret.y = point.y;
        }
        
        if (point.z < m_Min.z) {
            ret.z = m_Min.z;
        } else if (point.z > m_Max.z) {
            ret.z = m_Max.z;
        } else {
            ret.z = point.z;
        }
        
        return ret;
    }
    
    bool Bounds::contains(const Vec3 &point) const {
        if (isEmpty()) return false;
        return  (point.x >= m_Min.x) && (point.y >= m_Min.y) &&
                (point.z >= m_Min.z) && (point.x <= m_Max.x) &&
                (point.y <= m_Max.y) && (point.z <= m_Max.z);
    }
    
    void Bounds::encapsulate(const Vec3 &point) {
        if (point.x < m_Min.x) m_Min.x = point.x;
        if (point.y < m_Min.y) m_Min.y = point.y;
        if (point.z < m_Min.z) m_Min.z = point.z;
        if (point.x > m_Max.x) m_Max.x = point.x;
        if (point.y > m_Max.y) m_Max.y = point.y;
        if (point.z > m_Max.z) m_Max.z = point.z;
    }
    
    void Bounds::expand(const float amount) {
        m_Size.x += amount;
        m_Size.y += amount;
        m_Size.z += amount;
        m_Extents = m_Size / 2;
        m_Min = Vec3(m_Size.x-m_Extents.x, m_Size.y-m_Extents.y, m_Size.z-m_Extents.z);
        m_Max = Vec3(m_Size.x+m_Extents.x, m_Size.y+m_Extents.y, m_Size.z+m_Extents.z);
        
    }
    
    bool Bounds::intersectRay(const Ray &ray) {
        using namespace math;
        Vec3 dirfrac(1.0f/ray.getDirection().x, 1.0f/ray.getDirection().y, 1.0f/ray.getDirection().z);
        
        float t1 = (m_Min.x - ray.getOrigin().x) * dirfrac.x;
        float t2 = (m_Max.x - ray.getOrigin().x) * dirfrac.x;
        float t3 = (m_Min.y - ray.getOrigin().y) * dirfrac.y;
        float t4 = (m_Max.y - ray.getOrigin().y) * dirfrac.y;
        float t5 = (m_Min.z - ray.getOrigin().z) * dirfrac.z;
        float t6 = (m_Max.z - ray.getOrigin().z) * dirfrac.z;
        
        float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
        float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));
        
        if (tmax < 0) return false;
        if (tmin > tmax) return false;
        return true;
    }
    
    bool Bounds::interset(const Bounds &bounds) const {
        if (m_Min.x > bounds.getMax().x) return false;
        if (m_Min.y > bounds.getMax().y) return false;
        if (m_Min.z > bounds.getMax().z) return false;
        if (m_Max.x < bounds.getMin().x) return false;
        if (m_Max.y < bounds.getMin().y) return false;
        if (m_Max.z < bounds.getMin().z) return false;
        return true;
    }
    
    void Bounds::setMinMax(const Vec3 &min, const Vec3 &max) {
        m_Min = min;
        m_Max = max;
    }
    
    float Bounds::sqrDistance(const Vec3 &point) {
        Vec3 cPoint = closestPoint(point);
        if (point == cPoint)
            return 0.0f;
        return (point-cPoint).sqrLength();
    }
    
    bool Bounds::isEmpty(void) const {
        return (m_Min.x > m_Max.x) || (m_Min.y > m_Max.y) || (m_Min.z > m_Max.z);
    }
    
}
