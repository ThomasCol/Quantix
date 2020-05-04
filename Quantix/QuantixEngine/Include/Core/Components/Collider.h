#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "Physic/IPhysicType.h"
#include <PxPhysicsAPI.h>
#include "rttrEnabled.h"
#include "Core/MathHeader.h"
#include "Physic/PhysicSetting.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	enum class EPhysXType
	{
		DEFAULT,
		STATIC,
		DYNAMIC,
		COUNT
	};

	enum class ETypeShape
	{
		DEFAULT,
		SPHERE,
		CUBE, 
		CAPSULE,
		COUNT
	};

	struct QUANTIX_API ICollider : public virtual Core::DataStructure::Component
	{
#pragma region Attributes
		ETypeShape typeShape = ETypeShape::DEFAULT;
		physx::PxShape* shape{ nullptr };
		EPhysXType physicType { EPhysXType::DEFAULT };
		Physic::IPhysicType* actorPhysic{ nullptr };

		Physic::ShapeFlag shapeFlag;
		bool toRender{ true };
		Math::QXvec3 scale{ 1.f, 1.f, 1.f };

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new ICollider object
		 * 
		 */
		ICollider() = default;

		/**
		 * @brief Construct a new ICollider object
		 * 
		 * @param par Parent of the ICollider
		 */
		ICollider(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new ICollider object
		 * 
		 * @param col ICollider to copy
		 */
		ICollider(const ICollider& col) noexcept;

		/**
		 * @brief Construct a new ICollider object
		 * 
		 * @param col Collider To Move
		 */
		ICollider(ICollider&& col) noexcept;

		/**
		 * @brief Destroy the ICollider object
		 * 
		 */
		virtual ~ICollider() = default;
#pragma endregion

#pragma region Functions

#pragma region Operators

		/**
		 * @brief Operator = copy
		 * 
		 * @param other Collider to Copy
		 * @return ICollider& new Collider
		 */
		ICollider& operator=(const ICollider& other) noexcept;

		/**
		 * @brief Operator = move 
		 * 
		 * @param other Collider to move
		 * @return ICollider& new Collider
		 */
		ICollider& operator=(ICollider&& other) noexcept;

#pragma endregion

		/**
		 * @brief Copy new collider
		 * 
		 * @return ICollider* new collider
		 */
		ICollider* Copy() const override;

		/**
		 * @brief Init New Collider
		 * 
		 * @param par Parent of the Collider
		 */
		virtual void Init(DataStructure::GameComponent* par) override;

		/**
		 * @brief Destroy Collider
		 * 
		 */
		virtual void Destroy() override;

#pragma region Acessors 

		/**
		 * @brief Get the Position object
		 * 
		 * @return Math::QXvec3 Position of the Collider
		 */
		Math::QXvec3 GetPosition();

		/**
		 * @brief Set the Position object
		 * 
		 * @param pos new position
		 */
		void SetPosition(Math::QXvec3 pos);

		/**
		 * @brief Get the Rotation object
		 * 
		 * @return Math::QXquaternion Rotation of the Collider
		 */
		Math::QXquaternion GetRotation();

		/**
		 * @brief Set the Rotation object
		 * 
		 * @param rot new Rotation
		 */
		void SetRotation(Math::QXquaternion rot);

		/**
		 * @brief Set the Shape Flag Scene Query object
		 * 
		 * @param b Value of the flag
		 */
		void SetShapeFlagSceneQuery(bool b);

		/**
		 * @brief Get the Shape Flag Scene Query object
		 * 
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagSceneQuery();

		/**
		 * @brief Set the Shape Flag Simulation object
		 * 
		 * @param b Value of the flag
		 */
		void SetShapeFlagSimulation(bool b);

		/**
		 * @brief Get the Shape Flag Simulation object
		 * 
		 * @return true Flag is at true
		 * @return false  Flag is at false
		 */
		bool GetShapeFlagSimulation();

		/**
		 * @brief Set the Shape Flag Trigger object
		 * 
		 * @param b Value of the Flag
		 */
		void SetShapeFlagTrigger(bool b);

		/**
		 * @brief Get the Shape Flag Trigger object
		 * 
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagTrigger();

		/**
		 * @brief Set the Shape Flag Visualization object
		 * 
		 * @param b Value of the Flag
		 */
		void SetShapeFlagVisualization(bool b);

		/**
		 * @brief Get the Shape Flag Visualization object
		 * 
		 * @return Value of the flag 
		 */
		bool GetShapeFlagVisualization();

#pragma endregion

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

