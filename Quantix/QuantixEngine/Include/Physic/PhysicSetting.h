#ifndef __PHYSICSETTING_H__
#define __PHYSICSETTING_H__

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Physic
{
	struct QUANTIX_API RigidBodyFlag
	{

	};

	struct QUANTIX_API BaseFlag
	{

	};

	struct QUANTIX_API ActorFlag
	{
		bool disableGravity = false;
		bool disableSimulation = false;
		bool sendSleepNotifies = false;
		bool visualization = false;

		CLASS_REGISTRATION()
	};

	RTTR_PLUGIN_REGISTRATION
	{
		rttr::registration::class_<Quantix::Physic::ActorFlag>("ActorFlag")
		.constructor<>()
		.constructor<const Quantix::Physic::ActorFlag&>()
		.constructor<Quantix::Physic::ActorFlag&&>()
		.property("disableGravity", &Quantix::Physic::ActorFlag::disableGravity)
		.property("disableSimulation", &Quantix::Physic::ActorFlag::disableSimulation)
		.property("sendSleepNotifies", &Quantix::Physic::ActorFlag::sendSleepNotifies)
		.property("visualization", &Quantix::Physic::ActorFlag::visualization);
	}
}

#endif // !__PHYSICSETTING_H__
