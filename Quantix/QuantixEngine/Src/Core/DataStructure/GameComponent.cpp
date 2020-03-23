#include "..\..\..\Include\Core\DataStructure\GameObject.h"

Core::DataStructure::GameComponent::GameComponent() noexcept
{
}

Core::DataStructure::GameComponent::GameComponent(const GameComponent& object) noexcept :
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

Core::DataStructure::GameComponent::GameComponent(GameComponent&& object) noexcept :
					_component{ std::move(object._component) },
					//_transform{ std::move(object._transform },
					_name{ std::move(object._name) },
					_layer{ std::move(object._layer) },
					_isStatic{ std::move(object._isStatic) }
{
}

Core::DataStructure::GameComponent::GameComponent(std::string name, const QXbool& isStatic) :
					_name{ name },
					_layer{ 0 },
					_isStatic{ isStatic }
{
}

Core::DataStructure::GameComponent::~GameComponent()
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
