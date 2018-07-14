#include "Menu.h"
#include <GLFW/glfw3.h>
#include "../Source/Utils/newOverride.h"

namespace kodi
{
	namespace graphics
	{
		Menu::Menu(std::vector<std::string> _menuItems, vec2 _position, unsigned int _colour, bool _isActive)
		{

			this->transformationMatrix = mat4::translation(vec3(_position.x, _position.y, 1));

			defaultColour = _colour;

			// TODO: Fix the spacing and positioning issues.


			auto error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			auto i = 0;
			for (const auto& menu_item : _menuItems)
			{
				// TODO: Why is this a thing?? We need to be able to specify that it as zero and do it.
				auto temp_label = DBG_NEW Label(menu_item, _position.x, i--, _colour);

				this->labels.push_back(temp_label);
				this->renderables.push_back(temp_label);

			}

			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			selectorTexture = DBG_NEW Texture("C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/Assets/Textures/selector.png");


			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			selector = DBG_NEW Sprite(_position.x - 1, this->labels[selectedIndex]->position.y + 0.25, 0.5, 0.5, selectorTexture);
			this->renderables.push_back(selector);

		}

		Menu::~Menu()
		{
			// Groups deletion is handled in Groups destructor. Once you add the renderable to the group, it gets deleted that way.
			delete selectorTexture;
		}

		void Menu::MenuDown()
		{
			if (glfwGetTime() - timeAtLastSelection > timerDelayForMenuSelection)
			{
				selectedIndex += 1;

				if (selectedIndex > labels.size() - 1)
				{
					(selectedIndex -= (labels.size()));
				}

				for (auto temp : labels)
				{
					temp->colour = defaultColour;
				}

				this->selector->position.y = this->labels[selectedIndex]->position.y + 0.25;

				timeAtLastSelection = glfwGetTime();
			}
		}

		void Menu::MenuUp()
		{

			if ( glfwGetTime() - timeAtLastSelection > timerDelayForMenuSelection)
			{
				
				selectedIndex -= 1;

				if (selectedIndex < 0)
				{
					selectedIndex += labels.size();
				}

				for (auto temp : labels)
				{
					temp->colour = defaultColour;
				}

				this->selector->position.y = this->labels[selectedIndex]->position.y + 0.25;

				timeAtLastSelection = glfwGetTime();

			}
			
		}
	}
}
