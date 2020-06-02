#include <iostream>

#include "Physic/IPhysicType.h"
#include "Physic/PhysicStatic.h"
#include "Physic/PhysicDynamic.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Physic::IPhysicType>("IPhysicType")
	.constructor<>()
	.constructor<Quantix::Physic::ETypePhysic>()
	.constructor<const Quantix::Physic::IPhysicType&>()
	.constructor<Quantix::Physic::IPhysicType&&>()
	.enumeration<Quantix::Physic::ETypePhysic>("ETypePhysic")
					 (rttr::value("None", Quantix::Physic::ETypePhysic::NONE),
					 rttr::value("Dynamic", Quantix::Physic::ETypePhysic::DYNAMIC),
					 rttr::value("Static", Quantix::Physic::ETypePhysic::STATIC))
	.property("Type", &Quantix::Physic::IPhysicType::type);
}

namespace Quantix::Physic
{
	IPhysicType::IPhysicType() noexcept :
		type{ ETypePhysic::NONE }
	{}

	IPhysicType::IPhysicType(ETypePhysic oType) noexcept :
		type{ oType }
	{}

	IPhysicType::IPhysicType(const IPhysicType& Pt) noexcept : 
		type{ Pt.type }
	{}

	IPhysicType::IPhysicType(IPhysicType&& pt) noexcept :
		type {std::move(pt.type)}
	{}

	ETypePhysic& IPhysicType::GetType() noexcept
	{
		return type;
	}
}

