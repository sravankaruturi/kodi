#pragma once
#include "../Source/Kodi.h"
#include "../Source/Graphics/Layers/Menu.h"

namespace kodi
{

	using namespace graphics;

	class Metagame : public Kodi
	{

	public:

		Window * window;

		Layer * selectionLayer{};
		Menu * selectionMenu;

		Shader * selectionShader;

		float deltaTime, time;

		bool isAGameActive = false;

		Kodi * currentGame;

		Metagame();
		void Init() override;
		void StartGame() override;
		void Tick() override;
		void Update() override;
		void Render() override;
		void PhysicsTick() override;
		void ResetGame() override;
		~Metagame() override;

	};

}


