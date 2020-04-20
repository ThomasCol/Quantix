#include "Core/Components/Mesh.h"

#include <iostream>
#include "MathDefines.h"
#include "Core/Profiler/Profiler.h"
#include "Core/DataStructure/GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Mesh>("Mesh")
	.constructor<Quantix::Resources::Model*, Quantix::Resources::Material*>()
	.constructor<const Quantix::Core::Components::Mesh&>()
	.constructor<Quantix::Core::Components::Mesh&&>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.property("Material", &Quantix::Core::Components::Mesh::GetMaterial, &Quantix::Core::Components::Mesh::SetMaterial);
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

	Mesh* Mesh::Copy() const
	{
		return new Mesh(*this);
	}
	void Mesh::SetActive(QXbool enable)
	{
		_isEnable = enable;
		_object->SetRender(enable);
	}
}
