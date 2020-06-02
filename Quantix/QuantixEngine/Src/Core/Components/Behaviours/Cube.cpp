#include "Core/Components//Behaviours//Cube.h"

#include <Core/Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core/Components/Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Behaviours::Cube>("Cube")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::Behaviours::Cube&>()
		.constructor<Quantix::Core::Components::Behaviours::Cube&&>();
}

namespace Quantix::Core::Components::Behaviours
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
		if (_object->GetComponent<Core::Components::Mesh>())
		{
			_mesh = _object->GetComponent<Core::Components::Mesh>();
			currentMaterial = new Resources::Material(*_mesh->GetMaterial());
			saveMaterial= _mesh->GetMaterial();
			_mesh->SetMaterial(currentMaterial);

		}
	}

	void Cube::Start()
	{}

	void Cube::Destroy()
	{
		_mesh->SetMaterial(saveMaterial);
		delete currentMaterial;
	}

	void Cube::Update(QXdouble deltaTime)
	{
		switch (_stateMagnet)
		{
			case ECubeMagnetState::MAGNET_POS:	Attract(deltaTime); break;
			case ECubeMagnetState::MAGNET_NEG:	Reject(deltaTime); break;
			default: break;
		}
	}

	void Cube::Attract(QXdouble deltaTime) noexcept
	{
		Core::DataStructure::GameObject3D* gameobject = static_cast<Core::DataStructure::GameObject3D*>(_object);

		std::vector<Core::DataStructure::GameObject3D*> overlapedObjects = Physic::PhysicHandler::GetInstance()->OverlapSphere(_rangeOfMagnet, gameobject->GetTransform());
		
		for (QXuint i = 0; i < overlapedObjects.size(); i++)
		{
			if (overlapedObjects[i] != _object)
			{
				Cube* cube = nullptr;
				if (overlapedObjects[i])
					cube = overlapedObjects[i]->GetComponent<Cube>(true);

				if (cube)
				{
					if ((gameobject->GetGlobalPosition() - overlapedObjects[i]->GetGlobalPosition()).Length() > 0.5f)
					{
						Core::Components::Rigidbody* rigid = overlapedObjects[i]->GetComponent< Core::Components::Rigidbody>();

						if (rigid && cube->GetStatePhysic() == ECubePhysicState::DEFAULT)
							rigid->AddForce((gameobject->GetGlobalPosition() - overlapedObjects[i]->GetLocalPosition()) * (QXfloat)deltaTime * ATTRACTFORCE);
					}
				}
			}
		}
	}

	void Cube::Reject(QXdouble deltaTime) noexcept
	{
		Core::DataStructure::GameObject3D* gameobject = static_cast<Core::DataStructure::GameObject3D*>(_object);

		std::vector<Core::DataStructure::GameObject3D*> overlapedObjects = Physic::PhysicHandler::GetInstance()->OverlapSphere(_rangeOfMagnet, gameobject->GetTransform());

		for (QXuint i = 0; i < overlapedObjects.size(); i++)
		{
			if (overlapedObjects[i] != _object)
			{
				Cube* cube = nullptr;
				if (overlapedObjects[i])
					cube = overlapedObjects[i]->GetComponent<Cube>(true);

				if (cube)
				{
					Core::Components::Rigidbody* rigid = overlapedObjects[i]->GetComponent< Core::Components::Rigidbody>();

					if (rigid && cube->GetStatePhysic() == ECubePhysicState::DEFAULT)
						rigid->AddForce((overlapedObjects[i]->GetLocalPosition() - gameobject->GetGlobalPosition()) * (QXfloat)deltaTime * REJECTFORCE);
				}
			}
		}
	}

	void Cube::UpdateMaterial() noexcept
	{
		QXbool physicColor = false;
		switch (_stateMagnet)
		{
		case ECubeMagnetState::MAGNET_NEG:
			_mesh->GetMaterial()->ambient = Math::QXvec3(200, 60, 40) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(253, 130, 130) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case ECubeMagnetState::MAGNET_POS:
			_mesh->GetMaterial()->ambient = Math::QXvec3(40, 60, 200) / 255;
			_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 130, 253) / 255;
			_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
			break;
		case ECubeMagnetState::DEFAULT:
			physicColor = true;
			break;
		default:
			break;
		}

		if (physicColor)
		{
			switch (_statePhysic)
			{
			case ECubePhysicState::DEFAULT:
				_mesh->GetMaterial()->ambient = saveMaterial->ambient;
				_mesh->GetMaterial()->diffuse = saveMaterial->diffuse;
				_mesh->GetMaterial()->specular = saveMaterial->specular;
				break;
			case ECubePhysicState::FROZEN:
				_mesh->GetMaterial()->ambient = Math::QXvec3(119, 248, 253) / 255;
				_mesh->GetMaterial()->diffuse = Math::QXvec3(119, 248, 253) / 255;
				_mesh->GetMaterial()->specular = Math::QXvec3(255, 255, 255) / 255;
				break;
			default:
				break;
			}
		}

	}
}