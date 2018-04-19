#include "IndexBuffer.h"

namespace kodi {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLuint * _data, GLsizei _count)
			: indexCount(_count)
		{

			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GLuint), _data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &bufferID);
		}

		GLuint IndexBuffer::GetBufferID() const
		{
			return this->bufferID;
		}

		GLuint IndexBuffer::GetIndexCount() const
		{
			return this->indexCount;
		}

		void IndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		}

		void IndexBuffer::UnBind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}