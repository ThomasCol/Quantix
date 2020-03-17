#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>

#include "Mat4.h"
#include "Mat.h"
#include "Vec2.h"

namespace Math
{
    /**
     * @brief Solve an quadratic equation
     * 
     * @param a Value for coef in x^2
     * @param b Value for coef in x
     * @param c Value for const
     * @return QXQXfloat Quadratic solver
     */
    QXfloat   QuadraticSolver(const QXfloat& a, const QXfloat& b, const QXfloat& c) noexcept;
    
    /**
     * @brief Clamp method
     * 
     * @tparam T Type of variable
     * @param min Minimum limit
     * @param max Maximum limit
     * @param val Value to clamp
     */
    template<typename T>
    inline void Clamp(const T& min, const T& max, T& val) noexcept
    {
        if (val < min)
            val = min;

        if(val > max)
            val = max;
    }
    
    /**
     * @brief Clamp method
     * 
     * @tparam T Type of variable
     * @param min Minimum limit
     * @param max Maximum limit
     * @param val Value to clamp
     * @return T Result of the clamp in New T 
     */
    template<typename T>
    inline T   Clamp(const T& min, const T& max, const T& val)
    {
        if (val < min)
            return min;

        if (val > max)
            return max;

        return val;
    }
}

#endif //_MATH_H_
