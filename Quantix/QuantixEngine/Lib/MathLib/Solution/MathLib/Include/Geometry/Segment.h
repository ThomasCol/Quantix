#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "Vec3.h"

namespace Math::Geometry
{
	class QXsegment
	{
	private:
		#pragma region Attributes
		QXvec3	_a;
		QXvec3	_b;
		#pragma endregion Attributes

	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new QXsegment object
		 * 
		 * @param a first point
		 * @param b second point
		 */
		QXsegment(const QXvec3& a = 0.f, const QXvec3 & b = 1.f);

		/**
		 * @brief Construct a new QXsegment object
		 * 
		 * @param seg QXsegment to copy
		 */
		QXsegment(const QXsegment& seg);

		/**
		 * @brief Construct a new QXsegment object
		 * 
		 * @param seg QXsegment to move
		 */
		QXsegment(QXsegment&& seg) noexcept;

		/**
		 * @brief Destroy the QXsegment object
		 * 
		 */
		~QXsegment() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		#pragma region Accessors

		/**
		 * @brief Get the Point A object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetPointA() const {return _a;}

		/**
		 * @brief Get the Point B object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetPointB() const {return _b;}

		/**
		 * @brief Get the Segment AB object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetSegmentAB() const {return _b - _a;}

		/**
		 * @brief Get the Segment BA object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetSegmentBA() const {return _a - _b;}

		/**
		 * @brief Get the Point object
		 * 
		 * @param t QXfloat ratio
		 * @return QXvec3 point on the segment
		 */
		inline QXvec3	GetPoint(const QXfloat& t) const {return _a + (_b - _a) * t;}
		#pragma endregion Accessors

		#pragma region Operator

		/**
		 * @brief Operator = by copy
		 * 
		 * @param seg QXsegment to copy
		 * @return QXsegment& 
		 */
		QXsegment&		operator=(const QXsegment& seg);
		#pragma endregion Operator
		#pragma endregion Methods
	};
}



#endif
