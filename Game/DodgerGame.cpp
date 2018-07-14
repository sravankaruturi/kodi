#include "../Source/Kodi.h"
#include "../Source/Graphics/Renderers/BatchRenderer2D.h"
#include "../Source/Graphics/Label.h"
#include "../Source/Graphics/Layers/Menu.h"
#include <chrono>
#include "../Source/Utils/newOverride.h"

using namespace kodi;
using namespace graphics;

class DodgerGame : public Kodi
{
	
private:

#define FALLING_BLOCKS_LIMIT	32

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
	float playerSpeed = 7.f;
	float speed = 5.f;

	int health = 100;

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

	DodgerGame(Window * _window)
	{

		this->window = _window;
		_ASSERT(nullptr != window);

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

		startGameMenu = DBG_NEW Menu(test, vec2(-4.1f, 0.5f), 0xFFFF11, 1);

		scoreLabel = DBG_NEW Label(std::to_string(health), -15.5f, 8.0f, 0xFFFFFF);

		gameOverLabel = DBG_NEW Label("Game Over Press Enter to restart", -6.0f, -0.5f, 0xFFFFFF);

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
		shader = DBG_NEW Shader(
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.vert",
			"C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Source/Shaders/batchTexture.frag");

		menuLayer = DBG_NEW Layer(DBG_NEW BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		gameLayer = DBG_NEW Layer(DBG_NEW BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		gameOverLayer = DBG_NEW Layer(DBG_NEW BatchRenderer2D(), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		fallingBlockTexture = DBG_NEW Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Fallin-Down-Enemy.png");

		// They are just above the visible screen space.
		for(auto i = 0 ; i < FALLING_BLOCKS_LIMIT ; i++)
		{
			fallingBlocks[i] = (DBG_NEW Sprite(-15 + i * 1.5, 10, 1, 1, fallingBlockTexture));
		}

		playerSprite = DBG_NEW Sprite(0, 0, 1, 1, DBG_NEW Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Dodger/Falling-Down-Player.png"));

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

		auto local_speed = speed * deltaTime;
		auto player_local_speed = playerSpeed * deltaTime;

		playerSpeed += deltaTime;

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
			{
				if (playerSprite->position.y < 9.0f)
					playerSprite->position.y += player_local_speed;
			}				
			else if (window->IsKeyPressed(GLFW_KEY_DOWN))
			{
				if (playerSprite->position.y > -9.0f)
					playerSprite->position.y -= player_local_speed;
			}

			if (window->IsKeyPressed(GLFW_KEY_LEFT))
			{
				if (playerSprite->position.x > -16.0f)
					playerSprite->position.x -= player_local_speed;
			}				
			else if (window->IsKeyPressed(GLFW_KEY_RIGHT))
			{
				if (playerSprite->position.x < 16.0f)
					playerSprite->position.x += player_local_speed;
			}
				

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
					ResetGame();
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

	void ResetGame() override
	{
		gameLayer->ClearRenderables();
		this->Init();
		gameOver = false;
		gameInitialised = false;
		health = 100;
		// fallingBlocks.clear();
		activatedFallinBlockIndices.clear();
		this->scoreLabel->text = std::to_string(health);
	}

};