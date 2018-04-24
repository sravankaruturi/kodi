#include "TetrisGame.h"
#include "../Source/Graphics/Renderables/Sprite.h"

TetrisGame::TetrisGame(std::string& _title, int _width, int _height)
{
	TetrisGame(_title.c_str(), _width, _height);
}

TetrisGame::TetrisGame(const char * _title, int _width, int _height)
{
	// TODO: Ikkada manaku fullscreen kosam oka option kaavaali.
	windowHandler = new graphics::Window(_title, _width, _height);

	glClearColor(0.1, 0.1, 0.1, 1.f);
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	const auto ortho = mat4::orthographic(-16.f, 16.f, -9.f, 9.f, -1.f, 1.f);

	// TODO: Add static layer Shaders here.
	staticLayerShader = new graphics::Shader(
		"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Game/Shaders/static.vert",
		"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Game/Shaders/static.frag");

	// TODO: Manaki screen lo oka rectangular box kaavaali, Play arena denote cheyyataaniki.
	// Avi static layer lo vuntaayi.
	staticLayer = new graphics::Layer(new graphics::BatchRenderer2D(), staticLayerShader, math::mat4::orthographic(-16, 16, -9, 9, -1, 1));

	staticLayerShader->Enable();
	staticLayerShader->setMat4("pl_matrix", ortho);

	
	

	/* Anni Renderablesnee Initialize Cheyyi */
	InitRenderables();

}


void TetrisGame::InitRenderables()
{

	// TODO: Oka koththa class kaavaali. Sprite padhulu manaki. Sprite Class ki, position madhyalo ledhu. krindha edamavaipu vundhi.
	staticLayer->Add(new graphics::Sprite(0, 0, 16, 16, vec4(0.7, 0.2, .7, 1)));

}

void TetrisGame::Update()
{
	graphics::Window::Clear();

	/* Update Stuff */

	/* Update Ikkadatho Aapu*/

	staticLayer->Render();

	this->windowHandler->Update();
	
}

TetrisGame::~TetrisGame()
{
	delete staticLayer;
	delete windowHandler;
}
