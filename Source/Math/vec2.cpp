#include "vec2.h"

namespace kodi {

	namespace math {



		vec2::vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		vec2::vec2(const float & _x, const float & _y)
		{
			x = _x;
			y = _y;
		}

		vec2 & vec2::add(const vec2 & other)
		{
			// TODO: insert return statement here
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2 & vec2::subtract(const vec2 & other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2 & vec2::multiply(const vec2 & other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2 & vec2::divide(const vec2 & other)
		{
			// TODO: Check for zero division
			x /= other.x;
			y /= other.y;

			return *this;
		}

		vec2 vec2::operator+(const vec2 & other)
		{
			return vec2(x + other.x, y + other.y);
		}

		vec2 vec2::operator-(const vec2 & other)
		{
			return vec2(x - other.x, y - other.y);
		}

		vec2 vec2::operator*(const vec2 & other)
		{
			return vec2(x * other.x, y * other.y);
		}

		vec2 vec2::operator/(const vec2 & other)
		{
			return vec2(x / other.x, y / other.y);
		}

		vec2 & vec2::operator+=(const vec2 & other)
		{
			return add(other);
		}

		vec2 & vec2::operator/=(const vec2 & other)
		{
			return divide(other);
		}

		bool vec2::operator==(const vec2 & other)
		{
			return ((x == other.x) && (y == other.y));
		}

		bool vec2::operator!=(const vec2 & other)
		{
			return !(*this == other);
		}

		vec2 & vec2::operator-=(const vec2 & other)
		{
			return subtract(other);
		}

		vec2 & vec2::operator*=(const vec2 & other)
		{
			return multiply(other);
		}


		std::ostream & operator<<(std::ostream& _stream, const vec2 & _vector)
		{
			_stream << "vec2: (" << _vector.x << ", " << _vector.y << ")";
			return _stream;
		}

	}

}