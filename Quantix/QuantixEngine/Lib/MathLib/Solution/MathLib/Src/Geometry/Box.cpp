#include "Box.h"

namespace Math::Geometry
{

	#pragma region Attributes

	QXbox::QXbox(const QXvec3& position, const QXfloat& x, const QXfloat& y, const QXfloat& z) noexcept:
		_position{position},
		_halfSizes{QXvec3(x, y, z)}
	{}

	QXbox::QXbox(const QXvec3& position, const QXvec3& sizes) noexcept :
		_position{position},
		_halfSizes{sizes}
	{}

	QXbox::QXbox(const QXbox& box) noexcept: 
		_position{box._position},
		_halfSizes{box._halfSizes}
	{}

	QXbox::QXbox(QXbox&& box) noexcept:
		_position{std::move(box._position)},
		_halfSizes{std::move(box._halfSizes)}
	{}

	#pragma endregion Attributes

	#pragma region Functions

	#pragma region Operators

	QXbox& QXbox::operator=(const QXbox& box) noexcept
	{
		_position = box._position;
		_halfSizes = box._halfSizes;

		return *this;
	}

	QXbox& QXbox::operator=(QXbox&& box) noexcept
	{
		_position = std::move(box._position);
		_halfSizes = std::move(box._halfSizes);
		return *this;
	}

	#pragma endregion Operators

	#pragma endregion Functions
}
