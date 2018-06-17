#pragma once
#include "Group.h"
#include "../Label.h"
#include "../Renderables/Sprite.h"

namespace kodi
{
	namespace graphics
	{
		class Menu : public Group
		{

		protected:

			std::vector<Label *> labels;
			bool isActive = false;
			
			unsigned int defaultColour;

			Sprite * selector;

			float timerDelayForMenuSelection = 0.25f;
			float timeAtLastSelection = -1 * timerDelayForMenuSelection;

		public:

			int selectedIndex = 0;

			Menu(std::vector<std::string> _menuItems, vec2 _position, unsigned int _colour, bool _isActive);
			~Menu();

			void MenuDown();
			void MenuUp();
			
		};
	}
}
