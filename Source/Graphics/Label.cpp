#include "Label.h"

namespace kodi
{
	namespace graphics
	{
		Label::Label(std::string _text, float _x, float _y, unsigned int _colour)
		{
			text = _text;
			position = vec3(_x, _y, 0.0f);
			colour = _colour;
		}

		void Label::SubmitToRenderer(Renderer2D* _renderer) const
		{
			_renderer->DrawString(text, position.x, position.y, colour, 1.0f / 64);
		}
	}
}