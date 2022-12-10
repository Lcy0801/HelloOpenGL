#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
using namespace std;

#define VIEWWIDTH 1000;
#define VIEWHEIGHT 1000;

//���λ��
glm::vec3 cameraPos(0, 0, 3);
//�������
glm::vec3 cameraFront(0, 0, -0.1);
//����춥����
glm::vec3 cameraUp(0, 1, 0);
//����ƶ��ٶ�
float cameraSpeed = 5.0;
//��Ⱦʱ��
float currentTime, lastTime;
float timeDelta = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//��ǰ�ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraFront*cameraSpeed*timeDelta;
	}
	//����ƶ�
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraFront*cameraSpeed*timeDelta;
	}
	//�����ƶ�
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= (glm::cross(cameraFront, cameraUp))*cameraSpeed*timeDelta;
	}
	//�����ƶ�
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += (glm::cross(cameraFront, cameraUp))*cameraSpeed*timeDelta ;
	}
}

//
double lastXpos, lastYpos;
bool firstFlag = true;
double sensitive = 0.05;
double heading = -90;
double pitch = 0;
void cursorPos_callback(GLFWwindow * window,double xPos,double yPos) {
	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==false)
	{
		return;
	}
	if (firstFlag) {
		firstFlag = false;
		lastXpos = xPos;
		lastYpos = yPos;
	}
	double xoffset = xPos - lastXpos;
	double yoffset = yPos - lastYpos;
	heading += xoffset * sensitive;
	pitch += yoffset * sensitive;
	if (pitch >= 90) {
		pitch = 89.99999;
	}
	if (pitch <= -90) {
		pitch = -89.99999;
	}
	cameraFront = glm::vec3(glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(heading)),
		glm::cos(glm::radians(pitch) * glm::sin(glm::radians(heading))),
		glm::sin(glm::radians(pitch))
	);
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
	glfwSetCursorPosCallback(window, cursorPos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD��ʼ��ʧ��!" << endl;
		return 0;
	}
	// ��������
	float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f
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
	//��ʼ����ɫ��
	Shader shaderProgram("./3d.vert", "./3d.frag");
	if (shaderProgram.getId() == -1) {
		cout << "��ɫ������ʧ��!" << endl;
		return 0;
	}
	//������������ɫ����������֮������ӹ�ϵ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//������һ���������
	//��ʼ���������
	int width, height, nChannels;
	unsigned char* textureData1 = stbi_load("./texture.png", &width, &height, &nChannels, 0);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	float rAangle = 0;
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		if (lastTime) {
			timeDelta = currentTime - lastTime;
		}
		else
		{
			timeDelta = 0;
		}
		lastTime = currentTime;
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//��������Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		//��������Ԫ
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		//������ɫ��
		shaderProgram.use();
		//����任����
		//��ǰ֡����ת��
		rAangle = rAangle;
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rAangle), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		view = glm::lookAt(cameraPos, cameraFront, cameraUp);
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		//��ʩ��ɫ���еı仯����
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "model"), 1, false, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "view"), 1, false, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "proj"), 1, false, glm::value_ptr(proj));
		//�󶨶����������
		glBindVertexArray(VAO);
		//���߿�ģʽ���л���
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//����ģʽ���л���
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//�ͷ������Դ���˳�����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram.getId());
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glfwTerminate();
	return 1;
}