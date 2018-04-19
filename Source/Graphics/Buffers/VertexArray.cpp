#include "VertexArray.h"

namespace kodi {
	namespace graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &vertexArrayID);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &vertexArrayID);
		}

		// Ikkada _index manaki shaderlo location tho samaanamu
		void VertexArray::AddBuffer(Buffer * _buffer, GLuint _index)
		{

			Bind();
			_buffer->Bind();

			glEnableVertexAttribArray(_index);

			// Ikkada chaalaa assuptions chesukonnaamu.
			// Type GL_FLOAT vuntundhanee, stride 0 vuntundhanee
			glVertexAttribPointer(_index, _buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, NULL, NULL);

			_buffer->UnBind();
			UnBind();

		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(vertexArrayID);
		}

		void VertexArray::UnBind() const
		{
			glBindVertexArray(0);
		}

	}
}