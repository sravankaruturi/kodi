#include "../Source/Kodi.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"


using namespace kodi;
using namespace graphics;

class Game : public Kodi
{
	
private:

	Window * window;
	Layer * layer;
	Sprite * sprite, *sprite2;
	Shader * shader;

public:

	Game()
	{
		
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
		sprite = new Sprite(0, 0, 4, 4, new Texture(
			                    "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/awesomeface.png"));
		sprite2 = new Sprite(4, 0, 4, 4, new Texture(
			                     "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/container.jpg"));

		/*Manam mundhu pettinavi venukaala kanipisthaayi.*/
		layer->Add(sprite);
		layer->Add(sprite2);
		
	}

	void Tick() override
	{
		printf("Updates per second: %d. Frames Per Second: %d\n", GetUpdatesPerSecond(), GetFramesPerSecond());
	}

	void Update() override
	{
		const auto speed = 0.05f;
		if (window->IsKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->IsKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		else if (window->IsKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;

		double x, y;
		window->GetMousePosition(x, y);
		shader->setVec2("light_pos", math::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));
	}

	void Render() override
	{
		layer->Render();
	}

};