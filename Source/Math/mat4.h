#pragma once

#include "vec3.h"
#include "vec4.h"

namespace kodi {
	namespace math {

		// Idhi Column Major matrix.
		// OpenGL kooda idhe vaaduthundhi.
		/*
		0	4	8	12
		1	5	9	13
		2	6	10	14
		3	7	11	15

		Element X = Row + Col * 4;

		*/

		struct mat4 {

			// Idhi Column major kaabatti pani chesthundhi. Leka pothe ilaapanicheyyadhu appudumanam rows pettukovaalikkada.
			union {
				float elements[16];
				vec4 columns[4];
			};
			

			mat4();
			mat4(float diagonal);

			mat4& multiply(const mat4& _other);


			static mat4 identity();

			// Operatorlu
			mat4 operator * (const mat4& _other) const;
			vec4 operator * (const vec4& _other) const;
			vec3 operator * (const vec3& _other) const;

			mat4& operator *= (const mat4& _other);

			//mat4 operator ==(const mat4& _other);
			//mat4 operator + (const mat4& _other);

			// Projection matrixlu
			static mat4 orthographic(float _left, float _right, float _bottom, float _top,  float _near, float _far);
			static mat4 perspective(float _fov, float _aspectRation, float _near, float _far);

			static mat4 translation(const vec3& _translation);
			static mat4 rotation(float _angle, const vec3& _axis);
			static mat4 scale(const vec3& _scale);


		};

	}
}