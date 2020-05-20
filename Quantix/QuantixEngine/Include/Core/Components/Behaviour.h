#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"
#include "Core/MathHeader.h"
#include <iostream>

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;
	class GameObject3D;
}

namespace Quantix::Core::Components
{

	struct QUANTIX_API Behaviour : public virtual Core::DataStructure::Component
	{
		Behaviour() = default;
		Behaviour(Core::DataStructure::GameComponent* object);
		Behaviour(const Behaviour & behaviour) = default;
		Behaviour(Behaviour && behaviour) = default;
		virtual ~Behaviour() = default;

		//inline virtual void	Start(Core::DataStructure::ResourcesManager * rm) { (void)rm; };

		virtual void	Awake() {}
		virtual void	Start() {}
		virtual void	Update(QXdouble deltaTime) {}
		virtual void    OnCollision(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal) {}
		virtual void    OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) {}
		virtual void	Destroy() override {}

		//inline virtual void	OnCollision(Physics::Collision::Collider * collider) {};

		Behaviour* Copy() const;

		void Init(Core::DataStructure::GameComponent* object) override;


		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component)
	};

}

#endif

