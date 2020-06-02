#include <iostream>

#include "Core/Physic/IPhysicType.h"
#include "Core/Physic/PhysicStatic.h"
#include "Core/Physic/PhysicDynamic.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Physic::IPhysicType>("IPhysicType")
	.constructor<>()
	.constructor<Quantix::Core::Physic::ETypePhysic>()
	.constructor<const Quantix::Core::Physic::IPhysicType&>()
	.constructor<Quantix::Core::Physic::IPhysicType&&>()
	.enumeration<Quantix::Core::Physic::ETypePhysic>("ETypePhysic")
					 (rttr::value("None", Quantix::Core::Physic::ETypePhysic::NONE),
					 rttr::value("Dynamic", Quantix::Core::Physic::ETypePhysic::DYNAMIC),
					 rttr::value("Static", Quantix::Core::Physic::ETypePhysic::STATIC))
	.property("Type", &Quantix::Core::Physic::IPhysicType::type);
}

namespace Quantix::Core::Physic
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

