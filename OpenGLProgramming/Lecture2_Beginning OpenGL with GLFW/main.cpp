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
#include <vector>
#include <GL/GLU.h>

const int width_window = 640;
const int height_window = 480;
std::map<int, bool> key_status;

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

bool isKeyPressedAndReleased(GLFWwindow *glfw_window, const int& key)
{

	if (key_status.count(key) <= 0) key_status[key] == false;  // register key to map

	if (glfwGetKey(glfw_window, key) == GLFW_RELEASE)
	{
		if (key_status[key] == true)
		{
			key_status[key] == false;
			return true;
		}
		else
		{
			key_status[key] = false;
			return false;
		}
	}
	else
	{
		key_status[key] = true;
		return false;
	}
}


int main(void)
{
	GLFWwindow* window = nullptr;

	// initialize the library
	if (!glfwInit())
		return -1;

	// create a windowed mode window and its OpenGL context
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

	printf("%s\n", glGetString(GL_VERSION));

	// default color for display buffer
	glClearColor(174.0/255.0, 95.0/255.0, 95.0 / 255.0, 1);   
	//glClearColor(1, 1, 1, 1); // white background

	gluLookAt(0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0, 1, 0);  // it requires 9 parameters for 3-Dimension

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	const float aspect_ratio = (float)width / (float)height;  // 1.66, 1.9 TV display
	glOrtho((double)-1 * aspect_ratio, (double)1 * aspect_ratio, -1, 1, -10.0, 10.0);


	const Vector3D color[4] = {
						Vector3D(1.0, 0.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 0.0, 1.0),
						Vector3D(0.0, 0.0, 1.0),
						};

	const Vector3D vertex[4] = {
						Vector3D{ 0.0, 0.0, 0.0 },  
						Vector3D{ 0.5, 0.0, 0.0 },	
						Vector3D{ 0.25, 0.5, 0.0 },
						Vector3D{ 0.5, 0.5, -0.5 }};	
	
	GLubyte indices[] = { 0, 1, 2, 1, 2, 3 };  // multiple triangle by using less vertices, in the field of topology theory

	int num_vertices = 4;

	GLuint vbo[3];  // unsigned array pointer of GPU memory, same as float* my_array[3];

	glGenBuffers(3, vbo);  // 3: 3-array

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);  // bind to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * sizeof(Vector3D), color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 3, vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 6, indices, GL_STATIC_DRAW);  // 6: the number of indices

	// NOTE: don't forget glDeleteBuffersARB(1, &vbo);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// render here
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
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6 * 3);

		// send connectivity information between vertices 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		//if (isKeyPressedAndReleased(window, GLFW_KEY_ESCAPE)) glfwTerminate();
	}

	glfwTerminate();

	return 0;
}
