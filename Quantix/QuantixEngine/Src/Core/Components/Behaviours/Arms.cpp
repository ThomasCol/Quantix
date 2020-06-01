#include "Core/Components/Behaviours/Arms.h"
#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core\Components\Behaviours\Cube.h"
#include "Core\Components\Mesh.h"
#include "Physic/Transform3D.h"

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
		if (!_mesh)
		{
			std::list<Physic::Transform3D*> list = _gameobject->GetTransform()->GetChilds();

			if ((*list.begin())->GetObject()->GetComponent<Core::Components::Mesh>())
			{
				_mesh = (*list.begin())->GetObject()->GetComponent<Core::Components::Mesh>();
				UpdateMaterial();
			}
		}

		if (GetKey(QX_KEY_TAB) == Core::UserEntry::EKeyState::PRESSED)
			SwitchPower();
		
		if (GetKey(QX_KEY_E) == Core::UserEntry::EKeyState::PRESSED)
			UseHands();

		if (GetKey(QX_MOUSE_BUTTON_LEFT) == Core::UserEntry::EKeyState::PRESSED)
			Throw();

		if (GetKey(QX_MOUSE_BUTTON_RIGHT) == Core::UserEntry::EKeyState::PRESSED)
			UsePower();

		//Set the kinematic values for the grabbed cube to follow the eyes of the player
		if (_isGrabbingObject && _gameobject)
		{
			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetKinematicTarget(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
			_grabbedObject->SetGlobalPosition(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
		}
	}

	void Arms::SwitchPower()
	{
		switch (_state)
		{
		case EArmState::FREEZE:
			_state = EArmState::MAGNET_NEG;
			break;
		case EArmState::MAGNET_NEG:
			_state = EArmState::MAGNET_POS;
			break;
		case EArmState::MAGNET_POS:
			_state = EArmState::FREEZE;
			break;
		default:
			break;
		}

		UpdateMaterial();
	}

	void Arms::UsePower()
	{
		switch (_state)
		{
		case EArmState::FREEZE:
			UseIce();
			break;
		case EArmState::MAGNET_NEG:
			UseMagnet(QX_FALSE);
			break;
		case EArmState::MAGNET_POS:
			UseMagnet(QX_TRUE);
			break;
		default:
			break;
		}
	}

	void Arms::UseHands()
	{
		if (_isGrabbingObject)
			Drop();
		else
			Grab();
	}

	void Arms::Grab()
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube is near enough to be grabbed
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100.f };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE)// is a Cube
			{
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				//Check if the object got by the raycast is indeed a cube and can be grabbed
				if (cube && cube->GetState() == ECubeState::DEFAULT)
				{
					cube->ChangeState(ECubeState::GRABBED);
					
					_grabbedObject = ray.actorClosestBlock;

					//Set the kinematic flags to follow the player arms
					_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(true);
					_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(true);
					_isGrabbingObject = QX_TRUE;
				}
			}
		}
	}

	void Arms::Drop()
	{
		_grabbedObject->GetComponent<Cube>()->ChangeState(ECubeState::DEFAULT);

		Core::Components::Rigidbody* rigid = _grabbedObject->GetComponent<Core::Components::Rigidbody>();

		if (rigid)
		{
			//Set the kinematic flags for the cube to be affected again by gravity and forces and to stop follow the player arms
			rigid->SetRigidFlagKinematic(false);
			rigid->SetRigidFlagKineForQueries(false);
		}

		_grabbedObject = nullptr;

		_isGrabbingObject = QX_FALSE;
	}

	void Arms::UseIce()
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be frozen
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100 };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE)// is a Cube
			{
				Core::Components::Rigidbody* rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				//Check if the object got by the raycast is indeed a cube and can be frozen or unfrozen
				if (cube && cube->GetState() != ECubeState::GRABBED)
				{
					if (rigid)
					{
						//Detect if is already frozen or not
						if (rigid->GetRigidFlagKinematic())
						{
							cube->ChangeState(ECubeState::DEFAULT);
							UnFreeze(ray.actorClosestBlock, rigid);
						}
						else
						{
							cube->ChangeState(ECubeState::FROZEN);
							Freeze(ray.actorClosestBlock, rigid);
						}

						cube->UpdateMaterial();
					}
				}
			}
		}
	}

	void	Arms::Freeze(Core::DataStructure::GameObject3D* cube, Core::Components::Rigidbody* rigid)
	{
		//Register velocity of the frozen cube to give it back when unfrozen
		_objectFrozenVelocity = rigid->GetLinearVelocity();
			
		//Set the kinematic flags for the cube not to be affected by gravity and forces
		rigid->SetRigidFlagKinematic(true);
		rigid->SetRigidFlagKineForQueries(true);
	}

	void	Arms::UnFreeze(Core::DataStructure::GameObject3D* cube, Core::Components::Rigidbody* rigid)
	{
		rigid->SetKinematicTarget(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetUp());

		//Set the kinematic flags for the cube to be affected again by gravity and forces
		rigid->SetRigidFlagKinematic(false);
		rigid->SetRigidFlagKineForQueries(false);

		//Set registered velocity of the frozen cube
		rigid->SetLinearVelocity(_objectFrozenVelocity);
	}

	void	Arms::Throw()
	{
		if (_gameobject)
		{
			if (_isGrabbingObject && _grabbedObject->GetComponent<Cube>()->GetState() == ECubeState::GRABBED)
			{
				//Give a force to the cube to be thrown
				_grabbedObject->GetComponent<Core::Components::Rigidbody>()->AddForce(_gameobject->GetTransform()->GetForward() * 50, Physic::ForceMode::IMPULSE);
				
				Drop();
			}
		}
	}

	void	Arms::UseMagnet(QXbool positiveField)
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be magnetized
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100 };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE)// is a Cube
			{
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				//Check if the object got by the raycast is indeed a cube and can be magnetized
				if (cube && cube->GetState() == ECubeState::DEFAULT)
				{
					if (positiveField)
						cube->ChangeState(ECubeState::MAGNET_POS);
					else
						cube->ChangeState(ECubeState::MAGNET_NEG);
				}
				else
					cube->ChangeState(ECubeState::DEFAULT);
				
				cube->UpdateMaterial();
			}
		}
	}

	void Arms::UpdateMaterial()
	{
		switch (_state)
		{
		case EArmState::FREEZE: //Light Blue Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case EArmState::MAGNET_NEG: //Dark Red Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(200, 60, 40) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(253, 130, 130) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case EArmState::MAGNET_POS: //Dark Blue Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(40, 60, 200) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 130, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		default:
			break;
		}
	}
}