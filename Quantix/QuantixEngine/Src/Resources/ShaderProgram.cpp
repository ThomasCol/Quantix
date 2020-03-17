#include "Resources/ShaderProgram.h"

#include <glad/glad.h>
#include <iostream>

#include "Resources/Shader.h"

namespace Quantix::Resources
{
#pragma region Constructors

	ShaderProgram::ShaderProgram(const ShaderProgram& program) noexcept :
		_id {program._id}
	{}

	ShaderProgram::ShaderProgram(ShaderProgram&& program) noexcept :
		_id {std::move(program._id)}
	{}

	ShaderProgram::ShaderProgram(const QXchar* vertexShader, const QXchar* fragmentShader) noexcept :
		_id { (QXuint)-1}
	{
		Shader vertex { vertexShader, EShaderType::VERTEX };
		Shader fragment { fragmentShader, EShaderType::FRAGMENT };

		_id = glCreateProgram();

		glAttachShader(_id, vertex.GetId());
		glAttachShader(_id, fragment.GetId());

		glLinkProgram(_id);

		int  success;
		char info_log[512];
		glGetShaderiv(_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << info_log << std::endl;
		}
	}

	ShaderProgram::~ShaderProgram() noexcept
	{
		glDeleteProgram(_id);
	}

#pragma endregion

#pragma region Functions

	QXuint ShaderProgram::GetLocation(QXstring location) noexcept
	{
		if (_locations.count(location) == 0)
		{
			QXuint new_id { (QXuint)glGetUniformLocation(_id, location.c_str()) };

			if (new_id == -1)
				return -1;

			_locations[location] = new_id;

			return new_id;
		}

		return _locations[location];
	}

	void ShaderProgram::Use() noexcept
	{
		glUseProgram(_id);
	}

	void ShaderProgram::Unuse() noexcept
	{
		glUseProgram(0);
	}

#pragma endregion
}
