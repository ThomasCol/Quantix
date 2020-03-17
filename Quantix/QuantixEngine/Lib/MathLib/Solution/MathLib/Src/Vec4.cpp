#include "Vec4.h"

#include <math.h>

namespace Math
{
#pragma region Attributes

	const QXvec4	QXvec4::zero {0.f, 0.f, 0.f, 0.f};
	const QXvec4	QXvec4::up {0.f, 1.f, 0.f, 0.f};
	const QXvec4	QXvec4::down {0.f, -1.f, 0.f, 0.f};
	const QXvec4	QXvec4::left {-1.f, 0.f, 0.f, 0.f};
	const QXvec4	QXvec4::right {1.f, 0.f, 0.f, 0.f};
	const QXvec4	QXvec4::forward {0.0f, 0.0f, 1.0f, 0.f};
	const QXvec4	QXvec4::backward {0.0f, 0.0f, -1.0f, 0.f};

#pragma endregion

#pragma region Constructors

	QXvec4::QXvec4(const QXfloat& posX, const QXfloat& posY, const QXfloat& posZ, const QXfloat& posW) noexcept :
		x (posX),
		y (posY),
		z (posZ),
		w (posW)
	{
	}

	QXvec4::QXvec4(const QXvec3& vec, QXfloat posW) noexcept :
		x { vec.x },
		y { vec.y },
		z { vec.z },
		w { posW }
	{}

	QXvec4::QXvec4(const QXvec4& vec)  noexcept :
		x{ vec.x },
		y{ vec.y },
		z{ vec.z },
		w{ vec.w }
	{}

	QXvec4::QXvec4(QXvec4&& vec)  noexcept :
		x{ std::move(vec.x) },
		y{ std::move(vec.y) },
		z{ std::move(vec.z) },
		w{ std::move(vec.w) }
	{}

#pragma endregion

#pragma region Operators

	QXvec4& QXvec4::operator=(const QXvec4& vect) noexcept
	{
		x = vect.x;
		y = vect.y;
	    z = vect.z;
		w = vect.w;

		return *this;
	}

	QXvec4&	QXvec4::operator=(QXvec4&& vec)  noexcept
	{
		x = std::move(vec.x);
		y = std::move(vec.y);
		z = std::move(vec.z);
		w = std::move(vec.w);

		return *this;
	}

	
	QXvec4&	QXvec4::operator+=(const QXvec4& vect) noexcept
	{
		x += vect.x;
		y += vect.y;
	    z += vect.z;
		w += vect.w;

		return *this;
	}

	QXvec4	QXvec4::operator+(const QXvec4& vect) const noexcept
	{
		QXvec4	res;

		res.x = x + vect.x;
		res.y = y + vect.y;
	    res.z = z + vect.z;
		res.w = w + vect.w;

		return res;
	}

	QXvec4&	QXvec4::operator-=(const QXvec4& vect) noexcept
	{
		x -= vect.x;
		y -= vect.y;
	    z -= vect.z;
		w -= vect.w;

		return *this;
	}

	QXvec4	QXvec4::operator-(const QXvec4& vect) const noexcept
	{
		QXvec4	res;

		res.x = x - vect.x;
		res.y = y - vect.y;
	    res.z = z - vect.z;
		res.w = w - vect.w;

		return res;
	}

	QXvec4	QXvec4::operator-() const noexcept
	{
		QXvec4	res;

		res.x = -x;
		res.y = -y;
		res.z = -z;
		res.w = -w;

		return res;
	}

	QXvec4&	QXvec4::operator*=(QXfloat nb) noexcept
	{
		x *= nb;
		y *= nb;
	    z *= nb;
		w *= nb;

		return *this;
	}

	QXvec4	QXvec4::operator*(QXfloat nb) const noexcept
	{
		QXvec4	res;

		res.x = x * nb;
		res.y = y * nb;
	    res.z = z * nb;
		res.w = w * nb;

		return res;
	}

	QXvec4&	QXvec4::operator/=(QXfloat nb) noexcept
	{
		x /= nb;
		y /= nb;
	    z /= nb;
		w /= nb;

		return *this;
	}

	QXvec4	QXvec4::operator/(QXfloat nb) const noexcept
	{
		QXvec4	res;

		res.x = x / nb;
		res.y = y / nb;
	    res.z = z / nb;
		res.w = w / nb;

		return res;
	}

	QXbool	QXvec4::operator==(const QXvec4& vect) const noexcept
	{
		return SqrLength() == vect.SqrLength();
	}

	QXbool	QXvec4::operator!=(const QXvec4& vect) const noexcept
	{
		return SqrLength() != vect.SqrLength();
	}

	QXbool	QXvec4::operator<(const QXvec4& vect) const noexcept
	{
		return SqrLength() < vect.SqrLength();
	}

	QXbool	QXvec4::operator<=(const QXvec4& vect) const noexcept
	{
		return SqrLength() <= vect.SqrLength();
	}

	QXbool	QXvec4::operator>(const QXvec4& vect) const noexcept
	{
		return SqrLength() > vect.SqrLength();
	}

	QXbool	QXvec4::operator>=(const QXvec4& vect) const noexcept
	{
		return SqrLength() >= vect.SqrLength();
	}

	QXfloat& QXvec4::operator[](QXuint idx) noexcept
	{
		return e[idx];
	}

	const QXfloat QXvec4::operator[](QXuint idx) const noexcept
	{
		return e[idx];
	}

#pragma endregion

#pragma region Functions

	void 	QXvec4::Homogenize() noexcept
	{
		if (w == 0)
			return;

		x /= w;
		y /= w;
		z /= w;
	}

	QXfloat	QXvec4::Length() const noexcept
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	QXvec4	QXvec4::Normalize() const noexcept
	{
		QXvec4	res;

		QXfloat size{ Length() };

	    if (size == 0)
	    	return res;

		res.x = x / size;
		res.y = y / size;
	    res.z = z / size;
		res.w = w / size;

		return res;
	}

	QXvec4&	QXvec4::Normalize() noexcept
	{
		QXfloat	size{ Length() };

		if (size == 0)
	    	return *this;

		x = x / size;
		y = y / size;
	    z = z / size;
		w = w / size;

		return *this;
	}

	QXvec4	QXvec4::Scale(QXfloat nb) const noexcept
	{
		QXvec4	res;

		res.x = x * nb;
		res.y = y * nb;
	    res.z = z * nb;
		res.w = w * nb;

		return res;
	}

	QXvec4& QXvec4::Scale(QXfloat nb) noexcept
	{
		x = x * nb;
		y = y * nb;
	    z = z * nb;
		w = w * nb;

		return *this;
	}

	QXfloat	QXvec4::SqrLength() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	QXstring	QXvec4::ToString() const noexcept
	{
		QXstring vec = std::to_string(x) + ", " + std::to_string(y) + ", " +
		std::to_string(z) + ", " + std::to_string(w) + "\n";

		return vec;
	}

#pragma endregion
	
	std::ostream&	operator<<(std::ostream& os, const QXvec4& vect) noexcept
	{
		os << vect.x << ", " << vect.y << ", " << vect.z <<
								", " << vect.w << std::endl;

		return os;
	}

	QXstring	operator+(std::string& str, const QXvec4& vect) noexcept
	{
		QXstring	res = str + "x : " + std::to_string(vect.x) +
		" , y : " + std::to_string(vect.y) + " , z : " + std::to_string(vect.z) +
		" , w : " + std::to_string(vect.w);

		return res;
	}
}
