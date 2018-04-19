#pragma once

#include "Renderer2D.h"

namespace kodi {
	namespace graphics {

		// Ikkada manam anni 2D Renderablesoo Rectanglesani anukuntaamu andhukani indices sizelo 6 * max sprites anee buffer size lo 4 * vertexsize * max sprites anee pettukontaamu.

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENRERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX			0
#define SHADER_COLOUR_INDEX			1

		class BatchRenderer2D : public Renderer2D {

		private:

			GLuint			VAO;
			GLuint			VBO;
			IndexBuffer*	IBO;

			GLsizei	indexCount;
			
			VertexData * buffer;

		public:

			BatchRenderer2D();
			~BatchRenderer2D();

			void Submit(const Renderable2D* _renderable) override;

			void Begin();
			void End();

			void Flush() override;

		private:

			void Init();

		};

	}
}