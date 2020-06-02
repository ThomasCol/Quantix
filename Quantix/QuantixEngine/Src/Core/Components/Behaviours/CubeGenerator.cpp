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
		.property("Max Cubes", &Quantix::Gameplay::CubeGenerator::GetNbMaxOfCubes, &Quantix::Gameplay::CubeGenerator::SetNbMaxOfCubes)
		.property("Distance for Generation", &Quantix::Gameplay::CubeGenerator::GetDistForGeneration, &Quantix::Gameplay::CubeGenerator::SetDistForGeneration)
		.method("SetSceneAndResourcesManager", &Quantix::Gameplay::CubeGenerator::SetSceneAndResourcesManager);
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
		if (!_IsGeneratorCreated)
		{
			if (_scene->IsReady())
			{
				CreateGenerator();
				_IsGeneratorCreated = true;
			}
			else
				return;
		}

		for (auto it = _cubes.begin(); it != _cubes.end(); ++it)
		{
			if (!(*it)->GetIsActive())
			{
				ReUseCube((*it));
				return;
			}

			if ((_gameobject->GetGlobalPosition() - (*it)->GetGlobalPosition()).Length() < _distForGeneration)
				return;
		}

		if ((QXuint)_cubes.size() < _nbMaxOfCubes)
			CreateCube();
	}

	void CubeGenerator::Destroy()
	{
		for (auto it = _gameobject->GetTransform()->GetChilds().begin(); it != _gameobject->GetTransform()->GetChilds().end();)
		{
			for (QXuint i = 0; i < (*it)->GetObject()->GetComponents().size(); i++)
				(*it)->GetObject()->RemoveComponent((*it)->GetObject()->GetComponents()[i]);
			it = _gameobject->GetTransform()->GetChilds().erase(it);
		}
	}

	void CubeGenerator::GenerateMesh(QXstring name, Math::QXvec3 pos, Math::QXvec3 scale, Math::QXvec3 ambient, Math::QXvec3 diffuse, Math::QXvec3 specular) noexcept
	{
		Core::DataStructure::GameObject3D* go = _scene->AddGameObject(name, _gameobject);
		go->SetTransformValue(pos, Math::QXquaternion(1.f, 0.f, 0.f, 0.f), scale);
		//MESH
		Core::Components::Mesh* mesh = go->AddComponent<Core::Components::Mesh>();
		mesh->Init(go);
		_manager->CreateMesh(mesh, "media/Mesh/cube.obj");
		mesh->GetMaterial()->ambient = ambient;
		mesh->GetMaterial()->diffuse = diffuse;
		mesh->GetMaterial()->specular = specular;
	}

	void CubeGenerator::CreateGenerator() noexcept
	{
		GenerateMesh("TopCube", Math::QXvec3(0.f, 0.72f, 0.f), Math::QXvec3(3.f, 0.1f, 3.f), COLORTAMBIENT, COLORTDIFFUSE, COLORB);
		GenerateMesh("BottomCube1", Math::QXvec3(0.f, -0.72f, -1.163f), Math::QXvec3(3.f, 0.1f, 0.7f), COLORB, COLORB, COLORB);
		GenerateMesh("BottomCube2", Math::QXvec3(0.f, -0.72f, 1.163f), Math::QXvec3(3.f, 0.1f, 0.7f), COLORB, COLORB, COLORB);
		GenerateMesh("BottomCube3", Math::QXvec3(-1.163f, -0.72f, 0.f), Math::QXvec3(0.7f, 0.1f, 3.f), COLORB, COLORB, COLORB);
		GenerateMesh("BottomCube4", Math::QXvec3(1.163f, -0.72f, 0.f), Math::QXvec3(0.7f, 0.1f, 3.f), COLORB, COLORB, COLORB);
		GenerateMesh("Plot1", Math::QXvec3(-1.38f, 0.f, 0.f), Math::QXvec3(0.2f, 1.5f, 0.2f), COLORPAMBIENT, COLORPDIFFUSE, COLORPSPECULAR);
		GenerateMesh("Plot2", Math::QXvec3(1.38f, 0.f, 0.f), Math::QXvec3(0.2f, 1.5f, 0.2f), COLORPAMBIENT, COLORPDIFFUSE, COLORPSPECULAR);
		GenerateMesh("Plot3", Math::QXvec3(0.f, 0.f, -1.38f), Math::QXvec3(0.2f, 1.5f, 0.2f), COLORPAMBIENT, COLORPDIFFUSE, COLORPSPECULAR);
		GenerateMesh("Plot4", Math::QXvec3(0.f, 0.f, 1.38f), Math::QXvec3(0.2f, 1.5f, 0.2f), COLORPAMBIENT, COLORPDIFFUSE, COLORPSPECULAR);
	}

	void CubeGenerator::SetSceneAndResourcesManager(Quantix::Resources::Scene* scene, Quantix::Core::DataStructure::ResourcesManager* rm)
	{
		_scene = scene;
		_manager = rm;
	}

	void CubeGenerator::CreateCube() noexcept
	{
		//GAMEOBJECT
		Core::DataStructure::GameObject3D* cube = _scene->AddGameObject("Generated Cube " + std::to_string(_cubes.size() + 1));
		cube->SetTransformValue(_gameobject->GetGlobalPosition(), _gameobject->GetGlobalRotation(), _gameobject->GetGlobalScale());

		cube->SetLayer(Core::DataStructure::Layer::SELECTABLE);

		//MESH
		Core::Components::Mesh* mesh = cube->AddComponent<Core::Components::Mesh>();
		mesh->Init(cube);
		_manager->CreateMesh(mesh, "media/Mesh/cube.obj");

		//CUBE COLLIDER
		Core::Components::CubeCollider* collider = cube->AddComponent<Core::Components::CubeCollider>();
		collider->Init(cube);

		//RIGIDBODY
		Core::Components::Rigidbody* rigid = cube->AddComponent<Core::Components::Rigidbody>();
		rigid->Init(cube);
		rigid->SetTransformPosition(_gameobject->GetGlobalPosition());

		//CUBE BEHAVIOUR
		cube->AddComponent<Cube>()->Init(cube);

		_cubes.push_back(cube);
	}

	void CubeGenerator::ReUseCube(Core::DataStructure::GameObject3D* cube) noexcept
	{
		cube->SetTransformValue(_gameobject->GetGlobalPosition(), _gameobject->GetGlobalRotation(), _gameobject->GetGlobalScale());
		cube->GetComponent<Core::Components::Rigidbody>()->SetTransformPosition(_gameobject->GetGlobalPosition());

		cube->SetIsActive(QX_TRUE);
	}
}