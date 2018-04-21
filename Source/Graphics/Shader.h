#pragma once

#include "../Utils/fileUtils.h"
#include <GL/glew.h>
#include "../Math/Math.h"
#include <cassert>

namespace kodi {
	namespace graphics {

		class Shader {

		private:
			GLuint shaderID;
			const char * vertPath;
			const char * fragPath;

		public:
			Shader(const char * _vertPath, const char * _fragPath);
			~Shader();

			void Enable();
			void Disable();

			inline GLuint GetShaderID() {
				return this->shaderID;
			};

			// Shaderlalo Uniformlu ikkada vaaduthaamu
			// utility uniform functions
			// Code Ikkada nundi theesaamu https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
			// ------------------------------------------------------------------------
			void setBool(const std::string &name, bool value) const
			{
				glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
			}
			// ------------------------------------------------------------------------
			void setInt(const std::string &name, int value) const
			{
				glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
			}

			void SetIntArray(const std::string& _name, int _count, int* _value) const
			{
				auto l = glGetUniformLocation(shaderID, _name.c_str());
				glUniform1iv(l, _count, _value);
			}

			void SetFloatArray(const std::string& _name, int _count, float* _value) const
			{
				glUniform1fv(glGetUniformLocation(shaderID, _name.c_str()), _count, _value);
			}

			// ------------------------------------------------------------------------
			void setFloat(const std::string &name, float value) const
			{
				glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
			}
			// ------------------------------------------------------------------------
			void setVec2(const std::string &name, const math::vec2 &value) const
			{
				glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
			}
			void setVec2(const std::string &name, float x, float y) const
			{
				glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
			}
			// ------------------------------------------------------------------------
			void setVec3(const std::string &name, const math::vec3 &value) const
			{
				glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
			}
			void setVec3(const std::string &name, float x, float y, float z) const
			{
				glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
			}
			// ------------------------------------------------------------------------
			void setVec4(const std::string &name, const math::vec4 &value) const
			{
				glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
			}
			void setVec4(const std::string &name, float x, float y, float z, float w)
			{
				glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
			}
			//// ------------------------------------------------------------------------
			//void setMat2(const std::string &name, const math::mat2 &mat) const
			//{
			//	glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
			//}
			//// ------------------------------------------------------------------------
			//void setMat3(const std::string &name, const math::mat3 &mat) const
			//{
			//	glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
			//}
			// ------------------------------------------------------------------------
			void setMat4(const std::string &name, const math::mat4 &mat) const
			{
				glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat.elements[0]);
			}


		private:
			GLuint Load();
		};

	}
}
