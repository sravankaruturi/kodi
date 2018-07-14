#include "Metagame.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"

#include "../Game/DodgerGame.cpp"

namespace kodi
{
	Metagame::Metagame()
	{

		window = createWindow("Kodi Engine & Games", 800, 600);

		const std::vector<std::string> game_names = {
			"Dodger",
			"Memory Puzzle",
			"Sliding Puzzle"
		};

		selectionMenu = DBG_NEW Menu(game_names, vec2(-4.0f, 2.0f), 0xFFFFFF, 1);

	}

	void Metagame::Init()
	{
		
		selectionShader = DBG_NEW Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag"
		);

		auto error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		selectionLayer = DBG_NEW Layer(DBG_NEW BatchRenderer2D(), selectionShader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		selectionLayer->Add(selectionMenu);
		
	}

	void Metagame::StartGame()
	{

	}

	void Metagame::Tick()
	{

	}

	void Metagame::Update()
	{
		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		if (window->IsKeyPressed(GLFW_KEY_UP))
		{
			this->selectionMenu->MenuUp();
		}
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
		{
			this->selectionMenu->MenuDown();
		}

		if (window->IsKeyPressed(GLFW_KEY_ENTER)) {
			switch (this->selectionMenu->selectedIndex) {

				case 0:
					currentGame = reinterpret_cast<Kodi *>(DBG_NEW DodgerGame(this->window));
					isAGameActive = true;
					currentGame->Start();
					break;

			}
		}

	}

	void Metagame::Render()
	{
		selectionLayer->Render();
	}

	void Metagame::PhysicsTick()
	{

	}

	void Metagame::ResetGame()
	{

	}

	Metagame::~Metagame()
	{

		delete currentGame;

		delete selectionLayer;
		delete selectionShader;
		delete selectionMenu;

		delete window;

		// Window would be terminated in Kodi Destructor.
	}

}
