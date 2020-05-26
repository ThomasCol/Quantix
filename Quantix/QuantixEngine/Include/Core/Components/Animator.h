#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "Core/DataStructure/Component.h"
#include "Resources/Animation.h"
#include <map>

namespace Quantix::Core::Components
{
	enum class QUANTIX_API StateAnimation
	{
		IDLE = (1 << 0),
		RUN = (1 << 1),
		JUMPSTART = (1 << 2),
		JUMPLOOP = (1 << 3),
		JUMPEND = (1 << 4)
	};

	class QUANTIX_API Animator : public virtual Core::DataStructure::Component
	{
	private:
		std::map<StateAnimation, Quantix::Resources::Animation*>	_animations;
	public:
		
		Animator() = default;
		Animator(const Animator& anim) = default;
		Animator(Animator&& anim) = default;
		~Animator() = default;


		Animator*		Copy() const noexcept override;
		void			Init(Core::DataStructure::GameComponent* object) noexcept override;
		void 			Destroy() noexcept override {};

		void			Update(StateAnimation stateToPlay);
	};
}

#endif // !_ANIMATOR_H_