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
		QXfloat breakForce = 1;
		QXfloat breakTorque = 1;
	};

}
#endif

