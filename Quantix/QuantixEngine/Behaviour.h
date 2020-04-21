#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

namespace Quantix::Core::Components
{

	struct Behaviour : public virtual Core::DataStructure::Component
	{
		Behaviour() = default;
		Behaviour(Core::DataStructure::GameComponent* object);
		Behaviour(const Behaviour & behaviour) = default;
		Behaviour(Behaviour && behaviour) = default;
		virtual ~Behaviour() = default;

		inline virtual void	Start(Resources::ResourcesManager * rm) { (void)rm; };
		inline virtual void	Update(CRenderWindow * win, double frameTime) { (void)win; (void)frameTime; };
		//inline virtual void	OnCollision(Physics::Collision::Collider * collider) {};

		virtual void				Destroy() = 0;
	};

}

#endif

