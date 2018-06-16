#include "../Source/Kodi.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"
#include "../Source/Graphics/Label.h"


using namespace kodi;
using namespace graphics;

class DodgerGame : public Kodi
{
	
private:

#define FALLING_BLOCKS_LIMIT	32

	Window * window;
	Layer * layer;
	Texture * fallingBlockTexture;
	std::vector<Sprite *> fallingBlocks;
	Sprite * playerSprite;
	Shader * shader;
	std::vector<int> activatedFallinBlockIndices;
	float deltaTime;
	float time;
	/*Activate a block each second or the time specified here in seconds*/
	float activateBlockDelay = 1.f;
	float timerForActivatingBlocks = 0.f;
	const float speed = 5.f;

	int health = 100;

	Label * testLabel;
	/**
	 * \brief The Text Start Game.
	 */
	Label * startGame;
	/**
	 * \brief The Text End Game,
	 */
	Label * endGame;
	/**
	 * \brief Manam e Label Select chesukunnamo manaki gurthu vundataaniki.
	 */
	int selectedLabel = 1; // 1 if Start Game and -1 if Quit.

	/**
	 * \brief This would be activated once the player hits Start Game.
	 */
	bool gameActive = false;
	bool gameInitialised = false;

	///* Testing */
	//Layer * textLayer;
	//Shader * textShader;

public:

	DodgerGame()
	{
		fallingBlocks.resize(2 * FALLING_BLOCKS_LIMIT);
		time = glfwGetTime();

		testLabel = new Label(std::to_string(health), -16, 8, 255);
		startGame = new Label("Start Game", -5, -1, 0xFFFFFF);
		endGame = new Label("End Game", -4, -2, 255);

	};

	~DodgerGame()
	{
		delete layer;
		delete testLabel;
	}

	void Init() override
	{

		window = createWindow("Test DodgerGame", 800, 600);

		// TODO : Ikkada Shader map thayaaru chesukoni pettuko.
		shader = new Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag");

		auto error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		assert("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif


		layer = new Layer(new BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		assert("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		/*textShader = new Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/text.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/text.frag");

		textLayer = new Layer(new BatchRenderer2D(), textShader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));*/

		fallingBlockTexture = new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Fallin-Down-Enemy.png");

		// They are just above the visible screen space.
		for(auto i = 0 ; i < FALLING_BLOCKS_LIMIT ; i++)
		{
			fallingBlocks[i] = (new Sprite(-15 + i * 1.5, 10, 1, 1, fallingBlockTexture));
		}

		playerSprite = new Sprite(0, 0, 1, 1, new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Falling-Down-Player.png"));

		layer->Add(startGame);
		layer->Add(endGame);

	}

	void StartGame() override
	{
		/*Manam mundhu pettinavi venukaala kanipisthaayi.*/
		layer->Add(playerSprite);
		layer->Add(testLabel);

		for (auto i = 0; i < FALLING_BLOCKS_LIMIT; i++)
		{
			if (nullptr != fallingBlocks[i])
			{
				layer->Add(fallingBlocks[i]);
			}
		}

		gameInitialised = true;

	}

	void Tick() override
	{
		printf("Updates per second: %d. Frames Per Second: %d\n", GetUpdatesPerSecond(), GetFramesPerSecond());
	}

	void Update() override
	{

		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		const auto local_speed = speed * deltaTime;

		// Activate a sprite each second? Or maybe have it as a variable and activate them according to that?
		timerForActivatingBlocks += deltaTime;
		if ( timerForActivatingBlocks > activateBlockDelay)
		{
			timerForActivatingBlocks = 0.f;
			// Chose a block at random.
			activatedFallinBlockIndices.push_back(rand() % FALLING_BLOCKS_LIMIT);
		}

		auto error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		assert("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		PhysicsTick();

		// For each block, prop them down.
		for (auto index: activatedFallinBlockIndices)
		{
			fallingBlocks[index]->position.y -= local_speed;
			if ( fallingBlocks[index]->position.y < -9.f)
			{
				fallingBlocks[index]->position.y = 10.f;
			}
		}

		if ( gameActive)
		{
			
			if (window->IsKeyPressed(GLFW_KEY_UP))
				playerSprite->position.y += local_speed;
			else if (window->IsKeyPressed(GLFW_KEY_DOWN))
				playerSprite->position.y -= local_speed;
			if (window->IsKeyPressed(GLFW_KEY_LEFT))
				playerSprite->position.x -= local_speed;
			else if (window->IsKeyPressed(GLFW_KEY_RIGHT))
				playerSprite->position.x += local_speed;

		}else
		{
			if ( (window->IsKeyPressed(GLFW_KEY_UP)) || (window->IsKeyPressed(GLFW_KEY_DOWN)) )
				selectedLabel *= -1 ;
		}

		if ( selectedLabel == 1 )
		{
			startGame->colour = 0xFFFF;
			endGame->colour = 255;
		}else if ( selectedLabel == -1)
		{
			endGame->colour = 0xFFFFFF;
			startGame->colour = 255;
		}

		double x, y;
		window->GetMousePosition(x, y);
		shader->setVec2("light_pos", math::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));

		error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		assert("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		testLabel->text = std::to_string(time);
	}

	void Render() override
	{
		layer->Render();
		// textLayer->Render();
	}

	void PhysicsTick() override
	{
		// TODO: We need to make sure that the score decreases only once per a falling block.
		for ( auto sprite: fallingBlocks)
		{
			if ( playerSprite->CheckCollision(sprite))
			{
				printf("Touched a block, %p", sprite);
			}
		}
	}

};