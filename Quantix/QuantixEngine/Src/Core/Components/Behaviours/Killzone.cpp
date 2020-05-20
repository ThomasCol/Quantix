#include "Core/Components//Behaviours//Killzone.h"
#include "Core\DataStructure\GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::Killzone>("Killzone")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::Killzone&>()
		.constructor<Quantix::Gameplay::Killzone&&>();
}

namespace Quantix::Gameplay
{
	Killzone::Killzone(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	Killzone* Killzone::Copy() const
	{
		return new Killzone(*this);
	}

	void    Killzone::OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other)
	{
		if (other->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE)
			other->Destroy();
	}
	void   Killzone::OnCollision(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal)
	{
		if (other->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE)
			other->Destroy();
	}
}