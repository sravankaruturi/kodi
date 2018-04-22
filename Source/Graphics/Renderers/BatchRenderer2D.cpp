#include "BatchRenderer2D.h"
#include <assert.h>

#include "../Renderables/Sprite.h"

namespace kodi {
	namespace graphics {

		const vec2& bottom_left = vec2(0, 0);
		const vec2& bottom_right = vec2(1, 0);
		const vec2& top_left = vec2(0, 1);
		const vec2& top_right = vec2(1, 1);

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

			const GLuint tid = _renderable->GetTexID();

			unsigned int c = 0;
			float tslot = 0.0f;
			if ( tid > 0)
			{
				bool found = false;
				for (int i = 0; i < textureSlots.size(); i++)
				{
					if ( tid == textureSlots[i] )
					{
						tslot = (float)i + 1;
						found = true;
						break;
					}
				}

				if (!found)
				{
					if ( textureSlots.size() >= 32)
					{
						End();
						Flush();
						Begin();
					}

					// Ikkada else pettakapothe paruvaaleidhaa?

					textureSlots.push_back(tid);
					tslot = float(textureSlots.size());
				}

			}else
			{
				auto r = int(colour.x * 255);
				auto g = int(colour.y * 255);
				auto b = int(colour.z * 255);
				auto a = int(colour.w * 255);

				c = a << 24 | b << 16 | g << 8 | r;
			}
			
			// First Vertex.
			buffer->vertex	= *transformationStackBack * position;
			buffer->colour = c;
			buffer->texCoord = bottom_left;
			buffer->tSlot = tslot;
			buffer++;

			// Rendava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x, position.y + size.y, position.z);
			buffer->colour = c;
			buffer->texCoord = top_left;
			buffer->tSlot = tslot;
			buffer++;

			// Moodava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x, position.y + size.y, position.z);
			buffer->colour = c;
			buffer->texCoord = top_right;
			buffer->tSlot = tslot;
			buffer++;

			// Naalugava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x, position.y, position.z);
			buffer->colour = c;
			buffer->texCoord = bottom_right;
			buffer->tSlot = tslot;
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

			for ( int i = 0 ; i < textureSlots.size(); i++)
			{
				// Definitionlo GL_TEXTURE0 tharuvaatha annee varusaga vunnayi.
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
			}

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
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);

			// glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 * sizeof(GLfloat), GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 , GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::colour));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tSlot));

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
