#pragma once

#include "Renderer2D.h"
#include "../Buffers/IndexBuffer.h"
#include "../Renderables/Renderable2D.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

namespace kodi {
	namespace graphics {

		// Ikkada manam anni 2D Renderablesoo Rectanglesani anukuntaamu andhukani indices sizelo 6 * max sprites anee buffer size lo 4 * vertexsize * max sprites anee pettukontaamu.

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENRERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6

#define RENDERER_MAX_TEXTURES		32

#define SHADER_VERTEX_INDEX			0
#define SHADER_COLOUR_INDEX			1
#define SHADER_TEXCOORD_INDEX		2
#define SHADER_TEXID_INDEX			3

		/// Holds all state information relevant to a character as loaded using FreeType
		struct Character {
			GLuint texture_id;   // ID handle of the glyph texture
			math::vec2 size;    // Size of glyph
			math::vec2 bearing;  // Offset from baseline to left/top of glyph
			GLuint advance;    // Horizontal offset to advance to next glyph
		};

		class BatchRenderer2D : public Renderer2D {

		private:

			GLuint			VAO;
			GLuint			VBO;
			IndexBuffer*	IBO;

			GLsizei	indexCount;
			
			VertexData * buffer;

			std::vector<GLuint> textureSlots;

			std::map<GLchar, Character> characters;

			FT_Library ft;
			FT_Face textFace;

		public:

			BatchRenderer2D();
			~BatchRenderer2D();

			void Submit(const Renderable2D* _renderable) override;

			void Begin();
			void End();

			void DrawString(const std::string& _text, const float _x, const float _y, const unsigned& _colour, const float _scale) override;

			void Flush() override;

		private:

			void Init();

		};

	}
}
