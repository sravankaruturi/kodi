#define ENGINE_DEMO 1
#include "../Game/Metagame.h"
#if ENGINE_DEMO

#include "Graphics/Window.h"
#include <iostream>
#include "Math/Math.h"

#include "Graphics/Renderables/Sprite.h"

#include <ctime>

#include "Utils/Timer.h"

#include "TileLayer.h"
#include <cassert>

#include "Graphics/Layers/Group.h"

#define STRESS_TEST			0
#define GAME_TEST			1

using namespace kodi;
using namespace graphics;
using namespace math;

#if _WINDOWS
#define _CRTDBG_MAP_ALLOC  
#include <cstdlib>
#include <crtdbg.h>  
#endif

#if STRESS_TEST

int main()
{
	using namespace kodi;
	using namespace graphics;
	using namespace math;

	Window window("Kodi", 960, 540);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// const auto ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* shader = new Shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert",
	              "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");

	shader->Enable();
	shader->setVec2("light_pos", vec2(4.0f, 1.5f));

	TileLayer tile_layer(shader);
	TileLayer tile_layer2(shader);

#if STRESS_TEST

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

#elif LAYER_TEST

	Group* group1 = new Group();
	group1->SetTransformMatrix(mat4::translation(vec3(-15.0f, 5.0f, 0.0f)) * mat4::rotation(45.0f, vec3(0, 0,1)));
	group1->AddRenderable(new Sprite(0, 0, 6, 3, vec4(1, 1, 1, 1)));

	Group* button = new Group();
	button->SetTransformMatrix(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
	button->AddRenderable(new Sprite(0, 0, 5.0f, 2.0f, vec4(1, 0, 1, 1)));
	button->AddRenderable(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, vec4(0.2f, 0.3f, 0.8f, 1)));

	group1->AddRenderable(button);

	tile_layer.Add(group1);

#endif

	printf("Rendering, %d sprites", static_cast<int>(tile_layer.GetSpriteCount()));

	while (!window.IsClosed())
	{
		kodi::graphics::Window::Clear();
#if LAYER_TEST
		group1->SetTransformMatrix(mat4::translation(vec3(-15.0f, 5.0f, 0.0f)) * mat4::rotation( glfwGetTime() * 100 , vec3(0, 0, 1)));
#endif

		shader->Enable();
		glActiveTexture(GL_TEXTURE0);
		t.Bind();
		shader->setInt("texture0", 0);
		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000)
		{
			shader->setVec2("light_pos", vec2(static_cast<float>(x * 32.0f / 960.0f - 16.0f), static_cast<float>(9.0f - y * 18.0f / 540.0f)));
		}

		// tile_layer.Render();
		textureTest->SubmitToRenderer((Renderer2D *)&simple);
		t.UnBind();
		simple.Flush();

		window.Update();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	delete shader;
}

#endif

#if GAME_TEST
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

#define KODI_THROW_EXCEPTIONS 1

	//DodgerGame g;
	//g.Start();
	//return 0;

	Metagame m;
	m.Start();
	return 0;

}
#endif


#endif