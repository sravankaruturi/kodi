#pragma once

#include "../Buffers/VertexArray.h"
#include "../Buffers/IndexBuffer.h"

#include "../../Math/Math.h"
#include "../Shader.h"

#include "../Renderers/Renderer2D.h"

using namespace kodi::math;

namespace kodi {
	namespace graphics {

		struct VertexData
		{
			// TODO: Packing. Memory align avvaledhu tharuvaatha optimisatin chesetappudu manam ikkada packing kosam choodu.
			vec3 vertex;
			unsigned int colour;
			vec2 texCoord;
			//vec4 colour;
		};

		class Renderable2D {

		protected:
			vec3 position;
			vec2 size;
			vec4 colour;

		protected:

			Renderable2D(){}

		public:

			Renderable2D(vec3 _position, vec2 _size, vec4 _colour)
				: position(_position), size(_size), colour(_colour)
			{	
			}

			~Renderable2D()
			{
			}

			virtual void SubmitToRenderer(Renderer2D* _renderer) const
			{
				_renderer->Submit(this);
			}


			inline const vec3& GetPosition() const { return position; }
			inline const vec2& GetSize() const { return size; }
			inline const vec4& GetColour() const { return colour; }

		};

	}
}