#include "Resources/Scene.h"
#include "Mat4.h"

#include "Core/DataStructure/ResourcesManager.h"

namespace Quantix::Resources
{
	#pragma region Constructors&Destructor

	Scene::Scene(const QXstring& name, Core::DataStructure::GameObject3D* root, const QXuint& id) noexcept :
		_name{ name },
		_root {root},
		_id {id}
	{}

	Scene::Scene(const Scene& copy) noexcept :
		_name {copy._name}, 
		_root {copy._root},
		_id {copy._id}
	{}

	Scene::Scene(Scene&& copy) noexcept :
		_name { std::move(copy._name) }, 
		_root{ std::move(copy._root) },
		_id{ std::move(copy._id) }
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Functions

	Core::DataStructure::GameObject3D* Scene::AddGameObject(const QXstring& name, const QXstring& parentName)
	{
		Core::DataStructure::GameObject3D* object = new Core::DataStructure::GameObject3D(name);
		QXbool is_set = false;

		if (parentName == "")
			_root->AddChild(object);
		else
		{
			for (QXsizei i = 0; i < _objects.size(); ++i)
			{
				if (_objects[i]->GetName() == parentName)
				{
					_objects[i]->AddChild(object);
					is_set = true;
					break;
				}
			}

			if (is_set)
				_root->AddChild(object);
		}

		_objects.push_back(object);
		return object;
	}

	void	Scene::Init(Quantix::Core::DataStructure::ResourcesManager& manager)
	{
		_root = std::make_shared<Quantix::Core::DataStructure::GameObject3D>(Quantix::Core::DataStructure::GameObject3D("root"));

		Quantix::Core::DataStructure::GameObject3D* gameObject = new Quantix::Core::DataStructure::GameObject3D("Mesh");
		Quantix::Core::DataStructure::GameObject3D* gameObject2 = new Quantix::Core::DataStructure::GameObject3D("Mesh2");

		_root->AddChild(gameObject);
		gameObject->AddChild(gameObject2);

		gameObject->AddComponent<Quantix::Core::Components::Mesh>();
		gameObject2->AddComponent<Quantix::Core::Components::Mesh>();

		Quantix::Core::Components::Mesh* mesh = gameObject->GetComponent<Quantix::Core::Components::Mesh>();
		mesh = manager.CreateMesh(mesh, "../QuantixEngine/Media/Mesh/fantasy_game_inn.obj");
		mesh->SetMaterialMainTexture(manager.CreateTexture("../QuantixEngine/Media/Textures/fantasy_game_inn_diffuse.png"));

		mesh = gameObject2->GetComponent<Quantix::Core::Components::Mesh>();
		mesh = manager.CreateMesh(mesh, "../QuantixEngine/Media/Mesh/cube.obj");
	}

	void	Scene::Update(std::vector<Core::Components::Mesh*>& meshes)
	{
		// TODO pas complet update mesh et update gameobject
		if (_root)
			_root->Update(meshes);
	}

	void Scene::Rename(const QXstring& str) noexcept
	{
		_name = str;
	}

	void Scene::Reset() noexcept
	{
		// TODO
	}

	Core::DataStructure::GameObject3D* Scene::GetGameObject(const QXstring& name)
	{
		for (QXsizei i = 0; i < _objects.size(); ++i)
		{
			if (_objects[i]->GetName() == name)
			{
				return _objects[i];
			}
		}

		return nullptr;
	}

	#pragma endregion

	#pragma region Operators

	Scene& Scene::operator=(const Scene& s) noexcept
	{
		_name = s._name;
		_root = s._root;
		_id = s._id;

		return *this;
	}

	Scene& Scene::operator=(Scene&& s) noexcept
	{
		_name = std::move(s._name);
		_root = std::move(s._root);
		_id = std::move(s._id);

		return *this;
	}

	#pragma endregion

	#pragma endregion
}