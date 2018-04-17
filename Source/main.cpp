#pragma once

#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"
#include "Utils/fileUtils.h"

int main() {

	using namespace kodi;
	using namespace graphics;

	Window window("Kodi", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl; 

	std::string test = utils::read_file("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/main.cpp");
	std::cout << test << std::endl;
	return 0;

	math::vec4 a(1.0f, 1.0f, 1.0f, 1.0f);
	math::vec4 b(2.0f, 2.0f, 2.0f, 2.0f);

	math::vec4 c = a + b;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;

	b -= a;

	if (b == a) {
		std::cout << "Equal" << std::endl;
	}

	double x, y;
	
	math::mat4 position = math::mat4::translation(math::vec3(2, 3, 4));
	math::mat4 newPosition = math::mat4::translation(math::vec3(0, 1, 2));

	math::mat4 newMatrix = position * newPosition;

	std::cout << newMatrix.columns[0] << std::endl;

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