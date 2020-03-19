#include "..\..\..\Include\Core\DataStructure\GameObject.h"

Core::DataStructure::GameObject::GameObject() noexcept
{
}

Core::DataStructure::GameObject::GameObject(const GameObject& object) noexcept :
					//_transform{ new Transform(*object._transorm) },
					_name{ object._name },
					_layer{ object._layer },
					_isStatic{ object._isStatic }
{
	for (size_t i = 0; i < object._component.size(); i++)
	{
		_component.push_back(object._component[i]->Copy());
	}
}

Core::DataStructure::GameObject::GameObject(GameObject&& object) noexcept :
					_component{ std::move(object._component) },
					//_transform{ std::move(object._transform },
					_name{ std::move(object._name) },
					_layer{ std::move(object._layer) },
					_isStatic{ std::move(object._isStatic) }
{
}

Core::DataStructure::GameObject::GameObject(std::string name, const QXbool& isStatic) :
					_name{ name },
					_layer{ 0 },
					_isStatic{ isStatic }
{
}

Core::DataStructure::GameObject::~GameObject()
{
	for (size_t i = 0; i < _component.size(); i++)
	{
		if (_component[i] != nullptr)
		{
			_component[i]->Destroy();
			delete _component[i];
		}
	}
}

void Core::DataStructure::GameObject::AddChild(GameObject* object)
{
	//_transform.AddChild(object->_transform);
}

void Core::DataStructure::GameObject::CleanDestroyedComponents()
{
	for (unsigned i{ 0 }; i < _component.size(); ++i)
	{
		if (_component[i]->IsDestroyed())
		{
			_component[i]->Destroy();
			delete _component[i];
			_component.erase(_component.begin() + i--);
		}
	}
}

void Core::DataStructure::GameObject::SetGlobalPosition(Math::QXvec3 pos)
{
	//_transform.SetGlobalPosition(pos);
}

void Core::DataStructure::GameObject::SetGlobalRotation(Math::QXvec3 rot)
{
	//_transform.SetGlobalRotation(pos);
}

void Core::DataStructure::GameObject::SetLocalPosition(Math::QXvec3 pos)
{
	//_transform.SetLocalPosition(pos);
}

void Core::DataStructure::GameObject::SetLocalRotation(Math::QXvec3 rot)
{
	//_transform.SetLocalRotation(pos);
}

void Core::DataStructure::GameObject::SetLocalScale(Math::QXvec3 scale)
{
	//_transform.SetLocalScale(pos);
}

void Core::DataStructure::GameObject::SetTransform(const Math::QXmat4& mat)
{
	//_transform.SetTransform(mat);
}

void Core::DataStructure::GameObject::SetTransform(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale)
{
	//_transform.SetTransform(pos, rot, scale);
}
