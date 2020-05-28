#include "Core/Components/Behaviours/CubeGenerator.h"

#include "Core/Components/Mesh.h"
#include "Core/Components/CubeCollider.h"
#include "Core/Components/Rigidbody.h"
#include "Resources/Model.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::CubeGenerator>("Cube Generator")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::CubeGenerator&>()
		.constructor<Quantix::Gameplay::CubeGenerator&&>();
}

namespace Quantix::Gameplay
{
	CubeGenerator::CubeGenerator(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	CubeGenerator* CubeGenerator::Copy() const
	{
		return new CubeGenerator(*this);
	}

	void CubeGenerator::Awake()
	{
		_gameobject = static_cast<Core::DataStructure::GameObject3D*>(_object);
	}

	void CubeGenerator::Start()
	{}

	void CubeGenerator::Update(QXdouble deltaTime)
	{
		for (std::list<Core::DataStructure::GameObject3D*>::iterator it = _cubes.begin(); it != _cubes.end(); ++it)
		{
			if (!(*it))
			{
				_cubes.erase(it);
				CreateCube();
			}
		}
	}

	void CubeGenerator::CreateCube()
	{
		Core::DataStructure::GameObject3D* cube = new Core::DataStructure::GameObject3D("Cube", _gameobject->GetGlobalPosition(), _gameobject->GetGlobalRotation(), _gameobject->GetGlobalScale());

		//MESH
		Core::Components::Mesh* mesh = cube->AddComponent<Core::Components::Mesh>();
		//mesh = 

		//CUBE COLLIDER
		cube->AddComponent<Core::Components::CubeCollider>();

		//RIGIDBODY
		cube->AddComponent<Core::Components::Rigidbody>();

		//CUBE BEHAVIOUR
		cube->AddComponent<Cube>();

		_cubes.push_back(cube);
	}
}

//Questions to ask my teammates
/*
* Comment on cr�er un Mesh avec ensuite un model ? ResourcesManager ? 
*/

//TODO:
/*
*
*/