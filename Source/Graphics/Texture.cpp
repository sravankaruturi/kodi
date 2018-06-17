#include "Texture.h"
#include <cassert>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kodi
{
	namespace graphics
	{
		Texture::Texture(std::string _fileName)
			: fileName(std::move(_fileName))
		{

			textureID = Load();

		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &textureID);
		}

		GLuint Texture::Load()
		{
			int nr_channels;
			stbi_set_flip_vertically_on_load(true);

			const auto data = stbi_load(fileName.c_str(), &width, &height, &nr_channels, 0);

#if KODI_THROW_EXCEPTIONS
			_ASSERT("Texture cannot be loaded.", NULL != data);
#endif

			glGenTextures(1, &textureID);

			glBindTexture(GL_TEXTURE_2D, textureID);

			switch (nr_channels)
			{
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			default:
#if KODI_THROW_EXCEPTIONS
				_ASSERT("Unknown Channel" + nr_channels);
#endif
				break;
			}

			glGenerateMipmap(GL_TEXTURE_2D);

			UnBind();
			stbi_image_free(data);

			return textureID;

		}

		/**
		 * \brief 
		 * ee textureni bind cheyyi.
		 */
		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		// This can be static. But we dont do that.
		/**
		 * \brief 
		 * This is used to Unbind the texture. This can be a static method because. it doesn't matter what we are trying to unbind.
		 */
		void Texture::UnBind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}
