#include "Resources/ShaderProgram.h"

#include <glad/glad.h>
#include <iostream>

#include "Resources/Shader.h"
#include "Core/Debugger/Logger.h"

namespace Quantix::Resources
{
#pragma region Constructors

	ShaderProgram::ShaderProgram(const ShaderProgram& program) noexcept :
		_id {program._id}
	{}

	ShaderProgram::ShaderProgram(ShaderProgram&& program) noexcept :
		_id {std::move(program._id)}
	{}

	ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) noexcept :
		_id { (QXuint)-1}
	{
		_id = glCreateProgram();

		glAttachShader(_id, vertexShader->GetId());
		glAttachShader(_id, fragmentShader->GetId());

		glLinkProgram(_id);

		int  success;
		char info_log[512];
		glGetProgramiv(_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_id, 512, NULL, info_log);
			LOG(ERROR, QXstring("ERROR::SHADER::PROGRAM::LINK_FAILED") + info_log);
		}

		/*glGenBuffers(1, &_lightUniformBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, _lightUniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, 10 * sizeof(), &Lights[0], GL_DYNAMIC_DRAW);*/
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
