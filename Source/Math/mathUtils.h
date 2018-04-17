#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace kodi {
	namespace math {

		float toRadians(float _degrees) {

			return _degrees * ((float)M_PI / 180.0f);
		}

	}
}
