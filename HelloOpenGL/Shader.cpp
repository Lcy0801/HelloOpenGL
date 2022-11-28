#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
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
	GLFWwindow * window = glfwCreateWindow(600, 600, "Hello OpenGL", NULL, NULL);
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
	//打印顶点着色器允许的最大数目的顶点属性
	cout << "最多允许的顶点属性数目:" << GL_MAX_VERTEX_ATTRIBS << endl;

	const char* vertexShaderSource = 
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 vColor;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	vertexColor=vec4(vColor,1.0f);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader= glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		cout << "顶点着色器编译失败！"<<endl;
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << infoLog << endl;
		return 0;
	}
	const char* fragmentShaderSource =
		"#version 460 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		"void main()"
		"{\n"
			"FragColor = vertexColor;\n"
		"}\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		cout << "片段着色器编译失败!" << endl;
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << infoLog << endl;
		return 0;
	}
	unsigned shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		cout << "着色器链接失败!" << endl;
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << infoLog << endl;
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,
	 0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,
	 0.0f,  0.5f, 0.0f,0.0f,0.0f,1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	//启用顶点属性
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//激活着色器
		glUseProgram(shaderProgram);
		unsigned int uniformColorLocation= glGetUniformLocation(shaderProgram, "ourColor");	
		if (uniformColorLocation != -1) {
			double t = glfwGetTime();
			//必须在激活着色器之后修复uniform的数值，glUniform4f修改的是当前激活的着色器中的uniform
			glUniform4f(uniformColorLocation, (GLfloat)sin(t), (GLfloat)cos(t), 1, 1);
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);	
		glfwPollEvents();
	}	
	//释放相关资源，退出程序
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}