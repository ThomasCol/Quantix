#include "Core/DataStructure/GameObject3D.h"

namespace Core::DataStructure
{

	GameObject3D::GameObject3D() noexcept :
		GameComponent()//,
		//_transform{ Transform3D() }
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
}