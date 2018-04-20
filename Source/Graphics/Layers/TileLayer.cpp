#include "TileLayer.h"

namespace kodi
{
	namespace graphics
	{
		TileLayer::TileLayer(Shader* _shader)
			: Layer(new BatchRenderer2D(), _shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{

		}

		TileLayer::~TileLayer()
		= default;
	}
}


