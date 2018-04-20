#pragma once

#include <GL/glew.h>
#include <string>

namespace kodi
{
	namespace graphics
	{
		
		class Texture
		{

		private:

			GLuint textureID;
			std::string fileName;

			int width{}, height{};

		public:

			Texture(std::string _fileName);
			~Texture();

			void Bind() const;
			void UnBind() const;

			inline unsigned int getWidth() const{
				return width;
			}

			inline unsigned int getHeight() const {
				return height;
			}

			inline const GLuint getTextureID() const { return textureID; }

		private:
			GLuint Load();

		};


	}
}

