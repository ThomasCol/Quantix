#include "Resources/Material.h"

#include<glad/glad.h>

namespace Quantix::Resources
{
#pragma region Constructors

	Material::Material(ShaderProgram* program) :
		_program {program}
	{}

	Material::~Material()
	{}

#pragma endregion

#pragma region Functions
	
	void Material::SendData()
	{
		SetFloat3("material.ambient", ambient.e);
		SetFloat3("material.diffuse", diffuse.e);
		SetFloat3("material.specular", specular.e);
		SetFloat("material.shininess", shininess);
		if (_mainTexture != nullptr)
			SetUint("material.texture", _mainTexture->GetId());
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