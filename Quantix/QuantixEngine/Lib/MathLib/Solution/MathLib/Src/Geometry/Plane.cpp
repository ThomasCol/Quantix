#include "Plane.h"
#include <iostream>

namespace Math::Geometry
{
	QXplane::QXplane():
		_normal(0, 1, 0),
		_d{0}
	{}

	QXplane::QXplane(const QXplane& plane):
		_normal(plane._normal),
		_d{plane._d}
	{}

	QXplane::QXplane(QXplane&& plane):
		_normal(std::move(plane._normal)),
		_d{std::move(plane._d)}
	{}

	QXplane::QXplane(const QXvec3& normal, const QXfloat& d)
	{
		_normal = normal.Normalized();
		_d = d / normal.Length();
	}

	QXplane::QXplane(const QXvec3& p1, const QXvec3& p2, const QXvec3& p3)
	{
		QXvec3 v1(p2 - p1);
		QXvec3 v2(p3 - p1);
		_normal = v1.Cross(v2).Normalized();
		_d = p3.Dot(_normal);
	}

	QXplane::QXplane(const QXvec3& normal, const QXvec3& p)
	{
		_normal = normal.Normalized();
		_d = p.Dot(_normal);
	}




	float QXplane::GetDistanceToPoint(const QXvec3& p) const
	{
		return abs(p.Dot(_normal) - _d) / _normal.Length();
	}

	QXvec3 QXplane::GetClosestPointOnPlane(const QXvec3& p) const
	{
		QXfloat	distance{GetDistanceToPoint(p)};

		return p + _normal * -distance;
	}

	bool QXplane::GetSide(const QXvec3& p) const
	{
		return (p.Dot(_normal) > _d);
	}

	bool QXplane::SameSide(const QXvec3& p1, const QXvec3& p2) const
	{
		return (GetSide(p1) == GetSide(p2));
	}


	QXvec3 QXplane::PlanesIntersection(const QXplane& plane1, const QXplane& plane2,
									const QXplane& plane3)
	{
		QXmat	matA(plane1._normal, plane2._normal, plane3._normal);

		if (matA.Determinant() == 0)
			return QXvec3(0);

		QXmat	matB(3, 1);

		matB[0][0] = plane1._d;
		matB[1][0] = plane2._d;
		matB[2][0] = plane3._d;

		QXmat	matX(3, 1);

		matX = matA.Inverse() * matB;

		return QXvec3(matX[0][0], matX[1][0], matX[2][0]);
	}

	QXplane& QXplane::operator=(const QXplane& plane)
	{
		_normal = plane._normal;
		_d = plane._d;

		return *this;
	}
}
