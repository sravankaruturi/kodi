#pragma once
#include <iostream>

namespace kodi {
	namespace math {

		struct vec2 {

			float x, y;

			vec2();
			vec2(const float& _x,const float& _y);

			vec2& add(const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divide(const vec2& other);

			vec2 operator+(const vec2& other);
			vec2 operator-(const vec2& other);
			vec2 operator*(const vec2& other);
			vec2 operator/(const vec2& other);

			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			bool operator==(const vec2& other);
			bool operator!=(const vec2& other);

			// Friend ikkadavasaram ledhu kaani uththine pettaamu
			friend std::ostream& operator <<(std::ostream& _stream, const vec2& _vector);
			
		};

		


	}
}