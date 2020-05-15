#ifndef __CHARACTERCONTROLLER_H__
#define __CHARACTERCONTROLLER_H__

#include <Type.h>
#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"

#include "Physic/PhysicHandler.h"

#define GRAVITY Math::QXvec3(0, -9.81, 0)

namespace Quantix::Core::Components
{
	struct QUANTIX_API CharacterController : public Quantix::Core::DataStructure::Component
	{
		// pointeur de controlelr
		physx::PxCapsuleController* controller = nullptr;

		Math::QXvec3 _velocity;

		CharacterController() = default;
		CharacterController(const CharacterController& src) = default;
		CharacterController(CharacterController&& src) = default;
		~CharacterController() = default;

		CharacterController* Copy() const noexcept override;
		void	Init(Core::DataStructure::GameComponent* object) noexcept override;
		void	Destroy() noexcept override {};

		void Move(Math::QXvec3 vec, QXint minDist, QXfloat deltaTime);
		void Jump(Math::QXvec3 vec, QXint minDist, QXfloat deltaTime);
		QXbool CheckIsFalling();

		QXfloat GetRadius();
		void SetRadius(QXfloat f);

		QXfloat GetHeight();
		void SetHeight(QXfloat f);

		void Resize(QXfloat f);

		Math::QXvec3 GetUpDirection();
		void SetUpDirection(Math::QXvec3 vec);

		Math::QXvec3 GetPosition();
		void SetPosition(Math::QXvec3 v);

		Math::QXvec3 GetFootPosition();
		void SetFootPosition(Math::QXvec3 v);

		void SetNonWalkableMode(Physic::NonWalkableMode mode);
		Physic::NonWalkableMode GetNonWalkableMode();

		void SetClimbingMode(Physic::ClimbingMode mode);
		Physic::ClimbingMode GetClimbingMode();

		Math::QXvec3 GetLinearVelocity();

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

