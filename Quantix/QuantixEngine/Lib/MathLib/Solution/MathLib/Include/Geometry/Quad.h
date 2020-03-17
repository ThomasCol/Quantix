#ifndef __QUAD_H__
#define __QUAD_H__

#include "Ref3.h"
#include "Vec2.h"

namespace Math::Geometry
{
	class QXquad
	{
	private:
		#pragma region Attributes

		QXref3 		_ref;
		QXvec2		_halfSizes;

		#pragma endregion Attributes

	public:

		#pragma region Constructors

		/**
		 * @brief Construct a new QXquad object
		 * 
		 * @param position Value for _ref.o parameter QXvec3(0) by default
		 * @param i Value for _ref.i parameter right by default
		 * @param j Value for _ref.j parameter up by default
		 * @param k Value for _ref.k parameter forward by default
		 * @param x Value for _halfSizes.x parameter 1 by default
		 * @param y Value for _halfSizes.y parameter 1 by default
		 */
		QXquad(const QXvec3& position = QXvec3(0), const QXvec3& i = QXvec3(1, 0, 0),
				const QXvec3& j = QXvec3(0, 1, 0), const QXvec3& k = QXvec3(0, 0, 1),
				const QXfloat& x = 1.f, const QXfloat & y = 1.f) noexcept;

		/**
		 * @brief Construct a new QXquad object
		 * 
		 * @param ref Value for _ref
		 * @param halfSizes Value for _halfSizes
		 */
		QXquad(const QXref3& ref, const QXvec2& halfSizes) noexcept;

		/**
		 * @brief Construct a new QXquad object
		 * 
		 * @param quad Quad to copy
		 */
		QXquad(const QXquad& quad) noexcept;

		/**
		 * @brief Construct a new QXquad object
		 * 
		 * @param quad Quad to move
		 */
		QXquad(QXquad&& quad) noexcept;

		/**
		 * @brief Destroy the QXquad object
		 */
		~QXquad() = default;

		#pragma endregion Contructors

		#pragma region Functions

		#pragma region Operators

		/**
		 * @brief Operator = by copy
		 * 
		 * @param quad Quad to copy
		 * @return QXquad& Reference of the new quad
		 */
		QXquad&			operator=(const QXquad& quad) noexcept;

		/**
		 * @brief Operator = by move
		 * 
		 * @param quad Quad to move
		 * @return QXquad& Reference of the new quad
		 */
		QXquad&			operator=(QXquad&& quad) noexcept;

		#pragma endregion Operators

		#pragma region Accessors

		/**
		 * @brief Get the Ref object
		 * 
		 * @return QXref3 
		 */
		inline QXref3	GetRef() const noexcept {return _ref;}

		/**
		 * @brief Set the Ref object
		 * 
		 * @return QXref3& 
		 */
		inline QXref3&	SetRef() noexcept {return _ref;}

		/**
		 * @brief Get the Half Sizes object
		 * 
		 * @return QXvec2 
		 */
		inline QXvec2	GetHalfSizes() const noexcept {return _halfSizes;}

		/**
		 * @brief Set the Half Sizes object
		 * 
		 * @return QXvec2& 
		 */
		inline QXvec2&	SetHalfSizes() noexcept {return _halfSizes;}
		

		#pragma endregion Accessors

		#pragma endregion Functions
	};
}


#endif
