//#include <glad/glad.h>
//#include <glfw3.h>
//#include <iostream>
//#include "stb_image.h"
//#include "Shader.h"
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//int main() {
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	GLFWwindow* window = glfwCreateWindow(600, 600, "Hello OpenGL", NULL, NULL);
//	if (window == NULL) {
//		cout << "��������ʧ�ܣ�" << endl;
//		glfwTerminate();
//		return 0;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "GLAD��ʼ��ʧ��!" << endl;
//		return 0;
//	}
//	const char* vertexShaderSource =
//		"#version 460 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		cout << "������ɫ������ʧ�ܣ�" << endl;
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		cout << infoLog << endl;
//		return 0;
//	}
//	const char* fragmentShaderSource =
//		"#version 460 core\n"
//		"out vec4 FragColor;\n"
//		"void main(){\n"
//		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0";
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		cout << "Ƭ����ɫ������ʧ��!" << endl;
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		cout << infoLog << endl;
//		return 0;
//	}
//	unsigned shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		cout << "��ɫ������ʧ��!" << endl;
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		cout << infoLog << endl;
//		return 0;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	float vertices[] = {
//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	0.5f, -0.5f, 0.0f,  // ���½�
//	-0.5f, -0.5f, 0.0f, // ���½�
//	-0.5f, 0.5f, 0.0f   // ���Ͻ�
//	};
//	unsigned int indices[] = {
//		// ע��������0��ʼ! 
//		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
//		// �����������±��������ϳɾ���
//		0, 1, 3, // ��һ��������
//		1, 2, 3  // �ڶ���������
//	};
//	//��ʼ����������϶���
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	//��ʼ�����㻺��϶���
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		//������ɫ��
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		//���߿�ģʽ���л���
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		//����ģʽ���л���
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	//�ͷ������Դ���˳�����
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//	glfwTerminate();
//	return 0;
//}