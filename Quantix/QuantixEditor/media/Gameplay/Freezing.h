#ifndef __FREEZING_H__
#define __FREEZING_H__

#include "Core\Components\Behaviour.h"
#include "Core/Components/Rigidbody.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Freezing : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Methods

			void	Use();
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
#endif //__FREEZING_H__