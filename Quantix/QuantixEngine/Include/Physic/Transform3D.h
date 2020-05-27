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

namespace Quantix::Physic
{
	enum class QUANTIX_API Space
	{
		WORLD,
		LOCAL
	};

	class QUANTIX_API Transform3D
	{
		private:

		#pragma region Attributes
			
			Transform3D*								_parent;
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
			void	UpdateTRS();

			void	UpdateTRSLocal(const Transform3D* parentTransform);

			void	UpdateGlobalTransform();

		#pragma endregion

		public:
		#pragma region Constructors&Destructor

			/**
			 * @brief Construct a new 3D Transform object
			 */
			Transform3D();

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
			Transform3D(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& sca, Quantix::Core::DataStructure::GameObject3D* object);

			/**
			 * @brief Construct a new 3D Transform object by rvalues
			 *
			 * @param pos The Position of the transform
			 * @param rot The Rotation of the transform
			 * @param sca The Scale angle of the transform
			 */
			Transform3D(Math::QXvec3&& pos, Math::QXquaternion&& rot, Math::QXvec3&& sca);

			/**
			 * @brief Destroy the 3D Transform object
			 */
			~Transform3D();

		#pragma endregion

		#pragma region Methods

		#pragma region Getters&Setters

			/**
			 * @brief Get the parent of the current transform
			 *
			 * @return const Transform3D* Current Parent
			 */
			Transform3D*								GetParent() const;
			
			/**
			 * @brief Get the position of the current transform
			 *
			 * @return const Math::QXvec3& Current Position
			 */
			const Math::QXvec3&							GetPosition();

			const Math::QXvec3&							GetGlobalPosition();

			/**
			 * @brief Get the rotation of the current transform
			 *
			 * @return const Math::QXvec3& Current Rotation
			 */
			Math::QXquaternion&							GetRotation();

			Math::QXquaternion&							GetGlobalRotation();

			/**
			 * @brief Get the scale of the current transform
			 *
			 * @return const Math::QXvec3& Current Scale
			 */
			const Math::QXvec3&							GetScale();

			const Math::QXvec3&							GetGlobalScale();

			const Math::QXvec3&							GetForward();

			const Math::QXvec3&							GetUp();

			/**
			 * @brief Get the trs of the current transform
			 *
			 * @return const Math::QXmat4& Current TRS
			 */
			const Math::QXmat4&							GetTRS();

			inline const Math::QXmat4&					GetLocalTRS() { return _trsLocal; };

			void										SetTRS(Math::QXmat4& trs);

			/**
			 * @brief Set the parent of the current transform
			 *
			 * @param newParent the new parent of the current transform
			 */
			void										SetParent(Transform3D* newParent);

			/**
			 * @brief Set the position of the current transform
			 *
			 * @param newPos the new position of the current transform
			 */
			void										SetPosition(const Math::QXvec3& newPos);

			void										SetGlobalPosition(const Math::QXvec3& newPos);

			/**
			 * @brief Set the rotation of the current transform
			 *
			 * @param newPos the new rotation of the current transform
			 */
			void										SetRotation(const Math::QXquaternion& newRot);

			void										SetGlobalRotation(const Math::QXquaternion& newRot);

			/**
			 * @brief Set the scale of the current transform
			 *
			 * @param newPos the new scale of the current transform
			 */
			void										SetScale(const Math::QXvec3& newSca);

			void										SetGlobalScale(const Math::QXvec3& newSca);

			void										SetForward(const Math::QXvec3& newFor);

			void										SetUp(const Math::QXvec3& newUp);

			inline Core::DataStructure::GameObject3D*	GetObject() const { return _gameObject; };

			inline std::list<Transform3D*>&				GetChilds() { return _childs; };

			void										SetSpace(Space space);
			inline Space								GetSpace() { return _space; };

		#pragma endregion

		#pragma region Functions

			/**
			 * @brief Take the parent TRS to convert itself in global then make its children to the same
			 *
			 * @param trsParent The parent TRS to convert its own trs in global
			 */
			void										Update(Transform3D* parentTransform);

			/**
			 * @brief Translate the current transform
			 *
			 * @param pos The position that it will go further
			 */
			void										Translate(const Math::QXvec3& pos);

			/**
			 * @brief Rotate the current transform
			 *
			 * @param rot The rotation that it will turn further
			 */
			void										Rotate(const Math::QXquaternion& rot);

			/**
			 * @brief Scale the current transform
			 *
			 * @param sca The scale that it will be further
			 */
			void										Scale(const Math::QXvec3& sca);

			/**
			 * @brief Add a child to the current transform
			 *
			 * @param child The 3D transform child to add to the current transform
			 */
			void										AddChild(Transform3D* child);

			/**
			 * @brief Remove a child to the current transform
			 *
			 * @param child The 3D transform child to remove from the current transform
			 */
			void										RemoveChild(Transform3D* toRemove);

			/**
			 * @brief Detach the current transform from any parent
			 *
			 */
			void										Detach();

			QXbool										FindTransform(Transform3D* toFind);
			template<class Archive>
			void save(Archive& archive) const
			{
				archive(_position, _rotation, _scale, _gameObject, _childs);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(_position, _rotation, _scale, _gameObject, _childs);
			}

		#pragma endregion

		#pragma region Operators

			/**
			 * @brief Operator = for 3D transforms
			 *
			 * @param t Transform to copy
			 * @return Transform3D& Reference to the current transform
			 */
			Transform3D&	operator=(const Transform3D& t) noexcept;

			/**
			 * @brief Operator = for 3D transforms
			 *
			 * @param t Transform to copy
			 * @return Transform3D& Reference to the current transform
			 */
			Transform3D&	operator=(Transform3D&& t) noexcept;

		#pragma endregion

		#pragma endregion

	};
}

#endif // __TRANSFORM3D_H__
