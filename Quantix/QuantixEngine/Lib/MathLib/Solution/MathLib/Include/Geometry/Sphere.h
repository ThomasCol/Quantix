#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Vec3.h"


namespace Math::Geometry
{
	/**
	 * @brief QXsphere class
	 * 
	 */
	class QXsphere
	{
	private:
		#pragma region Attributes
		QXvec3	_position;
		QXfloat	_radius;
		#pragma endregion Attributes

	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a QXsphere object
		 * 
		 * @param position QXvec3 for the center
		 * @param radius QXfloat for the radius
		 */
		QXsphere(const QXvec3& position = QXvec3(0), const QXfloat& radius = 1.f);
		/**
		 * @brief Construct a QXsphere object
		 * 
		 * @param sphere QXsphere to copy
		 */
		QXsphere(const QXsphere& sphere);
		/**
		 * @brief Construct a QXsphere object
		 * 
		 * @param sphere QXsphere to move
		 */
		QXsphere(QXsphere&& sphere);
		/**
		 * @brief Destroy a QXsphere object
		 * 
		 */
		~QXsphere() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		#pragma region Accessors
		
		/**
		 * @brief Get Position
		 * 
		 * @return QXvec3 position of the center of the sphere
		 */
		inline QXvec3	GetPosition() const {return _position;}

		/**
		 * @brief Set Position
		 * 
		 * @return Reference QXvec3 position of the center of the sphere
		 */
		inline QXvec3&	SetPosition() {return _position;}

		/**
		 * @brief Get Radius
		 * 
		 * @return QXfloat radius of the sphere
		 */
		inline QXfloat	GetRadius() const {return _radius;}

		/**
		 * @brief Set Radius
		 * 
		 * @return Reference QXfloat radius of the sphere
		 */
		inline QXfloat&	SetRadius() {return _radius;}
		#pragma endregion Accessors

		#pragma region Operator
		
		/**
		 * @brief Operator = by move
		 * 
		 * @param sphere QXsphere to move
		 * @return QXsphere& Reference of current sphere
		 */
		QXsphere&			operator=(const QXsphere& sphere);
		#pragma endregion Operator
		#pragma endregion Methods
	};
}


#endif
