#pragma once

#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"
#include "Graphics/Shader.h"

#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/IndexBuffer.h"

int main() {

	using namespace kodi;
	using namespace graphics;
	using namespace math;

	Window window("Kodi", 800, 600);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl; 

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat coloursA[] = {

		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1
	};

	GLfloat coloursB[] = {

		0.2, 0.8, 0.5, 1,
		1, 0, 0, 1,
		0, 1, 1, 1,
		1, 0, 1, 1
	};

	VertexArray sprite1, sprite2;
	Buffer * vbo = new Buffer(vertices, 12, 3);
	Buffer * cboA = new Buffer(coloursA, 16, 4);
	Buffer * cboB = new Buffer(coloursB, 16, 4);
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(vbo, 0);
	sprite1.addBuffer(cboA, 1);

	sprite2.addBuffer(vbo, 0);
	sprite2.addBuffer(cboB, 1);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert", "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");

	shader.Enable();
	shader.setMat4("pr_matrix", ortho);
	// glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "projectionMatrix"), 1, GL_FALSE, ortho.elements);
	

	shader.setVec2("light_pos", vec2(4.0f, 1.5f));
	shader.setVec4("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.IsClosed()) {
		
		window.clear();

		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000) {
			shader.setVec2("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		}

		sprite1.Bind();
		ibo.Bind();
		shader.setMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		ibo.UnBind();
		sprite1.UnBind();

		sprite2.Bind();
		ibo.Bind();
		shader.setMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		ibo.UnBind();
		sprite2.UnBind();

		window.Update();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}
	}

}