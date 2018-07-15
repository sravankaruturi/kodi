#pragma once
#include "../Source/Kodi.h"
#include "../Source/Graphics/Label.h"
#include "../Source/Graphics/Layers/Menu.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"


using namespace kodi;
using namespace graphics;

class MemoryPuzzle: public Kodi
{
	
	/* Layers */
	Layer * menuLayer;
	Layer * gameLayer;
	Layer * scoreCardLayer;

	std::vector<Texture *> tileTextures;
	std::vector<Sprite *> tileSprites;

	Label * scoreLabel;

	Shader * gameShader;

	Menu * gameMenu;

public:

	MemoryPuzzle(Window * _window)
	{
		this->window = _window;
		_ASSERT(nullptr != window);

		std::vector<std::string> menuItems = { "Start Game", "Options", "Quit" };

		gameMenu = DBG_NEW Menu(menuItems, vec2(-4.1f, 0.5f), 0xFF11FF, 1);

	}

	~MemoryPuzzle()
	{
		
		delete gameShader;

		delete gameMenu;

		delete menuLayer;

	}

	void Init() override
	{
		gameShader = DBG_NEW Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag"
		);

		menuLayer = DBG_NEW Layer(DBG_NEW BatchRenderer2D(), gameShader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		menuLayer->Add(gameMenu);
	}

	void StartGame() override
	{

		
	}

	void Tick() override
	{
		
	}

	void Update() override
	{
		
	}

	void Render() override
	{
		menuLayer->Render();
	}

	void PhysicsTick() override
	{
		
	}

	void ResetGame() override
	{
		
	}
};