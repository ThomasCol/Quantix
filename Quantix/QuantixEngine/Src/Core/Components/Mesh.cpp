#include "Core/Components/Mesh.h"

#include <iostream>
#include "MathDefines.h"
#include "Core/Profiler/Profiler.h"

namespace Quantix::Core::Components
{
	Mesh::Mesh(Resources::Model* model, Resources::Material* material):
		_model {model},
		_material {material}
	{}
}
