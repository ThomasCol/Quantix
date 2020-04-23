#pragma once

#include "Mat.h"
#include "Mat4.h"

namespace Math
{
	/**
	 * @brief Quaternion structure
	 * 
	 */
	struct	QXquaternion
	{
		#pragma region Attributes

		union
		{
			struct { QXfloat w; QXvec3 v; };
			QXfloat e[4];
		};

		#pragma endregion Attributes
	
		#pragma region Constructors/Destructor

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param vw Value of angle in radian
		 * @param vx Value for x parameter of Vector
		 * @param vy Value for y parameter of Vector
		 * @param vz Value for z parameter of Vector
		 */
		QXquaternion(QXfloat vw = 0.f, QXfloat vx = 0.f, QXfloat vy = 0.f, QXfloat vz = 0.f) noexcept;

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param vw Value of angle in radian
		 * @param vQ Vector of rotation
		 */
		QXquaternion(QXfloat vw, const QXvec3& vQ) noexcept;

		/**
		 * @brief Construct a new Quaternion object
		 * 
		 * @param q Quaternion to copy
		 */
		QXquaternion(const QXquaternion& q) noexcept;

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param q Quaternion to move 
		 */
		QXquaternion(const QXquaternion&& q) noexcept;

		/**
		 * @brief Destroy the Quaternion object
		 * 
		 */
		~QXquaternion() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Operators

		/**
		 * @brief Operator = by copy
		 * 
		 * @param q Quaternion to copy
		 * @return Reference QXquaternion of current Quaternion
		 */
		QXquaternion&		operator=(const QXquaternion& q) noexcept;

		/**
		 * @brief Operator = by move
		 * 
		 * @param q Quaternion to move
		 * @return QXquaternion& Reference of current Quaternion
		 */
		QXquaternion&		operator=(QXquaternion&& q) noexcept;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param s float scale value for multiplication
		 * @return QXquaternion result of multiplication
		 */
		QXquaternion		operator*(QXfloat s) const noexcept;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param q Quaternion for multiplication
		 * @return QXquaternion result of multiplication
		 */
		QXquaternion		operator*(const QXquaternion& q) const noexcept;

		/**
		 * @brief Operator *= multiplication
		 *
		 * @param q Quaternion for multiplication
		 * @return QXquaternion result of multiplication
		 */
		QXquaternion		operator*=(const QXquaternion& q) const noexcept;

		/**
		 * @brief Operator * multiplication with a vector
		 * 
		 * @param vec Vector to multiply
		 * @return QXvec3& Reference of the new vector
		 */
		QXvec3 				operator*(const QXvec3& vec) const noexcept;

		/**
		 * @brief Operator + addition
		 * 
		 * @param q QXquaternion for addition
		 * @return Reference of new QXquaternion result object
		 */
		QXquaternion		operator+(const QXquaternion& q) const noexcept;

		/**
		 * @brief Operator - substaction
		 * 
		 * @param q QXquaternion for substraction
		 * @return String quaternion of the current quaternion
		 */
		QXquaternion		operator-(const QXquaternion& q) const noexcept;

		/**
		 * @brief Operator to access quaternion values as an array
		 * 
		 * @param idx Index of the array
		 * @return QXfloat& Reference of the vector value
		 */
		QXfloat& 			operator[](const QXuint idx) noexcept;

		/**
		 * @brief Operator to access quaternion values as an array
		 * 
		 * @param idx Index of the array
		 * @return QXfloat Value of the vector array
		 */
		QXfloat 			operator[](const QXuint idx) const noexcept;

		#pragma endregion Operator Functions

		#pragma region Functions
		/**
		 * @brief Add two Quaternion object
		 * 
		 * @param q Quaternion to add
		 * @return Reference of new QXquaternion result object
		 */
		QXquaternion		AddQuaternion(const QXquaternion& q) const noexcept;

		/**
		 * @brief Conjugate of Quaternion object
		 * 
		 * @return Reference of new QXquaternion result object
		 */
		QXquaternion		ConjugateQuaternion() const noexcept;

		/**
		 * @brief Convert Quaternion object into Mat4 object
		 * 
		 * @return New QXmat4 from the current Quaternion
		 */
		QXmat4				ConvertQuaternionToMat() const noexcept;

		/**
		 * @brief Dot product between two Quaternion object
		 * 
		 * @param q Quaternion to compute dot product
		 * @return QXfloat float result of dot product
		 */
		QXfloat				DotProductQuaternion(const QXquaternion& q) const noexcept;

		/**
		 * @brief Inverse of the current Quaternion object
		 * 
		 * @return Reference QXquaternion of the current Quaternion
		 */
		QXquaternion		InverseQuaternion() noexcept;

		/**
		 * @brief Multiply Quaternion object with QXfloat
		 * 
		 * @param s float scale value for multiplication
		 * @return New reference QXquaternion result of multiplication 
		 */
		QXquaternion		MultQuaternion(QXfloat s) const noexcept;

		/**
		 * @brief Multiply two Quaternion object
		 * 
		 * @param q Quaternion for multiplication
		 * @return New reference QXquaternion result of multiplication
		 */
		QXquaternion		MultQuaternion(const QXquaternion& q) const noexcept;

		/**
		 * @brief Negate of the current Quaternion object
		 * 
		 */
		void				NegateQuaternion() noexcept;

		/**
		 * @brief Normalize Quaternion object
		 * 
		 * @return New reference QXquaternion result of normalize
		 */
		QXquaternion		NormalizeQuaternion() noexcept;

		/**
		 * @brief Nullify the current Quaternion object
		 * 
		 */
		void				NullQuaternion() noexcept;

		/**
		 * @brief Length of the current Quaternion object
		 * 
		 * @return QXfloat length of the current Quaternion
		 */
		float				QuaternionLength() const noexcept;

		/**
		 * @brief Negate Quaternion object
		 * 
		 * @return New reference QXquaternion result of negate Quaternion
		 */
		QXquaternion		ReturnNegateQuaternion() const noexcept;

		/**
		 * @brief Square root of Quaternion object
		 * 
		 * @return QXfloat of the square root of current Quaternion
		 */
		float				SqrtRootQuaternion() const noexcept;

		/**
		 * @brief Slerp of Quaternion object
		 * 
		 * @param q Quaternion destination
		 * @param t float ratio
		 * @return reference of the current QXquaternion slerp normalize
		 */
		QXquaternion		SlerpQuaternion(const QXquaternion& q, QXfloat t) noexcept;

		/**
		 * @brief Substract two Quaternion object
		 * 
		 * @param q Quaternion for substraction
		 * @return New reference QXquaternion result of substraction of two quaternion
		 */
		QXquaternion		SubQuaternion(const QXquaternion& q) const noexcept;

		QXvec3&				QuaternionToEuler();

		void				SetEulerToQuaternion(const QXvec3& vect);

		/**
		 * @brief String of Quaternion object
		 * 
		 * @return String quaternion of the current quaternion
		 */
		QXstring			ToString() const noexcept;
		#pragma region Static Functions

		/**
		 * @brief Convert Quaternion object into Mat4 object
		 * 
		 * @param q Quaternion for conversion
		 * @return New QXmat4 from the Quaternion
		 */
		static QXmat4		ConvertQuaternionToMat(const QXquaternion& q) noexcept;

		/**
		 * @brief Convert Mat4 object into Quaternion object
		 * 
		 * @param m Mat4 for conversion
		 * @return New Quaternion from the Mat4
		 */
		static QXquaternion	ConvertMatToQuaternion(const QXmat4& m) noexcept;

		/**
		 * @brief Convert Euler angle into Quaternion object
		 * 
		 * @param euler Vec3 for conversion
		 * @return New Quaternion from Vec3
		 */
		static QXquaternion	ConvertEulerAngleToQuaternion(const QXvec3& euler) noexcept;

		/**
		 * @brief Slerp of Quaternion object
		 * 
		 * @param q Quaternion begin
		 * @param q Quaternion destination
		 * @param t float ratio
		 * @return QXquaternion slerp normalize
		 */
		static QXquaternion	SlerpQuaternion(QXquaternion& q1, const QXquaternion& q2, QXfloat t) noexcept;


		static QXquaternion	EulerToQuaternion(const QXvec3& vect);
		#pragma endregion Static Functions
		#pragma endregion Functions


	};
}