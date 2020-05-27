#include "Core/Components/Animator.h"
#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Core::Components
{
	Animator* Animator::Copy() const noexcept
	{
		return new Animator(*this);
	}

	void Animator::Init(Core::DataStructure::GameComponent* object) noexcept
	{
		_object = object;
	}

	void Animator::Update(double frameTime)
	{
		_animation->Update(frameTime, ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform());
	}
}