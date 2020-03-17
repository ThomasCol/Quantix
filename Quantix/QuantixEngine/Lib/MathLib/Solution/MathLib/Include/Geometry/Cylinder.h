#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "Segment.h"

namespace Math::Geometry
{
	/**
	 * @brief Class for Cylinder
	 */
	class QXcylinder
	{
	private:

	#pragma region Attributes

		QXsegment	_segment;
		QXfloat	_radius;

	#pragma endregion Attributes

	public:

	#pragma region Constructors

		/**
		 * @brief Construct a new QXcylinder object
		 * 
		 * @param segment Value for _segment parameter Segment() by default
		 * @param radius Value for _radius parameter 1 by default
		 */
		QXcylinder(const QXsegment& segment = QXsegment(), const QXfloat& radius = 1.f) noexcept;

		/**
		 * @brief Construct a new QXcylinder object
		 * 
		 * @param cylinder Cylinder to copy
		 */
		QXcylinder(const QXcylinder& cylinder) noexcept;

		/**
		 * @brief Construct a new QXcylinder object
		 * 
		 * @param cylinder Cylinder to move
		 */
		QXcylinder(QXcylinder&& cylinder) noexcept;

		/**
		 * @brief Destroy the QXcylinder object
		 */
		~QXcylinder() = default;

	#pragma endregion Constructors

	#pragma region Functions

	#pragma region Operators

		/**
		 * @brief Operator = by copy
		 * 
		 * @param cylinder Cylinder to copy
		 * @return QXcylinder& Reference of the new Cylinder
		 */
		QXcylinder& operator=(const QXcylinder& cylinder) noexcept;

		/**
		 * @brief Operator = by move
		 * 
		 * @param cylinder Cylinder to move
		 * @return QXcylinder& Reference of the new Cylinder
		 */
		QXcylinder& operator=(QXcylinder&& cylinder) noexcept;
	
	#pragma endregion Operators

	#pragma region Statics Functions
	#pragma endregion Statics Functions

	#pragma region Accessors

		/**
		 * @brief Set the Segment object
		 * 
		 * @return Segment& 
		 */
		inline QXsegment&	SetSegment() { return _segment; }

		/**
		 * @brief Get the Segment object
		 * 
		 * @return Segment 
		 */
		inline QXsegment	GetSegment() const noexcept { return _segment; }

		/**
		 * @brief Set the Radius object
		 * 
		 * @return QXfloat& 
		 */
		inline QXfloat&	SetRadius() noexcept { return _radius; }

		/**
		 * @brief Get the Radius object
		 * 
		 * @return QXfloat 
		 */
		inline QXfloat	GetRadius() const noexcept { return _radius; }

		/**
		 * @brief Get the Square Radius object
		 * 
		 * @return QXfloat 
		 */
		inline QXfloat	GetSqrtRadius() const noexcept {return _radius * _radius;}

	#pragma endregion Accessors
	#pragma endregion Functions
	};
}


#endif
