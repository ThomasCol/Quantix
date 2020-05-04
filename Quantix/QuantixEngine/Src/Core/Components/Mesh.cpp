#include "Core/Components/Mesh.h"

#include <iostream>
#include "MathDefines.h"
#include "Core/Profiler/Profiler.h"
#include "Core/DataStructure/GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Mesh>("Mesh")
	.constructor<>()
	.constructor<Quantix::Resources::Model*, Quantix::Resources::Material*>()
	.constructor<const Quantix::Core::Components::Mesh&>()
	.constructor<Quantix::Core::Components::Mesh&&>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.property("Model", &Quantix::Core::Components::Mesh::_model)
	.property("Material", &Quantix::Core::Components::Mesh::_material);
}

namespace Quantix::Core::Components
{
	Mesh::Mesh(Resources::Model* model, Resources::Material* material):
		_model {model},
		_material {material}
	{}

	Mesh::Mesh(Core::DataStructure::GameComponent* object): 
		Quantix::Core::DataStructure::Component(object)
	{
		object->SetRender(true);
	}

	Mesh::Mesh(const Mesh& mesh)
	{
		_model = mesh._model;
		_material = mesh._material;
	}

	Mesh* Mesh::Copy() const
	{
		return new Mesh(*this);
	}

	void Mesh::Init(Core::DataStructure::GameComponent* object)
	{
		_object = object;
		object->SetRender(true);
		_isDestroyed = false;
		_isEnable = true;
		_material = new Resources::Material();
	}

	QXbool	Mesh::IsEnable()
	{
		if (!_model || !_model->IsReady())
			return false;
		else if (!_isMaterialInit && _material->IsReady())
		{
			if (_material->GetMainTexture())
				textureID = _material->GetMainTexture()->GetId();
			_isMaterialInit = true;
		}
		return _isEnable;
	}

	void Mesh::SetActive(QXbool enable)
	{
		_isEnable = enable;
		_object->SetRender(enable);
	}
}
