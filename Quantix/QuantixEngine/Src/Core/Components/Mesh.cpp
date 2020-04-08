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

	void Mesh::SendDataToShader(Core::Platform::AppInfo& info, std::vector<Light*>& lights, Components::Camera* cam)
	{
		Math::QXmat4 trs {Math::QXmat4::CreateTRSMatrix({0, 0, -1.f}, {0, (QXfloat)info.currentTime, 0}, { 1, 1, 1 })};
		Math::QXmat4 proj {Math::QXmat4::CreateProjectionMatrix(info.width, info.height, 0.1f, 1000.f, 80.f)};
		Math::QXmat4 view {cam->GetLookAt()};

		_material->UseShader();

		_material->SetMat4("TRS", trs);
		_material->SetMat4("proj", proj);
		_material->SetMat4("view", view);
		_material->SetFloat3("viewPos", cam->GetPos().e);

		QXsizei size = (lights.size() <= 10 ? lights.size() : 10);

		for (QXsizei i = 0; i < size; ++i)
		{
			std::string lightName{ "lightArray[" + std::to_string(i) + "]." };
			_material->SetFloat3(lightName + "ambient", lights[i]->ambient.e);
			_material->SetFloat3(lightName + "diffuse", lights[i]->diffuse.e);
			_material->SetFloat3(lightName + "specular", lights[i]->specular.e);
			_material->SetFloat3(lightName + "direction", lights[i]->direction.e);
			_material->SetFloat3(lightName + "position", lights[i]->position.e);

			_material->SetFloat(lightName + "constant", lights[i]->constant);
			_material->SetFloat(lightName + "linear", lights[i]->linear);
			_material->SetFloat(lightName + "quadratic", lights[i]->quadratic);
			_material->SetFloat(lightName + "cutOff", lights[i]->cutOff);
			_material->SetFloat(lightName + "outerCutOff", lights[i]->outerCutOff);
			
			_material->SetInt(lightName + "type", (QXint)lights[i]->type);
		}

		_material->SendData();
	}
}
