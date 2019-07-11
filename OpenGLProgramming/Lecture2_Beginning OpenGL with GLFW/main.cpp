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

Vector4D<float> positions[num_vertices] =
{
	Vector4D<float>(0.0, 0.0, 0.5, 1.0),
	Vector4D<float>(0.5, 0.0, 0.5, 1.0),
	Vector4D<float>(0.5, 0.0, 0.0, 1.0),
	Vector4D<float>(0.0, 0.0, 0.0, 1.0),

	Vector4D<float>(0.0, 0.0, 0.5, 1.0),
	Vector4D<float>(0.5, 0.0, 0.5, 1.0),
	Vector4D<float>(0.5, 0.5, 0.5, 1.0),
	Vector4D<float>(0.0, 0.5, 0.5, 1.0),

	Vector4D<float>(0.5, 0.0, 0.5, 1.0),
	Vector4D<float>(0.5, 0.0, 0.0, 1.0),
	Vector4D<float>(0.5, 0.5, 0.0, 1.0),
	Vector4D<float>(0.5, 0.5, 0.5, 1.0),

	Vector4D<float>(0.0, 0.0, 0.5, 1.0),
	Vector4D<float>(0.0, 0.0, 0.0, 1.0),
	Vector4D<float>(0.0, 0.5, 0.0, 1.0),
	Vector4D<float>(0.0, 0.5, 0.5, 1.0),

	Vector4D<float>(0.0, 0.0, 0.0, 1.0),
	Vector4D<float>(0.5, 0.0, 0.0, 1.0),
	Vector4D<float>(0.5, 0.5, 0.0, 1.0),
	Vector4D<float>(0.0, 0.5, 0.0, 1.0),

	Vector4D<float>(0.0, 0.5, 0.5, 1.0),
	Vector4D<float>(0.5, 0.5, 0.5, 1.0),
	Vector4D<float>(0.5, 0.5, 0.0, 1.0),
	Vector4D<float>(0.0, 0.5, 0.0, 1.0),
};


const GLbyte indices[num_quads * 4] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	16, 17, 18, 19,
	20, 21, 22, 23,
};

void moveBox()
{
	// translation
	/*const float dx = -0.01;
	const float dy = 0.0;
	const float dz = 0.0;

	Matrix4<float> tr;
	tr.setRow(0, 1, 0, 0, dx);
	tr.setRow(1, 0, 1, 0, dy);
	tr.setRow(2, 0, 0, 1, dz);
	tr.setRow(3, 0, 0, 0, 1);*/

	const float theta = 1.0 / 360.0 * 2.0 * 3.141592;  // degree * 2 * pi : 1 degree in radian

	Matrix4<float> rot;
	// rotation about x-axis
	rot.setRow(0, 1, 0, 0, 0.0);
	rot.setRow(1, 0, cos(theta), -sin(theta), 0.0);
	rot.setRow(2, 0, sin(theta), cos(theta), 0.0);
	rot.setRow(3, 0, 0, 0, 1);

	// rotation about y-axis
	rot.setRow(0, cos(theta), 0, sin(theta), 0.0);
	rot.setRow(1, 0, 1, 0, 0.0);
	rot.setRow(2, -sin(theta), 0, cos(theta), 0.0);
	rot.setRow(3, 0, 0, 0, 1);

	for (int v = 0; v < num_vertices; v++)
	{
		/*positions[v].x_ += dx;
		positions[v].y_ += dy;
		positions[v].z_ += dz;*/

		Vector4D<float> temp = positions[v];
		rot.multiply(temp, positions[v]);
	}
}

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
	//const float aspect_ratio = (float)width / (float)height;  // 1.66, 1.9 TV display
	//glOrtho((double)-1 * aspect_ratio, (double)1 * aspect_ratio, -1, 1, -10.0, 10.0);
	glOrtho(-1.2, 1.2, -1.2, 1.2, -10.0, 10.0);
	// TODO: consider anisotropic view
	gluLookAt(1.2, 0.8, 1.2, 0.5, 0.5, 0.5, 0, 1, 0);  // it requires 9 parameters for 3-Dimension
	
	//glLoadIdentity();
	//gluLookAt(1, 1, 1, 0.5, 0.5, 0.5, 0, 1, 0);
	//gluLookAt(0, 0, 0, 0.25, 0.25, 0.25, 0, 1, 0);
	//glEnableVertexAttribArray(0);
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	
	/*const Vector3D colors[6] = {
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						};*/
	
	GLuint vbo[3];  // unsigned array pointer of GPU memory, same as float* my_array[3];

	glGenBuffers(3, vbo);  // 3: 3-array

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);  // bind to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  // 6: the number of indices

	// NOTE: don't forget glDeleteBuffersARB(1, &vbo);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		moveBox();  // animation

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // depth test

		//TODO: draw here
		// Note: this is an old-style OpenGL
		// In this example, we draw only one triangle
		// this is for massive polygons
		//glBegin(GL_TRIANGLES);

		//for (int v = 0; v < 3; v++)
		//{
		//	glColor3f(color[v].r_, color[v].g_, color[v].b_);
		//	//glColor3fv(color[v].data);
		//	glVertex3f(vertex[v].x_, vertex[v].y_, vertex[v].z_);
		//}
		//glEnd();

		// Modern c++ style : save time to send data from GPU to CPU
		// 1. set my_array
		//glEnableClientState(GL_COLOR_ARRAY);  
		//glEnableClientState(GL_VERTEX_ARRAY);
		//
		//// 2. set the pointer of my_array
		//glColorPointer(3, GL_FLOAT, 0, color);  
		//glVertexPointer(3, GL_FLOAT, 0, vertex);
		//// 3. draw array
		//glDrawArrays(GL_TRIANGLES, 0, 9);  

		/*glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);*/

		// draw with glew function

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(4, GL_FLOAT, 0, 0);  // Vector4D

		// send connectivity information between vertices 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, num_quads * 4, GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}
