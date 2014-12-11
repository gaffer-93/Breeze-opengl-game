#define STB_IMAGE_IMPLEMENTATION

#include "main.h"
// dimensions of the window drawing surface
int gl_width = 1024;
int gl_height = 1024;

// copy a shader from a plain text file into a character array
bool parse_file_into_str (const char* file_name, char* shader_str, int max_len) {
    FILE* file = fopen (file_name , "r");
    int current_len = 0;
    char line[2048];
    
    shader_str[0] = '\0'; /* reset string */
    if (!file) {
        fprintf (stderr, "ERROR: opening file for reading: %s\n", file_name);
        return false;
    }
    strcpy (line, ""); /* remember to clean up before using for first time! */
    while (!feof (file)) {
        if (NULL != fgets (line, 2048, file)) {
            current_len += strlen (line); /* +1 for \n at end */
            if (current_len >= max_len) {
                fprintf (stderr,
                         "ERROR: shader length is longer than string buffer length %i\n",
                         max_len
                         );
            }
            strcat (shader_str, line);
        }
    }
    if (EOF == fclose (file)) { /* probably unnecesssary validation */
        fprintf (stderr, "ERROR: closing file from reading %s\n", file_name);
        return false;
    }
    return true;
}

GLuint load_shaders(string prefix){
    
    GLuint shader_programme;
    
    char* vertex_shader_str;
    char* fragment_shader_str;
    
    // allocate some memory to store shader strings
    vertex_shader_str = (char*)malloc (81920);
    fragment_shader_str = (char*)malloc (81920);
    // load shader strings from text files
    string vert_file = prefix + ".vert";
    string frag_file = prefix + ".frag";
    char vf[25];
    strcpy(vf, vert_file.c_str());
    char ff[25];
    strcpy(ff, frag_file.c_str());
    assert (parse_file_into_str (vf, vertex_shader_str, 81920));
    assert (parse_file_into_str (ff, fragment_shader_str, 81920));
    
    GLuint vs, fs;
    vs = glCreateShader (GL_VERTEX_SHADER);
    fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (vs, 1, (const char**)&vertex_shader_str, NULL);
    glShaderSource (fs, 1, (const char**)&fragment_shader_str, NULL);
    // free memory
    free (vertex_shader_str);
    free (fragment_shader_str);
    glCompileShader (vs);
    glCompileShader (fs);
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    
    return shader_programme;
}

int main () {
    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;
    
    //
    // Start OpenGL using helper libraries
    // --------------------------------------------------------------------------
    if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
     glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
     glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow (gl_width, gl_height, "Breeze", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: opening OS window\n");
        return 1;
    }
    glfwMakeContextCurrent (window);
    
    glewExperimental = GL_TRUE;
    glewInit ();
    
    /* get version info */
    renderer = glGetString (GL_RENDERER); /* get renderer string */
    version = glGetString (GL_VERSION); /* version as a string */
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    GLuint global_shader_programme = load_shaders("global");
    glLinkProgram (global_shader_programme);
    
    GLuint sky_shader_programme = load_shaders("skybox");
    glLinkProgram (sky_shader_programme);
    
    assert (init_text_rendering ("freemono.png", "freemono.meta", gl_width, gl_height));
    int score_text_id = add_text ("Time : \nScore : ", -0.9f, 0.9f, 100.0f, 0.5f, 0.5f, 1.0f, 1.0f);
    int end_text_id = add_text("          Times up!\nPress Spacebar to play again.", -0.75f, 0.0f, 100.0f, 0.5f, 0.5f, 1.0f, 1.0f);
    change_text_colour (end_text_id, 0.0f, 0.0f, 0.0f, 0.0f);

    //
    // Start rendering
    // --------------------------------------------------------------------------
    // tell GL to only draw onto a pixel if the fragment is closer to the viewer
    glEnable(GL_CULL_FACE);
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glClearColor (0.6, 0.6, 1.0, 1.0);
    
    //used to calculate delta_time for consistent camera movement with FPS
    double current_time = glfwGetTime();
    double last_time = current_time;
    double elapsed_time = 0;
    double time_limit = 63;
    
    bool timeout_trigger = true;
    
    Level level1;
    SkyBox sky;
    Player player1;
    SoundEngine sound;
    Camera controls(vec3(0,10,45), 3.14f, 0.0f, 3.5f);
    
    while (!glfwWindowShouldClose (window)) {
        
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window,1);
        }
        
        if(time_limit > elapsed_time){
            
            current_time = glfwGetTime();
            elapsed_time = elapsed_time + (current_time - last_time);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            mat4 V, P;
            
            controls.camera_control(window, global_shader_programme, current_time, last_time, V, P);
            sky.draw(sky_shader_programme, V, P);
            level1.draw(global_shader_programme, player1.position, player1.radius, sound);
            player1.draw(window, global_shader_programme, V);
            
            char tmp[256];
            sprintf (tmp, "Time: %d\nScore : %d", static_cast<int>(time_limit-elapsed_time), level1.score);
            update_text (score_text_id, tmp);
            float r = fabs (sinf (glfwGetTime()));
            float g = fabs (sinf (glfwGetTime() + 1.57f));
            change_text_colour (score_text_id, r, g, 0.0f, 1.0f);
            
            // draw all the texts
            draw_texts ();
            
            glfwPollEvents ();
            glfwSwapBuffers (window);
            
            last_time = current_time;
            
        }else{
            
            sound.pause_music();
            if(timeout_trigger == true){
                sound.play_timeout();
                timeout_trigger = false;
            }
            
            change_text_colour (end_text_id, 1.0f, 0.0f, 0.0f, 1.0f);

            // draw all the texts
            draw_texts ();
            
            glfwPollEvents ();
            
            if(glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS){
                level1 = Level();
                player1 = Player();
                sound.resume_music();
                controls = Camera(vec3(0,10,30), 3.14f, 0.0f, 3.5f);
                change_text_colour (end_text_id, 0.0f, 0.0f, 0.0f, 0.0f);
                timeout_trigger = true;
                
                current_time = glfwGetTime();
                last_time = current_time;
                elapsed_time = 0;
            }
            
            glfwSwapBuffers (window);
            
        }
            
        //fprintf(stderr, "X: %f, X2: %f\nY: %f, Y2: %f\nZ: %f, Z2: %f\n",player1.position.x, controls.position.x, player1.position.y, controls.position.y, player1.position.z, controls.position.z);
        
    }
    
    return 0;
    
}
