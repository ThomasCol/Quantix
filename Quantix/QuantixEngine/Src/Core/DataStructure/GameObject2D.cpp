#include "Core/DataStructure/GameObject2D.h"

namespace Quantix::Core::DataStructure
{
	GameObject2D::GameObject2D() noexcept :
		GameComponent(),
		_transform{ new Quantix::Physic::Transform2D() }
	{
	}

	GameObject2D::GameObject2D(std::string name) noexcept :
		GameComponent(name)
	{
	}

	GameObject2D::GameObject2D(const GameObject2D& g2d) noexcept :
		GameComponent(g2d),
		_transform{ g2d._transform }
	{
	}

	GameObject2D::GameObject2D(GameObject2D&& g2d) noexcept :
		GameComponent(g2d),
		_transform{ std::move(g2d._transform) }
	{
	}

	GameObject2D::~GameObject2D()
	{
	}

	void	GameObject2D::SetGlobalPosition(Math::QXvec2 pos)
	{
		//_transform.SetGlobalPosition(pos);
	}

	void	GameObject2D::SetGlobalRotation(QXfloat rot)
	{
		//_transform.SetGlobalRotation(pos);
	}

	void	GameObject2D::SetLocalPosition(Math::QXvec2 pos)
	{
		_transform->SetPosition(pos);
	}

	void	GameObject2D::SetLocalRotation(QXfloat rot)
	{
		_transform->SetRotationAngle(rot);
	}

	void	GameObject2D::SetLocalScale(Math::QXvec2 scale)
	{
		_transform->SetScale(scale);
	}

	void	GameObject2D::SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale)
	{
		_transform->SetPosition(pos);
		_transform->SetRotationAngle(rot);
		_transform->SetScale(scale);
	}
}