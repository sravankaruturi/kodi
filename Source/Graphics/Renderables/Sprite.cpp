#pragma once

#include "Sprite.h"

namespace kodi {
	namespace graphics {
		Sprite::Sprite(float _x, float _y, float _width, float _height, const vec4& _colour)
			: Renderable2D(vec3(_x, _y, 0), vec2(_width, _height), _colour)
		{
		}

		Sprite::Sprite(float _x, float _y, float _width, float _height, Texture * _texture)
			: Renderable2D(vec3(_x, _y, 0), vec2(_width, _height), 0xffffffff, _texture)
		{
		}
	}
}