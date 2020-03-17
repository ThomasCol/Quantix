#include "Core/Components/Mesh.h"

#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "MathDefines.h"

namespace Quantix::Core::Components
{
	Mesh::Mesh(const QXchar* objFile, const QXchar* vertexShader, const QXchar* fragmentShader):
		_model {},
		_material {vertexShader, fragmentShader}
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFile))
			std::cout << warn + err << std::endl;

		_model = Resources::Model(attrib, shapes);

		_material.SetMainTexture("../QuantixEngine/Media/Textures/wall.jpg");
		_material.diffuse = {0.5, 0.5, 0.5};
		_material.specular = {1, 1, 1};
		_material.ambient = {0.2, 0.2, 0.2};
		_material.shininess = 32;

		if (materials.size() == 0)
			return;
		
		//_material.SetMainTexture(materials[0].ambient_texname.c_str());

	}

	void Mesh::SendDataToShader(Core::Plateform::AppInfo& info, std::vector<Light*>& lights)
	{
		Math::QXmat4 trs {Math::QXmat4::CreateTRSMatrix({0, 5, -1.f}, {0, (QXfloat)info.currentTime, 0}, { 5, 5, 5 })};
		Math::QXmat4 proj {Math::QXmat4::CreateProjectionMatrix(info.width, info.height, 0.001f, 10000.f, 80.f)};
		Math::QXvec3 pos = { 0, 0, 20 };
		Math::QXvec3 dir = { 0, 0, -1 };
		Math::QXmat4 view {Math::QXmat4::CreateLookAtMatrix(pos, pos + dir, Math::QXvec3::up)};

		_material.UseShader();

		_material.SetMat4("TRS", trs);
		_material.SetMat4("proj", proj);
		_material.SetMat4("view", view);
		_material.SetFloat3("viewPos", pos.e);

		QXuint size = lights.size() <= 10 ? lights.size() : 10;

		for (QXuint i = 0; i < size; ++i)
		{
			std::string lightName{ "lightArray[" + std::to_string(i) + "]." };
			_material.SetFloat3(lightName + "ambient", lights[i]->ambient.e);
			_material.SetFloat3(lightName + "diffuse", lights[i]->diffuse.e);
			_material.SetFloat3(lightName + "specular", lights[i]->specular.e);
			_material.SetFloat3(lightName + "direction", lights[i]->direction.e);
			_material.SetFloat3(lightName + "position", lights[i]->position.e);

			_material.SetFloat(lightName + "constant", lights[i]->constant);
			_material.SetFloat(lightName + "linear", lights[i]->linear);
			_material.SetFloat(lightName + "quadratic", lights[i]->quadratic);
			_material.SetFloat(lightName + "cutOff", lights[i]->cutOff);
			_material.SetFloat(lightName + "outerCutOff", lights[i]->outerCutOff);
			
			_material.SetInt(lightName + "type", (QXint)lights[i]->type);
		}

		_material.SendData();
	}
}
