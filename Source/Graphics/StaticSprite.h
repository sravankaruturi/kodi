#pragma once

#include "Renderable2D.h"

namespace kodi {
	namespace graphics {

		class StaticSprite : public Renderable2D {

		private:

			VertexArray * vertexArray;
			IndexBuffer * indexBuffer;
			Shader& shader;

			Buffer * vertexBuffer;
			Buffer * colourBuffer;

		public:

			StaticSprite(float _x, float _y, float _width, float _height, const math::vec4& _colour, Shader& _shader);
			~StaticSprite();

			inline const VertexArray* GetVAO() const { return vertexArray; }
			inline const IndexBuffer* GetIBO() const { return indexBuffer; }

			inline Shader& GetShader() const { return shader; }

		};

	}
}