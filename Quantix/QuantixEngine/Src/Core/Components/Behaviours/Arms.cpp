//#include "Core\Components\Behaviours\Arms.h"
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
	{

	}

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
			UsePunch();
		if (GetKey(QX_MOUSE_BUTTON_RIGHT) == Core::UserEntry::EKeyState::PRESSED)
			UsePower();

		if (_isGrabbingObject)
		{
			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetKinematicTarget(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
			_grabbedObject->SetGlobalPosition(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2);
		}
	}

	void Arms::SwitchPower() noexcept
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

	void Arms::UsePower() noexcept
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

	void Arms::UseHands() noexcept
	{
		if (_isGrabbingObject)
			return Drop();
		else
			return Grab();
	}

	void Arms::Grab() noexcept
	{
		//Grab

		if (_gameobject)
		{
			//Cast a ray to check if a cube is near enough to be grabbed
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100.f };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE/*Layer?*/)// is a Cube
			{
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				if (cube && cube->GetStatePhysic() == ECubePhysicState::DEFAULT)
				{
					cube->ChangeStatePhysic(ECubePhysicState::GRABBED);

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

	void Arms::Drop() noexcept
	{
		//Drop

		_grabbedObject->GetComponent<Cube>()->ChangeStatePhysic(ECubePhysicState::DEFAULT);

		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(false);
		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(false);

		_grabbedObject = nullptr;

		_isGrabbingObject = QX_FALSE;
	}

	void Arms::UseIce() noexcept
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be frozen
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100 };

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE/*Layer?*/)// is a Cube
			{
				rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();
				Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

				if (cube && cube->GetStatePhysic() != ECubePhysicState::GRABBED)
				{
					//Detect if is already frozen or not
					if (rigid->GetRigidFlagKinematic())
					{
						cube->ChangeStatePhysic(ECubePhysicState::DEFAULT);
						UnFreeze(ray.actorClosestBlock);
						cube->UpdateMaterial();
					}
					else
					{
						cube->ChangeStatePhysic(ECubePhysicState::FROZEN);
						Freeze(ray.actorClosestBlock);
						cube->UpdateMaterial();
					}
				}
			}
		}
	}

	void	Arms::Freeze(Core::DataStructure::GameObject3D* cube) noexcept
	{
		objectFrozenVelocity = rigid->GetLinearVelocity();
			
		rigid->SetRigidFlagKinematic(true);
		rigid->SetRigidFlagKineForQueries(true);
	}

	void	Arms::UnFreeze(Core::DataStructure::GameObject3D* cube) noexcept
	{
		rigid->SetKinematicTarget(_gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetUp());

		rigid->SetRigidFlagKinematic(false);
		rigid->SetRigidFlagKineForQueries(false);
		rigid->SetLinearVelocity(objectFrozenVelocity);
	}

	void	Arms::UsePunch() noexcept
	{
		if (_isGrabbingObject && _grabbedObject->GetComponent<Cube>()->GetStatePhysic() == ECubePhysicState::GRABBED)
		{
			_grabbedObject->GetComponent<Cube>()->ChangeStatePhysic(ECubePhysicState::DEFAULT);

			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(false);
			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(false);

			Core::Components::Rigidbody* cube = _grabbedObject->GetComponent<Core::Components::Rigidbody>();
			if (cube)
				cube->AddForce(_gameobject->GetTransform()->GetForward() * 50, Physic::ForceMode::IMPULSE);

			_grabbedObject = nullptr;

			_isGrabbingObject = QX_FALSE;
		}
	}

	void	Arms::UseMagnet(QXbool positiveField) noexcept
	{
		if (_gameobject)
		{
			//Cast a ray to check if a cube can be frozen
			Physic::Raycast	ray{ _gameobject->GetGlobalPosition() + _gameobject->GetTransform()->GetForward() * 2, _gameobject->GetTransform()->GetForward(), 100 };

			rigid = ray.actorClosestBlock->GetComponent<Core::Components::Rigidbody>();
			Cube* cube = ray.actorClosestBlock->GetComponent<Cube>();

			if (cube && cube->GetStatePhysic() != ECubePhysicState::GRABBED)
			{
				if (positiveField)
				{
					if (cube->GetStateMagnet() != ECubeMagnetState::DEFAULT)
						cube->ChangeStateMagnet(ECubeMagnetState::DEFAULT);
					else
						cube->ChangeStateMagnet(ECubeMagnetState::MAGNET_POS);
					cube->UpdateMaterial();
				}
				else
				{
					if (cube->GetStateMagnet() != ECubeMagnetState::DEFAULT)
						cube->ChangeStateMagnet(ECubeMagnetState::DEFAULT);
					else
						cube->ChangeStateMagnet(ECubeMagnetState::MAGNET_NEG);
					cube->UpdateMaterial();
				}
			}
		}
	}

	void Arms::UpdateMaterial() noexcept
	{
		switch (_state)
		{
		case EArmState::FREEZE:
			_mesh->GetMaterial()->ambient = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case EArmState::MAGNET_NEG:
			_mesh->GetMaterial()->ambient = Math::QXvec3(200, 60, 40) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(253, 130, 130) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case EArmState::MAGNET_POS:
			_mesh->GetMaterial()->ambient = Math::QXvec3(40, 60, 200) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 130, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		default:
			break;
		}

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