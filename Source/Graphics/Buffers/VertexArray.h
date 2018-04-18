#pragma once
#include "Buffer.h"
#include <vector>

namespace kodi {
	namespace graphics {

		class VertexArray {

		private:

			GLuint vertexArrayID;

			// Naaku thelisi ikkada manam thappu chesthunnamu. manam prathee bufferroo oka vertex array ki point chesthe baagunthundhi.
			std::vector<Buffer *> buffers;


		public:

			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer * _buffer, GLuint _index);

			void Bind() const;
			void UnBind() const;

		};

	}
}