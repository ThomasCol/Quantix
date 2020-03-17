#ifndef _VEC4_H_
#define _VEC4_H_

#include <iostream>
#include <string>

#include "Vec3.h"

#include "Type.h"

namespace Math
{
	struct QXvec4
	{
#pragma region Attributes

		union
		{
			struct { QXfloat x, y, z, w; };
			struct { QXfloat r, g, b, a; };
			QXfloat e[4];
		};

		static const QXvec4	zero;
		static const QXvec4	up;
		static const QXvec4	down;
		static const QXvec4	left;
		static const QXvec4	right;
		static const QXvec4	forward;
		static const QXvec4	backward;

#pragma endregion Attributes

#pragma region Constructors

		/**
		 * @brief Construct a new QXvec4 object
		 * 
		 * @param posX Value for x parameter by default
		 * @param posY Value for y parameter by default
		 * @param posZ Value for z parameter by default
		 * @param posW Value for w parameter by default
		 */
		QXvec4(const QXfloat& posX = 0.f , const QXfloat& posY = 0.f, const QXfloat& posZ = 0.f, const QXfloat& posW = 0.f) noexcept;

		/**
		 * @brief Construct a new QXvec4 object
		 * 
		 * @param vec Vector for xyz
		 * @param posW Value for w parameter
		 */
		QXvec4(const QXvec3& vec, QXfloat posW) noexcept;

		/**
		 * @brief Construct a new QXvec4 object
		 * 
		 * @param vec Vector to copy
		 */
		QXvec4(const QXvec4& vec) noexcept;

		/**
		 * @brief Construct a new QXvec4 object
		 * 
		 * @param vec Vector to move
		 */
		QXvec4(QXvec4&& vec) noexcept;

		/**
		 * @brief Destroy the QXvec4 object
		 */
		~QXvec4() = default;

#pragma endregion Constructors

#pragma region Functions

		/**
		 * @brief Homogenize current vector
		 */
		void 		Homogenize() noexcept;

		/**
		 * @brief Length (magnitude) of current vector
		 * 
		 * @return QXfloat Length value
		 */
		QXfloat		Length() const noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4&		Normalize() noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec4 Vector normalized
		 */
		QXvec4		Normalize() const noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4&		Scale(QXfloat nb) noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec4& Scaled vector
		 */
		QXvec4		Scale(QXfloat nb) const noexcept;

		/**
		 * @brief Square length of current vector
		 * 
		 * @return QXfloat Square length value
		 */
		QXfloat		SqrLength() const noexcept;

		/**
		 * @brief Make a string with vector values
		 * 
		 * @return QXstring String with vector
		 */
		QXstring	ToString() const noexcept;

#pragma region Operators

		/* Copy and move operator */

		/**
		 * @brief Operator = by copy
		 *
		 * @param vec Vector to copy
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator=(const QXvec4& vec) noexcept;

		/**
		 * @brief Operator = by move
		 *
		 * @param vec Vector to move
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator=(QXvec4&& vec) noexcept;

		/* Mathematics operators */

		/**
		 * @brief Operator for vector addition
		 *
		 * @param vect Vector to Add
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator+=(const QXvec4& vect) noexcept;

		/**
		 * @brief Operator for addition
		 *
		 * @param vect Vector to add
		 * @return QXvec4 New vector
		 */
		QXvec4		operator+(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator for Vector Substraction
		 *
		 * @param vect Vector to Substract
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator-=(const QXvec4& vect) noexcept;

		/**
		 * @brief Operator for substraction
		 *
		 * @param vect Vector to substract
		 * @return QXvec4 New vector
		 */
		QXvec4		operator-(const QXvec4& vect) const noexcept;

		/**
		 * @brief Create a new QXvec4 as the opposite of the vector
		 *
		 * @return QXvec4 New vector
		 */
		QXvec4		operator-() const noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator/=(QXfloat value) noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec4 New vector
		 */
		QXvec4		operator/(QXfloat value) const noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to multiply
		 * @return QXvec4& Reference of current vector
		 */
		QXvec4& operator*=(QXfloat value) noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to multiply
		 * @return QXvec4 New vector
		 */
		QXvec4		operator*(QXfloat value) const noexcept;

		/**
		 * @brief Operator to compare length
		 *
		 * @param vect Vector to compare
		 * @return true Vectors have same length
		 * @return false Vectors have different length
		 */
		QXbool		operator==(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vectors have different length
		 * @return false Vectors have same length
		 */
		QXbool		operator!=(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is strictly inferior to compared vector
		 * @return false Vector length is superior or equal to compared vector
		 */
		QXbool		operator<(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is inferior or equal to compared vector
		 * @return false Vector length is strictly superior to compared vector
		 */
		QXbool		operator<=(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is strictly superior to compared vector
		 * @return false Vector length is inferior or equal to compared vector
		 */
		QXbool		operator>(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is superior or equal to compared vector
		 * @return false Vector length is strictly inferior to compared vector
		 */
		QXbool		operator>=(const QXvec4& vect) const noexcept;

		/**
		 * @brief Operator to access vector values as an array
		 *
		 * @param idx Index of the array
		 * @return QXfloat& Reference of the vector value
		 */
		QXfloat& operator[](QXuint idx) noexcept;

		/**
		 * @brief Operator to access vector values as an array
		 *
		 * @param idx Index of the array
		 * @return const QXfloat of the vector value
		 */
		const QXfloat	operator[](QXuint idx) const noexcept;


#pragma endregion Operators

#pragma endregion Functions
	};

	/**
	 * @brief Operator to print vector
	 * 
	 * @param stream Stream to add the vector
	 * @param vector Vector to add to the stream
	 * @return std::ostream& Reference to the stream
	 */
	std::ostream&	operator<<(std::ostream& os, const QXvec4& vect) noexcept;

	/**
	 * @brief Operator to add a print of vector in string
	 *
	 * @param string string to add the vector
	 * @param vector Vector to add to the stream
	 * @return QXstring New string
	 */
	QXstring		operator+(std::string& str, const QXvec4& vect) noexcept;
}

#endif //_VEC4_H_
