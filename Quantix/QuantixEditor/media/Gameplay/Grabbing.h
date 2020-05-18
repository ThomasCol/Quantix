#ifndef __GRABBING_H__
#define __GRABBING_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"

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

			#pragma region Methods

			void	Awake() override;
			void	Start() override;
			void	Update(QXdouble deltaTime) override;

			void	Use();
			
			#pragma endregion
	};
}
#endif //__GRABBING_H__