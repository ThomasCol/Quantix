#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "Core/DataStructure/Component.h"
#include "Resources/Animation.h"
#include <map>

namespace Quantix::Core::Components
{
	class QUANTIX_API Animator : public virtual Core::DataStructure::Component
	{
	private:
		Quantix::Resources::Animation*		_animation;
	public:
		
		Animator() = default;
		Animator(const Animator& anim) = default;
		Animator(Animator&& anim) = default;
		~Animator() = default;


		Animator*		Copy() const noexcept override;
		void			Init(Core::DataStructure::GameComponent* object) noexcept override;
		void 			Destroy() noexcept override {};

		void			Update(double frameTime);
	};
}

#endif // !_ANIMATOR_H_