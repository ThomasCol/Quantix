#include "Core/DataStructure/GameObject3D.h"

#include "Core/Components/CubeCollider.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::DataStructure::GameObject3D>("GameObject3D")
	.constructor<>()
	.constructor<const QXstring&, const Math::QXvec3&, const Math::QXquaternion&, const Math::QXvec3&>()
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
	GameObject3D::GameObject3D(const QXstring& name, const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& sca) noexcept :
		GameComponent(name, QX_FALSE, QX_TRUE),
		_transform { new Physic::Transform3D(pos, rot, sca, this) }
	{}

	GameObject3D::GameObject3D(const GameObject3D& g3d) noexcept :
		GameComponent(g3d),
		_transform{ g3d._transform }
	{
	}

	GameObject3D::GameObject3D(GameObject3D&& g3d) noexcept :
		GameComponent(std::move(g3d)),
		_transform{ std::move(g3d._transform) }
	{
	}

	GameObject3D::~GameObject3D()
	{
		// Destroy Component
		std::vector<Core::DataStructure::Component*> components = GetComponents<Core::DataStructure::Component>();
		for (QXsizei i = 0; i < components.size(); ++i)
		{
			components[i]->Destroy();
			delete components[i];
		}

		GetTransform()->GetParent()->RemoveChild(GetTransform());

		delete _transform;
	}

	void	GameObject3D::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
		std::vector<Components::Light>& lights, Platform::AppInfo& info, QXbool isPlaying)
	{
		if (_toRender)
		{
			Core::Components::Mesh* mesh = GetComponent<Core::Components::Mesh>();

			if (mesh && mesh->IsEnable())
				meshes.push_back(mesh);
		}

		for (Physic::Transform3D* child : _transform->GetChilds())
			child->GetObject()->Update(meshes, colliders, lights, this, info, isPlaying);
	}

	void	GameObject3D::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
		std::vector<Components::Light>& lights, const GameObject3D* parentObject, Platform::AppInfo& info, QXbool isPlaying)
	{
		if (_toRender)
		{
			Core::Components::Mesh* mesh = GetComponent<Core::Components::Mesh>();

			if (mesh && mesh->IsEnable())
				meshes.push_back(mesh);
		}

		Core::Components::ICollider* collider = GetComponent<Core::Components::ICollider>(true);
		if (collider && collider->toRender)
		{
			colliders.push_back(collider);
		}

		Core::Components::Light* light = GetComponent<Core::Components::Light>();
		if (light && light->IsEnable())
		{
			light->position = _transform->GetPosition();
			light->direction = _transform->GetForward();
			lights.push_back(*light);
		}

		if (isPlaying)
		{
			if (_toUpdate)
			{
				std::vector<Components::Behaviour*> behaviors = GetComponents<Components::Behaviour>(true);
				for (QXsizei i = 0; i < behaviors.size(); ++i)
					behaviors[i]->Update(info.deltaTime);
			}
		}

		_transform->Update(parentObject->GetTransform());

		for (Physic::Transform3D* child : _transform->GetChilds())
			child->GetObject()->Update(meshes, colliders, lights, this, info, isPlaying);
	}

	void	GameObject3D::Start()
	{
		if (_toUpdate)
		{
			std::vector<Components::Behaviour*> behaviors = GetComponents<Components::Behaviour>();
			for (QXsizei i = 0; i < behaviors.size(); ++i)
				behaviors[i]->Start();
		}

		for (Physic::Transform3D* child : _transform->GetChilds())
			child->GetObject()->Start();
	}
	
	void	GameObject3D::Awake()
	{
		if (_toUpdate)
		{
			std::vector<Components::Behaviour*> behaviors = GetComponents<Components::Behaviour>();
			for (QXsizei i = 0; i < behaviors.size(); ++i)
				behaviors[i]->Awake();
		}

		for (Physic::Transform3D* child : _transform->GetChilds())
			child->GetObject()->Awake();
	}

	void GameObject3D::Destroy()	
	{
		std::cout << "Destroy" << std::endl;
	}

	void	GameObject3D::CallOnTrigger(GameObject3D* other)
	{
		if (_toUpdate)
		{
			std::vector<Components::Behaviour*> behaviors = GetComponents<Components::Behaviour>(true);
			for (QXsizei i = 0; i < behaviors.size(); ++i)
				behaviors[i]->OnTrigger(this, other);
		}
	}

	void	GameObject3D::CallOnContact(GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal)
	{
		if (_toUpdate)
		{
			std::vector<Components::Behaviour*> behaviors = GetComponents<Components::Behaviour>(true);
			for (QXsizei i = 0; i < behaviors.size(); ++i)
				behaviors[i]->OnCollision(this, other, position, normal);
		}
	}

	void	GameObject3D::SetGlobalPosition(Math::QXvec3 pos)
	{
	}

	void	GameObject3D::SetGlobalRotation(Math::QXquaternion rot)
	{
	}

	void	GameObject3D::SetLocalPosition(Math::QXvec3 pos)
	{
		_transform->SetPosition(pos);
	}

	void	GameObject3D::SetLocalRotation(Math::QXquaternion rot)
	{
		_transform->SetRotation(rot);
	}

	void	GameObject3D::SetLocalScale(Math::QXvec3 scale)
	{
		_transform->SetScale(scale);
	}

	void	GameObject3D::SetTransformValue(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& scale)
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
