#include "Renderable2D.h"

kodi::graphics::Renderable2D::Renderable2D(vec3 _position, vec2 _size, vec4 _colour, Shader * _shader)
	: position(_position), size(_size), colour(_colour), shader(_shader)
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

	vertexBuffer = new Buffer(vertices, 12, 3);
	colourBuffer = new Buffer(colours, 16, 4);

	vertexArray->AddBuffer(vertexBuffer, 0);
	vertexArray->AddBuffer(colourBuffer, 1);

	// Anni renderable2deeloo oke shapelo vuntaayi.
	GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

	indexBuffer = new IndexBuffer(indices, 6);

}

kodi::graphics::Renderable2D::~Renderable2D()
{
	delete vertexBuffer;
	delete colourBuffer;

	delete vertexArray;
	delete indexBuffer;
}
