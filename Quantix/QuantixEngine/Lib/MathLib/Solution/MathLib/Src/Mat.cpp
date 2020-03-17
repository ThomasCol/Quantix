#include "Mat.h"
#include <iostream>
#include <cstring>
#include <math.h>

namespace Math
{
	#pragma region Constructor/Destructor
	QXmat::QXmat(QXint ln, QXint col):
		line {ln},
		column {col}
    {
        array = new float[ln * col];

        for (int i = 0; i < ln * col; i++)
        {
            array[i] = 0;
        }
    }

	QXmat::QXmat(const QXvec3& v1, const QXvec3& v2, const QXvec3& v3):
		line {3},
		column {3}
    {
        array = new QXfloat[line * column];

        (*this)[0][0] = v1.x;
		(*this)[0][1] = v1.y;
		(*this)[0][2] = v1.z;

		(*this)[1][0] = v2.x;
		(*this)[1][1] = v2.y;
		(*this)[1][2] = v2.z;

		(*this)[2][0] = v3.x;
		(*this)[2][1] = v3.y;
		(*this)[2][2] = v3.z;
    }


	QXmat::QXmat(const QXmat& mat)
    {
        line = mat.line;
        column = mat.column;
        array = new QXfloat[mat.line * mat.column];
        for (QXint i = 0; i < line; i++)
        {
            for (QXint j = 0; j < column; j++)
            {
                (*this)[i][j] = mat[i][j];
            }
        }
    }

	QXmat::QXmat(QXmat&& mat):
		line {std::move(mat.line)},
		column {std::move(mat.column)}
    {
        array = new QXfloat[line * column];
        for (QXint i = 0; i < line * column; i++)
        {
            array[i] = mat.array[i];
        }
    }


	QXmat::~QXmat()
    {
        if (array != nullptr)
            delete[] array;
        array = nullptr;
    }
	#pragma endregion Constructor/Destructor

	#pragma region Functions
    QXfloat QXmat::Determinant() const
	{
		if (line != column)
			return 0.f;

		if (line == 1 && column == 1)
			return (*this)[0][0];
		else if (line == 2 && column == 2)
			return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
		else if (line == 3 && column == 3)
		{
			return (*this)[0][0] * (*this)[1][1] * (*this)[2][2] +
					(*this)[0][1] * (*this)[1][2] * (*this)[2][0] +
					(*this)[0][2] * (*this)[1][0] * (*this)[2][1] -
					(*this)[0][2] * (*this)[1][1] * (*this)[2][0] -
					(*this)[0][1] * (*this)[1][0] * (*this)[2][2] -
					(*this)[0][0] * (*this)[1][2] * (*this)[2][1];
		}
		else if (line == 4 && column == 4)
		{
			return	(*this)[0][0] * (*this)[1][1] * (*this)[2][2] * (*this)[3][3] -
					(*this)[0][0] * (*this)[1][1] * (*this)[2][3] * (*this)[3][2] -
					(*this)[0][0] * (*this)[1][2] * (*this)[2][1] * (*this)[3][3] +
					(*this)[0][0] * (*this)[1][2] * (*this)[2][3] * (*this)[3][1] +
					(*this)[0][0] * (*this)[1][3] * (*this)[2][1] * (*this)[3][2] -
					(*this)[0][0] * (*this)[1][3] * (*this)[2][2] * (*this)[3][1] -
					(*this)[0][1] * (*this)[1][0] * (*this)[2][2] * (*this)[3][3] +
					(*this)[0][1] * (*this)[1][0] * (*this)[2][3] * (*this)[3][2] +
					(*this)[0][1] * (*this)[1][2] * (*this)[2][0] * (*this)[3][3] -
					(*this)[0][1] * (*this)[1][2] * (*this)[2][3] * (*this)[3][0] -
					(*this)[0][1] * (*this)[1][3] * (*this)[2][0] * (*this)[3][2] +
					(*this)[0][1] * (*this)[1][3] * (*this)[2][2] * (*this)[3][0] +
					(*this)[0][2] * (*this)[1][0] * (*this)[2][1] * (*this)[3][3] -
					(*this)[0][2] * (*this)[1][0] * (*this)[2][3] * (*this)[3][1] -
					(*this)[0][2] * (*this)[1][1] * (*this)[2][0] * (*this)[3][3] +
					(*this)[0][2] * (*this)[1][1] * (*this)[2][3] * (*this)[3][0] +
					(*this)[0][2] * (*this)[1][3] * (*this)[2][0] * (*this)[3][1] -
					(*this)[0][2] * (*this)[1][3] * (*this)[2][1] * (*this)[3][0] -
					(*this)[0][3] * (*this)[1][0] * (*this)[2][1] * (*this)[3][2] +
					(*this)[0][3] * (*this)[1][0] * (*this)[2][2] * (*this)[3][1] +
					(*this)[0][3] * (*this)[1][1] * (*this)[2][0] * (*this)[3][2] -
					(*this)[0][3] * (*this)[1][1] * (*this)[2][2] * (*this)[3][0] -
					(*this)[0][3] * (*this)[1][2] * (*this)[2][0] * (*this)[3][1] +
					(*this)[0][3] * (*this)[1][2] * (*this)[2][1] * (*this)[3][0];
		}
		else
		{
			/*float	result{0};
			int		sign{1};
			Mat		temp(line, column);

			for (unsigned int i = 0; i < line; i++)
			{
				temp = GetCofactor(0, i);
				result += sign * (*this)[0][i] * temp.Determinant();
				sign = -sign;
			}

			return result;*/

			return 0;
		}
	}

	QXfloat QXmat::GetCofactor(const QXuint& l, const QXuint& c) const
	{
		return (float)(pow(-1, l + c) * GetMinor(l, c));
	}

	QXmat QXmat::GetCofactorMatrix() const
	{
		QXmat	mat(line, column);

		for (QXint i = 0 ; i < line ; i++)
			for (QXint j = 0 ; j < column ; j++)
				mat[i][j] = (QXfloat)(pow(-1, i + j) * GetMinor(i + 1, j + 1));

		return mat;
	}

	QXfloat QXmat::GetMinor(const QXuint& l, const QXuint& c) const
	{
		if (line != column || line < 2)
			return 0.f;

		return GetSubMatrix(l, c).Determinant();
	}

	QXmat QXmat::GetSubMatrix(QXuint l, QXuint c) const
	{
		if (line != column || line <= 2)
			return QXmat(0, 0);

		QXmat	mat(line - 1, column - 1);

		l--;
		c--;

		for (QXint i = 0, i2 = 0 ; i < line ; i++)
			if (i != (QXint)l)
			{
				for (QXint j = 0, j2 = 0 ; j < column ; j++)
					if (j != (QXint)c)
					{
						mat[i2][j2] = (*this)[i][j];
						j2++;
					}

				i2++;
			}

		return mat;
	}

	QXmat QXmat::Inverse() const
	{
		if (line != column)
			return QXmat(0, 0);

		QXmat inv(line, column);
		QXfloat det = Determinant();

		if (line == 2)
		{
			inv[0][0] = (*this)[1][1] * (1 / det);
			inv[0][1] = -(*this)[0][1] * (1 / det);
			inv[1][0] = -(*this)[1][0] * (1 / det);
			inv[1][1] = (*this)[0][0] * (1 / det);
		}
		else
		{
			QXmat cofactor(GetCofactorMatrix());

			for (QXint i = 0; i < line; i++)
				for (QXint j = 0; j < column; j++)
					inv[i][j] = cofactor[j][i] / det;
		}

		return inv;
	}

	QXmat QXmat::InverseMat3()
	{
		// computes the inverse of a matrix m
		QXdouble det = (*this)[0][0] * ((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2]) -
			(*this)[0][1] * ((*this)[1][0] * (*this)[2][2] - (*this)[1][2] * (*this)[2][0]) +
			(*this)[0][2] * ((*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0]);

		if (!det)
			return *this;

		QXdouble invdet = 1 / det;

		QXmat minv(3, 3); // inverse of matrix m
		minv[0][0] = (float)(((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2]) * invdet);
		minv[0][1] = (float)(((*this)[0][2] * (*this)[2][1] - (*this)[0][1] * (*this)[2][2]) * invdet);
		minv[0][2] = (float)(((*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1]) * invdet);
		minv[1][0] = (float)(((*this)[1][2] * (*this)[2][0] - (*this)[1][0] * (*this)[2][2]) * invdet);
		minv[1][1] = (float)(((*this)[0][0] * (*this)[2][2] - (*this)[0][2] * (*this)[2][0]) * invdet);
		minv[1][2] = (float)(((*this)[1][0] * (*this)[0][2] - (*this)[0][0] * (*this)[1][2]) * invdet);
		minv[2][0] = (float)(((*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1]) * invdet);
		minv[2][1] = (float)(((*this)[2][0] * (*this)[0][1] - (*this)[0][0] * (*this)[2][1]) * invdet);
		minv[2][2] = (float)(((*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1]) * invdet);

		return minv;
	}

	QXmat  QXmat::Transpose() const
	{
		QXmat mat(column, line);

		for (QXint i = 0; i < line; i++)
		{
			for (QXint j = 0; j < column; j++)
			{
				QXfloat k = array[i * column + j];
				mat[j][i] = k;
			}
		}
		return mat;
	}

	#pragma region Operator Functions
	QXfloat* QXmat::operator[](QXint i)
	{
		return &array[i * column];
	}

	QXfloat* QXmat::operator[](QXint i) const
	{
		return &array[i * column];
	}

	QXmat  QXmat::operator+(const QXmat& mat)
	{
		QXmat  res(line, column);

		if (line != mat.line || column != mat.column)
		{
			return res;
		}

		for (QXint i = 0; i < line; i++)
		{
			for (QXint j = 0; j < column; j++)
			{
				res[i][j] = (*this)[i][j] + mat[i][j];
			}
		}

		return res;
	}

	QXvec3 QXmat::operator*(const QXvec3& vect) const
	{
		QXmat  v(3, 1);
		v[0][0] = vect.x;
		v[1][0] = vect.y;
		v[2][0] = vect.z;

		QXmat  res((*this) * v);

		QXvec3 v_res(res[0][0], res[1][0], res[2][0]);

		return v_res;
	}

	QXvec4 QXmat::operator*(const QXvec4& vect) const
	{
		QXmat  v(4, 1);
		v[0][0] = vect.x;
		v[1][0] = vect.y;
		v[2][0] = vect.z;
		v[3][0] = vect.w;

		QXmat  res((*this) * v);

		QXvec4 v_res(res[0][0], res[1][0], res[2][0], res[3][0]);

		return v_res;
	}

	QXmat  QXmat::operator*(const QXmat& mat) const
	{
		QXmat res(line, mat.column);
		if (column != mat.line)
		{
			return res;
		}

		for (QXint i = 0; i < line; i++)
		{
			for (QXint j = 0; j < mat.column; j++)
			{
				for (QXint k = 0; k < mat.line; k++)
				{
					res[i][j] += (*this)[i][k] * mat[k][j];
				}
			}
		}

		return res;
	}

	QXmat& QXmat::operator=(const QXmat& mat)
	{
		line = mat.line;
		column = mat.column;

		if (array != nullptr)
			delete array;

		array = new QXfloat[line * column];

		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				(*this)[i][j] = mat[i][j];
			}
		}
		return *this;
	}
	#pragma endregion Operator Functions

	#pragma region Static Functions
	QXmat  QXmat::Identity(QXint m)
	{
		QXmat mat(m, m);
		for (QXint i = 0; i < m; i++)
		{
			for (QXint j = 0; j < m; j++)
			{
				if (j == i)
					mat[i][j] = 1;
				else
					mat[i][j] = 0;
			}
		}
		return mat;
	}

	QXmat  QXmat::Zero(QXint m)
	{
		QXmat  mat(m, m);
		for (QXint i = 0; i < m; i++)
		{
			for (QXint j = 0; j < m; j++)
			{
				mat[i][j] = 0;
			}
		}
		return mat;
	}
	#pragma endregion Static Functions
	#pragma endregion Functions

	QXmat     operator*(QXmat mat, QXfloat nb)
	{
		QXmat  res(mat.line, mat.column);
		for (QXint i = 0; i < mat.line; i++)
		{
			for (QXint j = 0; j < mat.column; j++)
			{
				res[i][j] = mat[i][j] * nb;
			}
		}
		return res;
	}
}