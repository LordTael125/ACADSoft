#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>
#include <Shader/Shader_S.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow *window,int width, int height){
    glViewport(0, 0 , width, height);
}

void ExitOnEsc(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}


int main(){

    // import shaders

    const char* fragShad = "ShaderSource/Sh3/fragmentShader.shad";
    const char* vertShad = "ShaderSource/Sh3/vertexShader.shad";

    // window param

    int width = 800, height=600;

    // init Program
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width,height,"Vector Operations",NULL,NULL);
    if (window == NULL){
        std::cout << "Failed to initialize the  window" << std::endl;
        glfwTerminate();
        return -1;
    } else std::cout << "Window initialised successfully" << std::endl;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
    glViewport(0,0,width,height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    float vertices[]= {
        // Coords               Colour
        -0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,       // 0 Top Left
         0.5f,  0.5f,  0.0f,   0.0f, 1.0f, 0.0f,       // 1 Top right
         0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,       // 2 Bottom right
        -0.5f, -0.5f,  0.0f,   0.0f, 0.5f, 0.5f        // 3 Bottom Left

    };

    int indices[] = {
        0, 1, 2,     // Right Upper Triangle
        2, 3, 0      // Left  Lower Triangle
    };

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = vec * trans;

    std::cout << "\n\n" << vec.x << vec.y << vec.z << std::endl;


    unsigned int VAO;       // Vertex Array Objects
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;       // Vertex Array Buffers
    glGenBuffers(1, &VBO);

    unsigned int EBO;       // Element Object Buffers
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(6*sizeof(float)));
    // glEnableVertexAttribArray(2);



    Shader myShader(fragShad, vertShad);





    while (!glfwWindowShouldClose(window)){
        ExitOnEsc(window);


        glClearColor(0.2f,0.3f,0.3f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        myShader.use();

        // glBindTexture(GL_TEXTURE_2D,texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);

    
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;

}
