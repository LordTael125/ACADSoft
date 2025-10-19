/*
    This is a demo CAD program made by implementing C++
    This is a passion project inititalized by LordTael125
*/
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader/Shader_S.h>

#define version "0.0.0.1pre"

enum command  {line,elipse,rectangle,square,equi_triangle};


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

    const char* vpath="ShaderSource/vertexShader.shad";
    const char* fpath="ShaderSource/fragmentShader.shad";


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(800,600,"ACADSoft",NULL,NULL);
    if (window == NULL){
        std::cout<<"Failed to make a glfw window\n";
        glfwTerminate();
        return -1;
    } else std::cout<<"GLFW Window created successfully\n";

    glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);


    float vertices[]={
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       // right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.9f, 0.0f,       // left
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f        // top
        
    };

    Shader ourShader(fpath,vpath);

    // Vertex Arrays, elements and buffer 
    unsigned int VBO, VOA, EBO;
    glGenVertexArrays(1,&VOA);
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO);    

    glBindVertexArray(VOA);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);


    // Window loop
    while (!glfwWindowShouldClose(window)){


        process_input(window);

        //some render commands
        glClearColor(0.2f,0.3f,0.3f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        ourShader.use();

        glBindVertexArray(VOA);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    // while(!((bool)scanf("%d")));
    return 0;

}


