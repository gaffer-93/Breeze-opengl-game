//
//  level.cpp
//  Lab03
//
//  Created by Ciaran Gaffney on 04/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#include "level.h"

Level::Level(){
    load_multiple_objects(SCENEOBJECTS, "scene", vao, texture_buffer, object_points);
    
    for(int i = 0; i < RINGCOUNT; i++){
        int x = rand() % 41 + (-20);
        int y = rand() % 8 + (4);
        int z = rand() % 41 + (-20);
        rings.push_back(new Ring(vec3(x, y, z)));
    }
    
    int texture_width;
    int texture_height;
    int comp;
    unsigned char* T = stbi_load("ring.png", &texture_width, &texture_height, &comp, STBI_rgb_alpha);
    
    if(T==NULL){
        printf("FAILED TO LOAD TEXTURE\n");
    }
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ring_texture_buffer);
    glBindTexture(GL_TEXTURE_2D, ring_texture_buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, T);
    
}

void Level::draw(GLuint shader_programme, vec3 player_pos, float player_radius, SoundEngine sound){
    
    glUseProgram(shader_programme);
    
    mat4 M(1.0f);
    int M_loc = glGetUniformLocation (shader_programme, "M");
    glUniformMatrix4fv (M_loc, 1, GL_FALSE, value_ptr(M));
    
    glActiveTexture(GL_TEXTURE0);
    
    for(int i = 0; i < SCENEOBJECTS; i++){
        glBindTexture(GL_TEXTURE_2D, texture_buffer[i]);
        
        glBindVertexArray (vao[i]);
        glDrawArrays (GL_TRIANGLES, 0, object_points[i]);
    }
    
    int i = 0;
    for(auto &it : rings){
        it->draw(shader_programme, ring_texture_buffer);
        if(it->collected(player_pos,player_radius)){
            rings.erase(rings.begin() + i);
            score++;
            sound.play_ding();
        }
        i++;
    }
}


