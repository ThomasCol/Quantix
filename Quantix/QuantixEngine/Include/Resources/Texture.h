#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <Type.h>
#include "Core/DLLHeader.h"
#include "Resource.h"

#define RGB_CHANNEL 3
#define RGBA_CHANNEL 4
#define DEFAULTTEXTURESPATH "media/Textures/"

namespace Quantix::Resources
{
	class QUANTIX_API Texture : public Resource
	{
	private:
#pragma region Attributes

		QXfloat*	_HDRImage;
		QXbyte*		_image;
		QXuint		_id;

		QXint		_width { 0 };
		QXint		_height { 0 };
		QXint		_channel { 0 };

#pragma endregion

	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Texture object
		 */
		Texture() = default;

		/**
		 * @brief Construct a new Texture object
		 * 
		 * @param texture Texture to copy
		 */
		Texture(const Texture& texture) = default;

		/**
		 * @brief Construct a new Texture object
		 * 
		 * @param texture Texture to move
		 */
		Texture(Texture&& texture) = default;

		/**
		 * @brief Destroy the Texture object
		 */
		~Texture() noexcept;

#pragma endregion

#pragma region Functions

	/**
	 * @brief Load a texture
	 * 
	 * @param file Path to the texture file
	 */
	void Load(const QXstring& file) noexcept override;

	/**
	 * @brief Init the texture
	 * 
	 */
	void Init() noexcept override;

	/**
	 * @brief Load an HDR texture
	 * 
	 * @param file path to the HDR texture file
	 */
	void LoadHDRTexture(const QXstring& file) noexcept;

#pragma region Accessor

	/**
	 * @brief Get texture ID
	 * 
	 * @return QXuint ID value
	 */
	inline QXuint GetId() const noexcept { return _id; }

#pragma endregion

#pragma endregion
	};
}

#endif // __TEXTURE_H__