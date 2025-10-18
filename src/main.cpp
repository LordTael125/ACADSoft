/*
    This is a demo CAD program made by implementing C++
    
    This is a passion project inititalized by LordTael125

*/

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define version "0.0.0.1pre"

enum command  {line,elipse,rectangle,square,equi_triangle};

struct commands {
    bool line;
    bool elipse;
    bool rectangle;
    bool square;
    bool equi_triangle;
} typedef commands;

//To Resize the window
void framebuffer_size_callback(GLFWwindow* window,int height,int width){
    glViewport(0,0,width,height);
}


// To process input
void process_input(GLFWwindow* window){
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}



int main(){

    printf("Debug::Initializing glfw\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

 



    GLFWwindow* window = glfwCreateWindow(800,600,"ACADSoft",NULL,NULL);
    if (window == NULL){
        printf("Failed to make a glfw window\n");
        glfwTerminate();
        return -1;
    } else printf("GLFW Window created successfully\n");

    glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);






    float vertices[]={
        -0.5f, -0.5f, 0.0f,     // bottom left  0
         0.5f, -0.5f, 0.0f,     // bottom right 1
         0.5f,  0.5f, 0.0f,     // top right    2
        -0.5f,  0.5f, 0.0f      // top left     3
    };

    int indices[]={
        0, 1, 2,
        2, 3, 0
    };
    


    unsigned int VBO, VOA, EBO;
    glGenVertexArrays(1,&VOA);
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO);    

    glBindVertexArray(VOA);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);






    // Vertex Shaders 
    const char *vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader,1,&vertex_shader_source,NULL);
    glCompileShader(vertex_shader);


    // Fragment Shaders {rgba}
    const char *fragment_colour = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n";

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader,1,&fragment_colour, NULL);
    glCompileShader(fragment_shader);
    
    
    // Shader Program
    unsigned int shader_Program;
    shader_Program = glCreateProgram();

    glAttachShader(shader_Program,vertex_shader);
    glAttachShader(shader_Program,fragment_shader);
    glLinkProgram(shader_Program);



    // glUseProgram(shader_Program);

    // Debug parameters for shader
    int vs_success;
    char vs_infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS,&vs_success);

    if(!vs_success){
        glGetShaderInfoLog(vertex_shader,312,NULL,vs_infoLog);
        printf("ERROR::OPENGL::SHADER::VERTEX::COMPILATION fAILED!!\n %s",vs_infoLog);
    }
    else printf("Debug::Vertex Shader Passed\n");



    // Debug parameters for shaders
    int fs_success;
    char fs_infoLog[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS,&fs_success);

    if(!fs_success){
        glGetShaderInfoLog(fragment_shader,312,NULL,fs_infoLog);
        printf("ERROR::OPENGL::SHADER::Fragment::COMPILATION fAILED!!\n %s",fs_infoLog);
    }
    else printf("Debug::Fragment Shader Passed\n");



    // Removing shaders after loading / attaching to the workspace
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);



    // Window loop
    while (!glfwWindowShouldClose(window)){


        process_input(window);

        //some render commands
        glClearColor(0.1f,0.1f,0.1f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader_Program);
        glBindVertexArray(VOA);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}


