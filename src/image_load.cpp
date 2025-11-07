#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader/Shader_S.h>


//To Resize the window
void framebuffer_size_callback(GLFWwindow* window,int width, int height){
    glViewport(0,0,width,height);
}


// To process input
void process_input(GLFWwindow* window){
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}




int main()
{

    const char* vpath="ShaderSource/Sh2/vertexShader.shad";
    const char* fpath="ShaderSource/Sh2/fragmentShader.shad";

    int width = 800, height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(width,height,"ACADSoft",NULL,NULL);
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
    glViewport(0,0,width,height);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);


    float vertices[]=
    {
        // Position           //Colour           //TextureCoord
        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom left     0
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left        1
         0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top right       2
         0.5f, -0.5f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f  // bottom right    3
    };

    int indices[]={
        0, 1, 2,
        2, 3, 0
    };


    // Vertex Arrays, elements and buffer 
    unsigned int VBO, VOA, EBO;
    glGenVertexArrays(1,&VOA);
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO);    

    glBindVertexArray(VOA);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    // generate texure ID and bind to OpenGL
    unsigned int texture;
    glGenTextures(1,&texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // texture warping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int TexWidth, TexHeight, nrchannels;

    unsigned char *data = stbi_load("Textures/Small_rocks.jpg",&TexWidth, &TexHeight, &nrchannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TexWidth, TexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else std::cout << "Failed to Load textures" << std::endl;

    stbi_image_free(data);


    Shader myShader(fpath, vpath);


    // Window loop
    while (!glfwWindowShouldClose(window)){


        process_input(window);

        //some render commands
        glClearColor(0.2f,0.3f,0.3f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        myShader.use();

        glBindTexture(GL_TEXTURE_2D,texture);
        glBindVertexArray(VOA);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);

    
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;


}