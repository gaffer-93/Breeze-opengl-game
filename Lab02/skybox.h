//
//  skybox.h
//  Lab03
//
//  Created by Ciaran Gaffney on 07/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef __Lab03__skybox__
#define __Lab03__skybox__

#include "obj_loader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

class SkyBox{
public:
    GLuint vao;
    GLuint tex_cube;
    
    SkyBox();
    void create_cube_map (const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube);
    bool load_cube_map_side (GLuint texture, GLenum side_target, const char* file_name);
    void draw(GLuint shader_programme, mat4 V, mat4 P);
    
};

#endif /* defined(__Lab03__skybox__) */
