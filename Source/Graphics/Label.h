#pragma once
#include "Renderables/Renderable2D.h"

namespace kodi
{
	namespace graphics
	{

		class Label : public Renderable2D
		{

		private:


		public:

			std::string text;

			Label(std::string _text, float _x, float _y, unsigned int _colour);

			void SubmitToRenderer(Renderer2D* _renderer) const override;

		};

	}
}
