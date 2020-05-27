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
	{}

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
					if ((gameobject->GetGlobalPosition() - overlapedObjects[i]->GetGlobalPosition()).Length() > 1.f)
					{
						Core::Components::Rigidbody* rigid = overlapedObjects[i]->GetComponent< Core::Components::Rigidbody>();

						if (rigid)
							rigid->AddForce((gameobject->GetGlobalPosition() - overlapedObjects[i]->GetLocalPosition()) * (QXfloat)deltaTime * 100.f);
					}
				}
			}
		}
	}

	void Cube::Reject(QXdouble deltaTime)
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

					if (rigid)
						rigid->AddForce((overlapedObjects[i]->GetLocalPosition() - gameobject->GetGlobalPosition()) * (QXfloat)deltaTime * 100.f);
				}
			}
		}
	}

	//Questions to ask my teammates
	/*
	* Comment accéder à tout les cubes de la scène, ou à la limite tout ceux d'une certaine zone ?
	*/

	//TODO:
	/*
	* 
	*/
}