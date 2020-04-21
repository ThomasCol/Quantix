#ifndef _MAT4_H_
#define _MAT4_H_

#include "Vec3.h"
#include "Vec4.h"

#include <string>

namespace Math
{
	struct QXquaternion;
	/**
	 * @brief QXmat4 structure
	 * 
	 */
	struct QXmat4
	{
		#pragma region Attributes
		QXfloat	array[16];
		#pragma endregion Attributes

		#pragma region Constructor/Destructor
		/* constructor */
		/**
		 * @brief Construct a new QXmat4 object
		 * 
		 */
		QXmat4();

		/**
		 * @brief Construct a new QXmat4 object
		 * 
		 * @param mat QXmat4 to copy
		 */
		QXmat4(const QXmat4& mat);

		/* destructor */
		/**
		 * @brief Destroy the QXmat4 object
		 * 
		 */
		~QXmat4() = default;
		#pragma endregion Constructor/Destructor

		#pragma region Functions
		/* func to get inverse matrix */
		/**
		 * @brief Compute inverse Matrix
		 * 
		 * @return QXmat4 Mat inverse matrix
		 */
		QXmat4 				Inverse() const;

		/**
		 * @brief Compute transpose Matrix
		 * 
		 * @return QXmat4 Mat transpose matrix
		 */
		QXmat4				Transpose() const;

		/* for debug */
		/**
		 * @brief String of QXmat4 object
		 * 
		 * @return String matrix of the current mat4
		 */
		QXstring			ToString() const;

		#pragma region Operator Functions
		/* operator for access to the matrix */
		/**
		 * @brief Operator [] accessor
		 * 
		 * @param i QXint index to access in matrix
		 * @return QXfloat* value matrix at index that can be modified
		 */
		QXfloat*			operator[](QXint i);

		/**
		 * @brief Operator [] accessor
		 * 
		 * @param i QXint index to access in matrix
		 * @return QXfloat* value matrix at index that cannot be modified
		 */
		const QXfloat*		operator[](QXint i) const;

		/* math operators */
		/**
		 * @brief Operator + addition
		 * 
		 * @param Mat QXmat4 for addition
		 * @return QXmat4 result of the addition
		 */
		QXmat4				operator+(const QXmat4& mat) const;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param Mat QXmat4 for multiplication
		 * @return new QXmat4 result of the multiplication
		 */
		QXmat4				operator*(const QXmat4& mat) const;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param Mat QXmat4 for multiplication
		 * @return The current QXmat4 mat modify by the multiplication
		 */
		QXmat4&				operator*=(const QXmat4& mat);

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param vect QXvec3 for multiplication
		 * @return new QXvec3 result of the multiplication
		 */
		QXvec3				operator*(const QXvec3& vec) const;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param vect QXvec4 for multiplication
		 * @return new QXvec4 result of the multiplication
		 */
		QXvec4				operator*(const QXvec4& vec) const;
		#pragma endregion Operator Functions

		#pragma region Static Functions
		/**
		 * @brief Create scale matrix
		 * 
		 * @param scale QXvec3 scale vector
		 * @return new QXmat4 mat4 scale matrix
		 */
		static QXmat4		CreateScaleMatrix(const QXvec3& scale);

		/**
		 * @brief Create translation matrix
		 * 
		 * @param trans QXvec3 translation vector
		 * @return new QXmat4 mat4 translation matrix
		 */
		static QXmat4		CreateTranslationMatrix(const QXvec3& trans);

		/**
		 * @brief Create rotation matrix
		 * 
		 * @param axis QXvec3 rotation vector
		 * @param angle QXfloat the angle in radian
		 * @return new QXmat4 mat4 rotation matrix
		 */
		static QXmat4		CreateRotationMatrix(const QXvec3& axis, const QXfloat& angle);

		/**
		 * @brief Create rotation on X axis matrix
		 * 
		 * @param angle QXfloat the angle in radian
		 * @return new QXmat4 mat4 rotation matrix on X axis
		 */
		static QXmat4		CreateXRotationMatrix(const QXfloat angle);

		/**
		 * @brief Create rotation on Y axis matrix
		 * 
		 * @param angle QXfloat the angle in radian
		 * @return new QXmat4 mat4 rotation matrix on Y axis
		 */
		static QXmat4		CreateYRotationMatrix(const QXfloat angle);

		/**
		 * @brief Create rotation on Z axis matrix
		 * 
		 * @param angle QXfloat the angle in radian
		 * @return new QXmat4 mat4 rotation matrix on Z axis
		 */
		static QXmat4		CreateZRotationMatrix(const QXfloat angle);

		/**
		 * @brief Create euler rotation matrix
		 * 
		 * @param rotate QXvec3 rotation vector
		 * @return new QXmat4 mat4 rotation matrix around Y-X-Z axis
		 */
		static QXmat4		CreateFixedAngleEulerRotationMatrix(const QXvec3& rotate);

		/**
		 * @brief Create TRS matrix
		 * 
		 * @param trans QXvec3 translation vector
		 * @param rotate QXvec3 rotation vector
		 * @param scale QXvec3 scale vector
		 * @return new QXmat4 mat4 that is TRS matrix
		 */
		static QXmat4		CreateTRSMatrix(const QXvec3& trans, const QXvec3& rotate,
									const QXvec3& scale);

		/**
		 * @brief Create TRS matrix
		 *
		 * @param trans QXvec3 translation vector
		 * @param rotate QXquaternion rotation vector
		 * @param scale QXvec3 scale vector
		 * @return new QXmat4 mat4 that is TRS matrix
		 */
		static QXmat4		CreateTRSMatrix(const QXvec3& trans, const QXquaternion& rotate,
			const QXvec3& scale);
		/* ============================= */

		/**
		 * @brief Create projection matrix
		 * 
		 * @param width QXint width of screen
		 * @param height QXint height of screen
		 * @param near QXfloat near vision
		 * @param far QXfloat far vision
		 * @param fov QXfloat field of view
		 * @return new QXmat4 mat4 that is the projection matrix
		 */
		static QXmat4		CreateProjectionMatrix(QXint width, QXint height, QXfloat near,
													QXfloat far, QXfloat fov);

		/**
		 * @brief Create orthographic matrix
		 * 
		 * @param width QXint width of screen
		 * @param height QXint height of screen
		 * @param near QXfloat near vision
		 * @param far QXfloat far vision
		 * @return new QXmat4 mat4 that is the orthographic matrix
		 */
		static QXmat4		CreateOrthographicProjectionMatrix(QXint width, QXint height, QXfloat near, QXfloat far);

		/**
		 * @brief Create look at matrix
		 * 
		 * @param position QXvec3 position of the camera
		 * @param target QXvec3 position of the target to look
		 * @param up QXvec3 up vector
		 * @param Scale QXvec3 scale vector
		 * @return new QXmat4 mat4 that is the look at matrix
		 */
		static QXmat4		CreateLookAtMatrix(QXvec3 position, QXvec3 target, QXvec3 up);

		/**
		 * @brief Get Identity Matrix
		 * 
		 * @return QXmat4 Mat identity matrix
		 */
		static QXmat4		Identity();
		#pragma endregion Static Functions
		#pragma endregion Functions
	};
}

#endif //_MAT4_H_
