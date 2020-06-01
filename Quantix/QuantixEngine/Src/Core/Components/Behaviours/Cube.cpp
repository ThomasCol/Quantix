#include "Core/Components//Behaviours//Cube.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core/Components/Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::Cube>("Cube")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::Cube&>()
		.constructor<Quantix::Gameplay::Cube&&>();
}

namespace Quantix::Gameplay
{
	Cube::Cube(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	Cube* Cube::Copy() const
	{
		return new Cube(*this);
	}

	void Cube::Awake()
	{
		_gameobject = static_cast<Core::DataStructure::GameObject3D*>(_object);

		if (_object->GetComponent<Core::Components::Mesh>())
			_mesh = _object->GetComponent<Core::Components::Mesh>();
	}

	void Cube::Start()
	{}

	void Cube::Update(QXdouble deltaTime)
	{
		switch (_state)
		{
			case ECubeState::MAGNET_POS:	Attract(deltaTime); break;
			case ECubeState::MAGNET_NEG:	Reject(deltaTime); break;
			default: break;
		}
	}

	void Cube::Attract(QXdouble deltaTime)
	{
		if (_gameobject)
		{
			//Get every object that is in the magnet range
			std::vector<Core::DataStructure::GameObject3D*> overlapedObjects = Physic::PhysicHandler::GetInstance()->OverlapSphere(_rangeOfMagnet, _gameobject->GetTransform());

			for (QXuint i = 0; i < overlapedObjects.size(); i++)
			{
				if (overlapedObjects[i] != _object)
				{
					Cube* cube{ nullptr };
					if (overlapedObjects[i])
						cube = overlapedObjects[i]->GetComponent<Cube>(true);

					//Check if the overlaped object is indeed a Cube object
					if (cube)
					{
						//If the cube object is not too close from the magnet cube
						if ((_gameobject->GetGlobalPosition() - overlapedObjects[i]->GetGlobalPosition()).Length() > 1.f)
						{
							Core::Components::Rigidbody* rigid = overlapedObjects[i]->GetComponent< Core::Components::Rigidbody>();

							if (rigid) //Attract the cube
								rigid->AddForce((_gameobject->GetGlobalPosition() - overlapedObjects[i]->GetLocalPosition()) * (QXfloat)deltaTime * 100.f);
						}
					}
				}
			}
		}
	}

	void Cube::Reject(QXdouble deltaTime)
	{
		if (_gameobject)
		{
			//Get every object that is in the magnet range
			std::vector<Core::DataStructure::GameObject3D*> overlapedObjects = Physic::PhysicHandler::GetInstance()->OverlapSphere(_rangeOfMagnet, _gameobject->GetTransform());

			for (QXuint i = 0; i < overlapedObjects.size(); i++)
			{
				if (overlapedObjects[i] != _object)
				{
					Cube* cube{ nullptr };
					if (overlapedObjects[i])
						cube = overlapedObjects[i]->GetComponent<Cube>(true);

					//Check if the overlaped object is indeed a Cube object
					if (cube)
					{
						Core::Components::Rigidbody* rigid = overlapedObjects[i]->GetComponent< Core::Components::Rigidbody>();

						if (rigid) //Reject the cube
							rigid->AddForce((overlapedObjects[i]->GetLocalPosition() - _gameobject->GetGlobalPosition()) * (QXfloat)deltaTime * 100.f);
					}
				}
			}
		}
	}

	void Cube::UpdateMaterial()
	{
		switch (_state)
		{
		case ECubeState::DEFAULT: //Grey Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(51, 51, 51) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(128, 128, 128) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case ECubeState::FROZEN : //Light Blue Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 248, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case ECubeState::MAGNET_NEG: //Dark Red Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(200, 60, 40) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(253, 130, 130) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case ECubeState::MAGNET_POS: //Dark Blue Color
			_mesh->GetMaterial()->ambient = Math::QXvec3(40, 60, 200) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 130, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		default:
			break;
		}
	}
}