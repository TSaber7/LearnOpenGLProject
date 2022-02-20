#pragma once
#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

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
    // ����ID
    unsigned int Program;
    enum ShaderType {VERTEX,FRAGMENT,GEOMETRY};

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath=NULL)
    {   
        unsigned int vertex, fragment, geometry;
        vertex=loadAndCompileShader(VERTEX, vertexPath);
        fragment = loadAndCompileShader(FRAGMENT, fragmentPath);
        if(geometryPath!=NULL)
            geometry = loadAndCompileShader(GEOMETRY,geometryPath);

        // ��ɫ������
        Program = glCreateProgram();
        glAttachShader(Program, vertex);
        glAttachShader(Program, fragment);
        if (geometryPath != NULL)
            glAttachShader(Program, geometry);
        glLinkProgram(Program);

        // ��ӡ���Ӵ�������еĻ���
        int success;
        char infoLog[512];
        glGetProgramiv(Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != NULL)
            glDeleteShader(geometry);

    }
	unsigned int loadAndCompileShader(ShaderType shaderType,const char* shaderPath)
	{

		// 1. ���ļ�·���л�ȡ��ɫ��
		std::string shaderCode;
		std::ifstream ShaderFile;
		// ��֤ifstream��������׳��쳣
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// ���ļ�
			ShaderFile.open(shaderPath);
			std::stringstream gShaderStream;
			// ��ȡ�ļ��Ļ������ݵ���������
			gShaderStream << ShaderFile.rdbuf();

			// �ر��ļ�������
			ShaderFile.close();

			// ת����������string
			shaderCode = gShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// ������ɫ��
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
		// ��ӡ�����������еĻ���
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

