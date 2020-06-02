#include "Resources/Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include "Core/Debugger/Logger.h"

namespace Quantix::Resources
{
#pragma region Constructors

	Texture::~Texture() noexcept
	{
		if (_image)
		{
			stbi_image_free(_image);
			_image = nullptr;
		}
		if (_HDRImage)
		{
			stbi_image_free(_HDRImage);
			_HDRImage = nullptr;
		}
	}

#pragma endregion

#pragma region Functions

	void Texture::Load(const QXstring& file) noexcept
	{
		/* load image */
		_image = stbi_load(file.c_str(), &_width, &_height, &_channel, 0);

		if (_image == nullptr)
		{
			LOG(ERROR, "failed to load texture :\n" + file);
			_status.store(EResourceStatus::FAILED);

			return;
		}

		_status.store(EResourceStatus::LOADED);
	}

	void Texture::Init() noexcept
	{
		if (!_image && !_HDRImage)
		{
			_status.store(EResourceStatus::FAILED);
			return;
		}

		if (_HDRImage)
		{
			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_2D, _id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, _width, _height, 0, GL_RGB, GL_FLOAT, _HDRImage);

			/* set parameter */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			_status.store(EResourceStatus::READY);

			return;
		}
		
		glGenTextures(1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);

		if (_channel == RGB_CHANNEL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
		else if (_channel == RGBA_CHANNEL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);

		/* set parameter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		_status.store(EResourceStatus::READY);
	}

	void Texture::LoadHDRTexture(const QXstring& file) noexcept
	{
		stbi_set_flip_vertically_on_load(true);
		/* load image */
		_HDRImage = stbi_loadf(file.c_str(), &_width, &_height, &_channel, 0);

		if (_HDRImage == nullptr)
		{
			LOG(ERROR, "failed to load texture:  " + file);
			_status.store(EResourceStatus::FAILED);
			return;
		}

		_status.store(EResourceStatus::LOADED);
	}

#pragma endregion
}
