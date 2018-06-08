#include "../Source/Kodi.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"


using namespace kodi;
using namespace graphics;

class Game : public Kodi
{
	
private:

#define FALLING_BLOCKS_LIMIT	32

	Window * window;
	Layer * layer;
	Texture * fallingBlockTexture;
	std::vector<Sprite *> fallingBlocks;
	Sprite * playerSprite;
	Shader * shader;

public:

	Game()
	{
		fallingBlocks.resize(2 * FALLING_BLOCKS_LIMIT);
	};

	~Game()
	{
		delete layer;
	}

	void Init() override
	{
		window = createWindow("Test Game", 800, 600);
		// TODO : Ikkada Shader map thayaaru chesukoni pettuko.
		shader = new Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag");
		layer = new Layer(new BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		/* sprite = new Sprite(0, 0, 4, 4, new Texture(
			                    "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/awesomeface.png")); */

		fallingBlockTexture = new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Fallin-Down-Enemy.png");

		for(int i = 0 ; i < FALLING_BLOCKS_LIMIT ; i++)
		{
			fallingBlocks[i] = (new Sprite(0.5 + i * 0.5, i * 0.5, 1, 1, fallingBlockTexture));
		}

		playerSprite = new Sprite(0, 0, 1, 1, new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Falling-Down-Player.png"));

		/*Manam mundhu pettinavi venukaala kanipisthaayi.*/
		layer->Add(playerSprite);

		for (auto i = 0; i < FALLING_BLOCKS_LIMIT; i++)
		{
			if ( nullptr != fallingBlocks[i])
			{
				layer->Add(fallingBlocks[i]);
			}
		}
		
	}

	void Tick() override
	{
		printf("Updates per second: %d. Frames Per Second: %d\n", GetUpdatesPerSecond(), GetFramesPerSecond());
	}

	void Update() override
	{
		const auto speed = 0.005f;
		if (window->IsKeyPressed(GLFW_KEY_UP))
			playerSprite->position.y += speed;
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
			playerSprite->position.y -= speed;
		if (window->IsKeyPressed(GLFW_KEY_LEFT))
			playerSprite->position.x -= speed;
		else if (window->IsKeyPressed(GLFW_KEY_RIGHT))
			playerSprite->position.x += speed;

		double x, y;
		window->GetMousePosition(x, y);
		shader->setVec2("light_pos", math::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));
	}

	void Render() override
	{
		layer->Render();
	}

};