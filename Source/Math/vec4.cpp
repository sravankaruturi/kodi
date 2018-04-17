#include "vec4.h"

namespace kodi {

	namespace math {



		vec4::vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		vec4::vec4(const float & _x, const float & _y, const float & _z, const float & _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		vec4 & vec4::add(const vec4 & other)
		{
			// TODO: insert return statement here
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4 & vec4::subtract(const vec4 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		vec4 & vec4::multiply(const vec4 & other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		vec4 & vec4::divide(const vec4 & other)
		{
			// TODO: Check for zero division
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		vec4 vec4::operator+(const vec4 & other)
		{
			return vec4(x + other.x, y + other.y, z + other.z , w + other.w);
		}

		vec4 vec4::operator-(const vec4 & other)
		{
			return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		vec4 vec4::operator*(const vec4 & other)
		{
			return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		vec4 vec4::operator/(const vec4 & other)
		{
			return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		vec4 & vec4::operator+=(const vec4 & other)
		{
			return add(other);
		}

		vec4 & vec4::operator/=(const vec4 & other)
		{
			return divide(other);
		}

		bool vec4::operator==(const vec4 & other)
		{
			return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
		}

		bool vec4::operator!=(const vec4 & other)
		{
			return !(*this == other);
		}

		vec4 & vec4::operator-=(const vec4 & other)
		{
			return subtract(other);
		}

		vec4 & vec4::operator*=(const vec4 & other)
		{
			return multiply(other);
		}


		std::ostream & operator<<(std::ostream& _stream, const vec4 & _vector)
		{
			_stream << "vec4: (" << _vector.x << ", " << _vector.y << 
				", " << _vector.z << ", " << _vector.w << ")";
			return _stream;
		}

	}

}