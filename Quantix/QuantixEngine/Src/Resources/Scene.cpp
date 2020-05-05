#include "Resources/Scene.h"
#include "Mat4.h"

#include "Core/DataStructure/ResourcesManager.h"
#include "Core/Components/CubeCollider.h"

namespace Quantix::Resources
{
	#pragma region Constructors&Destructor

	Scene::Scene()
	{
		_root = new Quantix::Core::DataStructure::GameObject3D("root");
	}

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

	Scene::~Scene()
	{
		for (QXsizei i = 0; i < _objects.size(); ++i)
			delete _objects[i];
	}

	#pragma endregion

	#pragma region Methods

	#pragma region Functions

	Core::DataStructure::GameObject3D* Scene::AddGameObject(const QXstring& name, void* parent)
	{
		Core::DataStructure::GameObject3D* object = new Core::DataStructure::GameObject3D(name);
		QXbool is_set = false;

		if (parent == nullptr)
			_root->AddChild(object);
		else
		{
			for (QXsizei i = 0; i < _objects.size(); ++i)
			{
				if (_objects[i] == parent)
				{
					_objects[i]->AddChild(object);
					is_set = true;
					break;
				}
			}

			if (!is_set)
				_root->AddChild(object);
		}

		_objects.push_back(object);
		return object;
	}

	void	Scene::Init(Quantix::Core::DataStructure::ResourcesManager& manager) noexcept
	{
		AddGameObject("Mesh");

		Quantix::Core::DataStructure::GameObject3D* gameObject = GetGameObject("Mesh");

		gameObject->AddComponent<Core::Components::Mesh>();

		Core::Components::Mesh* mesh = gameObject->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(gameObject);
		mesh = manager.CreateMesh(mesh, "media/Mesh/cube.obj");

		gameObject->AddComponent<Core::Components::CubeCollider>()->Init(gameObject);
	}

	void	Scene::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::ICollider*>& colliders) noexcept
	{
		// TODO pas complet update mesh et update gameobject
		if (_root)
			_root->Update(meshes, colliders);
	}

	void Scene::Rename(const QXstring& str) noexcept
	{
		_name = str;
	}

	void Scene::Reset() noexcept
	{
		// TODO
	}

	Core::DataStructure::GameObject3D* Scene::GetGameObject(const QXstring& name) noexcept
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
