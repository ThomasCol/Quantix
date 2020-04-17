#include "Resources/Scene.h"
#include "Mat4.h"

namespace Quantix::Resources
{
	#pragma region Constructors&Destructor

	Scene::Scene(const QXstring& name, const Physic::Transform3D& world, const QXuint& id) noexcept :
		_name{ name },
		_world {world},
		_id {id}
	{}

	Scene::Scene(const Scene& copy) noexcept :
		_name {copy._name}, 
		_world {copy._world}, 
		_id {copy._id}
	{}

	Scene::Scene(Scene&& copy) noexcept :
		_name { std::move(copy._name) }, 
		_world{ std::move(copy._world) }, 
		_id{ std::move(copy._id) }
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Functions

	void	Scene::Init()
	{}

	void	Scene::Update()
	{
		// TODO pas complet update mesh et update gameobject
		_world.Update(Math::QXmat4::Identity());
	}

	void Scene::Rename(const QXstring& str) noexcept
	{
		_name = str;
	}

	void Scene::Reset() noexcept
	{
		// TODO
	}

	#pragma endregion

	#pragma region Operators

	Scene& Scene::operator=(const Scene& s) noexcept
	{
		_name = s._name;
		_world = s._world;
		_id = s._id;

		return *this;
	}

	Scene& Scene::operator=(Scene&& s) noexcept
	{
		_name = std::move(s._name);
		_world = std::move(s._world);
		_id = std::move(s._id);

		return *this;
	}

	#pragma endregion

	#pragma endregion
}