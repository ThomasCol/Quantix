#include "Core/Components/CharacterController.h"
#include "Physic/PhysicSetting.h"
#include "Physic/Raycast.h"

#include "Core/Components/Camera.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CharacterController>("CharacterController")
	.constructor<>()
	.constructor<const Quantix::Core::Components::CharacterController&>()
	.constructor<Quantix::Core::Components::CharacterController&&>()
	.enumeration<Quantix::Physic::NonWalkableMode>("NonWalkableMode")
					 (rttr::value("PreventClimbing", Quantix::Physic::NonWalkableMode::PREVENTCLIMBING),
					 rttr::value("PreventClimbingAndForceSlide", Quantix::Physic::NonWalkableMode::PREVENTCLIMBINGANDFORCESLIDING))
	.enumeration<Quantix::Physic::ClimbingMode>("ClimbingMode")
					 (rttr::value("Constrained", Quantix::Physic::ClimbingMode::CONSTRAINED),
					 rttr::value("Easy", Quantix::Physic::ClimbingMode::EASY),
					 rttr::value("Last", Quantix::Physic::ClimbingMode::LAST))
	.property("Radius", &Quantix::Core::Components::CharacterController::GetRadius, &Quantix::Core::Components::CharacterController::SetRadius)
	.property("Height", &Quantix::Core::Components::CharacterController::GetHeight, &Quantix::Core::Components::CharacterController::SetHeight)
	.property("UpDirection", &Quantix::Core::Components::CharacterController::GetUpDirection, &Quantix::Core::Components::CharacterController::SetUpDirection)
	.property("Pos", &Quantix::Core::Components::CharacterController::GetPosition, &Quantix::Core::Components::CharacterController::SetPosition)
	.property("FootPos", &Quantix::Core::Components::CharacterController::GetFootPosition, &Quantix::Core::Components::CharacterController::SetFootPosition)
	.property("NonWalkableMode", &Quantix::Core::Components::CharacterController::GetNonWalkableMode, &Quantix::Core::Components::CharacterController::SetNonWalkableMode)
	.property("ClimbingMode", &Quantix::Core::Components::CharacterController::GetClimbingMode, &Quantix::Core::Components::CharacterController::SetClimbingMode);
}

namespace Quantix::Core::Components
{
	void CharacterController::Init(Core::DataStructure::GameComponent* object) noexcept
	{
		_object = object;
		_isDestroyed = QX_FALSE;
		_isEnable = QX_TRUE;

		controller = Physic::PhysicHandler::GetInstance()->CreateController(object);
		_velocity = Math::QXvec3(0, 0, 0);
	}

	CharacterController* CharacterController::Copy() const noexcept
	{
		return new CharacterController(*this);
	}

	void CharacterController::Destroy() noexcept
	{
		if (_object->GetComponent<Core::Components::Camera>())
			_object->GetComponent<Core::Components::Camera>()->_controller = nullptr;

		Physic::PhysicHandler::GetInstance()->CleanController(controller);
	}

	void CharacterController::Move(Math::QXvec3 vec, QXint minDist, QXfloat deltaTime) noexcept
	{
		physx::PxControllerFilters filters;
		
		physx::PxControllerCollisionFlags tmp = controller->move(physx::PxVec3(vec.x, vec.y, vec.z), (physx::PxF32)minDist, deltaTime, filters);
	}

	QXbool CharacterController::CheckIsFalling() noexcept
	{
		Physic::Raycast ray(GetFootPosition(), -GetUpDirection(), 0.01f);

		if (ray.actorClosestBlock)
			return QX_FALSE;
		return QX_TRUE;
	}

	QXfloat CharacterController::GetRadius() noexcept
	{
		return controller->getRadius();
	}

	void CharacterController::SetRadius(QXfloat f) noexcept
	{
		controller->setRadius(f);
	}

	QXfloat CharacterController::GetHeight() noexcept
	{
		return controller->getHeight();
	}

	void CharacterController::SetHeight(QXfloat f) noexcept
	{
		controller->setHeight(f);
		
	}

	void CharacterController::Resize(QXfloat f) noexcept
	{
		controller->resize(f);
	}

	Math::QXvec3 CharacterController::GetUpDirection() noexcept
	{
		physx::PxVec3 v = controller->getUpDirection();
		return Math::QXvec3(v.x, v.y, v.z);
	}

	void CharacterController::SetUpDirection(Math::QXvec3 v) noexcept
	{
		controller->setUpDirection(physx::PxVec3(v.x, v.y, v.z));
	}

	Math::QXvec3 CharacterController::GetPosition() noexcept
	{
		physx::PxExtendedVec3 v = controller->getPosition();
		return Math::QXvec3((QXfloat)v.x, (QXfloat)v.y, (QXfloat)v.z);
	}

	void CharacterController::SetPosition(Math::QXvec3 v) noexcept
	{
		controller->setPosition(physx::PxExtendedVec3(v.x, v.y, v.z));
	}

	Math::QXvec3 CharacterController::GetFootPosition() noexcept
	{
		physx::PxExtendedVec3 v = controller->getFootPosition();
		return Math::QXvec3((QXfloat)v.x, (QXfloat)v.y, (QXfloat)v.z);
	}

	void CharacterController::SetFootPosition(Math::QXvec3 v) noexcept
	{
		controller->setFootPosition(physx::PxExtendedVec3(v.x, v.y, v.z));
	}

	void CharacterController::SetNonWalkableMode(Physic::NonWalkableMode mode) noexcept
	{
		if (mode == Physic::NonWalkableMode::PREVENTCLIMBING)
			controller->setNonWalkableMode(physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING);
		else
			controller->setNonWalkableMode(physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING);
	}

	Physic::NonWalkableMode CharacterController::GetNonWalkableMode() noexcept
	{
		physx::PxControllerNonWalkableMode::Enum tmp = controller->getNonWalkableMode();
		if (tmp == physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING)
			return Physic::NonWalkableMode::PREVENTCLIMBING;
		else
			return Physic::NonWalkableMode::PREVENTCLIMBINGANDFORCESLIDING;
	}

	Math::QXvec3 CharacterController::GetLinearVelocity() noexcept
	{
		physx::PxVec3 v = controller->getActor()->getLinearVelocity();
		return Math::QXvec3(v.x, v.y, v.z);
	}

	void CharacterController::SetClimbingMode(Physic::ClimbingMode mode) noexcept
	{
		if (mode == Physic::ClimbingMode::CONSTRAINED)
			controller->setClimbingMode(physx::PxCapsuleClimbingMode::eCONSTRAINED);
		else if (mode == Physic::ClimbingMode::EASY)
			controller->setClimbingMode(physx::PxCapsuleClimbingMode::eEASY);
		else
			controller->setClimbingMode(physx::PxCapsuleClimbingMode::eLAST);
	}

	Physic::ClimbingMode CharacterController::GetClimbingMode() noexcept
	{
		physx::PxCapsuleClimbingMode::Enum tmp = controller->getClimbingMode();
		if (tmp == physx::PxCapsuleClimbingMode::eCONSTRAINED)
			return Physic::ClimbingMode::CONSTRAINED;
		else if (tmp == physx::PxCapsuleClimbingMode::eEASY)
			return Physic::ClimbingMode::EASY;
		else
			return Physic::ClimbingMode::LAST;
	}
}