#include "Resources/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

#include "Core/Debugger/Logger.h"

namespace Quantix::Resources
{
#pragma region Constructors

	Texture::~Texture()
	{
		LOG(WARNING, "here");
		if (_image)
		{
			stbi_image_free(_image);
			_image = nullptr;
		}
	}

#pragma endregion

#pragma region Functions

	void Texture::Load(const QXchar* file) noexcept
	{
		glGenTextures(1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);

		int	width, height, channel = 0;

		stbi_set_flip_vertically_on_load(true);

		/* load image */
		_image = stbi_load(file, &width, &height, &channel, 0);

		if (_image == nullptr)
			return;

		if (channel == RGB_CHANNEL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
		else if (channel == RGBA_CHANNEL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);

		/* set parameter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture::LoadHDRTexture(const QXstring& file) noexcept
	{
		int	width, height, channel = 0;

		stbi_set_flip_vertically_on_load(true);
		/* load image */
		_skyImage = stbi_loadf(file.c_str(), &width, &height, &channel, 0);

		if (_skyImage == nullptr)
		{
			LOG(ERROR, "failed to load texture :\n" + file);
			return;
		}

		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, _skyImage);

		/* set parameter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

#pragma endregion
}
