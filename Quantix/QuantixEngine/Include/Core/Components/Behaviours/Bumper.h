#ifndef __BUMPER_H__
#define __BUMPER_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Components\Rigidbody.h"

#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Bumper : public Quantix::Core::Components::Behaviour
	{
	public :

		Math::QXvec3 force = Math::QXvec3(0, 3, 0);

		Bumper() = default;
		Bumper(Quantix::Core::DataStructure::GameComponent * par);
		Bumper(const Bumper&) = default;
		Bumper(Bumper&&) = default;
		~Bumper() = default;

		Bumper* Copy() const override;


		void    OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}

#endif

