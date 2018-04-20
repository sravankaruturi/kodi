#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"

#include "Graphics/Sprite.h"

#include <ctime>

#include "Utils/Timer.h"

#include "Graphics/TileLayer.h"
#include <cassert>

#define USE_BATCH_RENDERER 1

int main()
{
	using namespace kodi;
	using namespace graphics;
	using namespace math;

	Window window("Kodi", 800, 600);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// const auto ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* shader = new Shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert",
	              "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");

	shader->Enable();
	shader->setVec2("light_pos", vec2(4.0f, 1.5f));

	TileLayer tile_layer(shader);
	TileLayer tile_layer2(shader);

	srand(time(nullptr));

	const auto y_max = 9 * 20;
	const auto x_max = 16 * 20;
	for (auto y = 0; y < y_max; y++ ) 
	{
		for (auto x = 0; x < x_max; x++ )
		{
			tile_layer.Add(new Sprite(float(x/20.0f), float(y/20.f), 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	tile_layer2.Add(new Sprite(0, 0, 5, 5, vec4(1, 1, 0, 1)));

	printf("Rendering, %d sprites", static_cast<int>(tile_layer.GetSpriteCount()));

	while (!window.IsClosed())
	{
		kodi::graphics::Window::Clear();

		shader->Enable();
		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000)
		{
			shader->setVec2("light_pos", vec2(float(x * 16.0f / 800.f), float(9.0f - y * 9.0f / 600.f)));
		}

		tile_layer.Render();
		tile_layer2.Render();

		window.Update();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	delete shader;
}
