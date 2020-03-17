#ifndef _MAT_H_
#define _MAT_H_

#include "Vec3.h"
#include "Vec4.h"

namespace Math
{
	/**
	 * @brief QXmat structure
	 * 
	 */
    struct QXmat
    {
		#pragma region Attributes
        QXint       line;
        QXint       column;

        QXfloat*    array;
		#pragma endregion Attributes

		#pragma region Constructor/Destructor
		/**
		 * @brief Construct a default QXmat object
		 * 
		 */
		QXmat() = default;

		/**
		 * @brief Construct new QXmat object
		 * 
		 * @param ln int for number of line
		 * @param col int for number of column
		 */
		QXmat(QXint ln = 0, QXint col = 0);

		/**
		 * @brief Construct new QXmat object of size 3
		 * 
		 * @param v1 Vec3 for the first line
		 * @param v2 Vec3 for the second line
		 * @param v3 Vec3 for the third line
		 */
		QXmat(const QXvec3& v1, const QXvec3& v2, const QXvec3& v3);

		/**
		 * @brief Construct new QXmat object
		 * 
		 * @param Mat QXmat to copy
		 */
		QXmat(const QXmat& Mat);

		/**
		 * @brief Construct new QXmat object
		 * 
		 * @param mat QXmat to move
		 */
		QXmat(QXmat&& mat);

		/**
		 * @brief Destroy the QXmat object
		 */
        ~QXmat();
		#pragma endregion Constructor/Destructor

		#pragma region Functions
		/**
		 * @brief Compute Determinant
		 * 
		 * @return QXfloat value of the matrix determinant
		 */
		QXfloat			Determinant() const;

		/**
		 * @brief Get the matrix cofactor
		 * 
		 * @param l QXint for the number of line in matrix
		 * @param c QXint for the number of column in matrix
		 * @return QXfloat factor value of the matrix
		 */
		QXfloat			GetCofactor(const QXuint& l, const QXuint& c) const;

		/**
		 * @brief Get the matrix cofactor
		 * 
		 * @return QXmat Mat the cofactor matrix
		 */
		QXmat			GetCofactorMatrix() const;

		/**
		 * @brief Get the matrix Minor
		 * 
		 * @param l QXint for the number of line in matrix
		 * @param c QXint for the number of column in matrix
		 * @return QXfloat minor value of the matrix
		 */
		QXfloat			GetMinor(const QXuint& l, const QXuint& c) const;

		/**
		 * @brief Comupte Subdivision Matrix
		 * 
		 * @param line QXint for the number of line in matrix
		 * @param column QXint for the number of column in matrix
		 * @return QXmat Mat for the Subdivide matrix
		 */
		QXmat			GetSubMatrix(QXuint line, QXuint column) const;

		/**
		 * @brief Compute inverse Matrix
		 * 
		 * @return QXmat Mat inverse matrix
		 */
		QXmat 			Inverse() const;

		/**
		 * @brief Compute inverse Matrix3
		 * 
		 * @return QXmat3 Mat inverse matrix
		 */
		QXmat 			InverseMat3();

		/**
		 * @brief Compute transpose Matrix
		 * 
		 * @return QXmat Mat transpose matrix
		 */
		QXmat			Transpose() const;

		#pragma region Operator Functions
		/**
		 * @brief Operator [] accessor
		 * 
		 * @param i QXint index to access in matrix
		 * @return QXfloat* value matrix at index that can be modified
		 */
        QXfloat*		operator[](QXint i);
		
		/**
		 * @brief Operator [] accessor
		 * 
		 * @param i QXint index to access in matrix
		 * @return QXfloat* value matrix at index that cannot be modified
		 */
        QXfloat*		operator[](QXint i) const;

		/**
		 * @brief Operator + addition
		 * 
		 * @param Mat QXmat for addition
		 * @return QXmat result of the addition
		 */
		QXmat			operator+(const QXmat& Mat);

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param Mat QXmat for multiplication
		 * @return QXmat result of the multiplication
		 */
		QXmat			operator*(const QXmat& Mat)const;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param vect QXvec3 for multiplication
		 * @return QXvec3 result of the multiplication
		 */
		QXvec3			operator*(const QXvec3& vect) const;

		/**
		 * @brief Operator * multiplication
		 * 
		 * @param vect QXvec4 for multiplication
		 * @return QXvec4 result of the multiplication
		 */
		QXvec4			operator*(const QXvec4& vect) const;

		/**
		 * @brief Operator = by copy
		 * 
		 * @param Mat QXmat to copy
		 * @return Reference QXmat result of the current QXmat
		 */
		QXmat&			operator=(const QXmat& Mat);
		#pragma endregion Operator Functions

		#pragma region Static Functions
		/**
		 * @brief Get Identity Matrix
		 * 
		 * @param m QXint size of matrix
		 * @return QXmat Mat identity matrix
		 */
        static QXmat	Identity(QXint m);

		/**
		 * @brief Get Zero Matrix
		 * 
		 * @param m QXint size of matrix
		 * @return QXmat Mat zero matrix
		 */
        static QXmat	Zero(QXint m);
		#pragma endregion Static Functions
		#pragma endregion Functions

    };

	/**
	 * @brief Operator * multpication
	 * 
	 * @param QXmat mat matrix for the multiplication
	 * @param QXfloat nb value for the multiplication
	 * @return Qxmat result of the multiplication
	 */
	QXmat				operator*(QXmat mat, QXfloat nb);
}

#endif //_MAT_H_
