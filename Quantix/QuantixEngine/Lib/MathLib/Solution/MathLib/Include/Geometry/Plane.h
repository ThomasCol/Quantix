#ifndef __PLANE_H__
#define __PLANE_H__

#include <math.h>
#include "Vec3.h"
#include "Mat.h"

namespace Math::Geometry
{
	/**
	 * @brief QXplane class
	 */
	class QXplane
	{
	private:
		#pragma region Attributes
		QXvec3	_normal;
		QXfloat	_d;
		#pragma endregion Attributes

	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new QXplane object
		 * 
		 */
		QXplane();

		/**
		 * @brief Construct a new QXplane object
		 * 
		 * @param plane to copy
		 */
		QXplane(const QXplane& plane);

		/**
		 * @brief Construct a new QXplane object
		 * 
		 * @param plane to move 
		 */
		QXplane(QXplane&& plane);

		/**
		 * @brief Construct a new QXplane object
		 * 
		 * @param normal of the plane
		 * @param d distance
		 */
		QXplane(const QXvec3& normal, const QXfloat& d);

		/**
		 * @brief Construct a new QXplane object
		 * 
		 * @param p1 QXvec3 of the first point
		 * @param p2 QXvec3 of the second point
		 * @param p3 QXvec3 of the third point
		 */
		QXplane(const QXvec3& p1, const QXvec3& p2, const QXvec3& p3);

		/**
		 * @brief Construct a new QXplane object
		 * 
		 * @param normal of the plane
		 * @param p point on the plane
		 */
		QXplane(const QXvec3& normal, const QXvec3& p);

		/**
		 * @brief Destroy the QXplane object
		 * 
		 */
		~QXplane() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		/**
		 * @brief Get side of two vectors
		 * 
		 * @param p1 QXvec3
		 * @param p2 QXvec3
		 * @return QXbool 
		 */
		QXbool			SameSide(const QXvec3& p1, const QXvec3& p2) const;

		#pragma region Accessors
		/**
		 * @brief Get the Normal object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetNormal() const {return _normal;}

		/**
		 * @brief Get the Distance object
		 * 
		 * @return QXfloat 
		 */
		inline QXfloat	GetDistance() const {return _d;}

		/**
		 * @brief Get the Distance To Point object
		 * 
		 * @param p QXvec3
		 * @return QXfloat 
		 */
		QXfloat			GetDistanceToPoint(const QXvec3& p) const;

		/**
		 * @brief Get the Closest Point On Plane object
		 * 
		 * @param p QXvec3
		 * @return QXvec3 
		 */
		QXvec3			GetClosestPointOnPlane(const QXvec3& p) const;

		/**
		 * @brief Get the Side object
		 * 
		 * @param p QXvec3
		 * @return QXbool 
		 */
		QXbool			GetSide(const QXvec3& p) const;
		#pragma endregion Accessors

		#pragma region Static Methods

		/**
		 * @brief Get the point which is the intersection of three planes
		 * 
		 * @param plane1 first plane
		 * @param plane2 second plane
		 * @param plane3 third plane
		 * @return QXvec3 point
		 */
		static QXvec3	PlanesIntersection(const QXplane& plane1, const QXplane& plane2,
										const QXplane& plane3);
		#pragma endregion Static Methods

		#pragma region Operator

		/**
		 * @brief Operator = by copy
		 * 
		 * @param plane to copy
		 * @return QXplane& 
		 */
		QXplane& 			operator=(const QXplane& plane);
		#pragma endregion Operator
		#pragma endregion Methods
	};
}




#endif
