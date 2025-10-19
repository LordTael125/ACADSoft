#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
public :
    unsigned int programID;

    //constructor that reads and build shaders
    Shader(const char* fragment_path, const char* vertex_path){
        
        // Reading the files to get the source code
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);


        try
        {
            vShaderFile.open(vertex_path);
            fShaderFile.open(fragment_path);

            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();
            
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

        }
        catch(std::ifstream::failure e)
        {
            std::cout<<"Error failed to read the files";
        }

        const char* vertexShaderSC = vertexCode.c_str();
        const char* fragmentShaderSC = fragmentCode.c_str();

        // compiling the shaders
        unsigned int vertex;
        int success;
        char infoLog[512];
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        

        glShaderSource(vertex,1,&vertexShaderSC,NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);

        if(!success){
            glGetShaderInfoLog(vertex,512,NULL,infoLog);
            std::cout<<"ERROR::OPENGL::SHADER::VERTEX::COMPILATION fAILED!!\n"<<infoLog<<std::endl;
        }
        else printf("Debug::Vertex Shader Compiled\n");

        unsigned int fragment;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fragmentShaderSC,NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);


        if(!success){
            glGetShaderInfoLog(fragment,512,NULL,infoLog);
            std::cout<<"ERROR::OPENGL::SHADER::FRAGMENT::COMPILATION fAILED!!\n"<<infoLog<<std::endl;
        }
        else std::cout<<"Debug::Fragment Shader Compiled\n";

        programID = glCreateProgram();

        glAttachShader(programID, vertex);
        glAttachShader(programID, fragment);
        glLinkProgram(programID);

        glGetProgramiv(programID,GL_LINK_STATUS,&success);

        if (!success){
            glGetProgramInfoLog(programID,512,NULL,infoLog);
            std::cout<<"ERROR::OPENGL::PROGRAM::LINKING FAILED!!\n"<<infoLog<<std::endl;
        }
        else std::cout<<"Debug::Program Linking Successfull\n";


        // free up shader
        glDeleteShader(vertex);
        glDeleteShader(fragment);



    };

    // activate shader
    void use()
    {
        glUseProgram(programID);
    };


    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(programID, name.c_str() ), (int)value);
    };
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(programID, name.c_str() ), value);
    };
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(programID, name.c_str() ), value);
    };

};

#endif