#ifndef __KILLZONE_H__
#define __KILLZONE_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Killzone : public Quantix::Core::Components::Behaviour
	{
	public:

		Killzone() = default;
		Killzone(Quantix::Core::DataStructure::GameComponent * par);
		Killzone(const Killzone&) = default;
		Killzone(Killzone&&) = default;
		~Killzone() = default;

		Killzone* Copy() const override;
		void    OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) override;
		void    OnCollision(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif

