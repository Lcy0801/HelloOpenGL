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
		cout << "��������ʧ�ܣ�" << endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD��ʼ��ʧ��!" << endl;
		return 0;
	}

	//�������ݣ��������ꡢ������ɫ��������������
	//ע����������������ǻ���ͼ������ϵ��������ԭ�������Ͻ�
	float vertices[] = {
		0.5f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f,1.0f,0.0f, // ���Ͻ�
		0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,1.0f,1.0f,  // ���½�
		-0.5f, -0.5f, 0.0f,1.0f, 0.0f, 1.0f,0.0f,1.0f,// ���½�
		-0.5f, 0.5f, 0.0f ,1.0f, 1.0f, 0.0f,0.0f,0.0f // ���Ͻ�
	};
	unsigned int indices[] = {
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	//��ʼ����������϶���
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//��ʼ�����㻺��϶���
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//��ʼ����ɫ��
	Shader shaderProgram("./vertex.sha","./fragment.sha");
	if (shaderProgram.getId() == -1) {
		cout << "��ɫ������ʧ��!" << endl;
		return 0;
	}
	//������������ɫ����������֮������ӹ�ϵ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//������һ���������
	//��ʼ���������
	int width, height, nChannels;
	unsigned char* textureData1 = stbi_load("./texture.png",&width,&height,&nChannels,0);
	if (!textureData1) {
		cout << "��������ͼ��ʧ��!" << endl;
		return 0;
	}
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//��������Ĳ��Ʒ�ʽ
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//��������Ĺ��ˣ��ز�����ʽ��
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//��������ͼ��
	//ע����ͨ��ͼ��һ��Ҫ��RGBA����ʽ��ȡ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);
	//���ɶ༶��Զ����
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData1);
	//�����ڶ����������
	unsigned char* textureData2 = stbi_load("./face.png", &width, &height, &nChannels, 0);
	if (!textureData2) {
		cout << "��������ͼ��ʧ��!" << endl;
		return 0;
	}
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//��������Ĳ��Ʒ�ʽ
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//��������Ĺ��ˣ��ز�����ʽ��
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//��������ͼ��
	//ע����ͨ��ͼ��һ��Ҫ��RGBA����ʽ��ȡ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData2);
	//���ɶ༶��Զ����
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData2);
	//��Ƭ����ɫ��������������������һһ��Ӧ����
	shaderProgram.use();
	shaderProgram.setInt("textureUnit1", 0);
	shaderProgram.setInt("textureUnit2", 1);
	//�ָ�����ʼ��״̬
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
		//��������Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		//��������Ԫ
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		//����任����
		t += 0.001;
		r += 0.1;
		s -= 0.001;
		glm::mat4 mt=glm::mat4(1.0f);
		mt = glm::scale(mt, glm::vec3(s,s,s));
		mt = glm::rotate(mt, glm::radians(r), glm::vec3(0, 0, 1));
		mt = glm::translate(mt, glm::vec3(0,0,0));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "mt"),1,GL_FALSE,glm::value_ptr(mt));
		//������ɫ��
		shaderProgram.use();
		glBindVertexArray(VAO);
		//���߿�ģʽ���л���
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//����ģʽ���л���
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//�ͷ������Դ���˳�����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram.getId());
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glfwTerminate();
	return 1;
}