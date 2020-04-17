#ifndef __TRANSFORM2D_H__
#define __TRANSFORM2D_H__

#include <vector>
#include <Type.h>
#include <Vec2.h>
#include <Mat4.h>

namespace Quantix::Physic
{
	class Transform2D
	{
		private:

		#pragma region Attributes

			Math::QXvec2				_position;
			QXfloat						_rotationAngle;
			Math::QXvec2				_scale;

			Math::QXmat4				_trs;

			std::vector<Transform2D>	_childs;

			//Pointer GameComponent

		#pragma endregion

		#pragma region Functions

			/**
			 * @brief Update the TRS of the Transform
			 */
			void	UpdateTRS();

		#pragma endregion

		public:
		#pragma region Constructors&Destructor

			/**
			 * @brief Construct a new 2D Transform object
			 */
			Transform2D();

			/**
			 * @brief Construct a copy of the 2D Transform object
			 *
			 * @param copy Copy of the transform
			 */
			Transform2D(const Transform2D& copy) noexcept;

			/**
			 * @brief Construct a copy by rvalue of the 2D Transform object
			 *
			 * @param copy Copy by rvalue of the transform
			 */
			Transform2D(Transform2D&& copy) noexcept;

			/**
			 * @brief Construct a new 2D Transform object
			 *
			 * @param pos The Position of the transform
			 * @param rotAngle The Rotation Angle of the transform
			 * @param sca The Scale angle of the transform
			 */
			Transform2D(const Math::QXvec2& pos, const QXfloat& rotAngle, const Math::QXvec2& sca);

			/**
			 * @brief Construct a new 2D Transform object by rvalues
			 *
			 * @param pos The Position of the transform
			 * @param rotAngle The Rotation Angle of the transform
			 * @param sca The Scale angle of the transform
			 */
			Transform2D(Math::QXvec2&& pos, float&& rotAngle, Math::QXvec2&& sca);

			/**
			 * @brief Destroy the 2D Transform object
			 */
			~Transform2D();

		#pragma endregion

		#pragma region Methods

		#pragma region Getters&Setters

			/**
			 * @brief Get the position of the current transform
			 *
			 * @return const Math::QXvec2 Current Position
			 */
			Math::QXvec2	GetPosition() const;

			/**
			 * @brief Get the rotationAngle of the current transform
			 *
			 * @return const QXfloat& Current Rotation Angle
			 */
			QXfloat			GetRotationAngle() const;

			/**
			 * @brief Get the scale of the current transform
			 *
			 * @return const Math::QXvec2& Current Scale
			 */
			Math::QXvec2	GetScale() const;

			/**
			 * @brief Get the trs of the current transform
			 *
			 * @return const Math::QXmat4& Current TRS
			 */
			Math::QXmat4	GetTRS() const;

			/**
			 * @brief Set the position of the current transform
			 *
			 * @param newPos the new position of the current transform
			 */
			void			SetPosition(const Math::QXvec2& newPos);

			/**
			 * @brief Set the rotation angle of the current transform
			 *
			 * @param newRot the new rotation angle of the current transform
			 */
			void			SetRotationAngle(const QXfloat& newRot);

			/**
			 * @brief Set the scale of the current transform
			 *
			 * @param newSca the new scale of the current transform
			 */
			void			SetScale(const Math::QXvec2& newSca);

		#pragma endregion

		#pragma region Functions

			/**
			 * @brief Take the parent TRS to convert itself in global then make its children to the same
			 *
			 * @param trsParent The parent TRS to convert its own trs in global
			 */
			void			Update(const Math::QXmat4& trsParent) const;

			/**
			 * @brief Translate the current transform
			 *
			 * @param pos The position that it will go further
			 */
			void			Translate(const Math::QXvec2& pos);

			/**
			 * @brief Rotate the current transform
			 *
			 * @param rot The rotation that it will turn further
			 */
			void			Rotate(const QXfloat& rot);

			/**
			 * @brief Scale the current transform
			 *
			 * @param sca The scale that it will be further
			 */
			void			Scale(const Math::QXvec2& sca);

			/**
			 * @brief Add a child to the current transform
			 *
			 * @param child The 2D transform child to add to the current transform
			 */
			void			AddChild(const Transform2D& child);

			/**
			 * @brief Add a child by rvalue to the current transform
			 *
			 * @param child The 2D transform child to add by rvalue to the current transform
			 */
			void			AddChild(Transform2D&& child);

		#pragma endregion

		#pragma region Operators

			/**
			 * @brief Operator = for 2D transforms
			 *
			 * @param t Transform to copy
			 * @return Transform2D& Reference to the current transform
			 */
			Transform2D&	operator=(const Transform2D& t) noexcept;

			/**
			 * @brief Operator = for 2D transforms
			 *
			 * @param t Transform to copy
			 * @return Transform2D& Reference to the current transform
			 */
			Transform2D&	operator=(Transform2D&& t) noexcept;

		#pragma endregion

		#pragma endregion

		};
	}

#endif // __TRANSFORM2D_H__