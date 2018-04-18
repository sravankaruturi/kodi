#pragma once
#include <GL/glew.h>

namespace kodi {
	namespace graphics {

		class IndexBuffer {

		private:
			GLuint bufferID;
			GLuint indexCount;

		public:

			IndexBuffer(GLushort * _data, GLsizei _count);

			GLuint GetBufferID() const;
			GLuint GetIndexCount() const;

			void IndexBuffer::Bind();
			void IndexBuffer::UnBind();

		};

	}
}