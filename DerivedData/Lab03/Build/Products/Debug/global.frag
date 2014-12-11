#version 400

/* in vec2 texture_coordinates; // normals from vertex shader
   uniform sampler2D gun_texture;
*/

uniform mat4 M;

in vec3 normals;
in vec3 vertices;
in vec2 texture_coordinates;
uniform sampler2D current_texture;

vec4 texel = texture(current_texture, vec2(texture_coordinates.x, 1.0 - texture_coordinates.y));

vec3 light_position = vec3(-30.0f, 25.0f, 30.0f);
vec3 light_intensity = vec3(0.7,0.7,1.0); //a.k.a the color of the light

//direction of phong light
vec3 l_dir = normalize (vec3 (4.0f, -4.0f, -4.0f));
vec3 l_a = vec3 (0.7, 0.7, 0.7);    //phong light's ambient colour
vec3 l_d = vec3 (0.8, 0.8, 0.8);    //phong light's diffuse
vec3 l_s = vec3 (1.0, 1.0, 1.0);    //phong light's specular
float spec_exp = 100.0f;
vec3 k_a = texel.xyz;
vec3 k_d = texel.xyz;
vec3 k_s = texel.xyz;

out vec4 frag_colour;

void main () {
    
    mat3 normal_matrix = transpose(inverse(mat3(M)));
    vec3 n_wor = normalize(normal_matrix * normals);
    
    vec3 I = vec3 (0.0, 0.0, 0.0);
    I += l_a * k_a;
    I += l_d * k_d * max (dot (-l_dir, n_wor), 0.0);
    vec3 r = reflect (l_dir, n_wor);
    vec3 v = normalize (-vertices);
    
    // blinn
    vec3 h = normalize(v + -l_dir);
    
    I += l_s * k_s * pow (max (dot (h, n_wor), 0.0), spec_exp);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 frag_position = vec3(M * vec4(vertices, 1));
    
    //calculate the vector from this pixels surface to the light source
    vec3 surface_to_light = light_position - frag_position;
    
    //calculate the cosine of the angle of incidence
    float brightness = dot(n_wor, surface_to_light) / (length(surface_to_light) * length(n_wor));
    brightness = clamp(brightness, 0, 1);
    
    //vec4 texel = texture(gun_texture, vec2(texture_coordinates.x, 1.0 - texture_coordinates.y));
    frag_colour = vec4((brightness+I)*light_intensity * texel.xyz, texel.w);
}
