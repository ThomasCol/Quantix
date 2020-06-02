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
		QXbool toDestroy = false;

		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new GameObject3D object
		 * 
		 */
		GameObject3D() = default;

		/**
		 * @brief Construct a new GameObject3D object
		 * 
		 * @param pos 
		 * @param rot 
		 * @param sca 
		 */
		GameObject3D(const QXstring&, const Math::QXvec3& pos = Math::QXvec3(0, 0, 0), const Math::QXquaternion& rot = Math::QXquaternion(1, 0, 0, 0), const Math::QXvec3& sca = Math::QXvec3(1, 1, 1)) noexcept;

		/**
		 * @brief Construct a new GameObject3D object by copy
		 * 
		 * @param g3d 
		 */
		GameObject3D(const GameObject3D& g3d) noexcept;

		/**
		 * @brief Construct a new GameObject3D object by move
		 * 
		 * @param g3d 
		 */
		GameObject3D(GameObject3D&& g3d) noexcept;

		/**
		 * @brief Destroy the GameObject3D object
		 * 
		 */
		~GameObject3D() noexcept;
#pragma endregion Constructors/Destructor

#pragma region Methods

		/**
		 * @brief Add child in GameObject3D
		 *
		 * @param object
		 */
		inline void								AddChild(const GameObject3D* object) noexcept
		{
			_transform->AddChild(object->GetTransform());
		}

		/**
		 * @brief Update GameObject3D
		 *
		 * @param meshes
		 * @param colliders
		 * @param lights
		 * @param info
		 * @param isPlaying
		 */
		void									Update(std::vector<Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
			std::vector<Components::Light>& lights, Platform::AppInfo& info, QXbool isPlaying) override;

		/**
		 * @brief Update child GameObject3D
		 *
		 * @param meshes
		 * @param colliders
		 * @param lights
		 * @param parentObject
		 * @param info
		 * @param isPlaying
		 */
		void									Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
			std::vector<Components::Light>& lights, const GameObject3D* parentObject, Platform::AppInfo& info, QXbool isPlaying) noexcept;

		/**
		 * @brief Check Destroy GameObject
		 *
		 * @param info
		 */
		void									CheckDestroy(Platform::AppInfo& info) noexcept;

		/**
		 * @brief Start of GameObject3D
		 *
		 */
		void									Start() override;

		/**
		 * @brief Awake of GameObject3D
		 *
		 */
		void									Awake() override;

		/**
		 * @brief Destroy of Components
		 *
		 */
		void									Destroy() override;

		/**
		 * @brief Physics trigger
		 *
		 * @param other
		 */
		void									CallOnTrigger(GameObject3D* other) noexcept;

		/**
		 * @brief Physics contact
		 *
		 * @param other
		 * @param position
		 * @param normal
		 */
		void									CallOnContact(GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal) noexcept;

#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 *
		 * @param pos QXvec3
		 */
		void									SetGlobalPosition(Math::QXvec3 pos) noexcept;

		/**
		 * @brief Set the Global Rotation object
		 *
		 * @param rot QXvec3
		 */
		void									SetGlobalRotation(Math::QXquaternion rot) noexcept;

		/**
		* @brief Get the Global Position object
		*
		*/
		Math::QXvec3							GetGlobalPosition() const  noexcept { return _transform->GetGlobalPosition(); };

		/**
		* @brief Get the Global Rotation object
		*
		*/
		Math::QXquaternion						GetGlobalRotation() const  noexcept { return _transform->GetGlobalRotation(); };

		/**
		* @brief Get the Global Scale object
		*
		*/
		Math::QXvec3							GetGlobalScale() const  noexcept { return _transform->GetGlobalScale(); };

		/**
		* @brief Set the Local Position object
		*
		* @param pos QXvec3
		*/
		void									SetLocalPosition(Math::QXvec3 pos) noexcept;

		/**
		 * @brief Set the Local Rotation object
		 *
		 * @param rot QXvec3
		 */
		void									SetLocalRotation(Math::QXquaternion rot) noexcept;

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec3
		 */
		void									SetLocalScale(Math::QXvec3 scale) noexcept;

		/**
		* @brief Get the Local Position object
		*
		*/
		const Math::QXvec3& GetLocalPosition()  noexcept { return _transform->GetPosition(); };

		/**
		* @brief Get the Local Rotation object
		*
		*/
		const Math::QXquaternion& GetLocalRotation()  noexcept {
			return _transform->GetRotation();
		};

		/**
		* @brief Get the Local Scale object
		*
		*/
		const Math::QXvec3& GetLocalScale()  noexcept { return _transform->GetScale(); };

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec3
		 * @param rot QXvec3
		 * @param scale QXvec3
		 */
		void									SetTransformValue(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& scale) noexcept;

		/**
		 * @brief Set the Transform object
		 *
		 * @param transform
		 */
		inline void								SetTransform(Quantix::Physic::Transform3D* transform)  noexcept { _transform = transform; };

		/**
		 * @brief Get the Transform object
		 *
		 */
		Quantix::Physic::Transform3D* GetTransform() const  noexcept { return _transform; };
#pragma endregion Accessors
		/**
		 * @brief operator by copy
		 *
		 * @param object
		 * @return GameObject3D&
		 */
		GameObject3D& operator=(const GameObject3D& object) noexcept;
		#pragma endregion Methods

		CLASS_REGISTRATION(GameComponent);
	};
}

#endif // !_GAMEOBJECT3D_H_
