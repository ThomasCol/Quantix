#ifndef _REF3_H_
#define _REF3_H_

#include "Quaternion.h"

namespace Math
{
	/**
	 * @brief Referentiel3 structure
	 * 
	 */
	struct QXref3
	{
#pragma region Attributes		

		QXvec3 o, i, j, k;

#pragma endregion Attributes		

#pragma region Constructors

		/**
		 * @brief Construct a new QXref3 object
		 * 
		 * @param O Value for o
		 * @param AngleI Angle around right
		 * @param AngleJ Angle around up
		 * @param AngleK Angle around forward
		 */
		QXref3(const QXvec3& O, QXfloat AngleI, QXfloat AngleJ, QXfloat AngleK) noexcept;

		/**
		 * @brief Construct a new QXref3 object
		 * 
		 * @param O Value for o parameter by QXvec3::zero by default
		 * @param I Value for i parameter by QXvec3::right by default
		 * @param J Value for j parameter by QXvec3::up by default
		 * @param K Value for k parameter by QXvec3::forward by default
		 */
		QXref3(const QXvec3& O = {QXvec3::zero}, const QXvec3& I = {QXvec3::right},
			const QXvec3& J = {QXvec3::up}, const QXvec3& K = {QXvec3::forward}) noexcept;

		/**
		 * @brief Construct a new QXref3 object
		 * 
		 * @param ref Ref to copy
		 */
		QXref3(const QXref3& ref) noexcept;

		/**
		 * @brief Construct a new QXref3 object
		 * 
		 * @param ref Ref to move
		 */
		QXref3(QXref3&& ref) noexcept;

		/**
		 * @brief Destroy the QXref3 object
		 */
		~QXref3() = default;

#pragma endregion Constructors

#pragma region Functions

		/**
		 * @brief Transform to Global referential to a local referential
		 * 
		 * @param ref Referential to transform
		 * @return QXref3 New referential
		 */
		QXref3 GlobalToLocal(const QXref3& ref) const noexcept;

		/**
		 * @brief Transform to local referential to a Global referential
		 * 
		 * @param ref Referential to transform
		 * @return QXref3 New referential
		 */
		QXref3 LocalToGlobal(const QXref3& ref) const noexcept;
		
		/**
		 * @brief Rotate axes of referential
		 * 
		 * @param quat QXquaternion of rotation
		 * @return QXref3& Reference of current referential
		 */
		QXref3& Rotate(const QXquaternion& quat) noexcept;
				
		/**
		 * @brief Rotate axes of referential
		 * 
		 * @param quat QXquaternion of rotation
		 * @return QXref3 New referential
		 */
		QXref3 Rotate(const QXquaternion& quat) const noexcept;

		/**
		 * @brief Translate Center of referential
		 * 
		 * @param value Vector of translation
		 * @return QXref3& Reference of the current referential
		 */
		QXref3& Translate(const QXvec3& value) noexcept;

		
		/**
		 * @brief Translate Center of referential
		 * 
		 * @param value Vector of translation
		 * @return QXref3 New referential
		 */
		QXref3 Translate(const QXvec3& value) const noexcept;

#pragma region Operators

		/* Copy and move operator */

		/**
		 * @brief Operator = by copy
		 *
		 * @param ref Referentiel to copy
		 * @return QXref3& Reference of current referentiel
		 */
		QXref3& operator=(const QXref3& ref) noexcept;

		/**
		 * @brief Operator = by move
		 *
		 * @param ref Referentiel to move
		 * @return QXref3& Reference of current referentiel
		 */
		QXref3& operator=(QXref3&& ref) noexcept;

		/* Mathematics operators */

		/**
		 * @brief Operator to multiply a ref by a Matrix4
		 *
		 * @param m Matrix to multiply
		 * @return QXref3 new Ref3
		 */
		QXref3 operator*(const QXmat4& m) const noexcept;
		
		/**
		 * @brief Operator to multiply a ref by a Matrix4
		 *
		 * @param m Matrix to multiply
		 * @return QXref3& Reference of the current Ref3
		 */
		QXref3& operator*=(const QXmat4& m) noexcept;

		/**
		 * @brief Operator to compare vectors
		 *
		 * @param ref Referentiel compared
		 * @return true Referentiels have same vectors
		 * @return false Referentiels have different vectors
		 */
		QXbool 	operator==(const QXref3& ref) const noexcept;

		/**
		 * @brief Operator to compare vectors
		 *
		 * @param ref Referentiel compared
		 * @return true Referentiels have different vectors
		 * @return false Referentiels have same vectors
		 */
		QXbool  operator!=(const QXref3& ref) const noexcept;

#pragma endregion Operators

#pragma endregion Functions
	};
}

#endif //_REFERANTIAL3_H_
