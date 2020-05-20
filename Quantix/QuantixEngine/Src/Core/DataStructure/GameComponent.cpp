#include "Core\DataStructure\GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::DataStructure::GameComponent>("GameComponent")
	.constructor<>()
	.constructor<const Quantix::Core::DataStructure::GameComponent&>()
	.constructor<Quantix::Core::DataStructure::GameComponent&&>()
	.constructor<const QXstring&, const QXbool&, const QXbool&, const QXbool&>()
	.enumeration<Quantix::Core::DataStructure::Layer>("Layer")
					 (rttr::value("Default", Quantix::Core::DataStructure::Layer::DEFAULT),
					 rttr::value("Player", Quantix::Core::DataStructure::Layer::PLAYER),
					 rttr::value("Selectable", Quantix::Core::DataStructure::Layer::SELECTABLE),
					 rttr::value("KillZone", Quantix::Core::DataStructure::Layer::KILLZONE))
	.property("layer", &Quantix::Core::DataStructure::GameComponent::_layer);
}

namespace Quantix::Core::DataStructure
{
	GameComponent::GameComponent(const GameComponent& object) noexcept :
		_name{ object._name },
		_layer{ object._layer },
		_isStatic{ object._isStatic },
		_isActive{ object._isActive },
		_toRender{ QX_FALSE },
		_is2D{ object._is2D },
		_is3D{ object._is3D }
	{
		for (size_t i = 0; i < object._component.size(); i++)
		{
			_component.push_back(object._component[i]);
		}
	}

	GameComponent::GameComponent(GameComponent&& object) noexcept :
		_component{ std::move(object._component) },
		_name{ std::move(object._name) },
		_layer{ std::move(object._layer) },
		_isStatic{ std::move(object._isStatic) },
		_isActive{ std::move(object._isActive) },
		_toRender{ std::move(object._toRender) },
		_is2D{ std::move(object._is2D) },
		_is3D{ std::move(object._is3D) }
	{
	}

	GameComponent::GameComponent(const QXstring& name, const QXbool& is2D, const QXbool& is3D, const QXbool& isStatic) noexcept :
		_name{ name },
		_layer{ 0 },
		_isStatic{ isStatic },
		_isActive{ false },
		_toRender { false },
		_is2D{ is2D },
		_is3D{ is3D }
	{
	}

	GameComponent::~GameComponent()
	{
		for (size_t i = 0; i < _component.size(); i++)
		{
			if (_component[i] != nullptr)
			{
				//_component[i]->Destroy();
				delete _component[i];
			}
		}
	}

	void GameComponent::CleanDestroyedComponents()
	{
		for (unsigned i{ 0 }; i < _component.size(); ++i)
		{
			if (_component[i]->IsDestroyed())
			{
				//_component[i]->Destroy();
				delete _component[i];
				_component.erase(_component.begin() + i--);
			}
		}
	}

	GameComponent& GameComponent::operator=(const GameComponent& gc)
	{
		_component = gc._component;
		_name = gc._name;
		_layer = gc._layer;
		_isStatic = gc._isStatic;
		_isActive = gc._isActive;
		_toRender = gc._toRender;

		return *this;
	}
}
