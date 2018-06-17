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
			auto colour		= _renderable->GetColour();

			const GLuint tid = _renderable->GetTexID();

			
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
					if ( textureSlots.size() >= RENDERER_MAX_TEXTURES)
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
				
			}

#if 0

			// First Vertex.
			buffer->vertex	= *transformationStackBack * position;
			buffer->colour = colour;
			buffer->texCoord = bottom_left;
			buffer->tSlot = tslot;
			buffer++;

			// Rendava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x, position.y + size.y, position.z);
			buffer->colour = colour;
			buffer->texCoord = top_left;
			buffer->tSlot = tslot;
			buffer++;

			// Moodava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x, position.y + size.y, position.z);
			buffer->colour = colour;
			buffer->texCoord = top_right;
			buffer->tSlot = tslot;
			buffer++;

			// Naalugava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x, position.y, position.z);
			buffer->colour = colour;
			buffer->texCoord = bottom_right;
			buffer->tSlot = tslot;
			buffer++;

#else
			// First Vertex.
			buffer->vertex = *transformationStackBack * vec3(position.x - size.x/2, position.y - size.y/2, position.z);
			buffer->colour = colour;
			buffer->texCoord = bottom_left;
			buffer->tSlot = tslot;
			buffer->useColour = 0.0f;
			buffer++;

			// Rendava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x - size.x/2, position.y + size.y/2, position.z);
			buffer->colour = colour;
			buffer->texCoord = top_left;
			buffer->tSlot = tslot;
			buffer->useColour = 0.0f;
			buffer++;

			// Moodava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x/2, position.y + size.y/2, position.z);
			buffer->colour = colour;
			buffer->texCoord = top_right;
			buffer->tSlot = tslot;
			buffer->useColour = 0.0f;
			buffer++;

			// Naalugava Chukka
			buffer->vertex = *transformationStackBack * vec3(position.x + size.x/2, position.y - size.y/2, position.z);
			buffer->colour = colour;
			buffer->texCoord = bottom_right;
			buffer->tSlot = tslot;
			buffer->useColour = 0.f;
			buffer++;

#endif

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

		void BatchRenderer2D::DrawString(const std::string& _text, float _x, float _y, const unsigned& _colour, const float _scale)
		{
			
			// We go through each character. We create a renderable 2D for each of it.
			// We then submit that using the texture for now to check.

			std::string::const_iterator c;
			for (c = _text.begin() ; c!= _text.end() ; c++)
			{
				
				Character ch = characters[*c];

				auto xpos = _x + ch.bearing.x * _scale;
				auto ypos = _y - (ch.size.y - ch.bearing.y) * _scale;

				auto w = ch.size.x * _scale;
				auto h = ch.size.y * _scale;

				const auto tid = ch.texture_id;

				float tslot = 0.0f;
				if (tid > 0)
				{
					auto found = false;
					for (auto i = 0; i < textureSlots.size(); i++)
					{
						if (tid == textureSlots[i])
						{
							tslot = (float)i + 1;
							found = true;
							break;
						}
					}

					if (!found)
					{
						if (textureSlots.size() >= RENDERER_MAX_TEXTURES)
						{
							End();
							Flush();
							Begin();
						}

						// Ikkada else pettakapothe paruvaaleidhaa?

						textureSlots.push_back(tid);
						tslot = float(textureSlots.size());
					}

				}
				else
				{
					_ASSERT("Wutface?");
				}

				// First Vertex.
				buffer->vertex = *transformationStackBack * vec3(xpos, ypos + h, 1);
				buffer->colour = _colour;
				buffer->texCoord = bottom_left;
				buffer->tSlot = tslot;
				buffer->useColour = 0.0;
				buffer++;

				// Rendava Chukka
				buffer->vertex = *transformationStackBack * vec3(xpos, ypos, 1);
				buffer->colour = _colour;
				buffer->texCoord = top_left;
				buffer->tSlot = tslot;
				buffer->useColour = 0.0;
				buffer++;

				// Moodava Chukka
				buffer->vertex = *transformationStackBack * vec3(xpos + w, ypos, 1);
				buffer->colour = _colour;
				buffer->texCoord = top_right;
				buffer->tSlot = tslot;
				buffer->useColour = 0.0;
				buffer++;

				// Naalugava Chukka
				buffer->vertex = *transformationStackBack * vec3(xpos + w, ypos + h, 1);
				buffer->colour = _colour;
				buffer->texCoord = bottom_right;
				buffer->tSlot = tslot;
				buffer->useColour = 0.0;
				buffer++;

				indexCount += 6;

				_x += (ch.advance >> 6) * _scale;

			}

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
			textureSlots.clear();

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
			glEnableVertexAttribArray(SHADER_USE_COLOUR_INDEX);

			// glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 * sizeof(GLfloat), GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3 , GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::colour));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tSlot));
			glVertexAttribPointer(SHADER_USE_COLOUR_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::useColour));

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

			/*Font Stuff*/
#ifdef KODI_THROW_EXCEPTIONS
			_ASSERT(0 == FT_Init_FreeType(&ft));
			_ASSERT(0 == (FT_New_Face(ft, "C:/Users/Sravan Karuturi/Documents/Work/Kodi-CrossPlatform/Kodi/fonts/arial.ttf", 0,
				&textFace)));
#endif

			FT_Set_Pixel_Sizes(textFace, 0, 48);

			// We disable the byte-alignment restriction.. For some reason? --> Since the default packing for textures is 4 bytes. We change it to 1 for text rendering for obvious reasons..
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// Load the first 128 Characters of the ASCII set??
			// This is an extremely stupid way to do it as it means that you would need one texture for each character which kind of messes up the whole 
			// spirit of a batch renderer if we call flush it with every line of text.
			for ( GLubyte c = 0 ; c < 128 ; c++)
			{
				if ( FT_Load_Char(textFace, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYPE::Failed to load Glyph at " << c << std::endl;
					continue;
				}

				GLuint temp_texture;
				glGenTextures(1, &temp_texture);
				glBindTexture(GL_TEXTURE_2D, temp_texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					textFace->glyph->bitmap.width,
					textFace->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					textFace->glyph->bitmap.buffer
				);

				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Now store character for later use
				Character character = {
					temp_texture,
					math::vec2(textFace->glyph->bitmap.width, textFace->glyph->bitmap.rows),
					math::vec2(textFace->glyph->bitmap_left, textFace->glyph->bitmap_top),
					textFace->glyph->advance.x
				};

				characters.insert(std::pair<GLchar, Character>(c, character));

			}

			glBindTexture(GL_TEXTURE_2D, 0);
			FT_Done_Face(textFace);
			FT_Done_FreeType(ft);

		}

	}
}
