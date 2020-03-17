#ifndef __VEC3_H__
#define __VEC3_H__

#include <ostream>

#include "Type.h"

namespace Math
{
	struct QXref3;
	struct QXmat4;

	/**
	 * @brief Vector3 structure
	 * 
	 */
	struct QXvec3
	{
#pragma region Attributes

		union
		{
			struct { QXfloat x, y, z; };
			struct { QXfloat r, g, b; };
			QXfloat	e[3];
		};

		static const QXvec3 zero;
		static const QXvec3 up;
		static const QXvec3 down;
		static const QXvec3 right;
		static const QXvec3 left;
		static const QXvec3 forward;
		static const QXvec3 backward;
		static const QXvec3 infinity;

#pragma endregion Attributes

#pragma region Constructors

		/**
		 * @brief Construct a new QXvec3 object
		 * 
		 * @param x Value for x parameter 0 by default
		 * @param y Value for y parameter 0 by default
		 * @param z Value for z parameter 0 by default
		 */
		QXvec3(const QXfloat& x = 0.f, const QXfloat & y = 0.f, const QXfloat & z = 0.f) noexcept;
		
		/**
		 * @brief Construct a new QXvec3 object
		 * 
		 * @param vector Vector to copy
		 */
		QXvec3(const QXvec3& vector) noexcept;

		/**
		 * @brief Construct a new QXvec3 object
		 * 
		 * @param vector Vector to move
		 */
		QXvec3(QXvec3&& vector) noexcept;

		/**
		 * @brief Destroy the QXvec3 object
		 */
		~QXvec3() = default;

#pragma endregion Constructors

#pragma region Functions

		/**
		 * @brief Compute Angle between two vectors
		 * 
		 * @param vector Destination vector 
		 * @return QXfloat Angle value in radian
		 */
		QXfloat			Angle(const QXvec3& vector) const noexcept;

		/**
		 * @brief Cross product between two vectors
		 * 
		 * @param vector Vector to compute cross product
		 * @return QXvec3 Vector result of the cross product
		 */
		QXvec3			Cross(const QXvec3& vector) const noexcept;

		/**
		 * @brief Dot product between two vectors
		 * 
		 * @param vector Vector to compute dot product
		 * @return QXfloat Result of the dot product
		 */
		QXfloat			Dot(const QXvec3& vector) const noexcept;

		/**
		 * @brief Check if two vectors are collinear
		 * 
		 * @param vector Vector to check collinearity
		 * @return true Vectors are collinear
		 * @return false Vectors are not collinear
		 */
		QXbool			IsCollinear(const QXvec3& vector) const noexcept;

		/**
		 * @brief Length (magnitude) of current vector
		 * 
		 * @return QXfloat Length value
		 */
		QXfloat			Length() const noexcept;

		QXvec3			WorldToLocal(const QXref3& ref) const noexcept;
		QXvec3			LocalToWorld(const QXref3& ref) const noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3&			Normalize() noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec3 Vector normalized
		 */
		const QXvec3	Normalized() const noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3&			Scale(QXfloat value) noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec3& Scaled vector
		 */
		QXvec3			Scale(QXfloat value) const noexcept;

		/**
		 * @brief Square length of current vector
		 * 
		 * @return QXfloat Square length value
		 */
		QXfloat			SqrLength() const noexcept;

		/**
		 * @brief Make a string with vector values
		 * 
		 * @return QXstring String with vector
		 */
		QXstring		ToString() const noexcept;


#pragma region Operators

		/* Copy and move operator */

		/**
		 * @brief Operator = by copy
		 *
		 * @param vector Vector to copy
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator=(const QXvec3& vector) noexcept;

		/**
		 * @brief Operator = by move
		 *
		 * @param vector Vector to move
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator=(QXvec3&& vector) noexcept;

		/* Mathematics operators */

		/**
		 * @brief Operator for vector addition
		 *
		 * @param vector Vector to add
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator+=(const QXvec3& vector) noexcept;

		/**
		 * @brief Operator for addition
		 *
		 * @param vector Vector to add
		 * @return QXvec3 New vector
		 */
		QXvec3 	operator+(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator for substraction
		 *
		 * @param vector Vector to substract
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator-=(const QXvec3& vector) noexcept;

		/**
		 * @brief Operator for substraction
		 *
		 * @param vector Vector to substract
		 * @return QXvec3 New vector
		 */
		QXvec3 	operator-(const QXvec3& vector) const noexcept;

		/**
		 * @brief Create a new QXvec3 as the opposite of the vector
		 *
		 * @return QXvec3 New vector
		 */
		QXvec3	operator-() const noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator/=(QXfloat value) noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec3 New vector
		 */
		QXvec3 	operator/(QXfloat value) const noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to multiply
		 * @return QXvec3& Reference of current vector
		 */
		QXvec3& operator*=(QXfloat value) noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to multiply
		 * @return QXvec3 New vector
		 */
		QXvec3	operator*(QXfloat value) const noexcept;

		/* Binary operators */

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vectors have same length
		 * @return false Vectors have different length
		 */
		QXbool	operator==(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vectors have different length
		 * @return false Vectors have same length
		 */
		QXbool	operator!=(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is strictly inferior to compared vector
		 * @return false Vector length is superior or equal to compared vector
		 */
		QXbool	operator<(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is inferior or equal to compared vector
		 * @return false Vector length is strictly superior to compared vector
		 */
		QXbool	operator<=(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is strictly superior to compared vector
		 * @return false Vector length is inferior or equal to compared vector
		 */
		QXbool	operator>(const QXvec3& vector) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vector Vector to compare
		 * @return true Vector length is superior or equal to compared vector
		 * @return false Vector length is strictly inferior to compared vector
		 */
		QXbool	operator>=(const QXvec3& vector) const noexcept;

		/* Operator accessor*/

		/**
		 * @brief Operator to access vector values as an array
		 *
		 * @param idx Index of the array
		 * @return const QXfloat of the vector value
		 */
		const QXfloat	operator[](QXuint idx) const noexcept;

		/**
		* @brief Operator to access vector values as an array
		*
		* @param idx Index of the array
		* @return QXfloat& Reference of the vector value
		*/
		QXfloat& operator[](QXuint idx) noexcept;

#pragma endregion Operators

#pragma region Static Functions

		/**
		 * @brief Cumpute shortest angle between two vectors
		 * 
		 * @param vector1 Start vector
		 * @param vector2 Destination Vector
		 * @return QXfloat Angle value in radian
		 */
        static QXfloat	Angle(const QXvec3& vector1, const QXvec3& vector2) noexcept;

		/**
		 * @brief Compute center of a segment
		 * 
		 * @param pointA First point of the segment
		 * @param pointB Second point of the segment
		 * @return QXvec3 Point that reprensent center of the segment
		 */
		static QXvec3 	Center(const QXvec3& pointA, const QXvec3& pointB) noexcept;

		/**
		 * @brief Lerp a vector to an other
		 * 
		 * @param vector1 Current vector
		 * @param vector2 Destination vector
		 * @param ratio Ratio of lerp
		 * @return QXvec3 Vector result of lerp
		 */
        static QXvec3		Lerp(const QXvec3& vector1, const QXvec3& vector2, QXfloat ratio) noexcept;

		/**
		 * @brief Create a new QXvec3 object from two points
		 * 
		 * @param point1 First point
		 * @param point2 Second point
		 * @return QXvec3 New vector
		 */
        static QXvec3		Vec3FromPoints(const QXvec3& point1, const QXvec3& point2) noexcept;

#pragma endregion Static Functions

#pragma endregion Functions
	};

	/**
	 * @brief Operator to print vector
	 * 
	 * @param stream Stream to add the vector
	 * @param vector Vector to add to the stream
	 * @return std::ostream& Reference to the stream
	 */
	std::ostream&	operator<<(std::ostream& stream, const QXvec3& vector) noexcept;
}

namespace std
{
	template<>
	struct hash<Math::QXvec3>
	{
		size_t operator()(const Math::QXvec3& v)
		{
			return std::hash<float>{}(v.x) + std::hash<float>{}(v.y) + std::hash<float>{}(v.z);
		}
	};
}

#endif // __VEC3_H__
