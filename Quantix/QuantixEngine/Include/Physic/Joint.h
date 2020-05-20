#ifndef __JOINT_H__
#define __JOINT_H__

#include "Core/DLLHeader.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Type.h"

namespace Quantix::Physic
{
	struct QUANTIX_API Joint
	{
		// When a force apply on joint will be bigger than this, the joint break
		QXfloat breakForce = 1;

		// When a torque apply on joint will be bigger than this, the joint break
		QXfloat breakTorque = 1;
	};

}
#endif

