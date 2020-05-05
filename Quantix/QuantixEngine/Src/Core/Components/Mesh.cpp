#include "Core/Components/Mesh.h"

#include <iostream>
#include "MathDefines.h"
#include "Core/Profiler/Profiler.h"
#include "Core/DataStructure/GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Mesh>("Mesh")
	.constructor<>()
	.constructor<const Quantix::Core::Components::Mesh&>()
	.constructor<Quantix::Core::Components::Mesh&&>()
	.property("Model", &Quantix::Core::Components::Mesh::_model)
	.property("Material", &Quantix::Core::Components::Mesh::_material);
}

namespace Quantix::Core::Components
{
	Mesh* Mesh::Copy() const noexcept
	{
		return new Mesh(*this);
	}

	void Mesh::Init(Core::DataStructure::GameComponent* object) noexcept
	{
		_object = object;
		object->SetRender(true);
		_isDestroyed = false;
		_isEnable = true;
		_material = new Resources::Material();
	}

	QXbool	Mesh::IsEnable() noexcept
	{
		if (!_model || !_model->IsReady())
			return false;
		else if (!_isMaterialInit && _material->IsReady())
		{
			if (_material->GetDiffuseTexture())
				textureID = _material->GetDiffuseTexture()->GetId();
			_isMaterialInit = true;
		}
		return _isEnable;
	}

	void Mesh::SetActive(QXbool enable) noexcept
	{
		_isEnable = enable;
		_object->SetRender(enable);
	}
}
