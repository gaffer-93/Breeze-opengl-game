//
//  ring.cpp
//  Lab03
//
//  Created by Ciaran Gaffney on 04/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#include "ring.h"

Ring::Ring(vec3 _position){
    load_object("ring", vao, object_points);
    position = _position;
    M = mat4(1.0f) * translate(_position);
}

bool Ring::collected(vec3 plane_position, int plane_radius){
    if(plane_radius + radius > distance(plane_position, position))
        return true;
    else
        return false;
}

void Ring::draw(GLuint shader_programme, GLuint texture_buffer){
    
    glUseProgram(shader_programme);
    
    mat4 R = rotate(5.0f, vec3(0,1,0));
    M = M * R;
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
    
    glBindVertexArray (vao);
    int M_loc = glGetUniformLocation (shader_programme, "M");
    glUniformMatrix4fv (M_loc, 1, GL_FALSE, value_ptr(M));
    glDrawArrays (GL_TRIANGLES, 0, object_points);
    
}