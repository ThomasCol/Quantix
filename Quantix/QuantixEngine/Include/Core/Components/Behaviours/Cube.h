#ifndef __CUBE_H__
#define __CUBE_H__

#include "Core\Components\Behaviour.h"

namespace Quantix::Gameplay
{
	enum class QUANTIX_API ECubeState
	{
		DEFAULT,
		GRABBED,
		FROZEN,
		MAGNET_NEG,
		MAGNET_POS,
	};

	class QUANTIX_API Cube : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			ECubeState	_state	{ ECubeState::DEFAULT };

			#pragma endregion

			#pragma region Methods

			void	Attract(QXdouble deltaTime);
			void	Reject(QXdouble deltaTime);

			#pragma endregion
		
		public:

			#pragma region Methods

			void		Awake() override;
			void		Start() override;
			void		Update(QXdouble deltaTime) override;

			void		ChangeState(ECubeState newState);
			inline ECubeState	GetState() { return _state; };
			
			#pragma endregion
	};
}
#endif //__CUBE_H__