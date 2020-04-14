#include "Core/DataStructure/GameObject2D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::DataStructure::GameObject2D>("GameObject2D")
	.constructor<>()
	.constructor<const QXstring&>()
	.constructor<const Quantix::Core::DataStructure::GameObject2D&>()
	.constructor<Quantix::Core::DataStructure::GameObject2D&&>()
	.method("SetGlobalPosition", &Quantix::Core::DataStructure::GameObject2D::SetGlobalPosition)
	.method("SetGlobalRotation", &Quantix::Core::DataStructure::GameObject2D::SetGlobalRotation)
	.method("SetLocalPosition", &Quantix::Core::DataStructure::GameObject2D::SetLocalPosition)
	.method("SetLocalRotation", &Quantix::Core::DataStructure::GameObject2D::SetLocalRotation)
	.method("SetLocalScale", &Quantix::Core::DataStructure::GameObject2D::SetLocalScale)
	.method("GetLocalPosition", &Quantix::Core::DataStructure::GameObject2D::GetLocalPosition)
	.method("GetLocalRotation", &Quantix::Core::DataStructure::GameObject2D::GetLocalRotation)
	.method("GetLocalScale", &Quantix::Core::DataStructure::GameObject2D::GetLocalScale)
	.method("SetTransform", &Quantix::Core::DataStructure::GameObject2D::SetTransform)
	.method("GetTransform", &Quantix::Core::DataStructure::GameObject2D::GetTransform);
}

namespace Quantix::Core::DataStructure
{
	GameObject2D::GameObject2D() noexcept :
		GameComponent(),
		_transform{ new Quantix::Physic::Transform2D() }
	{
	}

	GameObject2D::GameObject2D(const QXstring& name) noexcept :
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