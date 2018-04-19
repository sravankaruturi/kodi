#pragma once
#include <GL/glew.h>

namespace kodi {
	namespace graphics {

		class IndexBuffer {

		private:
			GLuint bufferID;
			GLuint indexCount;

		public:

			IndexBuffer(GLuint * _data, GLsizei _count);
			~IndexBuffer();

			GLuint GetBufferID() const;
			GLuint GetIndexCount() const;

			void IndexBuffer::Bind() const;
			void IndexBuffer::UnBind() const;

		};

	}
}