#include "Segment.h"

namespace Math::Geometry
{
	QXsegment::QXsegment(const QXvec3& a, const QXvec3& b) :
		_a{ a },
		_b{ b }
	{}

	QXsegment::QXsegment(const QXsegment& seg):
		_a{ seg._a },
		_b{ seg._b }
	{}

	QXsegment::QXsegment(QXsegment&& seg) noexcept:
		_a{ std::move(seg._a) },
		_b{ std::move(seg._b) }
	{}

	QXsegment& QXsegment::operator=(const QXsegment& seg)
	{
		_a = seg._a;
		_b = seg._b;

		return *this;
	}
}
