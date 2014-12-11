//
//  level.h
//  Lab03
//
//  Created by Ciaran Gaffney on 04/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef __Lab03__level__
#define __Lab03__level__
#define SCENEOBJECTS 4
#define RINGCOUNT 600

#include <stdio.h>
#include "obj_loader.h"
#include "ring.h"
#include "sound_engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
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

class Level{
    
private:
    GLuint vao[SCENEOBJECTS];
    GLuint texture_buffer[SCENEOBJECTS];
    GLuint ring_texture_buffer;
    int object_points[SCENEOBJECTS];
    vector<Ring*> rings;
    
public:
    int score = 0;
    Level();
    void draw(GLuint shader_programme, vec3 player_position, float player_radius, SoundEngine sound);
};


#endif /* defined(__Lab03__level__) */
