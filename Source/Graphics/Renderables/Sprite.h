#pragma once

#include "Renderable2D.h"
#include "../Texture.h"

namespace kodi {
	namespace graphics {

		class Sprite : public Renderable2D {

		private:

		public:
			Sprite(float _x, float _y, float _width, float _height, const vec4& _colour);
			Sprite(float _x, float _y, float _width, float _height, Texture * _texture);

			GLboolean CheckCollision(Sprite* _other) const
			{
				// TODO: Fix this.
				if (nullptr == _other) return false;
				const auto collision_x = this->position.x + this->size.x >= _other->position.x && _other->position.x + _other->size.x >= this->position.x;
				const auto collision_y = this->position.y + this->size.y >= _other->position.y && _other->position.y + _other->size.y >= this->position.y;

				return collision_x && collision_y;
			}

		};

	}
}