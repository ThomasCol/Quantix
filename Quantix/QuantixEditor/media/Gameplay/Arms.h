#ifndef __ARMS_H__
#define __ARMS_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Arms : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			QXbool								_isGrabbingObject;
			Physic::Transform3D*				_originOfGrabbedObject;
			Core::DataStructure::GameObject3D*	_grabbedObject;

			Core::DataStructure::GameObject3D*	_gameobject;

			#pragma endregion

			#pragma region Methods

			void	UseHands();
			void	Grab();
			void	Drop();
			void	UseIce();
			void	Freeze(Core::Components::Rigidbody* cube);
			void	UnFreeze(Core::Components::Rigidbody* cube);

			#pragma endregion
		
		public:

			#pragma region Methods

			void	Awake() override;
			void	Start() override;
			void	Update(QXdouble deltaTime) override;

			
			#pragma endregion
	};
}
#endif //__ARMS_H__