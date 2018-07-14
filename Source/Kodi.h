#pragma once

#include "Graphics/Window.h"
#include "Utils/Timer.h"
#include "Graphics/Layers/Layer.h"
#include "Graphics/Renderables/Sprite.h"
#include "Utils/newOverride.h"

namespace kodi
{
	
	class Kodi
	{

	private:

		

		utils::Timer * myTimer;

		unsigned int framesPerSecond, updatesPerSecond;

	protected:

		graphics::Window * window;

		bool shouldClose = false;

		Kodi()
			: framesPerSecond(0), updatesPerSecond(0)
		{
			
		}

		graphics::Window * createWindow(const char * _name, int _width, int _height)
		{
			window = DBG_NEW graphics::Window(_name, _width, _height);
			return window;
		}

		unsigned GetFramesPerSecond() const
		{
			return framesPerSecond;
		}

		unsigned GetUpdatesPerSecond() const
		{
			return updatesPerSecond;
		}

		// Initialization appudu maathrame run avuthundhi.
		virtual void Init() = 0;
		// Manaki Game Start Ayyaka okati.
		virtual void StartGame() = 0;
		// Sekanukokkasaari
		virtual void Tick() = 0;
		/*Sekanuki 60 saarlu*/
		virtual void Update() = 0;
		/*Entha vegangaa kudhirithe antha vegangaa vsync lekapothe*/
		virtual void Render() = 0;
		/*Physics Ticks*/
		virtual void PhysicsTick() = 0;
		/*Reset the Game for the next Run*/
		virtual void ResetGame() = 0;



		virtual  ~Kodi()
		{
			delete window;
			delete myTimer;
		}

	public:
		void Start()
		{
			Init();
			Run();
		}

	private:

		void Run()
		{
			myTimer = DBG_NEW utils::Timer();
			auto timer = 0.f;
			auto update_timer = 0.f;
			const auto update_tick = 1.0f / 60.0f;

			unsigned int frames = 0;
			unsigned int updates = 0;

			while(!window->IsClosed())
			{
				graphics::Window::Clear();

				if ( myTimer->ElapsedTime() - update_timer > update_tick)
				{
					Update();
					updates++;
					update_timer += update_tick;
				}

				Render();

				frames++;
				window->Update();

				if ( myTimer->ElapsedTime() - timer > 1000.f)
				{
					timer += 1000.f;
					framesPerSecond = frames;
					updatesPerSecond = updates;
					frames = 0;
					updates = 0;
					Tick();
				}

				if ( window->IsKeyPressed(GLFW_KEY_ESCAPE) || this->shouldClose )
				{
					break;
				}

			}

		}

	};

}
