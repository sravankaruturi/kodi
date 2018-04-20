#pragma once
#include <sstream>

namespace kodi
{
	namespace utils
	{
		
	class GeneralUtils
	{
	public:

		/* https://stackoverflow.com/questions/10676364/fps-counter-in-the-window-title-glfw */
		template<class T>
		static std::string ToString(T _t)
		{
			std::ostringstream oss;
			oss << _t;
			return oss.str();
		}
	};

	}
}

