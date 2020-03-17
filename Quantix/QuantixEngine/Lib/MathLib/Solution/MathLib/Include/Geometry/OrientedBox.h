#ifndef __ORIENTEDBOX_H__
#define __ORIENTEDBOX_H__

#include "Box.h"
#include "Segment.h"
#include "Plane.h"
#include "Ref3.h"

namespace Math::Geometry
{
	/**
	 * @brief QXorientedBox class
	 */
	class QXorientedBox
	{
	private:
		#pragma region Attributes

		QXref3 _ref;
		QXvec3 _halfSizes;

		#pragma endregion Attributes

	public:
		#pragma region Constructors/Destructor

		/**
		 * @brief Construct a new QXorientedBox object
		 * 
		 * @param ref Value for _ref parameter QXref3() by default
		 * @param halfSizes Value for _halfSizes parameter QXvec3() by default
		 */
		QXorientedBox(const QXref3& ref = QXref3(), const QXvec3& halfSizes = QXvec3()) noexcept;

		/**
		 * @brief Construct a new QXorientedBox object
		 * 
		 * @param box QXorientedBox to copy
		 * @param offsetExtention 
		 */
		QXorientedBox(const QXorientedBox& box, const QXfloat& offsetExtention = 0.f) noexcept;

		/**
		 * @brief Construct a new QXorientedBox object
		 * 
		 * @param box QXorientedBox to move
		 */
		QXorientedBox(QXorientedBox&& box) noexcept;

		/**
		 * @brief Destroy the QXorientedBox object
		 */
		~QXorientedBox() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		#pragma region Operator

		/**
		 * @brief Operator = by copy
		 * 
		 * @param box to copy
		 * @return QXorientedBox& 
		 */
		QXorientedBox&	operator=(const QXorientedBox& box) noexcept;

		/**
		 * @brief Operator = by move
		 * 
		 * @param box Box to move
		 * @return QXorientedBox& Reference of the new Box 
		 */
		QXorientedBox& operator=(QXorientedBox&& box) noexcept;
		
		#pragma endregion Operator

		#pragma region Accessors

		/**
		 * @brief Get the Box object
		 * 
		 * @return Box 
		 */
		inline QXbox	GetBox() const  noexcept {return QXbox(_ref.o, _halfSizes);}

		/**
		 * @brief Get the Ref object
		 * 
		 * @return QXref3 
		 */
		inline QXref3	GetRef() const noexcept {return _ref;}

		/**
		 * @brief Set the Ref object
		 * 
		 * @return QXref3& 
		 */
		inline QXref3&	SetRef() noexcept {return _ref;}

		/**
		 * @brief Get the Half Sizes object
		 * 
		 * @return QXvec3 
		 */
		inline QXvec3	GetHalfSizes() const noexcept {return _halfSizes;}

		/**
		 * @brief Set the Half Sizes object
		 * 
		 * @return QXvec3& 
		 */
		inline QXvec3&	SetHalfSizes() noexcept {return _halfSizes;}

		/**
		 * @brief Get the AABB of the oriented box
		 * 
		 * @return QXBox 
		 */
		QXbox			GetAABB() const noexcept;

		/**
		 * @brief Get the Points object
		 * 
		 * @return QXvec3* 
		 */
		QXvec3*			GetPoints() const noexcept;

		/**
		 * @brief Get the Top Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetTopPlane() const noexcept;

		/**
		 * @brief Get the Bottom Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetBottomPlane() const noexcept;

		/**
		 * @brief Get the Front Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetFrontPlane() const noexcept;

		/**
		 * @brief Get the Back Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetBackPlane() const noexcept;

		/**
		 * @brief Get the Left Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetLeftPlane() const noexcept;

		/**
		 * @brief Get the Right Plane object
		 * 
		 * @return QXplane 
		 */
		QXplane			GetRightPlane() const noexcept;

		/**
		 * @brief Get the Number Plane Good Side object
		 * 
		 * @param point QXvec 
		 * @return QXint number of planes that are in the good side
		 */
		QXint			GetNumberPlaneGoodSide(const QXvec3& point) const noexcept;

		/**
		 * @brief Get the Segments With This Point object
		 * 
		 * @param point 
		 * @return QXsegment* between the point and the oriented box
		 */
		QXsegment*		GetSegmentsWithThisPoint(const QXvec3& point) const noexcept;
		#pragma endregion Accessors
		#pragma endregion Methods
	};
}



#endif
