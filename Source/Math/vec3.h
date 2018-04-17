#pragma once
#include <iostream>

namespace kodi {
	namespace math {

		struct vec3 {

			float x, y, z;

			vec3();
			vec3(const float& _x,const float& _y, const float& _z);

			vec3& add(const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& multiply(const vec3& other);
			vec3& divide(const vec3& other);

			vec3 operator+(const vec3& other);
			vec3 operator-(const vec3& other);
			vec3 operator*(const vec3& other);
			vec3 operator/(const vec3& other);

			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);

			bool operator==(const vec3& other);
			bool operator!=(const vec3& other);

			// Friend ikkadavasaram ledhu kaani uththine pettaamu
			friend std::ostream& operator <<(std::ostream& _stream, const vec3& _vector);
			
		};

		


	}
}