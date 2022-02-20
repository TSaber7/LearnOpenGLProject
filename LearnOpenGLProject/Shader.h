#pragma once
#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    // 程序ID
    unsigned int Program;
    enum ShaderType {VERTEX,FRAGMENT,GEOMETRY};

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath=NULL)
    {   
        unsigned int vertex, fragment, geometry;
        vertex=loadAndCompileShader(VERTEX, vertexPath);
        fragment = loadAndCompileShader(FRAGMENT, fragmentPath);
        if(geometryPath!=NULL)
            geometry = loadAndCompileShader(GEOMETRY,geometryPath);

        // 着色器程序
        Program = glCreateProgram();
        glAttachShader(Program, vertex);
        glAttachShader(Program, fragment);
        if (geometryPath != NULL)
            glAttachShader(Program, geometry);
        glLinkProgram(Program);

        // 打印连接错误（如果有的话）
        int success;
        char infoLog[512];
        glGetProgramiv(Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != NULL)
            glDeleteShader(geometry);

    }
	unsigned int loadAndCompileShader(ShaderType shaderType,const char* shaderPath)
	{

		// 1. 从文件路径中获取着色器
		std::string shaderCode;
		std::ifstream ShaderFile;
		// 保证ifstream对象可以抛出异常
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			ShaderFile.open(shaderPath);
			std::stringstream gShaderStream;
			// 读取文件的缓冲内容到数据流中
			gShaderStream << ShaderFile.rdbuf();

			// 关闭文件处理器
			ShaderFile.close();

			// 转换数据流到string
			shaderCode = gShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// 编译着色器
		unsigned int shader;
		int success;
		char infoLog[512];
        std::string typeString;
        switch (shaderType) {
            case VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                typeString = "VERTEX";
                break;
            case FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                typeString = "FRAGMENT";
                break;
            case GEOMETRY:
                shader = glCreateShader(GL_GEOMETRY_SHADER);
                typeString = "GEOMETRY";
                break;
        }

        const char* tShaderCode = shaderCode.c_str();
		glShaderSource(shader, 1, &tShaderCode, NULL);
		glCompileShader(shader);
		// 打印编译错误（如果有的话）
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::"+typeString+"::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		return shader;

	}
    void Use()
    {
        glUseProgram(Program);
    }
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(Program, name.c_str()), value);
    }
    void setMat4(const std::string& name, glm::mat4 matrix) {
        glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void setVec2(const std::string& name, glm::vec2 value) {
        glUniform2f(glGetUniformLocation(Program, name.c_str()), value.x, value.y);
    }

    void setVec3(const std::string& name, float x,float y,float z) {
        glUniform3f(glGetUniformLocation(Program, name.c_str()), x, y, z);
    }
    void setVec3(const std::string& name,glm::vec3 value) {
        glUniform3f(glGetUniformLocation(Program, name.c_str()), value.x, value.y, value.z);
    }
};

