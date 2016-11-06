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

#ifndef _uMath_h_
#define _uMath_h_

#include <iomanip>
#include <ostream>
#include <cmath>

#include "uTypes.h"

namespace Spore3D {

    namespace math {
        
        //constants
        
        const float PI = 3.141592654f;
        const float Epsilon = 0.000001f;
        
        enum NoInitHint {
            NO_INIT
        };
        
        static inline float degToRad(const float f) {
            // f * PI / 180
            return f * 0.017453293f;
        }
        
        static inline float radToDeg(const float f) {
            // f * 180 / PI
            return f * 57.29577951f;
        }
        
        static inline float clamp(const float f, const float min, const float max) {
            return f < min ? min : (f > max ? max : f);
        }
        
        static inline float fmin(const float a, const float b) {
            return a > b ? b : a;
        }
        
        static inline float fmax(const float a, const float b) {
            return a > b ? a : b;
        }
        
        static inline float degMap(float f) {
            int32 tf = int32(f);
            f -= tf - (tf % 360);
            return f > 180.f ? -(360.f - f) : f;
        }
        
    }
    
    
    
    
    //Vector
    
    class Vec3 {
    public:
        
        static const Vec3 up;
        static const Vec3 right;
        static const Vec3 forward;
        
        float x, y, z;
        
        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        
        explicit Vec3(math::NoInitHint) {}
        
        Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
        
        Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}
        
        float &operator[](const uint32 index) {
            return *(&x + index);
        }
        
        bool operator==(const Vec3 &v) const {
            return (x > v.x - math::Epsilon && x < v.x + math::Epsilon &&
                    y > v.y - math::Epsilon && y < v.y + math::Epsilon &&
                    z > v.z - math::Epsilon && z < v.z + math::Epsilon);
        }
        
        bool operator!=(const Vec3 &v) const {
            return (x < v.x - math::Epsilon || x > v.x + math::Epsilon ||
                    y < v.y - math::Epsilon || y > v.y + math::Epsilon ||
                    z < v.z - math::Epsilon || z > v.z + math::Epsilon);
        }
        
        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        }
        
        Vec3 operator+(const Vec3 &v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }
        
        Vec3 &operator+=(const Vec3 &v) {
            return *this = *this + v;
        }
        
        Vec3 operator-(const Vec3 &v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }
        
        Vec3 &operator-=(const Vec3 &v) {
            return *this = *this - v;
        }
        
        Vec3 operator*(const float f) const {
            return Vec3(x * f, y * f, z * f);
        }
        
        Vec3 &operator*=(const float f) {
            return *this = *this * f;
        }
        
        Vec3 operator/(const float f) const {
            return Vec3(x / f, y / f, z / f);
        }
        
        Vec3 &operator/=(const float f) {
            return *this = *this / f;
        }
        
        float dot(const Vec3 &v) const {
            return x * v.x + y * v.y + z * v.z;
        }
        
        Vec3 cross(const Vec3 &v) const {
            return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }
        
        float length() const {
            return sqrtf(x * x + y * y + z * z);
        }
        
        Vec3 normalized() const {
            float len = length();
            if (len > 0) {
                float invLen = 1.0f / length();
                return Vec3(x * invLen, y * invLen, z * invLen);
            } else {
                return Vec3();
            }
        }
        
        void normalize() {
            float len = length();
            if (len > 0) {
                float invLen = 1.0f / length();
                x *= invLen;
                y *= invLen;
                z *= invLen;
            }
        }
        
        Vec3 lerp(const Vec3 &v, const float f) const {
            return Vec3(x + (v.x - x) * f, y + (v.y - y) * f, z + (v.z - z) * f);
        }
        
        friend std::ostream &operator << (std::ostream &out, const Vec3 &v) {
            out<<std::setprecision(5)<<"Vec3("<<v.x<<", "<<v.y<<", "<<v.z<<")";
            return out;
        }
        
    };
    
    
    
    class Vec2 {
    public:
        float x, y;
        
        Vec2() : x(0.0f), y(0.0f) {}
        
        explicit Vec2(math::NoInitHint) {}
        
        Vec2(const float x, const float y) : x(x), y(y) {}
        
        Vec2(const Vec2 &v) : x(v.x), y(v.y) {}
        
        float &operator[](const uint32 index) {
            return *(&x + index);
        }
        
        bool operator==(const Vec2 &v) const {
            return (x > v.x - math::Epsilon && x < v.x + math::Epsilon &&
                    y > v.y - math::Epsilon && y < v.y + math::Epsilon);
        }
        
        bool operator!=(const Vec2 &v) const {
            return (x < v.x - math::Epsilon || x > v.x + math::Epsilon ||
                    y < v.y - math::Epsilon || y > v.y + math::Epsilon);
        }
        
        Vec2 operator-() const {
            return Vec2(-x, -y);
        }
        
        Vec2 operator+(const Vec2 &v) const {
            return Vec2(x + v.x, y + v.y);
        }
        
        Vec2 &operator+=(const Vec2 &v) {
            return *this = *this + v;
        }
        
        Vec2 operator-(const Vec2 &v) const {
            return Vec2(x - v.x, y - v.y);
        }
        
        Vec2 &operator-=(const Vec2 &v) {
            return *this = *this - v;
        }
        
        Vec2 operator*(const float f) const {
            return Vec2(x * f, y * f);
        }
        
        Vec2 &operator*=(const float f) {
            return *this = *this * f;
        }
        
        Vec2 operator/(const float f) const {
            return Vec2(x / f, y / f);
        }
        
        Vec2 &operator/=(const float f) {
            return *this = *this / f;
        }
        
        float dot(const Vec2 &v) const {
            return x * v.x + y * v.y;
        }
        
        Vec3 cross(const Vec2 &v) const {
            return Vec3(0.0f, 0.0f, x * v.y - y * v.x);
        }
        
        float length() const {
            return sqrtf(x * x + y * y);
        }
        
        Vec2 normalized() const {
            float len = length();
            if (len > 0) {
                float invLen = 1.0f / length();
                return Vec2(x * invLen, y * invLen);
            } else {
                return Vec2();
            }
        }
        
        void normalize() {
            float len = length();
            if (len > 0) {
                float invLen = 1.0f / length();
                x *= invLen;
                y *= invLen;
            }
        }
        
        Vec2 lerp(const Vec2 &v, const float f) const {
            return Vec2(x + (v.x - x) * f, y + (v.y - y) * f);
        }
        
        friend std::ostream &operator << (std::ostream &out, const Vec2 &v) {
            out<<std::setprecision(5)<<"Vec2("<<v.x<<", "<<v.y<<")";
            return out;
        }
    };
    
    class Vec4 {
    public:
        float x, y, z, w;
        
        Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        
        explicit Vec4(math::NoInitHint) {}
        
        Vec4(const float x, const float y, const float z, const float w) :
        x(x), y(y), z(z), w(w) {}
        
        explicit Vec4(const Vec3 &v) : x(v.x), y(v.y), z(v.z), w(1.0f) {}
        
        Vec4 operator-() const {
            return Vec4(-x, -y, -z, -w);
        }
        
        Vec4 operator+(const Vec4 &v) const {
            return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        
        Vec4 &operator+=(const Vec4 &v) {
            return *this = *this + v;
        }
        
        Vec4 operator-(const Vec4 &v) const {
            return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }
        
        Vec4 operator-=(const Vec4 &v) {
            return *this = *this - v;
        }
        
        Vec4 operator*(const float f) const {
            return Vec4(x * f, y * f, z * f, w * f);
        }
        
        Vec4 &operator*=(const float f) {
            return *this = *this * f;
        }
        
        friend std::ostream &operator << (std::ostream &out, const Vec4 &v) {
            out<<std::setprecision(5)<<"Vec4("<<v.x<<", "<<v.y<<", "<<v.z<<", "<<v.w<<")";
            return out;
        }
    };
    
    class Quaternion {
    public:
        
        static const Quaternion identity;
        
        float x, y, z, w;
        
        Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
        
        explicit Quaternion(math::NoInitHint) {}
        
        explicit Quaternion(const float x, const float y, const float z, const float w) :
        x(x), y(y), z(z), w(w) {}
        
        Quaternion(const Quaternion &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
        
        Quaternion(const float eulerX, const float eulerY, const float eulerZ) {
            float exr = math::degToRad(eulerX);
            float eyr = math::degToRad(eulerY);
            float ezr = math::degToRad(eulerZ);
            Quaternion roll(sinf(exr * 0.5f), 0.0f, 0.0f, cosf(exr * 0.5f));
            Quaternion pitch(0.0f, sinf(eyr * 0.5f), 0.0f, cosf(eyr * 0.5f));
            Quaternion yaw(0.0f, 0.0f, sinf(ezr * 0.5f), cosf(ezr * 0.5f));
            
            // Order: y * x * z means z->x->y
            *this = pitch * roll * yaw;
        }
        
        Quaternion &operator=(const Quaternion &q) {
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
            return *this;
        }
        
        Quaternion operator*(const Quaternion &q) const {
            return Quaternion(y * q.z - z * q.y + q.x * w + x * q.w,
                              z * q.x - x * q.z + q.y * w + y * q.w,
                              x * q.y - y * q.x + q.z * w + z * q.w,
                              w * q.w - (x * q.x + y * q.y + z * q.z));
        }
        
        Quaternion &operator*=(const Quaternion &q) {
            return *this = *this * q;
        }
        
        static Quaternion eulerAngle(const float eulerX, const float eulerY, const float eulerZ) {
            return Quaternion(eulerX, eulerY, eulerZ);
        }
        
        Vec3 eulerAngle() const {
            Vec3 re(math::NO_INIT);
            
            re.y = math::radToDeg(atan2f(x*z + w*y, 0.5f - (x*x + y*y)));
            re.x = math::radToDeg(asinf(-2.0f * (y*z - w*x)));
            re.z = math::radToDeg(atan2f(x*y + w*z, 0.5f - (x*x + z*z)));
            
            return re;
        }
        
        Quaternion slerp(const Quaternion &q, const float t) const {
            Quaternion tq(q);
            
            float cosOmega = w * q.w + x * q.x + y * q.y + z * q.z;
            
            if (cosOmega < 0.0f) {
                tq.x = -q.x;
                tq.y = -q.y;
                tq.z = -q.z;
                tq.w = -q.w;
                cosOmega = -cosOmega;
            }
            
            float k0 = 1.0f - t, k1 = t;
            if (1.0f - cosOmega > 0.001f) {
                float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
                float omega = atan2f(sinOmega, cosOmega);
                float invSinOmega =  1.0f / sinOmega;
                k0 = sinf((1.0f - t) * omega) * invSinOmega;
                k1 = sinf(t * omega) * invSinOmega;
            }
            
            return Quaternion(x * k0 + tq.x * k1, y * k0 + tq.y * k1 ,
                              z * k0 + tq.z * k1, w * k0 + tq.w * k1);
        }
        
        Quaternion nlerp(const Quaternion &q, const float t) const {
            Quaternion tq;
            float cosOmega = x * q.x + y * q.y + z * q.z + w * q.w;
            
            if( cosOmega < 0.0f )
                tq = Quaternion(x + (-q.x - x) * t, y + (-q.y - y) * t,
                                z + (-q.z - z) * t, w + (-q.w - w) * t);
            else
                tq = Quaternion(x + (q.x - x) * t, y + (q.y - y) * t,
                                z + (q.z - z) * t, w + (q.w - w) * t);
            
            float len = sqrtf(tq.x * tq.x + tq.y * tq.y + tq.z * tq.z + tq.w * tq.w);
            if (len > 0.0f) {
                float invLen = 1.0f / len;
                return Quaternion(tq.x * invLen, tq.y * invLen, tq.z * invLen, tq.w * invLen);
            } else {
                return Quaternion();
            }
        }
        
        float module() const {
            return sqrtf(w*w + x*x + y*y + z*z);
        }
        
        Quaternion &conjugated() {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }
        
        Quaternion conjugate() const {
            Quaternion re(*this);
            return re.conjugated();
        }
        
        Quaternion &inversed() {
            float im = 1.0f/module();
            conjugated();
            x *= im;
            y *= im;
            z *= im;
            w *= im;
            return *this;
        }
        
        Quaternion inverse() const {
            Quaternion re(*this);
            return re.inversed();
        }
        
        friend std::ostream &operator << (std::ostream &out, const Quaternion &q) {
            out<<std::setprecision(5)<<"Quaternion("<<q.x<<", "<<q.y<<", "<<q.z<<", "<<q.w<<")";
            return out;
        }
    };
    
    class Mat4 {
    public:
        
        //column-major order 4*4 matrix class
        
        union {
            float e[4][4];
            float s[16];
        };
        
        Mat4() {
            e[0][0] = 1.0f; e[1][0] = 0.0f; e[2][0] = 0.0f; e[3][0] = 0.0f;
            e[0][1] = 0.0f; e[1][1] = 1.0f; e[2][1] = 0.0f; e[3][1] = 0.0f;
            e[0][2] = 0.0f; e[1][2] = 0.0f; e[2][2] = 1.0f; e[3][2] = 0.0f;
            e[0][3] = 0.0f; e[1][3] = 0.0f; e[2][3] = 0.0f; e[3][3] = 1.0f;
        }
        
        explicit Mat4(math::NoInitHint) {}
        
        Mat4(const float *fa) {
            for (uint32 i = 0; i < 4; i ++) {
                for (uint32 j = 0; j < 4; j++) {
                    e[i][j] = fa[i * 4 + j];
                }
            }
        }
        
        Mat4(const Vec3 &col1, const Vec3 &col2, const Vec3 &col3) {
            e[0][0] = col1.x; e[1][0] = col2.x; e[2][0] = col3.x; e[3][0] = 0.0f;
            e[0][1] = col1.y; e[1][1] = col2.y; e[2][1] = col3.y; e[3][1] = 0.0f;
            e[0][2] = col1.z; e[1][2] = col2.z; e[2][2] = col3.z; e[3][2] = 0.0f;
            e[0][3] = 0.0f;   e[1][3] = 0.0f;   e[2][3] = 0.0f;   e[3][3] = 1.0f;
        }
        
        Mat4(const Quaternion &q) {
            float x2 = q.x + q.x, y2 = q.y + q.y, z2 = q.z + q.z;
            float xx = q.x * x2,  xy = q.x * y2,  xz = q.x * z2;
            float yy = q.y * y2,  yz = q.y * z2,  zz = q.z * z2;
            float wx = q.w * x2,  wy = q.w * y2,  wz = q.w * z2;
            
            e[0][0] = 1.0f - (yy + zz);  e[1][0] = xy - wz;
            e[2][0] = xz + wy;        e[3][0] = 0.0f;
            e[0][1] = xy + wz;        e[1][1] = 1.0f - (xx + zz);
            e[2][1] = yz - wx;        e[3][1] = 0.0f;
            e[0][2] = xz - wy;        e[1][2] = yz + wx;
            e[2][2] = 1.0f - (xx + yy);  e[3][2] = 0.0f;
            e[0][3] = 0.0f;              e[1][3] = 0.0f;
            e[2][3] = 0.0f;              e[3][3] = 1.0f;
        }
        
        Mat4 operator+(const Mat4 &m) const {
            Mat4 rm(math::NO_INIT);
            
            rm.s[0] = s[0] + m.s[0];
            rm.s[1] = s[1] + m.s[1];
            rm.s[2] = s[2] + m.s[2];
            rm.s[3] = s[3] + m.s[3];
            rm.s[4] = s[4] + m.s[4];
            rm.s[5] = s[5] + m.s[5];
            rm.s[6] = s[6] + m.s[6];
            rm.s[7] = s[7] + m.s[7];
            rm.s[8] = s[8] + m.s[8];
            rm.s[9] = s[9] + m.s[9];
            rm.s[10] = s[10] + m.s[10];
            rm.s[11] = s[11] + m.s[11];
            rm.s[12] = s[12] + m.s[12];
            rm.s[13] = s[13] + m.s[13];
            rm.s[14] = s[14] + m.s[14];
            rm.s[15] = s[15] + m.s[15];
            return rm;
        }
        
        Mat4 &operator+=(const Mat4 &m) {
            return *this = *this + m;
        }
        
        Mat4 operator*(const Mat4 &m) const {
            Mat4 rm(math::NO_INIT);
            
            rm.s[0] = s[0] * m.s[0] + s[4] * m.s[1] + s[8] * m.s[2] + s[12] * m.s[3];
            rm.s[1] = s[1] * m.s[0] + s[5] * m.s[1] + s[9] * m.s[2] + s[13] * m.s[3];
            rm.s[2] = s[2] * m.s[0] + s[6] * m.s[1] + s[10] * m.s[2] + s[14] * m.s[3];
            rm.s[3] = s[3] * m.s[0] + s[7] * m.s[1] + s[11] * m.s[2] + s[15] * m.s[3];
            
            rm.s[4] = s[0] * m.s[4] + s[4] * m.s[5] + s[8] * m.s[6] + s[12] * m.s[7];
            rm.s[5] = s[1] * m.s[4] + s[5] * m.s[5] + s[9] * m.s[6] + s[13] * m.s[7];
            rm.s[6] = s[2] * m.s[4] + s[6] * m.s[5] + s[10] * m.s[6] + s[14] * m.s[7];
            rm.s[7] = s[3] * m.s[4] + s[7] * m.s[5] + s[11] * m.s[6] + s[15] * m.s[7];
            
            rm.s[8] = s[0] * m.s[8] + s[4] * m.s[9] + s[8] * m.s[10] + s[12] * m.s[11];
            rm.s[9] = s[1] * m.s[8] + s[5] * m.s[9] + s[9] * m.s[10] + s[13] * m.s[11];
            rm.s[10] = s[2] * m.s[8] + s[6] * m.s[9] + s[10] * m.s[10] + s[14] * m.s[11];
            rm.s[11] = s[3] * m.s[8] + s[7] * m.s[9] + s[11] * m.s[10] + s[15] * m.s[11];
            
            rm.s[12] = s[0] * m.s[12] + s[4] * m.s[13] + s[8] * m.s[14] + s[12] * m.s[15];
            rm.s[13] = s[1] * m.s[12] + s[5] * m.s[13] + s[9] * m.s[14] + s[13] * m.s[15];
            rm.s[14] = s[2] * m.s[12] + s[6] * m.s[13] + s[10] * m.s[14] + s[14] * m.s[15];
            rm.s[15] = s[3] * m.s[12] + s[7] * m.s[13] + s[11] * m.s[14] + s[15] * m.s[15];
            
            return rm;
        }
        
        Mat4 &operator*=(const Mat4 &m) {
            return *this = *this * m;
        }
        
        Mat4 operator*(const float f) {
            Mat4 rm(*this);
            
            rm.s[0]  *= f; rm.s[1]  *= f; rm.s[2]  *= f; rm.s[3]  *= f;
            rm.s[4]  *= f; rm.s[5]  *= f; rm.s[6]  *= f; rm.s[7]  *= f;
            rm.s[8]  *= f; rm.s[9]  *= f; rm.s[10] *= f; rm.s[11] *= f;
            rm.s[12] *= f; rm.s[13] *= f; rm.s[14] *= f; rm.s[15] *= f;
            
            return rm;
        }
        
        Mat4 &operator*=(const float f) {
            return *this = *this * f;
        }
        
        Vec3 operator*(const Vec3 &v) const {
            return Vec3(v.x * e[0][0] + v.y * e[1][0] + v.z * e[2][0] + e[3][0],
                        v.x * e[0][1] + v.y * e[1][1] + v.z * e[2][1] + e[3][1],
                        v.x * e[0][2] + v.y * e[1][2] + v.z * e[2][2] + e[3][2]);
        }
        
        Vec4 operator*(const Vec4 &v) const {
            return Vec4(v.x * e[0][0] + v.y * e[1][0] + v.z * e[2][0] + v.w * e[3][0],
                        v.x * e[0][1] + v.y * e[1][1] + v.z * e[2][1] + v.w * e[3][1],
                        v.x * e[0][2] + v.y * e[1][2] + v.z * e[2][2] + v.w * e[3][2],
                        v.x * e[0][3] + v.y * e[1][3] + v.z * e[2][3] + v.w * e[3][3]);
        }
        
        void translate(const float x, const float y, const float z) {
            *this = TransMat(x, y, z) * *this;
        }
        
        void scale(const float x, const float y, const float z) {
            *this = ScaleMat(x, y, z) * *this;
        }
        
        void rotate(const float eulerX, const float eulerY, const float eulerZ) {
            *this = RotMat(eulerX, eulerY, eulerZ) * *this;
        }
        
        static Mat4 TransMat(const float x, const float y, const float z) {
            Mat4 rm;
            
            rm.e[3][0] = x;
            rm.e[3][1] = y;
            rm.e[3][2] = z;
            
            return rm;
        }
        
        static Mat4 TransMat(const Vec3 &v) {
            return TransMat(v.x, v.y, v.z);
        }
        
        static Mat4 ScaleMat(const float x, const float y, const float z) {
            Mat4 rm;
            
            rm.e[0][0] = x;
            rm.e[1][1] = y;
            rm.e[2][2] = z;
            
            return rm;
        }
        
        static Mat4 RotMat(const Quaternion &q) {
            return Mat4(q);
        }
        
        static Mat4 RotMat(const float eulerX, const float eulerY, const float eulerZ) {
            return Mat4(Quaternion(eulerX, eulerY, eulerZ));
        }
        
        static Mat4 RotMat(Vec3 axis, const float angle) {
            float rad = math::degToRad(angle);
            axis *= sinf(rad * 0.5f);
            return Mat4(Quaternion(axis.x, axis.y, axis.z, cosf(rad * 0.5f)));
        }
        
        static Mat4 PerspectiveMat(const float left, const float right, const float bottom, const float top, const float near, const float far) {
            Mat4 rm;
            
            rm.s[0] = -2.0f * near / (right - left);
            rm.s[5] = -2.0f * near / (top - bottom);
            rm.s[8] = (right + left) / (right - left);
            rm.s[9] = (top + bottom) / (top - bottom);
            rm.s[10] = (far + near) / (far - near);
            rm.s[11] = -1.0f;
            rm.s[14] = -2.0f * far * near / (far - near);
            rm.s[15] = 0.0f;
            
            return rm;
        }
        
        static Mat4 OrthoMat(const float left, const float right, const float bottom, const float top, const float near, const float far) {
            Mat4 rm;
            
            rm.s[0] = 2.0f / (right - left);
            rm.s[5] = 2.0f / (top - bottom);
            rm.s[10] = -2.0f / (far - near);
            rm.s[12] = -(right + left) / (right - left);
            rm.s[13] = -(top + bottom) / (top - bottom);
            rm.s[14] = -(far + near) / (far - near);
            rm.s[15] = 1.0f;
            
            return rm;
        }
        
        void transpose() {
            for(uint32 i = 0; i < 4; i++) {
                for(uint32 j = i + 1; j < 4; j++) {
                    float tmp = e[i][j];
                    e[i][j] = e[j][i];
                    e[j][i] = tmp;
                }
            }
        }
        
        Mat4 transposed() const {
            Mat4 rm(*this);
            rm.transpose();
            return rm;
        }
        
        float determinant() const {
            return
            e[0][3]*e[1][2]*e[2][1]*e[3][0] - e[0][2]*e[1][3]*e[2][1]*e[3][0] - e[0][3]*e[1][1]*e[2][2]*e[3][0] + e[0][1]*e[1][3]*e[2][2]*e[3][0] +
            e[0][2]*e[1][1]*e[2][3]*e[3][0] - e[0][1]*e[1][2]*e[2][3]*e[3][0] - e[0][3]*e[1][2]*e[2][0]*e[3][1] + e[0][2]*e[1][3]*e[2][0]*e[3][1] +
            e[0][3]*e[1][0]*e[2][2]*e[3][1] - e[0][0]*e[1][3]*e[2][2]*e[3][1] - e[0][2]*e[1][0]*e[2][3]*e[3][1] + e[0][0]*e[1][2]*e[2][3]*e[3][1] +
            e[0][3]*e[1][1]*e[2][0]*e[3][2] - e[0][1]*e[1][3]*e[2][0]*e[3][2] - e[0][3]*e[1][0]*e[2][1]*e[3][2] + e[0][0]*e[1][3]*e[2][1]*e[3][2] +
            e[0][1]*e[1][0]*e[2][3]*e[3][2] - e[0][0]*e[1][1]*e[2][3]*e[3][2] - e[0][2]*e[1][1]*e[2][0]*e[3][3] + e[0][1]*e[1][2]*e[2][0]*e[3][3] +
            e[0][2]*e[1][0]*e[2][1]*e[3][3] - e[0][0]*e[1][2]*e[2][1]*e[3][3] - e[0][1]*e[1][0]*e[2][2]*e[3][3] + e[0][0]*e[1][1]*e[2][2]*e[3][3];
        }
        
        Mat4 inverted() const {
            Mat4 rm(math::NO_INIT);
            
            float d = determinant();
            if( d == 0 ) return rm;
            d = 1.0f / d;
            
            rm.e[0][0] = d * (e[1][2]*e[2][3]*e[3][1] - e[1][3]*e[2][2]*e[3][1] + e[1][3]*e[2][1]*e[3][2] - e[1][1]*e[2][3]*e[3][2] - e[1][2]*e[2][1]*e[3][3] + e[1][1]*e[2][2]*e[3][3]);
            rm.e[0][1] = d * (e[0][3]*e[2][2]*e[3][1] - e[0][2]*e[2][3]*e[3][1] - e[0][3]*e[2][1]*e[3][2] + e[0][1]*e[2][3]*e[3][2] + e[0][2]*e[2][1]*e[3][3] - e[0][1]*e[2][2]*e[3][3]);
            rm.e[0][2] = d * (e[0][2]*e[1][3]*e[3][1] - e[0][3]*e[1][2]*e[3][1] + e[0][3]*e[1][1]*e[3][2] - e[0][1]*e[1][3]*e[3][2] - e[0][2]*e[1][1]*e[3][3] + e[0][1]*e[1][2]*e[3][3]);
            rm.e[0][3] = d * (e[0][3]*e[1][2]*e[2][1] - e[0][2]*e[1][3]*e[2][1] - e[0][3]*e[1][1]*e[2][2] + e[0][1]*e[1][3]*e[2][2] + e[0][2]*e[1][1]*e[2][3] - e[0][1]*e[1][2]*e[2][3]);
            rm.e[1][0] = d * (e[1][3]*e[2][2]*e[3][0] - e[1][2]*e[2][3]*e[3][0] - e[1][3]*e[2][0]*e[3][2] + e[1][0]*e[2][3]*e[3][2] + e[1][2]*e[2][0]*e[3][3] - e[1][0]*e[2][2]*e[3][3]);
            rm.e[1][1] = d * (e[0][2]*e[2][3]*e[3][0] - e[0][3]*e[2][2]*e[3][0] + e[0][3]*e[2][0]*e[3][2] - e[0][0]*e[2][3]*e[3][2] - e[0][2]*e[2][0]*e[3][3] + e[0][0]*e[2][2]*e[3][3]);
            rm.e[1][2] = d * (e[0][3]*e[1][2]*e[3][0] - e[0][2]*e[1][3]*e[3][0] - e[0][3]*e[1][0]*e[3][2] + e[0][0]*e[1][3]*e[3][2] + e[0][2]*e[1][0]*e[3][3] - e[0][0]*e[1][2]*e[3][3]);
            rm.e[1][3] = d * (e[0][2]*e[1][3]*e[2][0] - e[0][3]*e[1][2]*e[2][0] + e[0][3]*e[1][0]*e[2][2] - e[0][0]*e[1][3]*e[2][2] - e[0][2]*e[1][0]*e[2][3] + e[0][0]*e[1][2]*e[2][3]);
            rm.e[2][0] = d * (e[1][1]*e[2][3]*e[3][0] - e[1][3]*e[2][1]*e[3][0] + e[1][3]*e[2][0]*e[3][1] - e[1][0]*e[2][3]*e[3][1] - e[1][1]*e[2][0]*e[3][3] + e[1][0]*e[2][1]*e[3][3]);
            rm.e[2][1] = d * (e[0][3]*e[2][1]*e[3][0] - e[0][1]*e[2][3]*e[3][0] - e[0][3]*e[2][0]*e[3][1] + e[0][0]*e[2][3]*e[3][1] + e[0][1]*e[2][0]*e[3][3] - e[0][0]*e[2][1]*e[3][3]);
            rm.e[2][2] = d * (e[0][1]*e[1][3]*e[3][0] - e[0][3]*e[1][1]*e[3][0] + e[0][3]*e[1][0]*e[3][1] - e[0][0]*e[1][3]*e[3][1] - e[0][1]*e[1][0]*e[3][3] + e[0][0]*e[1][1]*e[3][3]);
            rm.e[2][3] = d * (e[0][3]*e[1][1]*e[2][0] - e[0][1]*e[1][3]*e[2][0] - e[0][3]*e[1][0]*e[2][1] + e[0][0]*e[1][3]*e[2][1] + e[0][1]*e[1][0]*e[2][3] - e[0][0]*e[1][1]*e[2][3]);
            rm.e[3][0] = d * (e[1][2]*e[2][1]*e[3][0] - e[1][1]*e[2][2]*e[3][0] - e[1][2]*e[2][0]*e[3][1] + e[1][0]*e[2][2]*e[3][1] + e[1][1]*e[2][0]*e[3][2] - e[1][0]*e[2][1]*e[3][2]);
            rm.e[3][1] = d * (e[0][1]*e[2][2]*e[3][0] - e[0][2]*e[2][1]*e[3][0] + e[0][2]*e[2][0]*e[3][1] - e[0][0]*e[2][2]*e[3][1] - e[0][1]*e[2][0]*e[3][2] + e[0][0]*e[2][1]*e[3][2]);
            rm.e[3][2] = d * (e[0][2]*e[1][1]*e[3][0] - e[0][1]*e[1][2]*e[3][0] - e[0][2]*e[1][0]*e[3][1] + e[0][0]*e[1][2]*e[3][1] + e[0][1]*e[1][0]*e[3][2] - e[0][0]*e[1][1]*e[3][2]);
            rm.e[3][3] = d * (e[0][1]*e[1][2]*e[2][0] - e[0][2]*e[1][1]*e[2][0] + e[0][2]*e[1][0]*e[2][1] - e[0][0]*e[1][2]*e[2][1] - e[0][1]*e[1][0]*e[2][2] + e[0][0]*e[1][1]*e[2][2]);
            
            return rm;
        }
        
        void setCol(const uint32 col, const Vec4 &v) {
            e[col][0] = v.x;
            e[col][1] = v.y;
            e[col][2] = v.z;
            e[col][3] = v.w;
        }
        
        Vec4 getCol(const uint32 col) const {
            return Vec4(e[col][0], e[col][1], e[col][2], e[col][3]);
        }
        
        Vec4 getRow(const uint32 row) const {
            return Vec4(e[0][row], e[1][row], e[2][row], e[3][row]);
        }
        
        friend std::ostream &operator << (std::ostream &out, const Mat4 &mat) {
            for (int i = 0; i < 4; i++) {
                out<<"| ";
                out<<std::setprecision(5)<<std::setiosflags(std::ios::fixed)<<mat.e[0][i]<<" "<<mat.e[1][i]<<" "<<mat.e[2][i]<<" "<<mat.e[3][i];
                out<<" |"<<std::endl;
            }
            return out;
        }
        
        Quaternion getQuaternion() {
            Quaternion ret(math::NO_INIT);
            
            float fourWSquaredMinus1 = e[0][0] + e[1][1] + e[2][2];
            float fourXSquaredMinus1 = e[0][0] - e[1][1] - e[2][2];
            float fourYSquaredMinus1 = e[1][1] - e[0][0] - e[2][2];
            float fourZSquaredMinus1 = e[2][2] - e[0][0] - e[1][1];
            uint32 biggestIndex = 0;
            float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
            if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
                fourBiggestSquaredMinus1 = fourXSquaredMinus1;
                biggestIndex = 1;
            }
            if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
                fourBiggestSquaredMinus1 = fourYSquaredMinus1;
                biggestIndex = 2;
            }
            if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
                fourBiggestSquaredMinus1 = fourZSquaredMinus1;
                biggestIndex = 3;
            }
            
            float biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
            float mult = 0.25f / biggestVal;
            
            switch (biggestIndex) {
                case 0:
                    ret.w = biggestVal;
                    ret.x = (e[1][2] - e[2][1]) * mult;
                    ret.y = (e[2][0] - e[0][2]) * mult;
                    ret.z = (e[0][1] - e[1][0]) * mult;
                    break;
                case 1:
                    ret.x = biggestVal;
                    ret.w = (e[1][2] - e[2][1]) * mult;
                    ret.y = (e[0][1] + e[1][0]) * mult;
                    ret.z = (e[2][0] + e[0][2]) * mult;
                    break;
                case 2:
                    ret.y = biggestVal;
                    ret.w = (e[2][0] - e[0][2]) * mult;
                    ret.x = (e[0][1] + e[1][0]) * mult;
                    ret.z = (e[1][2] + e[2][1]) * mult;
                    break;
                case 3:
                    ret.z = biggestVal;
                    ret.w = (e[0][1] - e[1][0]) * mult;
                    ret.x = (e[2][0] + e[0][2]) * mult;
                    ret.y = (e[1][2] + e[2][1]) * mult;
                    break;
            }
            
            return ret;
        }
        
    };

}

#endif /* _uMath_h_ */
