#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace kodi {

	namespace graphics {

#define	MAX_KEYS		1024
#define MAX_BUTTONS		16 

		class Window {

		private:

			const char * title;
			int width, height;

			GLFWwindow * window;

			bool keys[MAX_KEYS];
			bool mouseButtons[MAX_BUTTONS];
			double mouseX, mouseY;

		public:
			Window(const char * _title, int _width, int _height);
			~Window();

			void Update();

			bool IsClosed() const;

			inline int GetWidth() { 
				glfwGetFramebufferSize(window, &width, &height); 
				return width; }

			inline int GetHeight() {
				glfwGetFramebufferSize(window, &width, &height);
				return height;
			}

			bool isKeyPressed(unsigned int _keyCode) const; 
			bool isMouseButtonPressed(unsigned int _button) const;
			void GetMousePosition(double& x, double& y) const;

			void clear() const;

		private:
			bool Init();

			static friend void key_callback(GLFWwindow * _window, int key, int scancode, int action, int mods);

			static friend void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods);

			static friend void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos);
		};

	}

}
