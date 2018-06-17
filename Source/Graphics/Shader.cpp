#include "Shader.h"
#include <vector>
#include <iostream>

namespace kodi {
	namespace graphics {

		Shader::Shader(const char * _vertPath, const char * _fragPath)
			: vertPath(_vertPath), fragPath(_fragPath)
		{

			shaderID = Load();

		}

		Shader::~Shader()
		{
			glDeleteProgram(shaderID);
		}

		void Shader::Enable()
		{
			auto error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			glUseProgram(this->shaderID);

			error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

		}

		void Shader::Disable()
		{
			glUseProgram(0);
		}

		GLuint Shader::Load()
		{

			this->shaderID = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertString = utils::FileUtils::readFile(vertPath);
			std::string fragString = utils::FileUtils::readFile(fragPath);

			const char * vertSource = vertString.c_str();
			const char * fragSource = fragString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (GL_FALSE == result) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile Vertex Shader : " << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
			}

#ifdef KODI_THROW_EXCEPTIONS
			// Error Variable choodu
			_ASSERT(GL_FALSE != result);
#endif

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (GL_FALSE == result) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile Fragment Shader : " << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
			}

#ifdef KODI_THROW_EXCEPTIONS
			// Error Variable choodu
			_ASSERT(GL_FALSE != result);
#endif

			glAttachShader(shaderID, vertex);
			glAttachShader(shaderID, fragment);

			// TODO: Ikkada oka assert pettochchu. choodu.
			glLinkProgram(shaderID);
			glValidateProgram(shaderID);

			auto error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error : " << error << std::endl;
			}

#if KODI_THROW_EXCEPTIONS
			_ASSERT("An error occured in OpenGL Calls Somewhere.", error == GL_NO_ERROR);
#endif

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return shaderID;
		}
	}
}