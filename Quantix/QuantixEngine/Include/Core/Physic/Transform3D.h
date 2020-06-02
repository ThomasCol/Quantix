#ifndef __TRANSFORM3D_H__
#define __TRANSFORM3D_H__

#include <list>
#include <Quaternion.h>
#include <Vec3.h>
#include "Core/DLLHeader.h"

namespace Quantix::Core::DataStructure
{
	class GameObject3D;
}

namespace Quantix::Core::Physic
{
	/**
	 * @brief Space enum
	 *
	 */
	enum class QUANTIX_API Space
	{
		WORLD,
		LOCAL
	};

	/**
	 * @brief class Transform3D
	 *
	 */
	class QUANTIX_API Transform3D
	{
	private:

#pragma region Attributes

		Transform3D* _parent;
		Math::QXvec3								_globalPosition;
		Math::QXquaternion							_globalRotation;
		Math::QXvec3								_globalScale;
		Math::QXvec3								_position;
		Math::QXquaternion							_rotation;
		Math::QXvec3								_scale;
		Math::QXvec3								_forward;
		Math::QXvec3								_up;

		Math::QXmat4								_trs;
		Math::QXmat4								_trsLocal;

		std::list<Transform3D*>						_childs;

		Quantix::Core::DataStructure::GameObject3D* _gameObject;

		Space										_space;
		QXbool										_globalHasChanged;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Update the TRS of the Transform
		 */
		void	UpdateTRS() noexcept;

		/**
		 * @brief Update the Local TRS of the Transform
		 *
		 * @param parentTransform
		 */
		void	UpdateTRSLocal(const Transform3D* parentTransform) noexcept;

		/**
		 * @brief Update the Global Transform of the Transform
		 *
		 */
		void	UpdateGlobalTransform() noexcept;

#pragma endregion

	public:
#pragma region Constructors&Destructor

		/**
		 * @brief Construct a new 3D Transform object
		 */
		Transform3D() noexcept;

		/**
		 * @brief Construct a copy of the 3D Transform object
		 *
		 * @param copy Copy of the transform
		 */
		Transform3D(const Transform3D& copy) noexcept;

		/**
		 * @brief Construct a copy by rvalue of the 3D Transform object
		 *
		 * @param copy Copy by rvalue of the transform
		 */
		Transform3D(Transform3D&& copy) noexcept;

		/**
		 * @brief Construct a new 3D Transform object
		 *
		 * @param pos The Position of the transform
		 * @param rot The Rotation of the transform
		 * @param sca The Scale angle of the transform
		 */
		Transform3D(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& sca, Quantix::Core::DataStructure::GameObject3D* object) noexcept;

		/**
		 * @brief Construct a new 3D Transform object by rvalues
		 *
		 * @param pos The Position of the transform
		 * @param rot The Rotation of the transform
		 * @param sca The Scale angle of the transform
		 */
		Transform3D(Math::QXvec3&& pos, Math::QXquaternion&& rot, Math::QXvec3&& sca) noexcept;

		/**
		 * @brief Destroy the 3D Transform object
		 */
		~Transform3D() noexcept;

#pragma endregion

#pragma region Methods

#pragma region Getters&Setters

		/**
		 * @brief Get the parent of the current transform
		 *
		 * @return const Transform3D* Current Parent
		 */
		Transform3D* GetParent() const noexcept;

		/**
		 * @brief Get the position of the current transform
		 *
		 * @return const Math::QXvec3& Current Position
		 */
		const Math::QXvec3& GetPosition() noexcept;

		/**
		 * @brief Get the Global Position object
		 *
		 * @return const Math::QXvec3&
		 */
		const Math::QXvec3& GetGlobalPosition() noexcept;

		/**
		 * @brief Get the rotation of the current transform
		 *
		 * @return const Math::QXvec3& Current Rotation
		 */
		Math::QXquaternion& GetRotation() noexcept;

		/**
		 * @brief Get the Global Rotation object
		 *
		 * @return Math::QXquaternion&
		 */
		Math::QXquaternion& GetGlobalRotation() noexcept;

		/**
		 * @brief Get the scale of the current transform
		 *
		 * @return const Math::QXvec3& Current Scale
		 */
		const Math::QXvec3& GetScale() noexcept;

		/**
		 * @brief Get the Global Scale object
		 *
		 * @return const Math::QXvec3&
		 */
		const Math::QXvec3& GetGlobalScale() noexcept;

		/**
		 * @brief Get the Forward object
		 *
		 * @return const Math::QXvec3&
		 */
		const Math::QXvec3& GetForward() noexcept;

		/**
		 * @brief Get the Up object
		 *
		 * @return const Math::QXvec3&
		 */
		const Math::QXvec3& GetUp() noexcept;

		/**
		 * @brief Get the trs of the current transform
		 *
		 * @return const Math::QXmat4& Current TRS
		 */
		const Math::QXmat4& GetTRS() noexcept;

		/**
		 * @brief Get the Local TRS object
		 *
		 * @return const Math::QXmat4&
		 */
		inline const Math::QXmat4& GetLocalTRS()  noexcept { return _trsLocal; };

		/**
		 * @brief Set TRS
		 *
		 * @param trs
		 */
		void										SetTRS(Math::QXmat4& trs) noexcept;

		/**
		 * @brief Set the parent of the current transform
		 *
		 * @param newParent the new parent of the current transform
		 */
		void										SetParent(Transform3D* newParent) noexcept;

		/**
		 * @brief Set the position of the current transform
		 *
		 * @param newPos the new position of the current transform
		 */
		void										SetPosition(const Math::QXvec3& newPos) noexcept;

		/**
		 * @brief Set the Global Position object
		 *
		 * @param newPos
		 */
		void										SetGlobalPosition(const Math::QXvec3& newPos) noexcept;

		/**
		 * @brief Set the rotation of the current transform
		 *
		 * @param newPos the new rotation of the current transform
		 */
		void										SetRotation(const Math::QXquaternion& newRot) noexcept;

		/**
		 * @brief Set the Global Rotation object
		 *
		 * @param newRot
		 */
		void										SetGlobalRotation(const Math::QXquaternion& newRot) noexcept;

		/**
		 * @brief Set the scale of the current transform
		 *
		 * @param newPos the new scale of the current transform
		 */
		void										SetScale(const Math::QXvec3& newSca) noexcept;

		/**
		 * @brief Set the Global Scale object
		 *
		 * @param newSca
		 */
		void										SetGlobalScale(const Math::QXvec3& newSca) noexcept;

		/**
		 * @brief Set the Forward object
		 *
		 * @param newFor
		 */
		void										SetForward(const Math::QXvec3& newFor) noexcept;

		/**
		 * @brief Set the Up object
		 *
		 * @param newUp
		 */
		void										SetUp(const Math::QXvec3& newUp) noexcept;

		/**
		 * @brief Get the Object object
		 *
		 * @return Core::DataStructure::GameObject3D*
		 */
		inline Core::DataStructure::GameObject3D* GetObject() const  noexcept { return _gameObject; };

		/**
		 * @brief Get the Childs object
		 *
		 * @return std::list<Transform3D*>&
		 */
		inline std::list<Transform3D*>& GetChilds()  noexcept { return _childs; };

		/**
		 * @brief Set the Space object
		 *
		 * @param space
		 */
		void										SetSpace(Space space) noexcept;

		/**
		 * @brief Get the Space object
		 *
		 * @return Space
		 */
		inline Space								GetSpace()  noexcept { return _space; };

#pragma endregion

#pragma region Functions

		/**
		 * @brief Take the parent TRS to convert itself in global then make its children to the same
		 *
		 * @param trsParent The parent TRS to convert its own trs in global
		 */
		void										Update(Transform3D* parentTransform) noexcept;

		/**
		 * @brief Translate the current transform
		 *
		 * @param pos The position that it will go further
		 */
		void										Translate(const Math::QXvec3& pos) noexcept;

		/**
		 * @brief Rotate the current transform
		 *
		 * @param rot The rotation that it will turn further
		 */
		void										Rotate(const Math::QXquaternion& rot) noexcept;

		/**
		 * @brief Scale the current transform
		 *
		 * @param sca The scale that it will be further
		 */
		void										Scale(const Math::QXvec3& sca) noexcept;

		/**
		 * @brief Add a child to the current transform
		 *
		 * @param child The 3D transform child to add to the current transform
		 */
		void										AddChild(Transform3D* child) noexcept;

		/**
		 * @brief Remove a child to the current transform
		 *
		 * @param child The 3D transform child to remove from the current transform
		 */
		void										RemoveChild(Transform3D* toRemove) noexcept;

		/**
		 * @brief Detach the current transform from any parent
		 *
		 */
		void										Detach() noexcept;

		/**
		 * @brief Find a transform in the hierarchy
		 *
		 * @param toFind
		 * @return QXbool
		 */
		QXbool										FindTransform(Transform3D* toFind) noexcept;

#pragma endregion

#pragma region Operators

		/**
		* @brief Operator = for 3D transforms
		*
		* @param t Transform to copy
		* @return Transform3D& Reference to the current transform
		*/
		Transform3D& operator=(const Transform3D& t) noexcept;

		/**
		* @brief Operator = for 3D transforms
		*
		* @param t Transform to copy
		* @return Transform3D& Reference to the current transform
		*/
		Transform3D& operator=(Transform3D&& t) noexcept;

#pragma endregion

#pragma endregion

	};
}

#endif // __TRANSFORM3D_H__
