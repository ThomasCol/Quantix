#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

#include "Physic/IPhysicType.h"
#include "Physic/PhysicHandler.h"
#include "Core/MathHeader.h"

#include "Physic/PhysicSetting.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API Rigidbody : public virtual Core::DataStructure::Component
	{
#pragma region Attributes
		Physic::PhysicDynamic* actorPhysic{ nullptr };

		Physic::ActorFlag actorFlag;
		Physic::RigidBodyFlag rigidFlag;
		QXfloat mass {1.f};

#pragma endregion

#pragma region Constructors

		Rigidbody() = default;
		Rigidbody(DataStructure::GameComponent* par);
		Rigidbody(const Rigidbody& src) noexcept;
		Rigidbody(Rigidbody&& src) noexcept;
		~Rigidbody() noexcept = default;

#pragma endregion

#pragma region Functions

		void AddForce(Math::QXvec3 vec) noexcept;

#pragma endregion

#pragma region Accessors 
		Rigidbody* Copy() const;
		void Init(DataStructure::GameComponent* par);

		QXfloat GetMass();
		void SetMass(QXfloat);

		Math::QXvec3 GetLinearVelocity();
		void SetLinearVelocity(Math::QXvec3);

		Math::QXvec3 GetAngularVelocity();
		void SetAngularVelocity(Math::QXvec3);

		Math::QXvec3 GetTransformPosition();
		void SetTransformPosition(Math::QXvec3 v);

		Math::QXquaternion GetTransformRotation();
		void SetTransformRotation(Math::QXquaternion q);

		void SetActorFlagDisableGravity(bool b);
		bool GetActorFlagDisableGravity();
		void SetActorFlagDisableSimulation(bool b);
		bool GetActorFlagDisableSimulation();
		void SetActorFlagSendSleepNotifies(bool b);
		bool GetActorFlagSendSleepNotifies();
		void SetActorFlagVisualization(bool b);
		bool GetActorFlagVisualization();

		void SetRigidFlagCCD(bool b);
		bool GetRigidFlagCCD();
		void SetRigidFlagCCDFriction(bool b);
		bool GetRigidFlagCCDFriction();
		void SetRigidFlagSpeculativeCCD(bool b);
		bool GetRigidFlagSpeculativeCCD();
		void SetRigidFlagKinematic(bool b);
		bool GetRigidFlagKinematic();
		void SetRigidFlagRetainAcceleration(bool b);
		bool GetRigidFlagRetainAcceleration();
		void SetRigidFlagKineForQueries(bool b);
		bool GetRigidFlagKineForQueries();
		void SetRigidFlagPosePreview(bool b);
		bool GetActorFlagPosePreview();
		void SetActorFlagCCDMaxContactImpulse(bool b);
		bool GetActorFlagCCDMaxContactImpulse();

#pragma endregion 

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

