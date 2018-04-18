#include "IndexBuffer.h"

namespace kodi {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLushort * _data, GLsizei _count)
			: indexCount(_count)
		{

			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GLushort), _data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		}

		GLuint IndexBuffer::GetBufferID() const
		{
			return this->bufferID;
		}

		GLuint IndexBuffer::GetIndexCount() const
		{
			return this->indexCount;
		}

		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		}

		void IndexBuffer::UnBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}