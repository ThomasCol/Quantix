#include "Core/Components/Animator.h"

namespace Quantix::Core::Components
{
	Animator* Animator::Copy() const noexcept
	{
		return new Animator(*this);
	}

	void Animator::Init(Core::DataStructure::GameComponent* object) noexcept
	{
		_object = object;
		_animations.insert(std::make_pair(StateAnimation::IDLE, nullptr));
		_animations.insert(std::make_pair(StateAnimation::RUN, nullptr));
		_animations.insert(std::make_pair(StateAnimation::JUMPSTART, nullptr));
		_animations.insert(std::make_pair(StateAnimation::JUMPLOOP, nullptr));
		_animations.insert(std::make_pair(StateAnimation::JUMPEND, nullptr));
	}

	void Animator::Update(StateAnimation stateToPlay)
	{
	//	_animations[stateToPlay]->Play(_object);
	}
}