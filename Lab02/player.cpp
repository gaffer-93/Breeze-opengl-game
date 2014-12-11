//
//  player.cpp
//  Lab03
//
//  Created by Ciaran Gaffney on 03/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#include "player.h"

Player::Player(){
    
    load_object("plane", vao, texture_buffer, object_points);
}

void Player::draw(GLFWwindow*window, GLuint shader_programme, mat4 V){
    
    glUseProgram(shader_programme);
    
    M = inverse(V) * translate(vec3(0,-0.1,-1)) * scale(vec3(0.2,0.2,0.2));
    position = vec3(M * vec4(0,0,0,1));
    
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        M = M * rotate(8.0f, vec3(1,0,0));
    }
    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        M = M * rotate(-10.0f, vec3(1,0,0));
    }
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        M = M * rotate(8.0f, vec3(0,1,1)) * rotate(15.0f, vec3(0,0,1));
    }
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        M = M * rotate(-8.0f, vec3(0,1,0)) * rotate(-15.0f, vec3(0,0,1));
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
    
    glBindVertexArray (vao);
    int M_loc = glGetUniformLocation (shader_programme, "M");
    glUniformMatrix4fv (M_loc, 1, GL_FALSE, value_ptr(M));
    glDrawArrays (GL_TRIANGLES, 0, object_points);
}