#version 400

layout (location=0) in vec3 vp; // points
layout (location=1) in vec2 vt; // texture co-ords
layout (location=2) in vec3 vn;

uniform mat4 M; // model matrix
uniform mat4 P; // perspective
uniform mat4 V; // view

out vec2 texture_coordinates;
out vec3 normals;
out vec3 vertices;

void main () {
    texture_coordinates = vt;
    normals = vn;
    vertices = vp;
    gl_Position = P * V * M * vec4 (vp, 1.0);
}
