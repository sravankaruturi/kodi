#include "Shader.h"
#include <vector>
#include <assert.h>
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
			glUseProgram(this->shaderID);
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

#if _DEBUG
			// Error Variable choodu
			assert(GL_FALSE != result);
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

#if _DEBUG
			// Error Variable choodu
			assert(GL_FALSE != result);
#endif

			glAttachShader(shaderID, vertex);
			glAttachShader(shaderID, fragment);

			// TODO: Ikkada oka assert pettochchu. choodu.
			glLinkProgram(shaderID);
			glValidateProgram(shaderID);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return shaderID;
		}
	}
}