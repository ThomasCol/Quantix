#include "Gameplay/Arms.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Cube.h"

namespace Quantix::Gameplay
{
	void Arms::Awake()
	{
		_gameobject = static_cast<Core::DataStructure::GameObject3D*>(_object);
	}

	void Arms::Start()
	{}

	void Arms::Update(QXdouble deltaTime)
	{
		if (GetKey(QX_KEY_E) == Core::UserEntry::EKeyState::PRESSED)
			UseHands();
		if (GetKey(QX_KEY_F) == Core::UserEntry::EKeyState::PRESSED)
			UseIce();
	}

	void Arms::UseHands()
	{
		if (_isGrabbingObject)
			return Drop();
		else
			return Grab();
	}

	void Arms::Grab()
	{
		//Grab

		if (_gameobject)
		{
			//Cast a ray to check if a cube is near enough to be grabbed
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition(), _gameobject->GetTransform()->GetForward(), 10.f };

			if (ray.actorClosestBlock->GetLayer() == 8/*Layer?*/)// is a Cube
			{
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				if (cube->GetState() == ECubeState::DEFAULT)
				{
					cube->ChangeState(ECubeState::GRABBED);

					//Change hierarchy of the object
					_originOfGrabbedObject = ray.actorClosestBlock->GetTransform()->GetParent();
					_gameobject->AddChild(ray.actorClosestBlock);

					_grabbedObject = ray.actorClosestBlock;

					//Set new pos of Object
					_grabbedObject->SetGlobalPosition(_gameobject->GetGlobalPosition() + Math::QXvec3(0.f, 0.f, 5.f));
				}
			}
			else
				return;
		}
		else
			return;

		_isGrabbingObject = QX_TRUE;
	}

	void Arms::Drop()
	{
		//Drop

		_grabbedObject->GetComponent<Cube>()->ChangeState(ECubeState::DEFAULT);

		//Turn back Hierarchy
		_grabbedObject->GetTransform()->SetParent(_originOfGrabbedObject);

		_grabbedObject = nullptr;
		_originOfGrabbedObject = nullptr;

		_isGrabbingObject = QX_FALSE;
	}

	void Arms::UseIce()
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be frozen
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition(), _gameobject->GetTransform()->GetForward(), 100.f };

			if (ray.actorClosestBlock->GetLayer() == 8/*Layer?*/)// is a Cube
			{
				Core::Components::Rigidbody* rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				if (cube->GetState() != ECubeState::GRABBED)
				{
					//Detect if is already frozen or not
					if (rigid->GetRigidFlagKinematic())
					{
						cube->ChangeState(ECubeState::DEFAULT);
						UnFreeze(rigid);
					}
					else
					{
						cube->ChangeState(ECubeState::FROZEN);
						Freeze(rigid);
					}
				}
			}
		}
	}

	void	Arms::Freeze(Core::Components::Rigidbody* cube)
	{
		//Stop Kinematic
		cube->SetRigidFlagKinematic(false);
	}

	void	Arms::UnFreeze(Core::Components::Rigidbody* cube)
	{
		//Re-Activate Kinematic
		cube->SetRigidFlagKinematic(true);
	}

	//Questions to ask my teammates
	/*
	* Comment j'accède à la liste des layers pour comparer le layer actuel à ceux existants ?
	*/ 

	//TODO:
	/* 
	* 
	*/
}