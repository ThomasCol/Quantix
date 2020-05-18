#include "Gameplay/Freezing.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core/Components/Rigidbody.h"

namespace Quantix::Gameplay
{
	void Freezing::Awake()
	{}

	void Freezing::Start()
	{}

	void Freezing::Update(QXdouble deltaTime)
	{
		if (GetKey(QX_KEY_F) == Core::UserEntry::EKeyState::PRESSED)
			Use();
	}

	void Freezing::Use()
	{
		Core::DataStructure::GameObject3D* go = static_cast<Core::DataStructure::GameObject3D*>(_object);

		if (go)
		{
			Physic::Raycast	ray{ go->GetGlobalPosition(), go->GetTransform()->GetForward(), 10.f };

			if (ray.actorClosestBlock->GetLayer() == 8/*Layer?*/)// is a Cube
			{
				Core::Components::Rigidbody* rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();

				//Detect if is already frozen or not
				if (rigid->GetRigidFlagKinematic())
					UnFreeze(rigid);
				else
					Freeze(rigid);
			}
		}
	}

	void	Freezing::Freeze(Core::Components::Rigidbody* cube)
	{
		//Stop Kinematic
		cube->SetRigidFlagKinematic(false);
	}

	void	Freezing::UnFreeze(Core::Components::Rigidbody* cube)
	{
		//Re-Activate Kinematic
		cube->SetRigidFlagKinematic(true);
	}
}