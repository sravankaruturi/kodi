#include "Window.h"
#include <iostream>

namespace kodi {
	namespace graphics {

		void window_resize(GLFWwindow * _window, int width, int height);

		Window::Window(const char * _title, int _width, int _height)
			: title(_title), width(_width), height(_height)
		{

			if (!Init()) {
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++) {
				keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				mouseButtons[i] = false;
			}

		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::isKeyPressed(unsigned int _keyCode) const
		{
			// TODO: Log this.
			if (_keyCode >= MAX_KEYS) {
				return false;
			}

			return keys[_keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int _button) const
		{
			// TODO: Log this.
			if (_button >= MAX_BUTTONS) {
				return false;
			}

			return mouseButtons[_button];
		}

		void Window::GetMousePosition(double & x, double & y) const
		{
			x = mouseX;
			y = mouseY;
		}

		bool Window::Init()
		{

			if (!glfwInit()) {
				std::cout << " Failed to Initialize GLFW" << std::endl;
				return false;
			}

			window = glfwCreateWindow(width, height, title, NULL, NULL);

			if (!window) {
				std::cout << " Failed to Create GLFW window " << std::endl;
				return false;
			}

			glfwMakeContextCurrent(window);

			glfwSetWindowUserPointer(window, this);
			glfwSetKeyCallback(window, key_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwSetWindowSizeCallback(window, window_resize);
			glfwSetCursorPosCallback(window, cursor_position_callback);

			// Idhi contex windowki pettina tharuvaathe ikkada pettaali. Eelopoopedithe error vasthundhi.
			if (glewInit() != GLEW_OK) {
				std::cout << "Could not init GLEW" << std::endl;
				return false;
			}

			return true;

		}

		void Window::Update()
		{
			
			glfwPollEvents();

			glfwSwapBuffers(window);

		}

		bool Window::IsClosed() const
		{
			return glfwWindowShouldClose(window);
		}

		void window_resize(GLFWwindow * _window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow * _window, int key, int scancode, int action, int mods) {

			Window * win = (Window *)glfwGetWindowUserPointer(_window);

			win->keys[key] = (GLFW_RELEASE != action);

		}

		void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods) {

			Window * win = (Window *)glfwGetWindowUserPointer(_window);
			
			win->mouseButtons[_button] = (GLFW_RELEASE != _action);

		}

		void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos) {

			Window * win = (Window *)glfwGetWindowUserPointer(_window);

			win->mouseX = _xpos;
			win->mouseY = _ypos;

		}

	}
}