#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "Core/Physic/IPhysicType.h"
#include <PxPhysicsAPI.h>
#include "rttrEnabled.h"
#include "Core/MathHeader.h"
#include "Core/Physic/PhysicSetting.h"

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
		physx::PxShape* shape{ nullptr };
		Physic::IPhysicType* actorPhysic{ nullptr };
		
		EPhysXType physicType { EPhysXType::DEFAULT };
		ETypeShape typeShape { ETypeShape::DEFAULT };

		Physic::ShapeFlag shapeFlag;
		Physic::CollideGroup collideFilter;

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
		 * @brief Actualize actorPhysic
		 *
		 */
		void UpdateActorPhysic() noexcept;

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
		Math::QXvec3 GetPosition() noexcept;

		/**
		 * @brief Set the Position object
		 * 
		 * @param pos new position
		 */
		void SetPosition(Math::QXvec3 pos) noexcept;

		/**
		 * @brief Get the Rotation object
		 * 
		 * @return Math::QXquaternion Rotation of the Collider
		 */
		Math::QXquaternion GetRotation() noexcept;

		/**
		 * @brief Set the Rotation object
		 * 
		 * @param rot new Rotation
		 */
		void SetRotation(Math::QXquaternion rot) noexcept;

		/**
		 * @brief Set the My Filter Group object
		 * 
		 * @param newGroup 
		 */
		void SetMyFilterGroup(Physic::FilterGroup::Enum newGroup) noexcept;

		/**
		 * @brief Get the My Filter Group object
		 * 
		 * @return Physic::FilterGroup::Enum 
		 */
		Physic::FilterGroup::Enum GetMyFilterGroup() noexcept;

		/**
 		* @brief Set the Shape Flag Scene Query object
 		*	
 		* @param b Value of the flag
 		*/
		void SetShapeFlagSceneQuery(bool b) noexcept
		{
			shapeFlag.sceneQuery = b;
			shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Scene Query object
		 *
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagSceneQuery() noexcept { return shapeFlag.sceneQuery; };

		/**
		 * @brief Set the Shape Flag Simulation object
		 *
		 * @param b Value of the flag
		 */
		void SetShapeFlagSimulation(bool b) noexcept
		{
			if (b && GetShapeFlagTrigger())
				return;

			shapeFlag.simulation = b;
			shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Simulation object
		 *
		 * @return true Flag is at true
		 * @return false  Flag is at false
		 */
		bool GetShapeFlagSimulation() noexcept { return shapeFlag.simulation; };

		/**
		 * @brief Set the Shape Flag Trigger object
		 *
		 * @param b Value of the Flag
		 */
		void SetShapeFlagTrigger(bool b) noexcept
		{
			if (b && GetShapeFlagSimulation())
				return;

			shapeFlag.trigger = b;
			shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Trigger object
		 *
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagTrigger() noexcept { return shapeFlag.trigger; };

		/**
		 * @brief Set the Shape Flag Visualization object
		 *
		 * @param b Value of the Flag
		 */
		void SetShapeFlagVisualization(bool b) noexcept
		{
			shapeFlag.visualization = b;
			shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, b);
		}

		/**
		 * @brief Get the Shape Flag Visualization object
		 *
		 * @return Value of the flag
		 */
		bool GetShapeFlagVisualization() noexcept { return shapeFlag.visualization; };

		/**
		 * @brief Get the Collide Filter Pawn object
		 * 
		 * @return true if this collide with pawn
		 */
		bool GetCollideFilterPawn() noexcept { return collideFilter.pawn; };

		/**
		 * @brief Get the Collide Filter Mine object
		 * 
		* @return true if this collide with Mine
		 */
		bool GetCollideFilterMine() noexcept { return collideFilter.mine; };

		/**
		 * @brief Get the Collide Filter Mine object
		 * 
		* @return true if this collide with Crab
		 */
		bool GetCollideFilterCrab() noexcept { return collideFilter.crab; };

		/**
		 * @brief Set the Collide Filter Pawn object
		 * 
		 * @param b 
		 */
		void SetCollideFilterPawn(bool b) noexcept
		{
			collideFilter.pawn = b;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask = 0;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}

		/**
		 * @brief Set the Collide Filter Mine object
		 * 
		 * @param b 
		 */
		void SetCollideFilterMine(bool b) noexcept
		{
			collideFilter.mine = b;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask = 0;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}
		
		/**
		 * @brief Set the Collide Filter Crab object
		 * 
		 * @param b 
		 */
		void SetCollideFilterCrab(bool b) noexcept
		{
			collideFilter.crab = b;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask = 0;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}


#pragma endregion

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

