#include "Resources/Scene.h"
#include "Mat4.h"

#include "Core/DataStructure/ResourcesManager.h"
#include "Core/Components/CubeCollider.h"

namespace Quantix::Resources
{
	#pragma region Constructors&Destructor

	Scene::Scene()
	{
		_root3D = new Quantix::Core::DataStructure::GameObject3D("root3D");
		_root3D->GetTransform()->SetParent(nullptr);
		_root2D = new Quantix::Core::DataStructure::GameObject2D("root2D");
		_root2D->GetTransform()->SetParent(nullptr);
	}

	Scene::Scene(const QXstring& name, Core::DataStructure::GameObject3D* root, const QXuint& id) noexcept :
		_name{ name },
		_root3D {root},
		_id {id}
	{
		_root2D = new Quantix::Core::DataStructure::GameObject2D("root2D");
	}

	Scene::Scene(const Scene& copy) noexcept :
		_name {copy._name}, 
		_root3D {copy._root3D},
		_root2D{ copy._root2D },
		_rootComponent{ copy._rootComponent },
		_id {copy._id}
	{}

	Scene::Scene(Scene&& copy) noexcept :
		_name { std::move(copy._name) }, 
		_root3D{ std::move(copy._root3D) },
		_root2D{ std::move(copy._root2D) },
		_rootComponent{ std::move(copy._rootComponent) },
		_id{ std::move(copy._id) }
	{}

	Scene::~Scene()
	{
		for (auto it = _objects.begin(); it != _objects.end();)
			it = _objects.erase(it);
		for (auto it = _objects2D.begin(); it != _objects2D.end();)
			it = _objects2D.erase(it);
		for (auto it = _objectsComponent.begin(); it != _objectsComponent.end();)
			it = _objectsComponent.erase(it);

		delete _root3D;
		delete _root2D;
	}

	#pragma endregion

	#pragma region Methods

	#pragma region Functions

	Core::DataStructure::GameObject3D* Scene::AddGameObject(const QXstring& name, void* parent)
	{
		Core::DataStructure::GameObject3D* object = new Core::DataStructure::GameObject3D(name);
		QXbool is_set = false;

		if (parent == nullptr)
			_root3D->AddChild(object);
		else
		{
			for (auto it = _objects.begin(); it != _objects.end(); ++it)
			{
				if ((*it) == parent)
				{
					(*it)->AddChild(object);
					is_set = true;
					break;
				}
			}

			if (!is_set)
				_root3D->AddChild(object);
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
			for (auto it = _objects2D.begin(); it != _objects2D.end(); ++it)
			{
				if ((*it) == parent)
				{
					(*it)->AddChild(object);
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
		Quantix::Core::DataStructure::GameObject3D* gameObject = AddGameObject("Mesh");

		gameObject->AddComponent<Core::Components::Mesh>();

		Core::Components::Mesh* mesh = gameObject->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(gameObject);
		mesh = manager.CreateMesh(mesh, "media/Mesh/cube.obj");

		gameObject->AddComponent<Core::Components::CubeCollider>()->Init(gameObject);

		gameObject = AddGameObject("light");

		Core::Components::Light* light = gameObject->AddComponent<Core::Components::Light>();
		light->Init(gameObject);
		light->type = Core::Components::ELightType::DIRECTIONAL;
		light->ambient = { 0.3f, 0.3f, 0.3f };
		light->diffuse = { 0.7f, 0.7f, 0.7f };
		light->specular = { 0.7f, 0.7f, 0.7f };

		gameObject->SetLocalPosition({ -2.f, 4.f, -1.f });
	}

	void	Scene::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::ICollider*>& colliders,
		std::vector<Core::Components::Light>& lights, Core::Platform::AppInfo& info, const QXbool& isPlaying) noexcept
	{
		// TODO pas complet update mesh et update gameobject
		if (_root3D)
			_root3D->Update(meshes, colliders, lights, info, isPlaying);
		if (_root2D)
			_root2D->Update();
	}

	void Scene::Start() noexcept
	{
		if (_root3D)
			_root3D->Start();
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
		for (auto it = _objects.begin(); it != _objects.end(); ++it)
		{
			if ((*it)->GetName() == name)
			{
				return (*it);
			}
		}

		return nullptr;
	}

	Core::DataStructure::GameObject2D* Scene::GetGameObject2D(const QXstring& name) noexcept
	{
		for (auto it = _objects2D.begin(); it != _objects2D.end(); ++it)
		{
			if ((*it)->GetName() == name)
			{
				return (*it);
			}
		}
		return nullptr;
	}

	#pragma endregion

	#pragma region Operators

	Scene& Scene::operator=(const Scene& s) noexcept
	{
		_name = s._name;
		_root3D = s._root3D;
		_root2D = s._root2D;
		_rootComponent = s._rootComponent;
		_id = s._id;

		return *this;
	}

	Scene& Scene::operator=(Scene&& s) noexcept
	{
		_name = std::move(s._name);
		_root3D = std::move(s._root3D);
		_root2D = std::move(s._root2D);
		_rootComponent = std::move(s._rootComponent);
		_id = std::move(s._id);

		return *this;
	}

	#pragma endregion

	#pragma endregion
}
