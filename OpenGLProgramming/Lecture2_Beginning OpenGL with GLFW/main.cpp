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

	printf("%s\n", glGetString(GL_VERSION));


	glClearColor(174.0/255.0, 95.0/255.0, 95.0 / 255.0, 1);   
	//glClearColor(1, 1, 1, 1); // white background
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	const float aspect_ratio = (float)width / (float)height;  // 1.66, 1.9 TV display
	glOrtho((double)-1 * aspect_ratio, (double)1 * aspect_ratio, -1, 1, -1.0, 1.0);


	const Vector3D color[3] = {
						Vector3D(1.0, 0.0, 0.0),
						Vector3D(0.0, 1.0, 0.0),
						Vector3D(0.0, 0.0, 1.0) };

	const Vector3D vertex[3] = {
						Vector3D{ 0.0, 0.0, 0.0 },  // first vertex
						Vector3D{0.5, 0.0, 0.0},	// second vertex
						Vector3D{0.25, 0.5, 0.0} };	// third vectex
	

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// render here
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		// Note: this is an old-style OpenGL
		// In this example, we draw only one triangle
		// this is for massive polygons
		glBegin(GL_TRIANGLES);

		for (int v = 0; v < 3; v++)
		{
			glColor3f(color[v].r_, color[v].g_, color[v].b_);
			//glColor3fv(color[v].data);
			glVertex3f(vertex[v].x_, vertex[v].y_, vertex[v].z_);
		}

		// center of polygonized circle
		/*glVertex2f(circle_center_x, circle_center_y);

		const int num_triangles = 1000;
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
		const float radius = 0.5f;

		float theta = 0.0f;
		for(int i=0; i <= num_triangles; i++, theta += dtheta)
		for(float theta = 0.0; theta < 2.0 * 3.141592; theta+= dtheta)
		{
			const float x = radius * cos(theta) + circle_center_x;
			const float y = radius * sin(theta) + circle_center_y;

			glVertex2f(x, y);
		}*/
		glEnd();

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
