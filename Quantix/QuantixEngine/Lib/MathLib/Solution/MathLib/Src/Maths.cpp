#include "Maths.hpp"

namespace Math
{
    QXfloat QuadraticSolver(const QXfloat& a, const QXfloat& b, const QXfloat& c) noexcept
    {
        QXfloat delta {b * b - 4 * a * c};
        QXfloat doubleA = 2 * a;

        if (delta < 0)
            return -1;
        
        if (delta == 0)
            return -b / doubleA;

        QXfloat   sqrtDelta {(QXfloat)sqrt(delta)};
        QXfloat   first = (-b + sqrtDelta) / doubleA;
        QXfloat   second = (-b - sqrtDelta) / doubleA;

        if (first >= 0 && first <= 1)
        {
            if (second >= 0 && second <= 1)
            {
                if (second > first)
                    return first;

                return second;
            }
            return first;
        }
        if (second >= 0 && second <= 1)
            return second;

        return -1;
    }
}