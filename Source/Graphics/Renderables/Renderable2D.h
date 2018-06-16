#pragma once

#include "../Buffers/VertexArray.h"
#include "../Buffers/IndexBuffer.h"

#include "../../Math/Math.h"
#include "../Shader.h"

#include "../Renderers/Renderer2D.h"
#include "../Texture.h"

using namespace kodi::math;

namespace kodi {
	namespace graphics {

		struct VertexData
		{
			// TODO: Packing. Memory align avvaledhu tharuvaatha optimisatin chesetappudu manam ikkada packing kosam choodu.
			vec3 vertex;
			unsigned int colour;
			vec2 texCoord;
			float tSlot;
			float useColour; // This is either 0 or 1. No other value should be passed here.
		};

		class Renderable2D {

		public:
			vec3 position;

			unsigned int colour;

		protected:
			
			vec2 size;
			// GLuint textureID;	// Manaku idhi pointer kanna chinnadhi. Thakkuva space theesukontundhi.
			// Manam ikkada okokka renderable kee oka texture maathrame vuntundhani assume chesukontunnamu.
			Texture * texture;

		protected:

			Renderable2D(){}

		public:

			Renderable2D(vec3 _position, vec2 _size, unsigned int _colour, Texture * _texture = nullptr)
				: position(_position), size(_size), colour(_colour), texture(_texture)
			{	
			}

			Renderable2D(vec3 _position, vec2 _size, vec4 _colour, Texture * _texture = nullptr)
				: position(_position), size(_size), texture(_texture)
			{
				SetColour(_colour);
			}

			void SetColour(vec4 _colour)
			{
				unsigned int c = 0;
				auto r = int(_colour.x * 255);
				auto g = int(_colour.y * 255);
				auto b = int(_colour.z * 255);
				auto a = int(_colour.w * 255);
				c = a << 24 | b << 16 | g << 8 | r;

				this->colour = c;
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
			inline const unsigned int& GetColour() const { return colour; }
			inline const GLuint& GetTexID() const { return (nullptr == texture) ? 0 : texture->getTextureID(); }

		};

	}
}