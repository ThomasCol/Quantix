#include <PxPhysicsAPI.h>
#include "Core/Physic/Raycast.h"
#include "Core/Physic/PhysicHandler.h"

namespace Quantix::Core::Physic
{
	Raycast::Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax) noexcept
	{
		Physic::PhysicHandler::GetInstance()->Raycast(origin, unitDir, distMax, *this);
	}
}