#ifndef __GRABBING_H__
#define __GRABBING_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"

#include "Physic/Transform3D.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Grabbing : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			QXbool								_isUsed;
			Physic::Transform3D*				_originOfObject;
			Core::DataStructure::GameObject3D*	_grabbedObject;

			#pragma endregion

			#pragma region Methods

			void	Grab();
			void	Drop();

			#pragma endregion
		
		public:

			Grabbing() = default;
			Grabbing(Quantix::Core::DataStructure::GameComponent* par);
			Grabbing(const Grabbing&) = default;
			Grabbing(Grabbing&&) = default;
			~Grabbing() = default;

			Grabbing* Copy() const override;
			//void Init(Core::DataStructure::GameComponent* object) override;
			//void Init(Core::DataStructure::GameComponent* object) override;

			#pragma region Methods

			void	Awake() override;
			void	Start() override;
			void	Update(QXdouble deltaTime) override;

			void	Use();
			
			#pragma endregion
			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__GRABBING_H__