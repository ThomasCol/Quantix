#include "Ref3.h"

#include "Mat4.h"

namespace Math
{

#pragma region Constructors

	QXref3::QXref3(const QXvec3& O, QXfloat AngleI, QXfloat AngleJ, QXfloat AngleK) noexcept :
		o{ O },
		i{ QXmat4::CreateFixedAngleEulerRotationMatrix(QXvec3(AngleI, AngleJ, AngleK)) * QXvec3::right },
		j{ QXmat4::CreateFixedAngleEulerRotationMatrix(QXvec3(AngleI, AngleJ, AngleK)) * QXvec3::up },
		k{ QXmat4::CreateFixedAngleEulerRotationMatrix(QXvec3(AngleI, AngleJ, AngleK)) * QXvec3::forward }
	{}

	QXref3::QXref3(const QXvec3& O, const QXvec3& I, const QXvec3& J, const QXvec3& K) noexcept :
		o {O},
		i {I.Normalized()},
		j {J.Normalized()},
		k {K.Normalized()}        
  {}

	QXref3::QXref3(const QXref3& ref) noexcept :
  		o {ref.o},
		i {ref.i},
		j {ref.j},
		k {ref.k}
	{}

	QXref3::QXref3(QXref3&& ref) noexcept :
		o {std::move(ref.o)},
		i {std::move(ref.i)},
		j {std::move(ref.j)},
		k {std::move(ref.k)}
	{}

  #pragma endregion

  #pragma region Operators

	QXref3&   QXref3::operator=(const QXref3& ref) noexcept
	{
		o = ref.o;
		i = ref.i;
		j = ref.j;
		k = ref.k;

		return *this;
	}

	QXref3& QXref3::operator=(QXref3&& ref) noexcept
	{
		o = std::move(ref.o);
		i = std::move(ref.i);
		j = std::move(ref.j);
		k = std::move(ref.k);

		return *this;
	}

	QXbool QXref3::operator==(const QXref3& ref) const noexcept
	{
		if (o == ref.o && i == ref.i && j == ref.j && k == ref.k)
		return true;
		return false;
	}

	QXref3& QXref3::operator*=(const QXmat4& m) noexcept
	{
		o = m * o;
		i = m * i;
		j = m * j;
		k = m * k;
		return *this;
	}

	QXref3 QXref3::operator*(const QXmat4& m) const noexcept
	{
		QXref3 res{ *this };
		res.o = m * res.o;
		res.i = m * res.i;
		res.j = m * res.j;
		res.k = m * res.k;
		return res;
	}

	QXbool QXref3::operator!=(const QXref3& ref) const noexcept
	{
		if (o != ref.o || i != ref.i || j != ref.j || k != ref.k)
		return true;
		return false;
	}

#pragma endregion

#pragma region Functions

	QXref3 QXref3::GlobalToLocal(const QXref3& ref) const noexcept
	{
		QXmat4 m;

		m[0][0] = ref.i.x;
		m[0][1] = ref.j.x;
		m[0][2] = ref.k.x;
		m[0][3] = ref.o.x;
		m[1][0] = ref.i.y;
		m[1][1] = ref.j.y;
		m[1][2] = ref.k.y;
		m[1][3] = ref.o.y;
		m[2][0] = ref.i.z;
		m[2][1] = ref.j.z;
		m[2][2] = ref.k.z;
		m[2][3] = ref.o.z;
		m[3][3] = 1;

		m = m.Inverse();

		QXref3 res{ *this };

		return res*m;
	}

	QXref3 QXref3::LocalToGlobal(const QXref3& ref) const noexcept
	{
		QXmat4 m;

		m[0][0] = ref.i.x;
		m[0][1] = ref.j.x;
		m[0][2] = ref.k.x;
		m[0][3] = ref.o.x;
		m[1][0] = ref.i.y;
		m[1][1] = ref.j.y;
		m[1][2] = ref.k.y;
		m[1][3] = ref.o.y;
		m[2][0] = ref.i.z;
		m[2][1] = ref.j.z;
		m[2][2] = ref.k.z;
		m[2][3] = ref.o.z;
		m[3][3] = 1;

		QXref3 res { *this };

		return res * m;
	}

	QXref3& QXref3::Rotate(const QXquaternion& quat) noexcept
	{
		i = quat * i;
		j = quat * j;
		k = quat * k;

		return *this;
	}

	QXref3 QXref3::Rotate(const QXquaternion& quat) const noexcept
	{
		QXref3 res{ *this };

		res.i = quat * res.i;
		res.j = quat * res.j;
		res.k = quat * res.k;

		return res;
	}

	QXref3& QXref3::Translate(const QXvec3& value) noexcept
	{
		o += value;

		return *this;
	}

	QXref3 QXref3::Translate(const QXvec3& value) const noexcept
	{
		QXref3 res{ *this };
		res.o += value;

		return res;
	}
  #pragma endregion
}
