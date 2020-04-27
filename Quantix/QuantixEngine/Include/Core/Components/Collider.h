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

		physx::PxShape* shape{ nullptr };
		EPhysXType physicType { EPhysXType::DEFAULT };
		Physic::IPhysicType* actorPhysic{ nullptr };

		Physic::ShapeFlag shapeFlag;

#pragma endregion

#pragma region Constructors
		ICollider() = default;
		ICollider(DataStructure::GameComponent* par);
		ICollider(const ICollider& col) noexcept;
		ICollider(ICollider&& col) noexcept;
		virtual ~ICollider() = default;
#pragma endregion

#pragma region Functions

#pragma region Operators

		ICollider& operator=(const ICollider& other) noexcept;
		ICollider& operator=(ICollider&& other) noexcept;

#pragma endregion

		void Init(DataStructure::GameComponent* par) override;

#pragma region Acessors 
		ICollider* Copy() const override;


		Math::QXvec3 GetPosition();
		void SetPosition(Math::QXvec3);

		Math::QXquaternion GetRotation();
		void SetRotation(Math::QXquaternion);

		void SetShapeFlagSceneQuery(bool b);
		bool GetShapeFlagSceneQuery();
		void SetShapeFlagSimulation(bool b);
		bool GetShapeFlagSimulation();
		void SetShapeFlagTrigger(bool b);
		bool GetShapeFlagTrigger();
		void SetShapeFlagVisualization(bool b);
		bool GetShapeFlagVisualization();

		void Remove();

#pragma endregion

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

