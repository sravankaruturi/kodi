#include "../Source/Kodi.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"
#include "../Source/Graphics/Label.h"
#include "../Source/Graphics/Layers/Menu.h"
#include <chrono>


using namespace kodi;
using namespace graphics;

class DodgerGame : public Kodi
{
	
private:

#define FALLING_BLOCKS_LIMIT	32

	Window * window;

	/* Layers */
	Layer * menuLayer;
	Layer * gameLayer;
	Layer * gameOverLayer;

	Texture * fallingBlockTexture;
	std::vector<Sprite *> fallingBlocks;
	Sprite * playerSprite;
	Label * scoreLabel;
	Label * gameOverLabel;

	Shader * shader;
	std::vector<int> activatedFallinBlockIndices;
	float deltaTime;
	float time;
	/*Activate a block each second or the time specified here in seconds*/
	float activateBlockDelay = 1.f;
	float timerForActivatingBlocks = 0.f;
	const float speed = 5.f;

	int health = 100;

	/**
	 * \brief Manam e Label Select chesukunnamo manaki gurthu vundataaniki.
	 */
	int selectedLabel = 1; // 1 if Start Game and -1 if Quit.

	/**
	 * \brief This would be activated once the player hits Start Game.
	 */
	bool gameActive = false;
	bool gameInitialised = false;
	bool gameOver = false;

	Menu * startGameMenu;

	float physicsTimer = 0.0f;
	float physicsTickTime = 1.0 / 30.0f;

public:

	DodgerGame()
	{

		window = createWindow("Test DodgerGame", 800, 600);

		fallingBlocks.resize(2 * FALLING_BLOCKS_LIMIT);
		time = glfwGetTime();

		auto error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error : " << error << std::endl;
		}

#if KODI_THROW_EXCEPTIONS
		_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		std::vector<std::string> test = { "Start Game", "Quit" };

		startGameMenu = new Menu(test, vec2(-4.1f, 0.5f), 0xFFFF11, 1);

		scoreLabel = new Label(std::to_string(health), -15.5f, 8.0f, 0xFFFFFF);

		gameOverLabel = new Label("Game Over Press Enter to restart", -6.0f, -0.5f, 0xFFFFFF);

	};

	~DodgerGame()
	{
		delete menuLayer;
		delete gameLayer;
		delete gameOverLayer;
		// The Layer deletes it??
		// delete startGameMenu;
	}

	void Init() override
	{
				
		// TODO : Ikkada Shader map thayaaru chesukoni pettuko.
		shader = new Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag");

		menuLayer = new Layer(new BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		gameLayer = new Layer(new BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		gameOverLayer = new Layer(new BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		fallingBlockTexture = new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Fallin-Down-Enemy.png");

		// They are just above the visible screen space.
		for(auto i = 0 ; i < FALLING_BLOCKS_LIMIT ; i++)
		{
			fallingBlocks[i] = (new Sprite(-15 + i * 1.5, 10, 1, 1, fallingBlockTexture));
		}

		playerSprite = new Sprite(0, 0, 1, 1, new Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Falling-Down-Player.png"));

		menuLayer->Add(startGameMenu);

		gameLayer->Add(scoreLabel);

		gameOverLayer->Add(gameOverLabel);

	}

	void StartGame() override
	{
		/*Manam mundhu pettinavi venukaala kanipisthaayi.*/
		gameLayer->Add(playerSprite);

		for (auto i = 0; i < FALLING_BLOCKS_LIMIT; i++)
		{
			if (nullptr != fallingBlocks[i])
			{
				gameLayer->Add(fallingBlocks[i]);
			}
		}

		gameInitialised = true;
		gameActive = true;

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

		if ( gameActive)
		{
			
			// Activate a sprite each second? Or maybe have it as a variable and activate them according to that?
			timerForActivatingBlocks += deltaTime;
			if (timerForActivatingBlocks > activateBlockDelay)
			{
				timerForActivatingBlocks = 0.f;
				// Chose a block at random.

				// Seed something random?
				srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
				activatedFallinBlockIndices.push_back(rand() % FALLING_BLOCKS_LIMIT);
			}

			physicsTimer += deltaTime;

			if (physicsTimer > physicsTickTime)
			{
				PhysicsTick();
				physicsTimer = 0.0f;
			}

			// For each block, prop them down.
			for (auto index : activatedFallinBlockIndices)
			{
				fallingBlocks[index]->position.y -= local_speed;
				if (fallingBlocks[index]->position.y < -9.f)
				{
					fallingBlocks[index]->position.y = 10.f;
				}
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

			if (window->IsKeyPressed(GLFW_KEY_UP))
			{
				this->startGameMenu->MenuUp();
			}else if (window->IsKeyPressed(GLFW_KEY_DOWN))
			{
				this->startGameMenu->MenuDown();
			}

			if (window->IsKeyPressed(GLFW_KEY_ENTER))
			{
				if ( !gameInitialised )
				{
					switch (this->startGameMenu->selectedIndex)
					{
					case 0:
						StartGame();
						break;
					case 1:
						this->shouldClose = true;
						break;
					}
				}
				else if ( gameOver)
				{
					// TODO: Create a reset function..
					gameLayer->ClearRenderables();
					this->Init();
					gameOver = false;
					gameInitialised = false;
					health = 100;
					// fallingBlocks.clear();
					activatedFallinBlockIndices.clear();
					this->scoreLabel->text = std::to_string(health);
				}
													
			}
		}

		if ( this->health < 0.0f)
		{
			gameOver = true;
			gameActive = false;
		}

		double x, y;
		window->GetMousePosition(x, y);
		shader->setVec2("light_pos", math::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));

	}

	void Render() override
	{
		if ( !gameInitialised)
		{
			menuLayer->Render();
		}else if ( gameActive)
		{
			gameLayer->Render();
		}else if ( gameOver)
		{
			gameOverLayer->Render();
		}
		// textLayer->Render();
	}

	void PhysicsTick() override
	{
		// TODO: We need to make sure that the score decreases only once per a falling block or maybe once per tick.
		for ( auto sprite: fallingBlocks)
		{
			if ( playerSprite->CheckCollision(sprite))
			{
				printf("Touched a block, %p", sprite);
				health--;
				this->scoreLabel->text = std::to_string(health);
				break;
			}
		}
	}

};