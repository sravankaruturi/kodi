#include "BatchRenderer2D.h"
#include <assert.h>

namespace kodi {
	namespace graphics {

		BatchRenderer2D::BatchRenderer2D()
		{
			Init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete IBO;
			// delete VBO;
			glDeleteBuffers(1, &VBO);
			glDeleteVertexArrays(1, &VAO);
		}

		void BatchRenderer2D::Submit(const Renderable2D * _renderable)
		{

			const vec3& position	= _renderable->GetPosition();
			const vec2& size		= _renderable->GetSize();
			const vec4& colour		= _renderable->GetColour();

			// First Vertex.
			buffer->vertex	= position;
			buffer->colour = colour;
			buffer++;

			// Rendava Chukka
			buffer->vertex = vec3(position.x, position.y + size.y, position.z);
			buffer->colour = colour;
			buffer++;

			// Moodava Chukka
			buffer->vertex = vec3(position.x + size.x, position.y + size.y, position.z);
			buffer->colour = colour;
			buffer++;

			// Naalugava Chukka
			buffer->vertex = vec3(position.x + size.x, position.y, position.z);
			buffer->colour = colour;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::Begin()
		{
			// Ikkada manam buffer ID tho memory addressuni thechhukoni writeonly tho read access theesesthe ekkuva framerate vasthundhi.
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		}

		void BatchRenderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::Flush()
		{
			glBindVertexArray(VAO);

			IBO->Bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);


			IBO->UnBind();
			glBindVertexArray(0);

			indexCount = 0;

		}

		void BatchRenderer2D::Init()
		{

			indexCount = 0;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);

			// glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 * sizeof(GLfloat), GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 , GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
			// glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(3 * sizeof(GLfloat)));
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(3 * sizeof(GLfloat)));

			// Binding inkaa Unbinidng chaala ekkuva performance hits isthaayi.
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint * indices = new GLuint[RENRERER_INDICES_SIZE];

			for (int i = 0, offset = 0; i < RENRERER_INDICES_SIZE; i+=6 , offset += 4) {

				indices[	i] = offset	+ 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

			}

			IBO = new IndexBuffer(indices, RENRERER_INDICES_SIZE);

			glBindVertexArray(0);

		}

	}
}
