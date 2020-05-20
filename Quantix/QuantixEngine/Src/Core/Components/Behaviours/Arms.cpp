//#include "Core\Components\Behaviours\Arms.h"
#include "Core/Components/Behaviours/Arms.h"
#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core\Components\Behaviours\Cube.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::Arms>("Arms")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::Arms&>()
		.constructor<Quantix::Gameplay::Arms&&>();
}

namespace Quantix::Gameplay
{
	Arms::Arms(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	Arms* Arms::Copy() const
	{
		return new Arms(*this);
	}

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

		if (_isGrabbingObject)
		{
			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetKinematicTarget(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
			_grabbedObject->SetGlobalPosition(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
		}
		//if (rigid)
			//std::cout << rigid->GetRigidFlagKinematic() << std::endl;
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
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100.f };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE/*Layer?*/)// is a Cube
			{
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				if (cube->GetState() == ECubeState::DEFAULT)
				{
					cube->ChangeState(ECubeState::GRABBED);

					//Change hierarchy of the object
					_originOfGrabbedObject = ray.actorClosestBlock->GetTransform()->GetParent();
					_grabbedObject = ray.actorClosestBlock;

					_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(true);
					_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(true);
					_isGrabbingObject = QX_TRUE;
				}
			}
			else
				return;
		}
		else
			return;
	}

	void Arms::Drop()
	{
		//Drop

		_grabbedObject->GetComponent<Cube>()->ChangeState(ECubeState::DEFAULT);

		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(false);
		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(false);

		_grabbedObject = nullptr;
		_originOfGrabbedObject = nullptr;

		_isGrabbingObject = QX_FALSE;
	}

	void Arms::UseIce()
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be frozen
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100 };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE/*Layer?*/)// is a Cube
			{
				rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();
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
		cube->SetRigidFlagKinematic(true);
		cube->SetRigidFlagKineForQueries(true);
	}

	void	Arms::UnFreeze(Core::Components::Rigidbody* cube)
	{
		//Re-Activate Kinematic
		cube->SetRigidFlagKinematic(false);
		cube->SetRigidFlagKineForQueries(false);
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