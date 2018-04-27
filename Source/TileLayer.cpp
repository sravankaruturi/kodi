#include "TileLayer.h"
#include <cassert>

	TileLayer::TileLayer(kodi::graphics::Shader* _shader)
		: Layer(new kodi::graphics::BatchRenderer2D(), _shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
	{
//			GLint * tex_ids = new GLint[32];
//			for (auto i = 0; i < 32; i++) { tex_ids[i] = i; }
//
//			auto error = glGetError();
//
//			if (error != GL_NO_ERROR) {
//				std::cout << "OpenGL Error : " << error << std::endl;
//			}
//
//#ifdef KODI_THROW_EXCEPTIONS
//			assert(error == GL_NO_ERROR);
//#endif
//
//			_shader->SetIntArray("textures", 32, tex_ids);
//
	}

	TileLayer::~TileLayer()
	= default;