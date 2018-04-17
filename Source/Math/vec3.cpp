#include "vec3.h"

namespace kodi {

	namespace math {



		vec3::vec3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		vec3::vec3(const float & _x, const float & _y, const float & _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		vec3 & vec3::add(const vec3 & other)
		{
			// TODO: insert return statement here
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3 & vec3::subtract(const vec3 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3 & vec3::multiply(const vec3 & other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3 & vec3::divide(const vec3 & other)
		{
			// TODO: Check for zero division
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3 vec3::operator+(const vec3 & other)
		{
			return vec3(x + other.x, y + other.y, z+other.z);
		}

		vec3 vec3::operator-(const vec3 & other)
		{
			return vec3(x - other.x, y - other.y, z - other.z);
		}

		vec3 vec3::operator*(const vec3 & other)
		{
			return vec3(x * other.x, y * other.y, z * other.z);
		}

		vec3 vec3::operator/(const vec3 & other)
		{
			return vec3(x / other.x, y / other.y, z/other.z);
		}

		vec3 & vec3::operator+=(const vec3 & other)
		{
			return add(other);
		}

		vec3 & vec3::operator/=(const vec3 & other)
		{
			return divide(other);
		}

		bool vec3::operator==(const vec3 & other)
		{
			return ((x == other.x) && (y == other.y) && (z == other.z));
		}

		bool vec3::operator!=(const vec3 & other)
		{
			return !(*this == other);
		}

		vec3 & vec3::operator-=(const vec3 & other)
		{
			return subtract(other);
		}

		vec3 & vec3::operator*=(const vec3 & other)
		{
			return multiply(other);
		}


		std::ostream & operator<<(std::ostream& _stream, const vec3 & _vector)
		{
			_stream << "vec3: (" << _vector.x << ", " << _vector.y << ", " << _vector.z << ")";
			return _stream;
		}

	}

}