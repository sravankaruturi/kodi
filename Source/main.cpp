#define ENGINE_DEMO 1
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
#define LAYER_TEST			0
#define ROTATE_TEST			0
#define TEXTURE_TEST		0
#define TEXTURE_BATCH_TEST	0
#define GAME_TEST			1

using namespace kodi;
using namespace graphics;
using namespace math;

#include "../Game/Game.cpp"

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

#if TEXTURE_TEST
int main()
{	
	Window window("Kodi", 960, 540);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	const auto projectionMatrix = mat4::orthographic(-16.0, 16, -9, 9, -1, 1);

	Shader* shader = new Shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert",
		"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");

	shader->Enable();
	shader->setMat4("pr_matrix", projectionMatrix);
	shader->setInt("texture0", 0);

	Texture outTexture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/container.jpg");

	Simple2DRenderer renderer;
	StaticSprite sprite(0, 0, 6, 4, vec4(1, 0, 1, 1), shader);

	while (!window.IsClosed())
	{
		Window::Clear();

		outTexture.Bind();

		shader->Enable();
		renderer.Submit(&sprite);

		renderer.Flush();

		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000)
		{
			shader->setVec2("light_pos", vec2(static_cast<float>(x * 32.0f / 960.0f - 16.0f), static_cast<float>(9.0f - y * 18.0f / 540.0f)));
		}

		window.Update();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) 
		{
			break;
		}
	}

	delete shader;
}
#endif

#if ROTATE_TEST
int main()
{

	Window window("Kodi", 960, 540);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	Shader* shader = new Shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.vert",
		"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/basic.frag");

	shader->Enable();

	Sprite * sprite = new Sprite(0, 0, 2, 2, vec4(1, 1, 0, 1));

	shader->Enable();
	shader->setMat4("ml_matrix", mat4::translation(vec3(2, 0, 0)) * mat4::rotation(45, vec3(0, 0, 1)));

	TileLayer tile_layer(shader);
	tile_layer.Add(sprite);

	while (!window.IsClosed())
	{
		Window::Clear();

		shader->Enable();
		// shader->setMat4("ml_matrix", mat4::translation(vec3(sin(glfwGetTime()) * 5, 0, 0)) * mat4::rotation(cos(glfwGetTime()) * 180, vec3(0, 0, 1)) );

		tile_layer.Render();

		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000)
		{
			shader->setVec2("light_pos", vec2(static_cast<float>(x * 32.0f / 960.0f - 16.0f), static_cast<float>(9.0f - y * 18.0f / 540.0f)));
		}

		window.Update();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	delete shader;
}
#endif

#if TEXTURE_BATCH_TEST
int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);


	Window window("Kodi", 960, 540);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	const auto projection_matrix = mat4::orthographic(-16.0, 16, -9, 9, -1, 1);

	auto shader = new Shader("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
		"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag");

	Texture * textures[] = {
		new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/container.jpg"),
		new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/awesomeface.png")
	};

	auto tile_layer = new TileLayer(shader);

	srand(time(nullptr));

	const auto y_max = 9 * 2;
	const auto x_max = 16 * 2;
	for (auto y = 0; y < y_max; y++)
	{
		for (auto x = 0; x < x_max; x++)
		{
			if (rand() % 4 == 0) {
				tile_layer->Add(new Sprite(
					(x - x_max / 2.0f) + 0.475f,
					(y - y_max / 2.0f) + 0.475f,
					0.9f,
					0.9f,
					vec4(1, 0, 0, 1)));
			}
			else
			{
				tile_layer->Add(new Sprite(
					(x - x_max / 2.0f) + 0.475f,
					(y - y_max / 2.0f) + 0.475f,
					0.9f,
					0.9f,
					vec4(1, 0, 0, 1), textures[rand() % 2])
				);
			}
		}
	}

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader->Enable();
	shader->SetIntArray("textures", 10, texIDs);
	shader->setMat4("pr_matrix", projection_matrix);

	while (!window.IsClosed())
	{
		Window::Clear();

		/* Update Stuff */
		for ( auto iterator: tile_layer->GetRenderables())
		{
			iterator->SetColour(vec4(sin(glfwGetTime() + 1)/2, 0, 1, 0));
		}


		/* Render Stuff */

		tile_layer->Render();


		/* Input Stuff */
		double x, y;
		window.GetMousePosition(x, y);
		if (x > 0 && y > 0 && x < 2000 && y < 2000)
		{
			shader->setVec2("light_pos", vec2(static_cast<float>(x * 32.0f / window.GetWidth() - 16.0f), static_cast<float>(9.0f - y * 18.0f / window.GetHeight())));
		}

		window.Update();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	delete tile_layer;
	delete shader;

	for ( auto iterator: textures)
	{
		delete iterator;
	}
}
#endif

#if GAME_TEST
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	Game g;
	g.Start();
	return 0;
}
#endif


#endif