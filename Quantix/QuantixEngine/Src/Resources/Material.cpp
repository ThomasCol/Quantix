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
	.property("Tile", &Quantix::Resources::Material::tile)
	.property("Diffuse", &Quantix::Resources::Material::GetDiffuseTexture, &Quantix::Resources::Material::SetDiffuseTexture)
	.property("Emissive", &Quantix::Resources::Material::GetEmissiveTexture, &Quantix::Resources::Material::SetEmissiveTexture)
	.method("SetChanged", &Quantix::Resources::Material::HasChanged)
	.method("GetPath", &Quantix::Resources::Material::GetPath);
}

namespace Quantix::Resources
{
#pragma region Constructors

	Material::Material(ShaderProgram* program) noexcept :
		_program {program},
		_diffuse {nullptr}
	{
		program->Use();
		SetInt("material.shadowMap", 0);
		SetInt("material.pointShadowMap", 1);
		SetInt("material.diffuseTexture", 2);
		SetInt("material.emissiveTexture", 3);
	}

	Material::~Material() noexcept
	{}

#pragma endregion

#pragma region Functions

	QXbool	Material::IsReady() noexcept
	{
		if (!_diffuse)
			return true;
		return _diffuse->IsReady();
	}
	
	void Material::SendData(QXuint shadowTexture, QXbool isPointLight) noexcept
	{
		SetFloat3("material.ambient", ambient.e);
		SetFloat3("material.diffuse", diffuse.e);
		SetFloat3("material.specular", specular.e);
		SetFloat("material.shininess", shininess);

		SetFloat2("tile", tile.e);

		if (isPointLight)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, shadowTexture);
			SetFloat("farPlane", 100.f);
		}
		else
		{
			SetInt("material.shadowMap", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, shadowTexture);
		}
	}

	void Material::SendTextures() noexcept
	{
		if (_diffuse && _diffuse->IsReady())
		{
			SetInt("material.isTextured", 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, _diffuse->GetId());
			if (_emissive && _emissive->IsReady())
			{
				SetInt("material.hasEmissive", 1);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, _emissive->GetId());
			}
			else
				SetInt("material.hasEmissive", 0);
		}
		else
		{
			SetInt("material.hasEmissive", 0);
			SetInt("material.isTextured", 0);
		}
	}

	void Material::SetFloat(QXstring location, QXfloat value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1f(location_id, value);
	}
	
	void Material::SetFloat2(QXstring location, const QXfloat* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform2fv(location_id, 1, value);
	}
	
	void Material::SetFloat3(QXstring location, const QXfloat* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform3fv(location_id, 1, value);
	}
	
	void Material::SetFloat4(QXstring location, const QXfloat* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1fv(location_id, 4, value);
	}

	void Material::SetInt(QXstring location, QXint value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1i(location_id, value);
	}
	
	void Material::SetInt2(QXstring location, const QXint* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;
		glUniform1iv(location_id, 2, value);
	}
	
	void Material::SetInt3(QXstring location, const QXint* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1iv(location_id, 3, value);
	}
		
	void Material::SetMat4(QXstring location, Math::QXmat4 value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniformMatrix4fv(location_id, 1, false, value.array);
	}

	void Material::SetTexture(QXstring location, const Texture& texture) noexcept
	{
		SetUint(location, texture.GetId());
	}

	void Material::SetUint(QXstring location, QXuint value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1ui(location_id, value);
	}
	
	void Material::SetUint2(QXstring location, const QXuint* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1uiv(location_id, 2, value);
	}
	
	void Material::SetUint3(QXstring location, const QXuint* value) noexcept
	{
		QXuint location_id {_program->GetLocation(location)};

		if (location_id == -1)
			return;

		glUniform1uiv(location_id, 3, value);
	}

	void Material::HasChanged(QXbool changed) noexcept
	{
		textureHasChanged = changed;
	}

#pragma endregion
}
