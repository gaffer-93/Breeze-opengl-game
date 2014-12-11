//
//  ring.h
//  Lab03
//
//  Created by Ciaran Gaffney on 04/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef __Lab03__ring__
#define __Lab03__ring__

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

using namespace std;
using namespace glm;

class Ring{
    
private:
    GLuint vao;
    int object_points;
    mat4 M;
public:
    vec3 position;
    float radius = 0.2f;
    
    Ring(vec3 position);
    bool collected(vec3 plane_position, int plane_radius);
    void draw(GLuint shader_programme, GLuint texture_buffer);
    
};

#endif /* defined(__Lab03__ring__) */
