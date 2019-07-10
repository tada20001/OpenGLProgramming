#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <map>

const int width_window = 640;
const int height_window = 480;
std::map<int, bool> key_status;

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

	// Make the window's context current
	glfwMakeContextCurrent(window);
	//glClearColor(174.0/255.0, 95.0/255.0, 95.0 / 255.0, 1);   
	glClearColor(1, 1, 1, 1); // white background
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	const float aspect_ratio = (float)width / (float)height;  // 1.66, 1.9 TV display
	glOrtho((double)-1 * aspect_ratio, (double)1 * aspect_ratio, -1, 1, -1.0, 1.0);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// render here
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		// Note: this is an old-style OpenGL
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 0.0, 0.0);  // red
		//glVertex3f(0.0, 0.0, 0.0);  // it is equivalent to glVertex2f(0.0, 0.0) in 2D drawing
		//
		//glColor3f(0.0, 1.0, 0.0);
		//glVertex3f(0.5, 0.0, 0.0);

		//glColor3f(0.0, 0.0, 1.0);
		//glVertex3f(0.25, 0.5, 0.0);

		// center of polygonized circle
		glVertex2f(0.0, 0.0);

		const int num_triangles = 1000;
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
		const float radius = 0.5f;

		float theta = 0.0f;
		for(int i=0; i <= num_triangles; i++, theta += dtheta)
		for(float theta = 0.0; theta < 2.0 * 3.141592; theta+= dtheta)
		{
			const float x = radius * cos(theta);
			const float y = radius * sin(theta);

			glVertex2f(x, y);
		}
		glEnd();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (isKeyPressedAndReleased(window, GLFW_KEY_ESCAPE)) glfwTerminate();
	}

	glfwTerminate();

	return 0;
}
