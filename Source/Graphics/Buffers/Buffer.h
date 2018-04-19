#pragma once
#include <GL/glew.h>

namespace kodi {
	namespace graphics {

		class Buffer {

		private:
			GLuint bufferID;
			GLuint componentCount;	// Manaki vec3 vundhaa, lekapother vec4 vundhaa ani bufferki theliyataaniki.

		public:

			Buffer(GLfloat * _data, GLsizei _count, GLuint _componentCount);
			~Buffer();

			GLuint GetBufferID() const;
			GLuint GetComponentCount() const;

			void Bind();

			void UnBind();

		};

	}
}