#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glad/glad.h>
using namespace std;

class  Shader
{
	unsigned int id=-1;
public:
	 Shader(const char * vertexShaderSourceFile,const char * fragmentShaderSourceFile);
	~ Shader();
	void use();
	void setBool(const char * uniformName, bool uniformValue) const;
	void setInt(const  char* uniformName,  int uniformValue) const ;
	void setFloat( const char* uniformName,  float uniformValue) const;
	unsigned int getId() const;
};

 Shader:: Shader(const char* vertexShaderSourceFile, const char* fragmentShaderSourceFile)
{
     // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
     string vertexCode;
     string fragmentCode;
     ifstream vShaderFile;
     ifstream fShaderFile;
     // ��֤ifstream��������׳��쳣��
     vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
     fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
     try
     {
         // ���ļ�
         vShaderFile.open(vertexShaderSourceFile);
         fShaderFile.open(fragmentShaderSourceFile);
         std::stringstream vShaderStream, fShaderStream;
         // ��ȡ�ļ��Ļ������ݵ���������
         vShaderStream << vShaderFile.rdbuf();
         fShaderStream << fShaderFile.rdbuf();
         // �ر��ļ�������
         vShaderFile.close();
         fShaderFile.close();
         // ת����������string
         vertexCode = vShaderStream.str();
         fragmentCode = fShaderStream.str();
     }
     catch (ifstream::failure e)
     {
         cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
     }
     unsigned int vertexShader;
     unsigned int fragmentShader;
     vertexShader= glCreateShader(GL_VERTEX_SHADER);
     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     const char* vShaderCode = vertexCode.c_str();
     const char* fShaderCode = fragmentCode.c_str();
     glShaderSource(vertexShader, 1, &vShaderCode, NULL);
     glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
     int success;
     char* infoLog = new char[512];
     glCompileShader(vertexShader);
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
     if (!success) {
         cout << "������ɫ������ʧ��!" << endl;
         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
         cout << infoLog << endl;
         return;
     }
     glCompileShader(fragmentShader);
     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
     if (!success) {
         cout << "Ƭ����ɫ������ʧ��!" << endl;
         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
         cout << infoLog << endl;
         return;
     }
     unsigned shaderProgram;
     shaderProgram= glCreateProgram();
     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
     glLinkProgram(shaderProgram);
     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
     if (!success) {
         cout << "��ɫ������ʧ��" << endl;
         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
         cout << infoLog << endl;
     }
     delete []infoLog;
     glDeleteShader(vertexShader);
     glDeleteShader(fragmentShader);
     this->id = shaderProgram;
}

 Shader::~ Shader()
{
     //�ͷ���ɫ������ռ�õ���Դ
     glDeleteProgram(this->id);
}

 void Shader::use() 
 {
     glUseProgram(this->id);
 }

void  Shader::setBool(const char* uniformName, bool uniformValue) const
{
    int uniformLocation= glGetUniformLocation(this->id, uniformName);
    if (uniformLocation == -1) {
        cout << "This uniform variable does't exist in this shader program!" << endl;
        return;
    }
    glUniform1i(uniformLocation, (int)uniformValue);
}	

void Shader::setInt(const char* uniformName, int uniformValue) const
{
    int uniformLocation = glGetUniformLocation(this->id, uniformName);
    if (uniformLocation == -1) {
        cout << "This uniform variable does't exist in this shader program!" << endl;
        return;
    }
    glUniform1i(uniformLocation, uniformValue);
}

void Shader::setFloat(const char* uniformName, float uniformValue) const
{
    int uniformLocation = glGetUniformLocation(this->id, uniformName);
    if (uniformLocation == -1) {
        cout << "This uniform variable does't exist in this shader program!" << endl;
        return;
    }
    glUniform1f(uniformLocation, uniformValue);
}

unsigned int Shader::getId() const
{
    return this->id;
}
#endif
