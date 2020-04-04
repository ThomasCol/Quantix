#include "Core/DataStructure/GameObject3D.h"

namespace Core::DataStructure
{
	GameObject3D::GameObject3D(std::string name) noexcept :
		GameComponent(name)
	{
	}

	GameObject3D::GameObject3D(const GameObject3D& g3d) noexcept :
		GameComponent(g3d)//,
		//_transform{ g3d._transform }
	{
	}

	GameObject3D::GameObject3D(GameObject3D&& g3d) noexcept :
		GameComponent(g3d)//,
		//_transform{ std::move(g3d._transform) }
	{
	}

	GameObject3D::~GameObject3D()
	{
	}

	void GameObject3D::AddChild(GameObject3D* object)
	{
		//_transform.AddChild(object->_transform);
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
		//_transform.SetLocalPosition(pos);
	}

	void	GameObject3D::SetLocalRotation(Math::QXvec3 rot)
	{
		//_transform.SetLocalRotation(pos);
	}

	void	GameObject3D::SetLocalScale(Math::QXvec3 scale)
	{
		//_transform.SetLocalScale(pos);
	}

	void	GameObject3D::SetTransform(const Math::QXmat4& mat)
	{
		//_transform.SetTransform(mat);
	}

	void	GameObject3D::SetTransform(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale)
	{
		//_transform.SetTransform(pos, rot, scale);
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