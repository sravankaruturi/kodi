#include "StaticSprite.h"


namespace kodi {
	namespace graphics {

		StaticSprite::StaticSprite(float _x, float _y, float _width, float _height, const math::vec4 & _colour, Shader * _shader)
			: Renderable2D(vec3(_x, _y, 0), vec2(_width, _height), _colour), shader(_shader)
		{

			vertexArray = new VertexArray();

			GLfloat vertices[] = {
				0,			0,			0,
				0,			size.y,		0,
				size.x,		size.y,		0,
				size.x,		0,			0,
			};

			GLfloat colours[] = {
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w
			};

			GLfloat texcoord[] = {
				0, 0,
				0, 1,
				1, 1,
				1, 0
			};

			vertexBuffer = new Buffer(vertices, 12, 3);
			colourBuffer = new Buffer(colours, 16, 4);
			auto texCoordBuffer = new Buffer(texcoord, 8, 2);

			vertexArray->AddBuffer(vertexBuffer, 0);
			vertexArray->AddBuffer(colourBuffer, 1);
			vertexArray->AddBuffer(texCoordBuffer, 2);

			// Anni renderable2deeloo oke shapelo vuntaayi.
			GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

			indexBuffer = new IndexBuffer(indices, 6);

		}

		StaticSprite::~StaticSprite()
		{
			delete vertexArray;
			delete indexBuffer;

			delete vertexBuffer;
			delete colourBuffer;

		}

	}
}