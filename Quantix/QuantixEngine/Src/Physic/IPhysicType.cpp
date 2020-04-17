#include <iostream>

#include "Physic/IPhysicType.h"
//#include "Physic/PhysicStatic.h"
//#include "Physic/PhysicDynamic.h"

namespace Physic
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

	void IPhysicType::print()
	{
		/*if (type == ETypePhysic::STATIC)
			(dynamic_cast<PhysicStatic*>(this))->print();
		else if (type == ETypePhysic::DYNAMIC)
			(dynamic_cast<PhysicDynamic*>(this))->print();*/
	}

	ETypePhysic IPhysicType::GetType()
	{
		return type;
	}
}

