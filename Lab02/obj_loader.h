/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 7 Nov 2013                                                     |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries' separate legal notices                             |
|******************************************************************************|
| Anton's lazy Wavefront OBJ parser                                            |
| Anton Gerdelan 7 Nov 2013                                                    |
| Notes:                                                                       |
| I ignore MTL files                                                           |
| Mesh MUST be triangulated - quads not accepted                               |
| Mesh MUST contain vertex points, normals, and texture coordinates            |
| Faces MUST come after all other data in the .obj file                        |
\******************************************************************************/
#ifndef _OBJ_PARSER_H_
#define _OBJ_PARSER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include "stb_image.h"
#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

bool load_obj_file (
	const char* file_name,
	float*& points,
	float*& tex_coords,
	float*& normals,
	int& point_count
);

void load_multiple_objects(int object_count, string prefix, GLuint vao[], GLuint texture_buffer[], int object_points[]);
void load_object(string prefix, GLuint &vao, GLuint &texture_buffer, int &object_points);
void load_object(string prefix, GLuint &vao, int &object_points);
#endif
