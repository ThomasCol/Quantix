#include <PxPhysicsAPI.h>
#include "Physic/Raycast.h"
#include "Physic/PhysicHandler.h"

namespace Quantix::Physic
{
	Raycast::Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax)
	{
		physx::PxRaycastBuffer hitRaycast;                 // resultat du ray cast apres test

		Physic::PhysicHandler::GetInstance()->Raycast(origin, unitDir, distMax, *this);
	}
}