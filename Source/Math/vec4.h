#pragma once
#include <iostream>

namespace kodi {
	namespace math {

		struct vec4 {

			float x, y, z, w;

			vec4();
			vec4(const float& _x,const float& _y, const float& _z, const float& _w);

			vec4& add(const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);

			vec4 operator+(const vec4& other);
			vec4 operator-(const vec4& other);
			vec4 operator*(const vec4& other);
			vec4 operator/(const vec4& other);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			// Friend ikkadavasaram ledhu kaani uththine pettaamu
			friend std::ostream& operator <<(std::ostream& _stream, const vec4& _vector);
			
		};

		


	}
}