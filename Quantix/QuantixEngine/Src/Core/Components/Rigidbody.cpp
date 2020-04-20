#include "Core/Components/Rigidbody.h"
#include "Core/DataStructure/GameComponent.h"

//#include "PhysicHandler.h"
//#include "PhysicDynamic.h"

#include <iostream>

namespace Quantix::Core::Components
{

	Rigidbody::Rigidbody(DataStructure::GameComponent* par/*, PhysicHandler* handler*/) noexcept :
		Core::DataStructure::Component(par)//,
		//_actorPhysic{ handler->GetObject(_parent, true) }//,
		//_handler{ handler }
	{}

	Rigidbody::Rigidbody(const Rigidbody& src) noexcept :
		Core::DataStructure::Component(src),
		actorPhysic{ src.actorPhysic }//,
		//_handler{ src.handler }
	{}

	Rigidbody::Rigidbody(Rigidbody&& by_ref) noexcept :
		Core::DataStructure::Component(by_ref),
		actorPhysic{ std::move(by_ref.actorPhysic) }//,
		//_handler{ std::move(by_ref.handler) }
	{}

	void Rigidbody::AddForce(Math::QXvec3 vec) noexcept
	{
		//_actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z));
	}
}