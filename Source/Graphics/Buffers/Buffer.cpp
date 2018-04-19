#include "Buffer.h"
#include <stdio.h>

namespace kodi {
	namespace graphics {

		Buffer::Buffer(GLfloat * _data, GLsizei _count, GLuint _componentCount)
			: componentCount(_componentCount)
		{

			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ARRAY_BUFFER, _count * sizeof(GLfloat), _data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &bufferID);
		}

		GLuint Buffer::GetBufferID() const
		{
			return this->bufferID;
		}

		GLuint Buffer::GetComponentCount() const
		{
			return this->componentCount;
		}

		void Buffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		}

		void Buffer::UnBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}
}