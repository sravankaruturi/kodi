#include "Window.h"
#include <iostream>
#include <cassert>
#include "../Utils/GeneralUtils.h"

namespace kodi {
	namespace graphics {

		/**
		 * \brief 
		 * \param _title 
		 * \param _width 
		 * \param _height 
		 */
		Window::Window(const char * _title, const int _width, int _height)
			:  width(_width), height(_height)
		{

			title = std::string(_title);

			if (!Init()) {
				glfwTerminate();
			}

			for (auto& key : keys)
			{
				key = false;
			}

			for (auto& mouse_button : mouseButtons)
			{
				mouse_button = false;
			}

			/*Timing Stuff*/
			numberOfFrames = 0;
			currentTime = 0;
			lastTime = 0;
			/*Timing Stuff Ends*/

		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::IsKeyPressed(const unsigned int _keyCode) const
		{
			// TODO: Log this.
			if (_keyCode >= MAX_KEYS) {
				return false;
			}

			return keys[_keyCode];
		}

		bool Window::IsMouseButtonPressed(unsigned int _button) const
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

			window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

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

			glfwSwapInterval(0);

			// Idhi contex windowki pettina tharuvaathe ikkada pettaali. Eelopoopedithe error vasthundhi.
			if (glewInit() != GLEW_OK) {
				std::cout << "Could not init GLEW" << std::endl;
				return false;
			}

			return true;

		}

		void Window::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update()
		{
			const auto error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			assert(error == GL_NO_ERROR);
#endif

			glfwPollEvents();

			glfwSwapBuffers(window);

			currentTime = glfwGetTime();

			numberOfFrames++;

			if ( currentTime - lastTime >= 1.0)
			{
				fpsString =  std::string("                      FPS: ") + utils::GeneralUtils::ToString<double>(numberOfFrames);
				glfwSetWindowTitle(window, (title + fpsString).c_str());
				numberOfFrames = 0;
				lastTime = currentTime;
			}
			
		}

		bool Window::IsClosed() const
		{
			return glfwWindowShouldClose(window);
		}

		void window_resize(GLFWwindow * _window, int _width, int _height) {

			auto win = static_cast<Window *>(glfwGetWindowUserPointer(_window));

			win->width = win->GetWidth();
			win->height = win->GetHeight();

			glViewport(0, 0, _width, _height);
		}

		void key_callback(GLFWwindow * _window, int _key, int scancode, int action, int mods) {

			auto win = static_cast<Window *>(glfwGetWindowUserPointer(_window));

			win->keys[_key] =  (GLFW_RELEASE != action);
			// win->keys[_key] = (GLFW_RELEASE == action) ? keyBool::keyReleased : (GLFW_PRESS
		}

		void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods) {

			auto * win = (Window *)glfwGetWindowUserPointer(_window);
			
			win->mouseButtons[_button] = (GLFW_RELEASE != _action);

		}

		/**
		 * \brief 
		 * \param _window 
		 * \param _xpos 
		 * \param _ypos 
		 */
		void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos) {

			auto win = static_cast<Window *>(glfwGetWindowUserPointer(_window));

			win->mouseX = _xpos;
			win->mouseY = _ypos;

		}

	}
}