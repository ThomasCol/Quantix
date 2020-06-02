#ifndef _GAMEOBJECT2D_H_
#define _GAMEOBJECT2D_H_

#include "Core/DataStructure/GameComponent.h"
#include "Core/Physic/Transform2D.h"

namespace Quantix::Core::DataStructure
{
	/**
	 * @brief class GameObject2D
	 * 
	 */
	class QUANTIX_API GameObject2D : public GameComponent
	{
	protected:
		#pragma region Attributes
		Quantix::Core::Physic::Transform2D*		_transform;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new GameObject2D object
		 * 
		 */
		GameObject2D() noexcept;

		/**
		 * @brief Construct a new GameObject2D object
		 * 
		 * @param name 
		 */
		GameObject2D(const QXstring& name) noexcept;

		/**
		 * @brief Construct a new GameObject2D object by copy
		 * 
		 * @param g2d 
		 */
		GameObject2D(const GameObject2D& g2d) noexcept;

		/**
		 * @brief Construct a new GameObject2D object by move
		 * 
		 * @param g2d 
		 */
		GameObject2D(GameObject2D&& g2d) noexcept;

		/**
		 * @brief Destroy the GameObject2D object
		 * 
		 */
		~GameObject2D() noexcept;
#pragma endregion Constructors/Destructor

#pragma region Methods

		/**
		 * @brief Start of the GameObject2D
		 *
		 */
		void										Start() override;

		/**
		 * @brief Awake of the GameObject2D
		 *
		 */
		void										Awake() override;

		/**
		 * @brief Update of the GameObject2D
		 *
		 */
		void										Update() noexcept;

		/**
		 * @brief Update of child of GameObject2D
		 *
		 * @param parentObject
		 */
		void										Update(const GameObject2D* parentObject) noexcept;

		/**
		 * @brief Add child in GameObject2D
		 *
		 * @param object
		 */
		inline void									AddChild(const GameObject2D* object)  noexcept { _transform->AddChild(object->GetTransform()); }

#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 *
		 * @param pos Math::QXvec2 pos
		 */
		void										SetGlobalPosition(Math::QXvec2 pos) noexcept;

		/**
		 * @brief Set the Global Rotation object
		 *
		 * @param rot QXfloat angle
		 */
		void										SetGlobalRotation(QXfloat rot) noexcept;

		/**
		 * @brief Set the Local Position object
		 *
		 * @param pos Math::QXvec2 position
		 */
		void										SetLocalPosition(Math::QXvec2 pos) noexcept;

		/**
		 * @brief Set the Local Rotation object
		 *
		 * @param rot QXfloat rotation
		 */
		void										SetLocalRotation(QXfloat rot) noexcept;

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec2
		 */
		void										SetLocalScale(Math::QXvec2 scale) noexcept;

		/**
		 * @brief Get the Local Position object
		 *
		 * @return Math::QXvec2 position
		 */
		const Math::QXvec2&							GetLocalPosition() const  noexcept {
			return _transform->GetPosition();
		};

		/**
		 * @brief Get the Local Rotation object
		 *
		 * @return QXfloat rotation
		 */
		const QXfloat&								GetLocalRotation() const  noexcept { return _transform->GetRotationAngle(); };

		/**
		 * @brief Get the Local Scale object
		 *
		 * @return Math::QXvec2 scale
		 */
		const Math::QXvec2&							GetLocalScale() const  noexcept { return _transform->GetScale(); };

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec2 position
		 * @param rot QXfloat rotation
		 * @param scale QXvec2 scale
		 */
		void										SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale) noexcept;

		/**
		 * @brief Get the Transform object
		 *
		 * @return Transform2D transform
		 */
		Quantix::Core::Physic::Transform2D*			GetTransform() const noexcept{ return _transform; };
		#pragma endregion Accessors
		#pragma endregion Methods

		CLASS_REGISTRATION(GameComponent);
	};
}

#endif // !_GAMEOBJECT3D_H_
