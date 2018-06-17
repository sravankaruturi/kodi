#pragma once

#include "../Renderables/Renderable2D.h"
#include "../Renderers/Renderer2D.h"

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

		public:

			virtual ~Layer();
			virtual void Add(Renderable2D * _renderable);
			virtual void Render();

			Layer(Renderer2D* _renderer, Shader * _shader, mat4 _projectionMatrix);

			inline uint32_t GetSpriteCount() const { return renderables.size(); };

			std::vector<Renderable2D *> GetRenderables() { return renderables; };

			void ClearRenderables();

		};

	}
}


