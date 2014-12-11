//
//  player.h
//  Lab03
//
//  Created by Ciaran Gaffney on 03/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef __Lab03__player__
#define __Lab03__player__
#include "obj_loader.h"
#include "camera.h"
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
using namespace std;
using namespace glm;

class Player{

private:
    GLuint vao;
    GLuint texture_buffer;
    int object_points;
    mat4 M;
    
public:
    vec3 position;
    int radius = 0.2f;
    Player();
    void draw(GLFWwindow*window, GLuint shader_programme, mat4 V);
    
};

#endif /* defined(__Lab03__player__) */
