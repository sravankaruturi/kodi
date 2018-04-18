#pragma once

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"

#include "../Math/Math.h"
#include "Shader.h"

using namespace kodi::math;

namespace kodi {
	namespace graphics {

		class Renderable2D {

		protected:
			vec3 position;
			vec2 size;
			vec4 colour;

			Buffer * vertexBuffer;
			Buffer * colourBuffer;

			VertexArray * vertexArray;
			IndexBuffer * indexBuffer;

			Shader * shader;

		public:

			Renderable2D(vec3 _position, vec2 _size, vec4 _colour, Shader * _shader);
			~Renderable2D();

			inline const vec3& GetPosition() const { return position; }
			inline const vec2& GetSize() const { return size; }
			inline const vec4& GetColour() const { return colour; }

			inline const VertexArray * GetVAO() const { return vertexArray; }
			inline const IndexBuffer * GetIBO() const { return indexBuffer; }

			inline const Buffer * GetVertexBuffer() const { return vertexBuffer; }
			inline const Buffer * GetColourBuffer() const { return colourBuffer; }

			inline Shader * GetShader() const { return shader;  }

		};

	}
}