#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Hello OpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "创建窗口失败！" << endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD初始化失败!" << endl;
		return 0;
	}

	//顶点数据：顶点坐标、顶点颜色、顶点纹理坐标
	//注意这里的纹理坐标是基于图像坐标系，即坐标原点在左上角
	float vertices[] = {
		0.5f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f,1.0f,0.0f, // 右上角
		0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,1.0f,1.0f,  // 右下角
		-0.5f, -0.5f, 0.0f,1.0f, 0.0f, 1.0f,0.0f,1.0f,// 左下角
		-0.5f, 0.5f, 0.0f ,1.0f, 1.0f, 0.0f,0.0f,0.0f // 左上角
	};
	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	//初始化顶点数组合对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//初始化顶点缓冲合对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//初始化着色器
	Shader shaderProgram("./vertex.sha","./fragment.sha");
	if (shaderProgram.getId() == -1) {
		cout << "着色器生成失败!" << endl;
		return 0;
	}
	//顶点数据与着色器顶点属性之间的链接关系
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//创建第一个纹理对象
	//初始化纹理对象
	int width, height, nChannels;
	unsigned char* textureData1 = stbi_load("./texture.png",&width,&height,&nChannels,0);
	if (!textureData1) {
		cout << "载入纹理图像失败!" << endl;
		return 0;
	}
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//设置纹理的缠绕方式
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置纹理的过滤（重采样方式）
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//设置纹理图案
	//注意四通道图像一定要以RGBA的形式读取
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);
	//生成多级渐远纹理
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData1);
	//创建第二个纹理对象
	unsigned char* textureData2 = stbi_load("./face.png", &width, &height, &nChannels, 0);
	if (!textureData2) {
		cout << "载入纹理图像失败!" << endl;
		return 0;
	}
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//设置纹理的缠绕方式
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置纹理的过滤（重采样方式）
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//设置纹理图案
	//注意四通道图像一定要以RGBA的形式读取
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData2);
	//生成多级渐远纹理
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData2);
	//将片段着色器多个采样器与纹理对象一一对应起来
	shaderProgram.use();
	shaderProgram.setInt("textureUnit1", 0);
	shaderProgram.setInt("textureUnit2", 1);
	//恢复到初始化状态
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	float s=1, r=0, t=0;
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//激活纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		//激活纹理单元
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		//定义变换矩阵
		t += 0.001;
		r += 0.1;
		s -= 0.001;
		glm::mat4 mt=glm::mat4(1.0f);
		mt = glm::scale(mt, glm::vec3(s,s,s));
		mt = glm::rotate(mt, glm::radians(r), glm::vec3(0, 0, 1));
		mt = glm::translate(mt, glm::vec3(0,0,0));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "mt"),1,GL_FALSE,glm::value_ptr(mt));
		//激活着色器
		shaderProgram.use();
		glBindVertexArray(VAO);
		//以线框模式进行绘制
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//以面模式进行绘制
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//释放相关资源，退出程序
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram.getId());
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glfwTerminate();
	return 1;
}