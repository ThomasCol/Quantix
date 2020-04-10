#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Core/Type.h"
#include "Core/DLLHeader.h"

#define RGB_CHANNEL 3
#define RGBA_CHANNEL 4

namespace Quantix::Resources
{
	class QUANTIX_API Texture
	{
	private:
#pragma region Attributes

		QXbyte*	_image;
		QXuint	_id;

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
		~Texture();

#pragma endregion

#pragma region Functions

	/**
	 * @brief Load a texture
	 * 
	 * @param file Path to the texture file
	 */
	void Load(const QXchar* file);

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