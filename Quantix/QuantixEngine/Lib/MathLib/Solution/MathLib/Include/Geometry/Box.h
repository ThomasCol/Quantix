#ifndef __BOX_H__
#define __BOX_H__

#include "Vec3.h"

namespace Math::Geometry
{
	/**
	 * @brief Class for Box Object
	 */
	class QXbox
	{
	private:

	#pragma region Attributes

		QXvec3	_position;
		QXvec3	_halfSizes;

	#pragma endregion

	public:

	#pragma region Constructors

		/**
		 * @brief Construct a new QXbox object
		 * 
		 * @param position Value for _position parameter QXvec3(0) by default
		 * @param x Value for _halfSizes.x parameter 1 by default
		 * @param y Value for _halfSizes.y parameter 1 by default
		 * @param z Value for _halfSizes.z parameter 1 by default
		 */
		QXbox(const QXvec3& position = QXvec3(0), const QXfloat& x = 1.f,
					const QXfloat & y = 1.f, const QXfloat & z = 1.f) noexcept;

		/**
		 * @brief Construct a new QXbox object
		 * 
		 * @param position Value for _position
		 * @param sizes Value for _halfSizes
		 */
		QXbox(const QXvec3& position, const QXvec3& sizes) noexcept;

		/**
		 * @brief Construct a new QXbox object
		 * 
		 * @param QXbox Box to copy
		 */
		QXbox(const QXbox& QXbox) noexcept;

		/**
		 * @brief Construct a new QXbox object
		 * 
		 * @param QXbox Box to move
		 */
		QXbox(QXbox&& QXbox) noexcept;

		/**
		 * @brief Destroy the QXbox object
		 */
		~QXbox() = default;

	#pragma endregion

	#pragma region Functions


	#pragma region Operators

		/**
		 * @brief Operator = by copy
		 * 
		 * @param box Box to copy
		 * @return QXbox& Reference of the current bow
		 */
		QXbox&			operator=(const QXbox& box) noexcept;

		/**
		 * @brief Operator = by move
		 * 
		 * @param box Box to move
		 * @return QXbox& Reference of the current box
		 */
		QXbox& 			operator=(QXbox&& box) noexcept;

	#pragma endregion Operators

	#pragma region Statics Functions
	#pragma endregion Statics Functions

	#pragma region Accessors

		/**
		 * @brief Get the Position object
		 * 
		 * @return const QXvec3 
		 */
		inline const QXvec3	GetPosition() const noexcept {return _position;}

		/**
		 * @brief Set the Position object
		 * 
		 * @return QXvec3& 
		 */
		inline QXvec3&		SetPosition() noexcept {return _position;}
		
		/**
		 * @brief Get the Half Sizes object
		 * 
		 * @return const QXvec3 
		 */
		inline const QXvec3	GetHalfSizes() const noexcept {return _halfSizes;}
		
		/**
		 * @brief Set the Half Sizes object
		 * 
		 * @return QXvec3& 
		 */
		inline QXvec3&		SetHalfSizes() noexcept {return _halfSizes;}

	#pragma endregion Accessors

	#pragma endregion Functions
	};
}


#endif
