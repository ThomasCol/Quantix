#ifndef __RAYCAST_H__
#define __RAYCAST_H__

#include "Core/DLLHeader.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure//GameObject3D.h"

namespace Quantix::Physic
{
	struct Raycast
	{
		bool status{ false };

		Math::QXvec3 normalClosestBlock;
		Math::QXvec3 positionClosestBlock;
		QXfloat distanceClosestBlock;
		Core::DataStructure::GameObject3D* actorClosestBlock;

		Raycast() = delete;
		Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax);
		Raycast(const Raycast& src) = default;
		Raycast(Raycast&& src) = default;
	};
}
#endif