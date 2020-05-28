#ifndef _GAMEOBJECT3D_H_
#define _GAMEOBJECT3D_H_

#include "Core/DataStructure/GameComponent.h"
#include "Physic/Transform3D.h"

namespace Quantix::Core::DataStructure
{
	/**
	 * @brief class GameObject3D
	 * 
	 */
	class QUANTIX_API GameObject3D : public GameComponent
	{
	protected:
		#pragma region Attributes
		Quantix::Physic::Transform3D*		_transform;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameObject3D() = default;
		GameObject3D(const QXstring&, const Math::QXvec3& pos = Math::QXvec3(0, 0, 0), const Math::QXquaternion& rot = Math::QXquaternion(1, 0, 0, 0), const Math::QXvec3& sca = Math::QXvec3(1, 1, 1)) noexcept;
		GameObject3D(const GameObject3D& g3d) noexcept;
		GameObject3D(GameObject3D&& g3d) noexcept;
		~GameObject3D();
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		inline void								AddChild(const GameObject3D* object)
		{ 
			_transform->AddChild(object->GetTransform()); 
		}

		void									Update(std::vector<Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
													std::vector<Components::Light>& lights, Platform::AppInfo& info, QXbool isPlaying) override;

		void									Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
													std::vector<Components::Light>& lights, const GameObject3D* parentObject, Platform::AppInfo& info, QXbool isPlaying);

		void									Start() override;
		
		void									Awake() override;

		void									Destroy() override;

		void									CallOnTrigger(GameObject3D* other);
		void									CallOnContact(GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal);

		#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 *
		 * @param pos QXvec3
		 */
		void									SetGlobalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Global Rotation object
		 *
		 * @param rot QXvec3
		 */
		void									SetGlobalRotation(Math::QXquaternion rot);

		/**
		* @brief Get the Global Position object
		*
		*/
		Math::QXvec3							GetGlobalPosition() const { return _transform->GetGlobalPosition(); };

		/**
		* @brief Get the Global Rotation object
		*
		*/
		Math::QXquaternion						GetGlobalRotation() const { return _transform->GetGlobalRotation(); };

		/**
		* @brief Get the Global Scale object
		*
		*/
		Math::QXvec3							GetGlobalScale() const { return _transform->GetGlobalScale(); };

		/**
		* @brief Set the Local Position object
		*
		* @param pos QXvec3
		*/
		void									SetLocalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Local Rotation object
		 *
		 * @param rot QXvec3
		 */
		void									SetLocalRotation(Math::QXquaternion rot);

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec3
		 */
		void									SetLocalScale(Math::QXvec3 scale);

		/**
		* @brief Get the Local Position object
		*
		*/
		const Math::QXvec3&						GetLocalPosition() { return _transform->GetPosition(); };

		/**
		* @brief Get the Local Rotation object
		*
		*/
		const Math::QXquaternion&				GetLocalRotation() { return _transform->GetRotation();
		};

		/**
		* @brief Get the Local Scale object
		*
		*/
		const Math::QXvec3&						GetLocalScale() { return _transform->GetScale(); };

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec3
		 * @param rot QXvec3
		 * @param scale QXvec3
		 */
		void									SetTransformValue(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& scale);

		inline void								SetTransform(Quantix::Physic::Transform3D* transform) { _transform = transform; };

		/**
		 * @brief Get the Transform object
		 *
		 */
		Quantix::Physic::Transform3D*			GetTransform() const { return _transform; };
		#pragma endregion Accessors
		GameObject3D&							operator=(const GameObject3D& object);
		#pragma endregion Methods

		CLASS_REGISTRATION(GameComponent);
	};
}

#endif // !_GAMEOBJECT3D_H_
