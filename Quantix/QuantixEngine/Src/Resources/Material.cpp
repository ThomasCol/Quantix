#include "Resources/Material.h"

#include<glad/glad.h>

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Resources::Material>("Material")
	.constructor<>()
	.constructor<Quantix::Resources::ShaderProgram*>()
	.property("ambient", &Quantix::Resources::Material::ambient)
	.property("diffuse", &Quantix::Resources::Material::diffuse)
	.property("specular", &Quantix::Resources::Material::specular)
	.property("shininess", &Quantix::Resources::Material::shininess)
	.property("Diffuse", &Quantix::Resources::Material::GetDiffuseTexture, &Quantix::Resources::Material::SetDiffuseTexture)
	.property("Emissive", &Quantix::Resources::Material::GetEmissiveTexture, &Quantix::Resources::Material::SetEmissiveTexture)
	.method("GetPath", &Quantix::Resources::Material::GetPath);
}

namespace Quantix::Resources
{
#pragma region Constructors

	Material::Material(ShaderProgram* program) :
		_program {program},
		_diffuse {nullptr}
	{}

	Material::~Material()
	{}

#pragma endregion

#pragma region Functions

	QXbool	Material::IsReady()
	{
		if (!_diffuse)
			return true;
		return _diffuse->IsReady();
	}
	
	void Material::SendData(QXuint shadowTexture)
	{
		SetFloat3("material.ambient", ambient.e);
		SetFloat3("material.diffuse", diffuse.e);
		SetFloat3("material.specular", specular.e);
		SetFloat("material.shininess", shininess);

		SetInt("material.shadowMap", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowTexture);

		if (_diffuse && _diffuse->IsReady())
		{
			SetInt("material.isTextured", 1);

			SetInt("material.diffuseTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _diffuse->GetId());
			if (_emissive && _emissive->IsReady())
			{
				SetInt("material.hasEmissive", 1);
				SetInt("material.emissiveTexture", 2);
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, _emissive->GetId());
			}
			else
				SetInt("material.hasEmissive", 0);
		}
		else
			SetInt("material.textured", 0);
	}

	void Material::SetFloat(QXstring location, QXfloat value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1f(location_id, value);
	}
	
	void Material::SetFloat2(QXstring location, const QXfloat* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform2fv(location_id, 1, value);
	}
	
	void Material::SetFloat3(QXstring location, const QXfloat* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform3fv(location_id, 1, value);
	}
	
	void Material::SetFloat4(QXstring location, const QXfloat* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1fv(location_id, 4, value);
	}

	void Material::SetInt(QXstring location, QXint value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1i(location_id, value);
	}
	
	void Material::SetInt2(QXstring location, const QXint* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;
		glUniform1iv(location_id, 2, value);
	}
	
	void Material::SetInt3(QXstring location, const QXint* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1iv(location_id, 3, value);
	}

	void Material::SetLightArray(std::vector<Core::Components::Light*>& lights)
	{
		QXsizei size = (lights.size() <= 10 ? lights.size() : 10);

		for (QXsizei i = 0; i < size; ++i)
		{
			std::string lightName{ "lightArray[" + std::to_string(i) + "]." };
			SetFloat3(lightName + "ambient", lights[i]->ambient.e);
			SetFloat3(lightName + "diffuse", lights[i]->diffuse.e);
			SetFloat3(lightName + "specular", lights[i]->specular.e);
			SetFloat3(lightName + "direction", lights[i]->direction.e);
			SetFloat3(lightName + "position", lights[i]->position.e);

			SetFloat(lightName + "constant", lights[i]->constant);
			SetFloat(lightName + "linear", lights[i]->linear);
			SetFloat(lightName + "quadratic", lights[i]->quadratic);
			SetFloat(lightName + "cutOff", lights[i]->cutOff);
			SetFloat(lightName + "outerCutOff", lights[i]->outerCutOff);

			SetInt(lightName + "type", (QXint)lights[i]->type);
		}
	}
		
	void Material::SetMat4(QXstring location, Math::QXmat4 value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniformMatrix4fv(location_id, 1, false, value.array);
	}

	void Material::SetTexture(QXstring location, const Texture& texture)
	{
		SetUint(location, texture.GetId());
	}

	void Material::SetUint(QXstring location, QXuint value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1ui(location_id, value);
	}
	
	void Material::SetUint2(QXstring location, const QXuint* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1uiv(location_id, 2, value);
	}
	
	void Material::SetUint3(QXstring location, const QXuint* value)
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1uiv(location_id, 3, value);
	}

#pragma endregion
}
