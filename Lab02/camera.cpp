#include "camera.h"

Camera::Camera(vec3 _position, float _horizontal_angle, float _vertical_angle, float _speed){
    position = _position;
    horizontal_angle = _horizontal_angle;
    vertical_angle = _vertical_angle;
    FoV = 45.0f;
    speed = _speed;
    look_speed = 0.005f;
}

void Camera::camera_control(GLFWwindow* window, GLuint shader_programme, float current_time, float last_time, mat4 &V, mat4 &P){
    
    glUseProgram(shader_programme);
    
    //keeps movement speed independant of FPS.
    float delta_time = float(current_time - last_time);
    
    // Direction : Spherical coordinates to Cartesian coordinates conversion
    vec3 direction(cos(vertical_angle) * sin(horizontal_angle),
                   sin(vertical_angle),
                   cos(vertical_angle) * cos(horizontal_angle)
                   );
    
    // Right vector
    vec3 right(sin(horizontal_angle - 3.14f/2.0f),
               0,
               cos(horizontal_angle - 3.14f/2.0f)
               );
    
    // Up vector : perpendicular to both direction and right
    vec3 up = cross( right, direction );
    
    //if(vertical_angle > 0 && speed > 0.5f){
    //    speed -= 0.005f;
    //}else if (vertical_angle < 0 && speed < 3.0f){
    //    speed += 0.01f;
    //}
    
    position += direction * delta_time * speed;
    
    // Move forward
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        vertical_angle += look_speed * delta_time * 200;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        vertical_angle += look_speed * delta_time * -200;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        horizontal_angle += look_speed * delta_time * -350;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        horizontal_angle += look_speed * delta_time * 350;
    }
    
    if(position.y <= 3.5){
        position.y = 3.50001;
    }else if (position.y >= 14.0f){
        position.y = 13.9999;
    }
    
    if(position.x <= -25.0f){
        position.x = -24.9999;
    }else if(position.x >= 25.0f){
        position.x = 24.9999;
    }
    
    if(position.z <= -25.0f){
        position.z = -24.9999;
    }else if(position.z >= 25.0f){
        position.z = 24.9999;
    }
    
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    P = perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    V = lookAt(position,           // Camera is here
               position+direction, // and looks here : at the same position, plus "direction"
               up                  // Head is up (set to 0,-1,0 to look upside-down)
               );
    
    int P_loc = glGetUniformLocation(shader_programme, "P");
    glUniformMatrix4fv(P_loc,1,GL_FALSE, value_ptr(P));
    
    int V_loc = glGetUniformLocation(shader_programme, "V");
    glUniformMatrix4fv(V_loc,1,GL_FALSE, value_ptr(V));
    
}