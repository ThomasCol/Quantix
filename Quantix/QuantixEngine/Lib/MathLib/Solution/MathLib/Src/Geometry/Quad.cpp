#include "Quad.h"

namespace Math::Geometry
{
	#pragma region Constructors

	QXquad::QXquad(const QXvec3& position, const QXvec3& i, const QXvec3& j, const QXvec3& k,
			const QXfloat& x, const QXfloat& y) noexcept :
		_ref {QXref3(position, i, j, k)},
		_halfSizes {QXvec2(x, y)}
	{}

	QXquad::QXquad(const QXref3& ref, const QXvec2& halfSizes) noexcept :
		_ref {ref},
		_halfSizes {halfSizes}
	{}

	QXquad::QXquad(const QXquad& quad) noexcept :
		_ref {quad._ref},
		_halfSizes {quad._halfSizes}
	{}

	QXquad::QXquad(QXquad&& quad) noexcept:
		_ref {std::move(quad._ref)},
		_halfSizes {std::move(quad._halfSizes)}
	{}

	#pragma endregion Constructors

	#pragma region Functions

	#pragma region Operators

	QXquad& QXquad::operator=(const QXquad& quad) noexcept
	{
		_ref = quad._ref;
		_halfSizes = quad._halfSizes;

		return *this;
	}

	QXquad& QXquad::operator=(QXquad&& quad) noexcept
	{
		_ref = std::move(quad._ref);
		_halfSizes = std::move(quad._halfSizes);

		return *this;
	}
	#pragma endregion Operators
	#pragma endregion Functions
}
