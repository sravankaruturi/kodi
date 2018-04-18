#pragma once

#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"

#include "Graphics/Simple2DRenderer.h"

int main() {

	using namespace kodi;
	using namespace graphics;
	using namespace math;

	Window window("Kodi", 800, 600);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl; 

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert", "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");


	shader.Enable();
	shader.setMat4("pr_matrix", ortho);
	shader.setVec2("light_pos", vec2(4.0f, 1.5f));
	shader.setVec4("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	Renderable2D sprite1(vec3(5, 5, 0), vec2(4, 4), vec4(1, 0, 1, 1), &shader);
	Renderable2D sprite2(vec3(7, 1, 0), vec2(2, 3), vec4(0.2f, 0, 1, 1), &shader);

	Simple2DRenderer renderer;

	while (!window.IsClosed()) {
		
		window.clear();

		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000) {
			shader.setVec2("light_pos", vec2((float)(x * 16.0f / 800.f), (float)(9.0f - y * 9.0f / 600.f)));
		}

		shader.setMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

		renderer.Submit(&sprite1);
		renderer.Submit(&sprite2);

		renderer.Flush();
		
		window.Update();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}
	}

}
