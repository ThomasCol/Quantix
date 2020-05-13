#include "Resources/Scene.h"
#include "Mat4.h"

#include "Core/DataStructure/ResourcesManager.h"
#include "Core/Components/CubeCollider.h"

namespace Quantix::Resources
{
	#pragma region Constructors&Destructor

	Scene::Scene()
	{
		_root = new Quantix::Core::DataStructure::GameObject3D("root3D");
		_root2D = new Quantix::Core::DataStructure::GameObject2D("root2D");
	}

	Scene::Scene(const QXstring& name, Core::DataStructure::GameObject3D* root, const QXuint& id) noexcept :
		_name{ name },
		_root {root},
		_id {id}
	{
		_root2D = new Quantix::Core::DataStructure::GameObject2D("root2D");
	}

	Scene::Scene(const Scene& copy) noexcept :
		_name {copy._name}, 
		_root {copy._root},
		_root2D{ copy._root2D },
		_rootComponent{ copy._rootComponent },
		_id {copy._id}
	{}

	Scene::Scene(Scene&& copy) noexcept :
		_name { std::move(copy._name) }, 
		_root{ std::move(copy._root) },
		_root2D{ std::move(copy._root2D) },
		_rootComponent{ std::move(copy._rootComponent) },
		_id{ std::move(copy._id) }
	{}

	Scene::~Scene()
	{
		for (QXsizei i = 0; i < _objects.size(); ++i)
			delete _objects[i];
		for (QXsizei i = 0; i < _objects2D.size(); ++i)
			delete _objects2D[i];
		for (auto it = _objectsComponent.begin(); it != _objectsComponent.end();)
			it = _objectsComponent.erase(it);
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

	Core::DataStructure::GameObject2D* Scene::AddGameObject2D(const QXstring& name, void* parent)
	{
		Core::DataStructure::GameObject2D* object = new Core::DataStructure::GameObject2D(name);
		QXbool is_set = false;

		if (parent == nullptr)
			_root2D->AddChild(object);
		else
		{
			for (QXsizei i = 0; i < _objects2D.size(); ++i)
			{
				if (_objects2D[i] == parent)
				{
					_objects2D[i]->AddChild(object);
					is_set = true;
					break;
				}
			}

			if (!is_set)
				_root2D->AddChild(object);
		}

		_objects2D.push_back(object);
		return object;
	}

	Core::DataStructure::GameComponent* Scene::AddGameComponent(const QXstring& name, void* parent)
	{
		Core::DataStructure::GameComponent* object = new Core::DataStructure::GameComponent(name);
		_objectsComponent.push_back(object);
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

	void	Scene::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::ICollider*>& colliders, Core::Platform::AppInfo& info) noexcept
	{
		// TODO pas complet update mesh et update gameobject
		if (_root)
			_root->Update(meshes, colliders, info);
		if (_root2D)
			_root2D->Update();
	}

	void Scene::Start() noexcept
	{
		if (_root)
			_root->Start();
		if (_root2D)
			_root2D->Start();
	}

	void Scene::Rename(const QXstring& str) noexcept
	{
		_name = str;
	}

	void Scene::Reset() noexcept
	{
		// TODO
	}

	QXbool	Scene::FindGameComponent(Core::DataStructure::GameComponent* gc) noexcept
	{
		for (auto it = _objectsComponent.begin(); it != _objectsComponent.end(); ++it)
		{
			if ((*it) == gc)
				return QX_TRUE;
		}
		return QX_FALSE;
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

	Core::DataStructure::GameObject2D* Scene::GetGameObject2D(const QXstring& name) noexcept
	{
		for (QXsizei i = 0; i < _objects2D.size(); ++i)
		{
			if (_objects2D[i]->GetName() == name)
			{
				return _objects2D[i];
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
