#ifndef __ARMS_H__
#define __ARMS_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Components\Rigidbody.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Arms : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			QXbool								_isGrabbingObject;
			Physic::Transform3D*				_originOfGrabbedObject;
			Core::DataStructure::GameObject3D*	_grabbedObject;

			Core::DataStructure::GameObject3D*	_gameobject = nullptr;
			Core::Components::Rigidbody*		rigid = nullptr;

			Math::QXvec3 objectFrozenVelocity;
			#pragma endregion

			#pragma region Methods

			void	UseHands();
			void	Grab();
			void	Drop();
			void	UseIce();
			void	Freeze(Core::Components::Rigidbody* cube);
			void	UnFreeze(Core::Components::Rigidbody* cube);
			void	UsePunch();
			void	UseMagnet(QXbool positiveField);

			#pragma endregion
		
		public:

			Arms() = default;
			Arms(Quantix::Core::DataStructure::GameComponent * par);
			Arms(const Arms&) = default;
			Arms(Arms&&) = default;
			~Arms() = default;

			Arms* Copy() const override;

			#pragma region Methods

			void	Awake() override;
			void	Start() override;
			void	Update(QXdouble deltaTime) override;

			
			#pragma endregion
			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__ARMS_H__