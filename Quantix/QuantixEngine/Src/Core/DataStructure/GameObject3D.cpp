#include "Core/DataStructure/GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::DataStructure::GameObject3D>("GameObject3D")
	.constructor<>()
	.constructor<const QXstring&, Quantix::Physic::Transform3D*>()
	.constructor<const Quantix::Core::DataStructure::GameObject3D&>()
	.constructor<Quantix::Core::DataStructure::GameObject3D&&>()
	.method("SetGlobalPosition", &Quantix::Core::DataStructure::GameObject3D::SetGlobalPosition)
	.method("SetGlobalRotation", &Quantix::Core::DataStructure::GameObject3D::SetGlobalRotation)
	.method("SetLocalPosition", &Quantix::Core::DataStructure::GameObject3D::SetLocalPosition)
	.method("SetLocalRotation", &Quantix::Core::DataStructure::GameObject3D::SetLocalRotation)
	.method("SetLocalScale", &Quantix::Core::DataStructure::GameObject3D::SetLocalScale)
	.method("GetLocalPosition", &Quantix::Core::DataStructure::GameObject3D::GetLocalPosition)
	.method("GetLocalRotation", &Quantix::Core::DataStructure::GameObject3D::GetLocalRotation)
	.method("GetLocalScale", &Quantix::Core::DataStructure::GameObject3D::GetLocalScale)
	.method("SetTransform", &Quantix::Core::DataStructure::GameObject3D::SetTransform)
	.method("GetTransform", &Quantix::Core::DataStructure::GameObject3D::GetTransform);
}

namespace Quantix::Core::DataStructure
{
	GameObject3D::GameObject3D(const QXstring& name, Quantix::Physic::Transform3D* transform) noexcept :
		GameComponent(name),
		_transform { transform }
	{
		_transform->SetObject(this);
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
		_transform->SetPosition(pos);
	}

	void	GameObject3D::SetLocalRotation(Math::QXvec3 rot)
	{
		_transform->SetRotation(rot);
	}

	void	GameObject3D::SetLocalScale(Math::QXvec3 scale)
	{
		_transform->SetScale(scale);
	}

	void	GameObject3D::SetTransformValue(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale)
	{
		_transform->SetPosition(pos);
		_transform->SetRotation(rot);
		_transform->SetScale(scale);
	}
	GameObject3D& GameObject3D::operator=(const GameObject3D& object)
	{
		_transform = object._transform;
		_component = object._component;
		_name = object._name;
		_layer = object._layer;
		_isStatic = object._isStatic;
		_isActive = object._isActive;

		return *this;
	}
}
