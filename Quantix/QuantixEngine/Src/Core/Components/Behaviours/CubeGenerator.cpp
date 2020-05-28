#include "Core/Components/Behaviours/CubeGenerator.h"

#include "Core/Components/Mesh.h"
#include "Core/Components/CubeCollider.h"
#include "Core/Components/Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::CubeGenerator>("Cube Generator")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::CubeGenerator&>()
		.constructor<Quantix::Gameplay::CubeGenerator&&>()
		.property("Number Max of Cubes", &Quantix::Gameplay::CubeGenerator::GetNbMaxOfCubes, &Quantix::Gameplay::CubeGenerator::SetNbMaxOfCubes)
		.property("Minimum distance between Cubes and Generator ", &Quantix::Gameplay::CubeGenerator::GetDistMinBtwCubesAndGenerator, &Quantix::Gameplay::CubeGenerator::SetDistMinBtwCubesAndGenerator);
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
		for (auto it = _cubes.begin(); it != _cubes.end(); ++it)
			if ((_gameobject->GetGlobalPosition() - (*it)->GetGlobalPosition()).Length() < _distMinBtwCubesAndGenerator)
				return;

		CreateCube();
	}

	void CubeGenerator::CreateCube()
	{
		//GAMEOBJECT
		Core::DataStructure::GameObject3D* cube = _app->scene->AddGameObject("Generated Cube " + std::to_string(_cubes.size() + 1));
		cube->SetTransformValue(_gameobject->GetGlobalPosition(), _gameobject->GetGlobalRotation(), _gameobject->GetGlobalScale());

		cube->SetLayer(Core::DataStructure::Layer::SELECTABLE);

		//MESH
		Core::Components::Mesh* mesh = cube->AddComponent<Core::Components::Mesh>();
		mesh->Init(cube);
		_app->manager.CreateMesh(mesh, "media/Mesh/cube.obj");

		//CUBE COLLIDER
		Core::Components::CubeCollider* collider = cube->AddComponent<Core::Components::CubeCollider>();
		collider->Init(cube);

		//RIGIDBODY
		Core::Components::Rigidbody* rigid = cube->AddComponent<Core::Components::Rigidbody>();
		rigid->Init(cube);
		rigid->SetTransformPosition(_gameobject->GetGlobalPosition());

		//CUBE BEHAVIOUR
		cube->AddComponent<Cube>();

		_cubes.push_back(cube);
	}
}

//Questions to ask my teammates
/*
*
*/

//TODO:
/*
*
*/