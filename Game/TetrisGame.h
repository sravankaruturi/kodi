#pragma once

#include <iostream>
#include <string>
#include "../Source/Graphics/Window.h"
#include "../Source/Graphics/Layers/Layer.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"
#include "../Source/Graphics/Shader.h"

using namespace kodi;

class TetrisGame
{

protected:

	graphics::Window * windowHandler;

	/* Static Layer Variables */
	graphics::Layer * staticLayer;
	graphics::Shader * staticLayerShader;

protected:

	void InitRenderables();

public:

	TetrisGame(std::string& _title, int _width, int _height);
	TetrisGame(const char* _title, int _width, int _height);

	graphics::Window * GetWindow() { return windowHandler; }

	void Update();

	~TetrisGame();
	
};
