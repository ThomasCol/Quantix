#include "Core/DataStructure/GameObject2D.h"

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::DataStructure;
	rttr::registration::class_<GameObject2D>("GameObject2D")
	.constructor<>()
	.constructor<const QXstring&>()
	.constructor<const GameObject2D&>()
	.constructor<GameObject2D&&>()
	.method("SetGlobalPosition", &GameObject2D::SetGlobalPosition)
	.method("SetGlobalRotation", &GameObject2D::SetGlobalRotation)
	.method("SetLocalPosition", &GameObject2D::SetLocalPosition)
	.method("SetLocalRotation", &GameObject2D::SetLocalRotation)
	.method("SetLocalScale", &GameObject2D::SetLocalScale)
	.method("GetLocalPosition", &GameObject2D::GetLocalPosition)
	.method("GetLocalRotation", &GameObject2D::GetLocalRotation)
	.method("GetLocalScale", &GameObject2D::GetLocalScale)
	.method("SetTransform", &GameObject2D::SetTransform)
	.method("GetTransform", &GameObject2D::GetTransform);
}

namespace Quantix::Core::DataStructure
{
	GameObject2D::GameObject2D() noexcept :
		GameComponent(),
		_transform{ new Quantix::Physic::Transform2D(this) }
	{
	}

	GameObject2D::GameObject2D(const QXstring& name) noexcept :
		GameComponent(name, QX_TRUE),
		_transform { new Quantix::Physic::Transform2D(this) }
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

	GameObject2D::~GameObject2D() noexcept
	{
		delete _transform;
	}

	void	GameObject2D::Start()
	{
		for (Physic::Transform2D* child : _transform->GetChilds())
			child->GetObject()->Start();
	}

	void	GameObject2D::Awake()
	{
		for (Physic::Transform2D* child : _transform->GetChilds())
			child->GetObject()->Awake();
	}

	void	GameObject2D::Update() noexcept
	{
		for (Physic::Transform2D* child : _transform->GetChilds())
			child->GetObject()->Update(this);
	}

	void	GameObject2D::Update(const GameObject2D* parentObject) noexcept
	{
		_transform->Update(parentObject->GetTransform());
		for (Physic::Transform2D* child : _transform->GetChilds())
			child->GetObject()->Update(this);
	}

	void	GameObject2D::SetGlobalPosition(Math::QXvec2 pos) noexcept
	{
		//_transform.SetGlobalPosition(pos);
	}

	void	GameObject2D::SetGlobalRotation(QXfloat rot) noexcept
	{
		//_transform.SetGlobalRotation(pos);
	}

	void	GameObject2D::SetLocalPosition(Math::QXvec2 pos) noexcept
	{
		_transform->SetPosition(pos);
	}

	void	GameObject2D::SetLocalRotation(QXfloat rot) noexcept
	{
		_transform->SetRotationAngle(rot);
	}

	void	GameObject2D::SetLocalScale(Math::QXvec2 scale) noexcept
	{
		_transform->SetScale(scale);
	}

	void	GameObject2D::SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale) noexcept
	{
		_transform->SetPosition(pos);
		_transform->SetRotationAngle(rot);
		_transform->SetScale(scale);
	}
}
