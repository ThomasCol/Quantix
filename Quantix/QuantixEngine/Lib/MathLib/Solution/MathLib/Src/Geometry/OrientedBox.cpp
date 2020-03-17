#include "OrientedBox.h"
#include "Mat4.h"

#include <limits>
#include <float.h>
#include <vector>

namespace Math::Geometry
{
	QXorientedBox::QXorientedBox(const QXref3& ref, const QXvec3& halfSizes) noexcept:
		_ref {ref},
		_halfSizes {halfSizes}
	{}

	QXorientedBox::QXorientedBox(const QXorientedBox& box, const QXfloat& offsetExtention) noexcept :
		_ref {box._ref},
		_halfSizes {box._halfSizes + QXvec3(offsetExtention)}
	{}

	QXorientedBox::QXorientedBox(QXorientedBox&& box) noexcept :
		_ref(std::move(box._ref)),
		_halfSizes(std::move(box._halfSizes))
	{}

	QXorientedBox&	QXorientedBox::operator=(const QXorientedBox& box) noexcept
	{
		_ref = box._ref;
		_halfSizes = box._halfSizes;

		return *this;
	}

	QXorientedBox&	QXorientedBox::operator=(QXorientedBox&& box) noexcept
	{
		_ref = std::move(box._ref);
		_halfSizes = std::move(box._halfSizes);

		return *this;
	}

	QXfloat max(const QXfloat& f1, const QXfloat& f2) { return f1 > f2 ? f1 : f2;}

	QXbox QXorientedBox::GetAABB() const noexcept
	{
		QXvec3 verticesLocal[8]
		{
			{ _ref.o + _ref.i * _halfSizes.x - _ref.j * _halfSizes.y - _ref.k * _halfSizes.z },
			{ _ref.o + _ref.i * _halfSizes.x - _ref.j * _halfSizes.y + _ref.k * _halfSizes.z },
			{ _ref.o - _ref.i * _halfSizes.x - _ref.j * _halfSizes.y + _ref.k * _halfSizes.z },
			{ _ref.o - _ref.i * _halfSizes.x - _ref.j * _halfSizes.y - _ref.k * _halfSizes.z },
			{ _ref.o + _ref.i * _halfSizes.x + _ref.j * _halfSizes.y - _ref.k * _halfSizes.z },
			{ _ref.o + _ref.i * _halfSizes.x + _ref.j * _halfSizes.y + _ref.k * _halfSizes.z },
			{ _ref.o - _ref.i * _halfSizes.x + _ref.j * _halfSizes.y + _ref.k * _halfSizes.z },
			{ _ref.o - _ref.i * _halfSizes.x + _ref.j * _halfSizes.y - _ref.k * _halfSizes.z }
		};

		std::vector<QXvec3> vertices_global;

		for (int i = 0; i < 8; i++)
		{
			vertices_global.push_back(verticesLocal[i].LocalToWorld(_ref));
		}

		float xmin = -FLT_MAX, ymin = -FLT_MAX, zmin = -FLT_MAX, xmax = FLT_MAX, ymax = FLT_MAX, zmax = FLT_MAX;
		for (int i = 0; i < 8; i++)
		{
			if (vertices_global[i].x > xmax)
				xmax = vertices_global[i].x;
			else if (vertices_global[i].x < xmin)
				xmin = vertices_global[i].x;

			if (vertices_global[i].y > ymax)
				ymax = vertices_global[i].y;
			else if (vertices_global[i].y < ymin)
				ymin = vertices_global[i].y;

			if (vertices_global[i].z > zmax)
				zmax = vertices_global[i].z;
			else if (vertices_global[i].z < zmin)
				zmin = vertices_global[i].z;
		}

		return QXbox(_ref.o, QXvec3((xmax - xmin) * 0.5f, (ymax - ymin) * 0.5f, (zmax - zmin) * 0.5f));
	}

	QXvec3* QXorientedBox::GetPoints() const noexcept
	{
		QXvec3* array = new QXvec3[8];

		QXvec3 vx(_ref.i * _halfSizes.x);
		QXvec3 vy(_ref.j * _halfSizes.y);
		QXvec3 vz(_ref.k * _halfSizes.z);

		array[0] = _ref.o + vx + vy + vz;
		array[1] = _ref.o + vx + vy - vz;
		array[2] = _ref.o + vx - vy + vz;
		array[3] = _ref.o + vx - vy - vz;
		array[4] = _ref.o + vx * (-1) + vy + vz;
		array[5] = _ref.o + vx * (-1) + vy - vz;
		array[6] = _ref.o + vx * (-1) - vy + vz;
		array[7] = _ref.o + vx * (-1) - vy - vz;

		return array;
	}

	QXplane QXorientedBox::GetTopPlane() const noexcept
	{
		return QXplane(_ref.j, _ref.o + _ref.j * _halfSizes.y);
	}

	QXplane QXorientedBox::GetBottomPlane() const noexcept
	{
		return QXplane(_ref.j * (-1), _ref.o - _ref.j * _halfSizes.y);
	}

	QXplane QXorientedBox::GetFrontPlane() const noexcept
	{
		return QXplane(_ref.k, _ref.o + _ref.k * _halfSizes.z);
	}

	QXplane QXorientedBox::GetBackPlane() const noexcept
	{
		return QXplane(_ref.k * (-1), _ref.o - _ref.k * _halfSizes.z);
	}

	QXplane QXorientedBox::GetRightPlane() const noexcept
	{
		return QXplane(_ref.i, _ref.o + _ref.i * _halfSizes.x);
	}

	QXplane QXorientedBox::GetLeftPlane() const noexcept
	{
		return QXplane(_ref.i * (-1), _ref.o - _ref.i * _halfSizes.x);
	}

	QXint QXorientedBox::GetNumberPlaneGoodSide(const QXvec3& point) const noexcept
	{
		QXint counter{ 0 };

		if (GetTopPlane().GetSide(point))
			counter++;
		if (GetBottomPlane().GetSide(point))
			counter++;
		if (GetFrontPlane().GetSide(point))
			counter++;
		if (GetBackPlane().GetSide(point))
			counter++;
		if (GetRightPlane().GetSide(point))
			counter++;
		if (GetLeftPlane().GetSide(point))
			counter++;

		return counter;
	}

	QXsegment* QXorientedBox::GetSegmentsWithThisPoint(const QXvec3& point) const noexcept
	{
		QXsegment* array = new QXsegment[3];

		QXvec3 localPoint;

		localPoint.x = (point - _ref.o).Dot(_ref.i);
		localPoint.y = (point - _ref.o).Dot(_ref.j);
		localPoint.z = (point - _ref.o).Dot(_ref.k);

		QXvec3 p1(_ref.o + _ref.i * localPoint.x
			+ _ref.j * localPoint.y
			- _ref.k * localPoint.z);

		QXvec3 p2(_ref.o + _ref.i * localPoint.x
			- _ref.j * localPoint.y
			+ _ref.k * localPoint.z);

		QXvec3 p3(_ref.o - _ref.i * localPoint.x
								 + _ref.j * localPoint.y
								 + _ref.k * localPoint.z);

		array[0] = QXsegment(point, p1);
		array[1] = QXsegment(point, p2);
		array[2] = QXsegment(point, p3);

		return array;
	}
}