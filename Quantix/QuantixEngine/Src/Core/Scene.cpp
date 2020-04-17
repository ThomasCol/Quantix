#include "Core/Scene.h"
#include "Mat4.h"

namespace Quantix::Core
{
	#pragma region Constructors&Destructor

	Scene::Scene(const Scene& copy) noexcept :
		_name {copy._name}, _world {copy._world}, _id {copy._id}
	{}

	Scene::Scene(Scene&& copy) noexcept :
		_name { std::move(copy._name) }, _world{ std::move(copy._world) }, _id{ std::move(copy._id) }
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Functions

	void	Scene::Init()
	{}

	void	Scene::Update()
	{
		_world.Update(Math::QXmat4::Identity());
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