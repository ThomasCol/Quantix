#include "Cylinder.h"

namespace Math::Geometry
{
	#pragma region Constructors
	QXcylinder::QXcylinder(const QXsegment& segment, const QXfloat& radius) noexcept:
		_segment(segment),
		_radius{radius}
	{}

	QXcylinder::QXcylinder(const QXcylinder& cylinder) noexcept:
		_segment(cylinder._segment),
		_radius{cylinder._radius}
	{}

	QXcylinder::QXcylinder(QXcylinder&& cylinder) noexcept:
		_segment(std::move(cylinder._segment)),
		_radius{std::move(cylinder._radius)}
	{}

	#pragma endregion Constructors

	#pragma region Functions

	#pragma region Operators

	QXcylinder& QXcylinder::operator=(const QXcylinder& cylinder) noexcept
	{
		_segment = cylinder._segment;
		_radius = cylinder._radius;

		return *this;
	}

	QXcylinder& QXcylinder::operator=(QXcylinder&& cylinder) noexcept
	{
		_segment = std::move(cylinder._segment);
		_radius = std::move(cylinder._radius);

		return *this;
	}

	#pragma endregion Operators

	#pragma region Statics Functions
	#pragma endregion Statics Functions

	#pragma endregion Functions
}
