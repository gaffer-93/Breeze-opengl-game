//
//  gamecontrol.h
//  Lab03
//
//  Created by Ciaran Gaffney on 02/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef Lab03_gamecontrol_h
#define Lab03_gamecontrol_h

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

class Camera{
    
public:
    
    vec3 position;
    float horizontal_angle;
    float vertical_angle;
    // Initial Field of View
    float FoV;
    float speed;
    float look_speed;
    
    Camera(vec3 position, float horizontal, float vertical, float speed);
    void camera_control(GLFWwindow* window, GLuint shader_program, float current_time, float last_time, mat4 &V, mat4 &P);
    
};

#endif
