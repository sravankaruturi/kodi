#pragma once

#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"

#include "Graphics/Simple2DRenderer.h"
#include "Graphics/BatchRenderer2D.h"

#include "Graphics/Sprite.h"
#include "Graphics/StaticSprite.h"

#include <time.h>

#include <assert.h>

#define USE_BATCH_RENDERER 0

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

	std::vector<Renderable2D *> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
			sprites.push_back(new
#if USE_BATCH_RENDERER
				Sprite
#else
				StaticSprite
#endif
				(x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !USE_BATCH_RENDERER
					, shader
#endif

					));
		}
	}

#if USE_BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	while (!window.IsClosed()) {
		
		window.clear();

		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000) {
			shader.setVec2("light_pos", vec2((float)(x * 16.0f / 800.f), (float)(9.0f - y * 9.0f / 600.f)));
		}

		
#if USE_BATCH_RENDERER
		renderer.Begin();
#endif

		for (int i = 0; i < sprites.size(); i++) {
			renderer.Submit(sprites[i]);
		}

		//renderer.Submit(&sprite);
		//renderer.Submit(&sprite2);

#if USE_BATCH_RENDERER
		renderer.End();
#endif

		renderer.Flush();

		printf("Sprites: %d\n", sprites.size());
		
		window.Update();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}
	}

}
