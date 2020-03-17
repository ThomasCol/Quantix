#include "Sphere.h"

namespace Math::Geometry
{
	QXsphere::QXsphere(const QXvec3& position, const QXfloat& radius):
		_position{position},
		_radius{radius}
	{}

	QXsphere::QXsphere(const QXsphere& sphere):
		_position{sphere._position},
		_radius{sphere._radius}
	{}

	QXsphere::QXsphere(QXsphere&& sphere):
		_position{std::move(sphere._position)},
		_radius{std::move(sphere._radius)}
	{}

	QXsphere& QXsphere::operator=(const QXsphere& sphere)
	{
		_position = sphere._position;
		_radius = sphere._radius;

		return *this;
	}
}
