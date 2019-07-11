#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <map>
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4.h"
#include <vector>
#include <GL/GLU.h>

const int width_window = 640;
const int height_window = 480;

float circle_center_x = 0.0f;
float circle_center_y = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		circle_center_x += 0.05;

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		circle_center_x -= 0.05;

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		circle_center_y += 0.05;

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		circle_center_y -= 0.05;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwTerminate();
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << " " << ypos << std::endl;
}

const int num_vertices = 24;
const int num_quads = 6;

const Vector3D colors[num_vertices] =
{
	Vector3D(0, 0, 0.8), Vector3D(0, 0, 0.8), Vector3D(0, 0, 0.8), Vector3D(0, 0, 0.8),
    Vector3D(1, 0, 0), Vector3D(1, 0, 0), Vector3D(1, 0, 0), Vector3D(1, 0, 0),
	Vector3D(0, 1, 0), Vector3D(0, 1, 0), Vector3D(0, 1, 0), Vector3D(0, 1, 0),
	Vector3D(1, 1, 0), Vector3D(1, 1, 0), Vector3D(1, 1, 0), Vector3D(1, 1, 0),
	Vector3D(0.2, 0.2, 1), Vector3D(0.2, 0.2, 1), Vector3D(0.2, 0.2, 1), Vector3D(0.2, 0.2, 1),
	Vector3D(1, 0, 1), Vector3D(1, 0, 1), Vector3D(1, 0, 1), Vector3D(1, 0, 1),
};

Vector3D positions[num_vertices] =
{
	Vector3D(0.0, 0.0, 0.5),
	Vector3D(0.5, 0.0, 0.5),
	Vector3D(0.5, 0.0, 0.0),
	Vector3D(0.0, 0.0, 0.0),

	Vector3D(0.0, 0.0, 0.5),
	Vector3D(0.5, 0.0, 0.5),
	Vector3D(0.5, 0.5, 0.5),
	Vector3D(0.0, 0.5, 0.5),

	Vector3D(0.5, 0.0, 0.5),
	Vector3D(0.5, 0.0, 0.0),
	Vector3D(0.5, 0.5, 0.0),
	Vector3D(0.5, 0.5, 0.5),

	Vector3D(0.0, 0.0, 0.5),
	Vector3D(0.0, 0.0, 0.0),
	Vector3D(0.0, 0.5, 0.0),
	Vector3D(0.0, 0.5, 0.5),

	Vector3D(0.0, 0.0, 0.0),
	Vector3D(0.5, 0.0, 0.0),
	Vector3D(0.5, 0.5, 0.0),
	Vector3D(0.0, 0.5, 0.0),

	Vector3D(0.0, 0.5, 0.5),
	Vector3D(0.5, 0.5, 0.5),
	Vector3D(0.5, 0.5, 0.0),
	Vector3D(0.0, 0.5, 0.0),
};


const unsigned int indices[num_quads * 4] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	16, 17, 18, 19,
	20, 21, 22, 23,
};

const char* vertex_shader =
"#version 400\n"
"in vec3 a_pos;"   // "in" means the input to your vertex shader
"void main() {"
"				gl_Position = vec4(a_pos, 1.0);"  // determin position vertices and convert vec3 into vec4(XYZ and W)
			"}";

const char* fragment_shader =  // fragment shader determines color data
"#version 400\n"   // OpenGL 4.0.0
"out vec4 f_color;"  
"void main() {"
"				f_color = vec4(1.0, 0.0, 0.0, 1.0);"   // red
			"}";


int main(void)
{
	GLFWwindow* window = nullptr;

	/* initialize the library */
	if (!glfwInit())
		return -1;

	/* create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, cursor_position_callback);

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW  to allocate memory in GPU, should paste this function after context current
	glewExperimental = true;  // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	/* default color for display buffer */
	glClearColor(1, 1, 1, 1); // white background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glOrtho(-1.2, 1.2, -1.2, 1.2, -10.0, 10.0);
	gluLookAt(1.2, 0.8, 1.2, 0.5, 0.5, 0.5, 0, 1, 0);  // it requires 9 parameters for 3-Dimension
	
	//glLoadIdentity();
	//gluLookAt(1, 1, 1, 0.5, 0.5, 0.5, 0, 1, 0);
	//gluLookAt(0, 0, 0, 0.25, 0.25, 0.25, 0, 1, 0);
	//glEnableVertexAttribArray(0);
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	
	GLuint vbo[3];  // unsigned array pointer of GPU memory, same as float* my_array[3];
	glGenBuffers(3, vbo);  // 3: 3-array
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);  // bind to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  

	 //NOTE: don't forget glDeleteBuffersARB(1, &vbo);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Initialize shader programme
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glBindAttribLocation(shader_programme, 0, "a_pos");
	glLinkProgram(shader_programme);

	// check the link status
	GLint linked = 0;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(shader_programme, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(shader_programme);
		return false;
	}


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // depth test

		// We are using built-in shaders (we can not modify it)
		// draw with glew function : default shading, send data to GPU
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//glEnableClientState(GL_VERTEX_ARRAY);  // send positions vertex data to GPU
		//glVertexPointer(3, GL_FLOAT, 0, 0);  // Vector3D

		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glEnableClientState(GL_COLOR_ARRAY);
		//glColorPointer(3, GL_FLOAT, 0, 0);

		// send connectivity information between vertices 
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, num_quads * 4, GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);*/

		// we are going to use our custom shaders
		/* shader version */
		glUseProgram(shader_programme); // activate the shader

		/* draw here */
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer
		(
			0,						// attribute 0. No particular reason for 0, but
			3,						// size(x, y, z) position
			GL_FLOAT,				// type
			GL_FALSE,				// normalized?
			0,						// stride
			(void*)0				// array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_QUADS, num_quads * 4, GL_UNSIGNED_INT, 0);


		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}
