#include "Vec3.h"

#include <cmath>
#include <string>

#include "MathDefines.h"
#include "Mat4.h"
#include "Ref3.h"

namespace Math
{
#pragma region Attributes

    const QXvec3 QXvec3::zero       {0.f, 0.f, 0.f};
    const QXvec3 QXvec3::up         {0.f, 1.f, 0.f};
    const QXvec3 QXvec3::down       {0.f, -1.f, 0.f};
    const QXvec3 QXvec3::right      {1.f, 0.f, 0.f};
    const QXvec3 QXvec3::left       {-1.f, 0.f, 0.f};
    const QXvec3 QXvec3::forward    {0.f, 0.f, 1.f};
    const QXvec3 QXvec3::backward   {0.f, 0.f, -1.f};

#pragma endregion

#pragma region Constructors

    QXvec3::QXvec3(const QXfloat& x, const QXfloat& y, const QXfloat& z)  noexcept :
        r {x},
        g {y},
        b {z}
    {}

    QXvec3::QXvec3(const QXvec3& vector)  noexcept :
        x {vector.x},
        y {vector.y},
        z {vector.z}
    {}

    QXvec3::QXvec3(QXvec3&& vector)  noexcept :
        x {std::move(vector.x)},
        y {std::move(vector.y)},
        z {std::move(vector.z)}
    {}

#pragma endregion

#pragma region Operators

    QXvec3&   QXvec3::operator=(const QXvec3& vector) noexcept
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;

        return *this;
    }
    
    QXvec3&   QXvec3::operator=(QXvec3&& vector) noexcept
    {
        x = std::move(vector.x);
        y = std::move(vector.y);
        z = std::move(vector.z);

        return *this;
    }

    QXvec3&   QXvec3::operator+=(const QXvec3& vector) noexcept
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;

        return *this;
    }

    QXvec3    QXvec3::operator+(const QXvec3& vector) const noexcept
    {
        QXvec3 res;

        res.x = vector.x + x;
        res.y = vector.y + y;
        res.z = vector.z + z;

        return res;
    }

    QXvec3&   QXvec3::operator-=(const QXvec3& vector) noexcept
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;

        return *this;
    }

    QXvec3    QXvec3::operator-(const QXvec3& vector) const noexcept
    {
        QXvec3 res;

        res.x = x - vector.x;
        res.y = y - vector.y;
        res.z = z - vector.z;

        return res;
    }

    QXvec3    QXvec3::operator-() const noexcept
    {
        return {-x, -y, -z};
    }

    QXvec3&   QXvec3::operator/=(QXfloat value) noexcept
    {
        x /= value;
        y /= value;
        z /= value;

        return *this;
    }

    QXvec3    QXvec3::operator/(QXfloat value) const noexcept
    {
        QXvec3 res;

        res.x = x / value;
        res.y = y / value;
        res.z = z / value;

        return res;
    }

    QXvec3&   QXvec3::operator*=(QXfloat value) noexcept
    {
        x /= value;
        y /= value;
        z /= value;

        return *this;
    }

    QXvec3    QXvec3::operator*(QXfloat value) const noexcept
    {
        QXvec3 res;

        res.x = x * value;
        res.y = y * value;
        res.z = z * value;

        return res;
    }

    QXbool    QXvec3::operator==(const QXvec3& vector) const noexcept
    {
		float epsilon = 0.0001f;
        return fabs(x - vector.x) < epsilon && fabs(y - vector.y) < epsilon && fabs(z - vector.z) < epsilon;
    }

    QXbool    QXvec3::operator!=(const QXvec3& vector) const noexcept
    {
        return SqrLength() != vector.SqrLength();
    }

    QXbool    QXvec3::operator<(const QXvec3& vector) const noexcept
    {
        return SqrLength() < vector.SqrLength();
    }

    QXbool    QXvec3::operator<=(const QXvec3& vector) const noexcept
    {
        return SqrLength() <= vector.SqrLength();
    }

    QXbool    QXvec3::operator>(const QXvec3& vector) const noexcept
    {
        return SqrLength() > vector.SqrLength();
    }

    QXbool    QXvec3::operator>=(const QXvec3& vector) const noexcept
    {
        return SqrLength() >= vector.SqrLength();
    }

    QXfloat&   QXvec3::operator[](QXuint idx) noexcept
    {
		return e[idx];
    }

	const QXfloat   QXvec3::operator[](QXuint idx) const noexcept
	{
		switch (idx)
		{
		case 0: return x; break;

		case 1: return y; break;

		case 2: return z; break;

		default: return 0.f; break;
		}
	}

#pragma endregion

#pragma region Functions

    QXfloat   QXvec3::Angle(const QXvec3& vector) const noexcept
    {
		QXfloat len{ SqrLength() * vector.SqrLength() };
        if (len == 0.0f)
            return 0.0f;

		QXfloat div{ Dot(vector) / sqrt(len) };

        if (div > 1.0f)
            return 0.0f;
        else if (div < -1.0f)
            return (QXfloat)Q_PI;
        
        return acosf(div);
    }

    QXvec3    QXvec3::Cross(const QXvec3& vector) const noexcept
    {
        return {(y * vector.z) - (z * vector.y), (z * vector.x) - (x * vector.z), (x * vector.y) - (y * vector.x)};
    }

    QXfloat   QXvec3::Dot(const QXvec3& vector) const noexcept
    {
        return x * vector.x + y * vector.y + z * vector.z;
    }

	QXbool	QXvec3::IsCollinear(const QXvec3& vector) const noexcept
	{
		QXfloat res{ Dot(vector) };
		if (res == 1 || res == -1)
			return true;
		return false;
	}

	QXfloat QXvec3::Length() const noexcept
	{
		return sqrt(x * x + y * y + z * z);
	}

	QXvec3 QXvec3::WorldToLocal(const QXref3& ref) const noexcept
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
		return m * *this;

	}

	QXvec3 QXvec3::LocalToWorld(const QXref3& ref) const noexcept
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

		return m * *this;
	}

	QXvec3& QXvec3::Normalize() noexcept
	{
		QXfloat	size{ Length() };

		if (size == 0)
			return *this;

		x = x / size;
		y = y / size;
		z = z / size;

		return *this;
	}

	const QXvec3	QXvec3::Normalized() const noexcept
	{
		QXvec3	res;

		QXfloat size{ Length() };

		if (size == 0)
			return res;

		res.x = x / size;
		res.y = y / size;
		res.z = z / size;

		return res;
	}

	QXvec3& QXvec3::Scale(QXfloat value) noexcept
	{
		x = x * value;
		y = y * value;
		z = z * value;

		return *this;
	}

	QXvec3	QXvec3::Scale(QXfloat value) const noexcept
	{
		QXvec3	res;

		res.x = x * value;
		res.y = y * value;
		res.z = z * value;

		return res;
	}

	QXfloat QXvec3::SqrLength() const noexcept
	{
		return x * x + y * y + z * z;
	}

	QXstring QXvec3::ToString() const noexcept
	{
		QXstring vec = std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "\n";

		return vec;
	}

#pragma region Static Functions

	QXfloat QXvec3::Angle(const QXvec3& vector1, const QXvec3& vector2) noexcept
	{

		QXfloat len{ vector1.SqrLength() * vector2.SqrLength() };
		if (len == 0.0f)
			return 0.0f;

		QXfloat div{ vector1.Dot(vector2) / sqrt(len) };

		if (div > 1.0f)
			return 0.0f;
		else if (div < -1.0f)
			return (QXfloat)Q_PI;

		return acosf(div);
	}

	QXvec3 QXvec3::Center(const QXvec3& pointA, const QXvec3& pointB) noexcept
	{
		return pointA + (pointB - pointA) * 0.5;
	}

	QXvec3 QXvec3::Lerp(const QXvec3& vector1, const QXvec3& vector2, QXfloat ratio) noexcept
	{
		return vector1 + (vector2 - vector1) * ratio;
	}

	QXvec3 QXvec3::Vec3FromPoints(const QXvec3& point1, const QXvec3& point2) noexcept
	{
		return point1 - point2;
	}

#pragma endregion
#pragma endregion

	std::ostream& operator<<(std::ostream& stream, const QXvec3& vector) noexcept
	{
		stream << vector.x << ", " << vector.y << ", " << vector.z << std::endl;

		return stream;
	}
}

