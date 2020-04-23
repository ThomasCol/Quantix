#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

#include "Physic/IPhysicType.h"
#include "Physic/PhysicHandler.h"
#include "Core/MathHeader.h"

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

		QXfloat GetMass();
		void SetMass(QXfloat);

		Math::QXvec3 GetLinearVelocity();
		void SetLinearVelocity(Math::QXvec3);

		Math::QXvec3 GetAngularVelocity();
		void SetAngularVelocity(Math::QXvec3);

#pragma endregion 

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

