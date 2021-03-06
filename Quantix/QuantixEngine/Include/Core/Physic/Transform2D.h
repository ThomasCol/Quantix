#ifndef __TRANSFORM2D_H__
#define __TRANSFORM2D_H__

#include <list>
#include <Type.h>
#include <Vec2.h>
#include <Mat4.h>
#include "Core/DLLHeader.h"

namespace Quantix::Core::DataStructure
{
	class GameObject2D;
}

namespace Quantix::Core::Physic
{
	class QUANTIX_API Transform2D
	{
	private:

#pragma region Attributes

		Transform2D* _parent;
		Math::QXvec2				_position;
		QXfloat						_rotationAngle;
		Math::QXvec2				_scale;

		Math::QXmat4				_trs;

		std::list<Transform2D*>		_childs;

		Quantix::Core::DataStructure::GameObject2D* _gameObject;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Update the TRS of the Transform
		 */
		void	UpdateTRS() noexcept;

#pragma endregion

	public:
#pragma region Constructors&Destructor

		/**
		 * @brief Construct a new 2D Transform object
		 */
		Transform2D() noexcept;

		/**
		 * @brief Construct a new 2D Transform object
		 *
		 * @param GameObject2D object
		 */
		Transform2D(Quantix::Core::DataStructure::GameObject2D* object) noexcept;

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
		Transform2D(const Math::QXvec2& pos, const QXfloat& rotAngle, const Math::QXvec2& sca) noexcept;

		/**
		 * @brief Construct a new 2D Transform object by rvalues
		 *
		 * @param pos The Position of the transform
		 * @param rotAngle The Rotation Angle of the transform
		 * @param sca The Scale angle of the transform
		 */
		Transform2D(Math::QXvec2&& pos, float&& rotAngle, Math::QXvec2&& sca) noexcept;

		/**
		 * @brief Destroy the 2D Transform object
		 */
		~Transform2D() noexcept;

#pragma endregion

#pragma region Methods

#pragma region Getters&Setters

		/**
		 * @brief Get the Parent object
		 *
		 * @return Transform2D*
		 */
		inline Transform2D* GetParent() const  noexcept { return _parent; };

		/**
		 * @brief Get the Object object
		 *
		 * @return Core::DataStructure::GameObject2D*
		 */
		inline Core::DataStructure::GameObject2D* GetObject() const  noexcept { return _gameObject; };

		/**
		 * @brief Get the Childs object
		 *
		 * @return std::list<Transform2D*>&
		 */
		inline std::list<Transform2D*>& GetChilds()  noexcept { return _childs; };

		/**
		 * @brief Get the position of the current transform
		 *
		 * @return const Math::QXvec2 Current Position
		 */
		const Math::QXvec2& GetPosition() noexcept;

		/**
		 * @brief Get the rotationAngle of the current transform
		 *
		 * @return const QXfloat& Current Rotation Angle
		 */
		const QXfloat& GetRotationAngle() noexcept;

		/**
		 * @brief Get the scale of the current transform
		 *
		 * @return const Math::QXvec2& Current Scale
		 */
		const Math::QXvec2& GetScale() noexcept;

		/**
		 * @brief Get the trs of the current transform
		 *
		 * @return const Math::QXmat4& Current TRS
		 */
		const Math::QXmat4& GetTRS() noexcept;

		/**
		 * @brief Set the position of the current transform
		 *
		 * @param newPos the new position of the current transform
		 */
		void										SetPosition(const Math::QXvec2& newPos) noexcept;

		/**
		 * @brief Set the rotation angle of the current transform
		 *
		 * @param newRot the new rotation angle of the current transform
		 */
		void										SetRotationAngle(const QXfloat& newRot) noexcept;

		/**
		 * @brief Set the scale of the current transform
		 *
		 * @param newSca the new scale of the current transform
		 */
		void										SetScale(const Math::QXvec2& newSca) noexcept;

		/**
		 * @brief Set the Parent object
		 *
		 * @param newParent
		 */
		void										SetParent(Transform2D* newParent) noexcept;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Take the parent TRS to convert itself in global then make its children to the same
		 *
		 * @param trsParent The parent TRS to convert its own trs in global
		 */
		void										Update(const Transform2D* parentTransform) noexcept;

		/**
		 * @brief Translate the current transform
		 *
		 * @param pos The position that it will go further
		 */
		void										Translate(const Math::QXvec2& pos) noexcept;

		/**
		 * @brief Rotate the current transform
		 *
		 * @param rot The rotation that it will turn further
		 */
		void										Rotate(const QXfloat& rot) noexcept;

		/**
		 * @brief Scale the current transform
		 *
		 * @param sca The scale that it will be further
		 */
		void										Scale(const Math::QXvec2& sca) noexcept;

		/**
		 * @brief Add a child to the current transform
		 *
		 * @param child The 2D transform child to add to the current transform
		 */
		void										AddChild(Transform2D* child) noexcept;

		/**
		 * @brief Find a transform in the hierarchy
		 *
		 * @param toFind
		 * @return QXbool
		 */
		QXbool										FindTransform(Transform2D* toFind) noexcept;

		/**
		 * @brief Remove a child
		 *
		 * @param toRemove
		 */
		void										RemoveChild(Transform2D* toRemove) noexcept;

#pragma endregion

#pragma region Operators

		/**
		 * @brief Operator = for 2D transforms
		 *
		 * @param t Transform to copy
		 * @return Transform2D& Reference to the current transform
		 */
		Transform2D& operator=(const Transform2D& t) noexcept;

		/**
		 * @brief Operator = for 2D transforms
		 *
		 * @param t Transform to copy
		 * @return Transform2D& Reference to the current transform
		 */
		Transform2D& operator=(Transform2D&& t) noexcept;

#pragma endregion

#pragma endregion

	};
}

#endif // __TRANSFORM2D_H__