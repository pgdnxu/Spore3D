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

#include <iostream>
#include <cstdio>
#include <unistd.h>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "uMath.h"
#include "cObject.h"
#include "uHash.h"
#include "cComponent.h"
#include "cObjectManager.h"
#include "cTransform.h"
#include "cGameObject.h"

#include <png.h>
#include <zlib.h>

#include <map>

unsigned char* buffer = NULL;
png_uint_32 width, height;
//获取每一行所用的字节数，需要凑足4的倍数
int getRowBytes(int width){
    //刚好是4的倍数
    if((width * 3) % 4 == 0){
        return width * 3;
    }else{
        return ((width * 3) / 4 + 1) * 4;
    }
}

void PngTest() {
    
    png_structp png_ptr;
    png_infop info_ptr;
    int bit_depth, color_type;
    FILE *fp;
    
    
    printf("lpng[%s], zlib[%s]\n",PNG_LIBPNG_VER_STRING, ZLIB_VERSION);

    if ((fp = fopen("/Users/shannonxu/Desktop/chr_sword.png", "rb")) == NULL) {
        return;
    }
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
        fclose(fp);
        return;
    }
    
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return;
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a problem reading the file */
        return;
    }
    
    png_init_io(png_ptr, fp);
    
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    //获取png图片相关信息
    png_get_bKGD(nullptr, nullptr, nullptr);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);
    
    printf("width[%d], height[%d], bit_depth[%d], color_type[%d]\n",
           width, height, bit_depth, color_type);
    
    //获得所有png数据
    png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
    //计算buffer大小
    unsigned int bufSize = 0;
    if (color_type == PNG_COLOR_TYPE_RGB) {
        bufSize = getRowBytes(width) * height;
    } else if (color_type == PNG_COLOR_TYPE_RGBA) {
        bufSize = width * height * 4;
    } else{
        return;
    }
    
    //申请堆空间
    buffer = (unsigned char*) malloc(bufSize);
    
    for (int i = 0; i < height; i++) {
        //拷贝每行的数据到buffer，
        //opengl原点在下方，拷贝时要倒置一下
        if(color_type == PNG_COLOR_TYPE_RGB){
            memcpy(buffer + getRowBytes(width) * i, row_pointers[height - i - 1], width * 3);
        }else if(color_type == PNG_COLOR_TYPE_RGBA){
            memcpy(buffer + i * width * 4, row_pointers[height - i - 1], width * 4);
        }
    }
    
//    int n = 0;
//    for (int i = 0; i < bufSize; i+=4) {
//        printf("%d:(%d, %d, %d, %d)\n",n++,buffer[i],buffer[i+1],buffer[i+2],buffer[i+3]);
//    }
    
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
}

void ObjectManagerTest() {
    using namespace std;
    using namespace Spore3D;
    ObjectManager *om = ObjectManager::getInstance();
    om->init();
    
    GameObject *go = (GameObject*)(om->createGameObject("sprite1"));
    go->addComponent("Component");
    if (go != nullptr) {
        cout<<go->toString()<<endl;
        Transform *t = (Transform*)(go->getComponent<Transform>());
        if (t != nullptr) {
            cout<<t->toString()<<endl;
        }
        Component *c = (Component*)(go->getComponent<Component>());
        if (c != nullptr) {
            cout<<c->toString()<<endl;
        }
    }
}

void QuaternionTest() {
    using namespace std;
    using namespace Spore3D;
    
    Quaternion a = Quaternion::eulerAngle(degToRad(10), degToRad(20), degToRad(30));
    cout<<degToRad(10)<<", "<<degToRad(20)<<", "<<degToRad(30)<<endl;
    Vec3 aa = a.eulerAngle();
    cout<<aa.x<<", "<<aa.y<<", "<<aa.z<<endl;
}

void PrTest() {
    using namespace std;
    using namespace Spore3D;
    Vec4 aa = Mat4::PerspectiveMat(0, 100, 0, 100, 50, 100)*Vec4(50,50,50,1);
    cout<<aa.x<<", "<<aa.y<<", "<<aa.z<<", "<<aa.w<<endl;
    cout<<aa.x/aa.w<<", "<<aa.y/aa.w<<", "<<aa.z/aa.w<<", "<<aa.w/aa.w<<endl;
    if (aa.x/aa.w == 0) cout<<"oops."<<endl;
}

int main(void)
{
    
//    ObjectManagerTest();
//    QuaternionTest();
    PngTest();
    PrTest();
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
//    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    
    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
    int cn = 0;
    while(cn < width)
    {
        glClearColor(buffer[cn*4]/255.0f, buffer[cn*4+1]/255.0f, buffer[cn*4+2]/255.0f, buffer[cn*4+3]/255.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
        cn++;
//        sleep(1);
    }
    
    glfwTerminate();
    return 0;
}
