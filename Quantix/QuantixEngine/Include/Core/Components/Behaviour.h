#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"
#include <iostream>

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;
	class GameObject3D;
}

namespace Quantix::Core::Components
{

	struct Behaviour : public virtual Core::DataStructure::Component
	{
		Behaviour() = default;
		Behaviour(Core::DataStructure::GameComponent* object);
		Behaviour(const Behaviour & behaviour) = default;
		Behaviour(Behaviour && behaviour) = default;
		virtual ~Behaviour() = default;

		//inline virtual void	Start(Core::DataStructure::ResourcesManager * rm) { (void)rm; };

		virtual void	Start() { /*std::cout << "start" << std::endl;*/ };
		virtual void	Update() { /*std::cout << "update" << std::endl;*/ };
		virtual void    OnContact(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) { std::cout << "OnContact" << std::endl; }
		virtual void    OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) { std::cout << "OnTrigger" << std::endl; }


		//inline virtual void	OnCollision(Physics::Collision::Collider * collider) {};

		//virtual void				Destroy() = 0;

		Behaviour* Copy() const;


		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component)
	};

}

#endif

