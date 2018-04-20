#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace kodi
{
	namespace graphics
	{
#define	MAX_KEYS		1024
#define MAX_BUTTONS		16

		class Window
		{
		private:

			/* Timing Variables Ikkada peduthunnanu. FPS glfwlo calculate chedhdhaamu */
			double lastTime;
			double currentTime;
			char * fps;
			std::string fpsString = "";
			double numberOfFrames;
			/*Timing Variables Ikkadatho ayyipoyaayi*/

			std::string title;
			int width, height;

			GLFWwindow* window{};

			bool keys[MAX_KEYS]{};
			bool mouseButtons[MAX_BUTTONS]{};
			double mouseX{}, mouseY{};

		public:
			Window(const char* _title, int _width, int _height);
			~Window();

			void Update();

			bool IsClosed() const;

			inline int GetWidth()
			{
				glfwGetFramebufferSize(window, &width, &height);
				return width;
			}

			inline int GetHeight()
			{
				glfwGetFramebufferSize(window, &width, &height);
				return height;
			}

			bool IsKeyPressed(unsigned int _keyCode) const;
			bool IsMouseButtonPressed(unsigned int _button) const;
			void GetMousePosition(double& x, double& y) const;

			static void Clear();

		private:
			bool Init();

			static friend void key_callback(GLFWwindow* _window, int _key, int scancode, int action, int mods);

			static friend void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods);

			static friend void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos);
		};
	}
}
