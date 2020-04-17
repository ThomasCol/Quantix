#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Core::DataStructure
{
	GameObject3D::GameObject3D(std::string name) noexcept :
		GameComponent(name)
	{
	}

	GameObject3D::GameObject3D(const GameObject3D& g3d) noexcept :
		GameComponent(g3d),
		_transform{ g3d._transform }
	{
	}

	GameObject3D::GameObject3D(GameObject3D&& g3d) noexcept :
		GameComponent(g3d),
		_transform{ std::move(g3d._transform) }
	{
	}

	GameObject3D::~GameObject3D()
	{
	}

	void	GameObject3D::SetGlobalPosition(Math::QXvec3 pos)
	{
		//_transform.SetGlobalPosition(pos);
	}

	void	GameObject3D::SetGlobalRotation(Math::QXvec3 rot)
	{
		//_transform.SetGlobalRotation(pos);
	}

	void	GameObject3D::SetLocalPosition(Math::QXvec3 pos)
	{
		_transform.SetPosition(pos);
	}

	void	GameObject3D::SetLocalRotation(Math::QXvec3 rot)
	{
		_transform.SetRotation(rot);
	}

	void	GameObject3D::SetLocalScale(Math::QXvec3 scale)
	{
		_transform.SetScale(scale);
	}

	void	GameObject3D::SetTransform(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale)
	{
		_transform.SetPosition(pos);
		_transform.SetRotation(rot);
		_transform.SetScale(scale);
	}
	GameObject3D& GameObject3D::operator=(const GameObject3D& object)
	{
		_component = object._component;
		_name = object._name;
		_layer = object._layer;
		_isStatic = object._isStatic;
		_isActive = object._isActive;

		return *this;
	}
}