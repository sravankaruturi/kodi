#pragma once

#include "Renderable2D.h"

namespace kodi {
	namespace graphics {

		class Sprite : public Renderable2D {

		private:

		public:
			Sprite(float _x, float _y, float _width, float _height, const vec4& _colour);

		};

	}
}