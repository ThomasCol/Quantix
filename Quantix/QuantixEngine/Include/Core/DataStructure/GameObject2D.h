#ifndef _GAMEOBJECT2D_H_
#define _GAMEOBJECT2D_H_

#include "Core/DataStructure/GameComponent.h"
#include "Physic/Transform2D.h"

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
		Quantix::Physic::Transform2D*		_transform;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameObject2D() noexcept;
		GameObject2D(const QXstring& name) noexcept;
		GameObject2D(const GameObject2D& g2d) noexcept;
		GameObject2D(GameObject2D&& g2d) noexcept;
		~GameObject2D();
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		void										Start() override;
		
		void										Awake() override;

		void										Update();

		void										Update(const GameObject2D* parentObject);

		template<class Archive>
		void save(Archive& archive) const
		{
			archive(_component);
		}

		template<class Archive>
		void load(Archive& archive)
		{
			archive(_component);
		}

		inline void									AddChild(const GameObject2D* object) { _transform->AddChild(object->GetTransform()); }

		#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 * 
		 * @param pos Math::QXvec2 pos
		 */
		void										SetGlobalPosition(Math::QXvec2 pos);

		/**
		 * @brief Set the Global Rotation object
		 * 
		 * @param rot QXfloat angle
		 */
		void										SetGlobalRotation(QXfloat rot);

		/**
		 * @brief Get the Global Position object
		 * 
		 * @return Math::QXvec2 position
		 */
	//	Math::QXvec2								GetGlobalPosition() const { return _transform.GetGlobalPosition(); };

		/**
		 * @brief Get the Global Rotation object
		 * 
		 * @return QXfloat rotation
		 */
	//	QXfloat										GetGlobalRotation() const { return _transform.GetGlobalRotation(); };

		/**
		 * @brief Set the Local Position object
		 * 
		 * @param pos Math::QXvec2 position
		 */
		void										SetLocalPosition(Math::QXvec2 pos);

		/**
		 * @brief Set the Local Rotation object
		 * 
		 * @param rot QXfloat rotation
		 */
		void										SetLocalRotation(QXfloat rot);

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec2
		 */
		void										SetLocalScale(Math::QXvec2 scale);

		/**
		 * @brief Get the Local Position object
		 * 
		 * @return Math::QXvec2 position
		 */
		const Math::QXvec2&							GetLocalPosition() const { return _transform->GetPosition();
		};

		/**
		 * @brief Get the Local Rotation object
		 *
		 * @return QXfloat rotation
		 */
		const QXfloat&								GetLocalRotation() const { return _transform->GetRotationAngle(); };

		/**
		 * @brief Get the Local Scale object
		 *
		 * @return Math::QXvec2 scale
		 */
		const Math::QXvec2&							GetLocalScale() const { return _transform->GetScale(); };

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec2 position
		 * @param rot QXfloat rotation
		 * @param scale QXvec2 scale
		 */
		void										SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale);

		/**
		 * @brief Get the Transform object
		 * 
		 * @return Transform2D transform
		 */
		Quantix::Physic::Transform2D*				GetTransform() const { return _transform; };
		#pragma endregion Accessors
		#pragma endregion Methods

		CLASS_REGISTRATION(GameComponent);
	};
}

#endif // !_GAMEOBJECT3D_H_