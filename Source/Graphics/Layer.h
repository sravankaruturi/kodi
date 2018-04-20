#pragma once

#include "Renderable2D.h"
#include "Renderer2D.h"

namespace kodi
{
	namespace graphics
	{
		
		class Layer
		{

		protected:

			Renderer2D * renderer2D;
			std::vector<Renderable2D *> renderables;

			Shader * shader;
			mat4 projectionMatrix;

		protected:

			Layer(Renderer2D* _renderer, Shader * _shader, mat4 _projectionMatrix);

		public:

			virtual ~Layer();
			virtual void Add(Renderable2D * _renderable);
			virtual void Render();

			inline uint32_t GetSpriteCount() const { return renderables.size(); };

		};

	}
}


