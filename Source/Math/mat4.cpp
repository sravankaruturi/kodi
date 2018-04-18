#include "mat4.h"
#include "mathUtils.h"

namespace kodi {
	namespace math {



		mat4::mat4()
		{
			// Ikkada memset vaadochchu.
			for (int i = 0; i < 16; i++) {
				elements[i] = 0;
			}
		}

		mat4::mat4(float diagonal)
		{
			// Idhi release mode lo optimise ayyipothundhi. manamemee cheyyanavasaram ledhu
			for (int i = 0; i < 16; i++) {
				elements[i] = 0.0f;
			}
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 & mat4::multiply(const mat4 & _other)
		{
			// Manamu mana matrixni vere matrixtho multiply chesi mana matrixlone pedathaamu.
			*this = *this * _other;
			return *this;
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		// Rendu matrixla multiplication ikkada chesthaamu.
		mat4 mat4::operator*(const mat4 & _other)
		{
			mat4 returnMatrix;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {

					float sum = 0.0f;
					for (int k = 0; k < 4; k++) {
						sum += (elements[j + 4 * k] * _other.elements[k + i * 4]);
					}
					returnMatrix.elements[j + 4 * i] = sum;

				}
			}

			return returnMatrix;
		}

		mat4& mat4::operator*=(const mat4 & _other)
		{
			*this = *this * _other;
			return *this;
		}

		mat4 mat4::orthographic(float _left, float _right, float _bottom, float _top, float _near, float _far)
		{
			// Orthographic matrixki formula. kavalante okasaari internetlo choodu.
			/*
			2/(r-l)		0			0			(r+l)/(l-r)
			0			2/(t-b)		0			(t+b)/(b-t)
			0			0			-2/(f-n)	(f+n)/(f-n)
			0			0			0			1
			*/
			mat4 returnMatrix(1.0f);

			//					Row		Col
			returnMatrix.elements[0 + 0 * 4] = 2.0f / (_right - _left);
			returnMatrix.elements[1 + 1 * 4] = 2.0f / (_top - _bottom);
			returnMatrix.elements[2 + 2 * 4] = -2.0f / (_far - _near);

			returnMatrix.elements[0 + 3 * 4] = (_right + _left)/ (_left - _right);
			returnMatrix.elements[1 + 3 * 4] = (_top + _bottom) / (_bottom - _top);
			returnMatrix.elements[2 + 3 * 4] = (_far + _near) / (_far - _near);
			returnMatrix.elements[3 + 3 * 4] = 1.0f;

			return returnMatrix;
		}

		mat4 mat4::perspective(float _fov, float _aspectRation, float _near, float _far)
		{
			/*

			TODO: Ikkada perspective formula vethiki pettu.

			*/

			mat4 returnMatrix;

			float q = 1.0f / tan(toRadians(0.5f * _fov));
			float a = q / _aspectRation;

			float b = (_near + _far) / (_near - _far);
			float c = (2.0f * _near * _far) / (_near - _far);

			returnMatrix.elements[0 + 0 * 4] = a;
			returnMatrix.elements[1 + 1 * 4] = q;
			returnMatrix.elements[2 + 2 * 4] = b;
			returnMatrix.elements[3 + 2 * 4] = -1.0f;
			returnMatrix.elements[2 + 3 * 4] = c;

			return returnMatrix;
		}

		mat4 mat4::translation(const vec3 & _translation)
		{
			mat4 returnMatrix(1.0f);

			returnMatrix.elements[0 + 3 * 4] = _translation.x;
			returnMatrix.elements[1 + 3 * 4] = _translation.y;
			returnMatrix.elements[2 + 3 * 4] = _translation.z;

			return returnMatrix;
		}

		// We rotate about an axis.
		mat4 mat4::rotation(float _angle, const vec3 & _axis)
		{
			mat4 returnMatrix(1.0f);

			float r = toRadians(_angle);
			float c = cos(r);
			float s = sin(r);

			returnMatrix.elements[0 + 0 * 4] = _axis.x * (1.0f - c) + c ;
			returnMatrix.elements[1 + 0 * 4] = _axis.y * _axis.x * (1.0f - c) + _axis.z * s;
			returnMatrix.elements[2 + 0 * 4] = _axis.x * _axis.z * (1.0f - c) - _axis.y * s;;

			returnMatrix.elements[0 + 1 * 4] = _axis.x * _axis.y * (1.0f - c) - _axis.z * s;
			returnMatrix.elements[1 + 1 * 4] = _axis.y * (1.0f - c) + c;
			returnMatrix.elements[2 + 1 * 4] = _axis.y * _axis.z * (1.0f - c) + _axis.z * s;

			returnMatrix.elements[0 + 2 * 4] = _axis.x * _axis.z * (1.0f - c) + _axis.y * s;
			returnMatrix.elements[1 + 2 * 4] = _axis.y * _axis.z * (1.0f - c) - _axis.x * s;
			returnMatrix.elements[2 + 2 * 4] = _axis.z * (1.0f - c) +c;

			return returnMatrix;
		}

		mat4 mat4::scale(const vec3 & _scale)
		{
			mat4 returnMatrix(1.0f);

			returnMatrix.elements[0 + 0 * 4] = _scale.x;
			returnMatrix.elements[1 + 1 * 4] = _scale.y;
			returnMatrix.elements[2 + 2 * 4] = _scale.z;

			return returnMatrix;
		}

	}
}