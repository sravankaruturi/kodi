#pragma once

#include "Graphics/Window.h"
#include <iostream>

int main() {

	using namespace kodi;
	using namespace graphics;

	Window window("Kodi", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl; 

	double x, y;

	while (!window.IsClosed()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (window.isKeyPressed(GLFW_KEY_A))
			std::cout <<  "Pressed" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			std::cout << "Left Mouse Pressed" << std::endl;

		window.GetMousePosition(x, y);

		// std::cout << x << ", " << y << std::endl;

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		
		glEnd();

		window.Update();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}
	}

}