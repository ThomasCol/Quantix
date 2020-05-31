#include "Resources/Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <iostream>

#include "Core/Debugger/Logger.h"

namespace Quantix::Resources
{
#pragma region Constructors

	Shader::Shader(const Shader& shader) noexcept :
		_id {shader._id},
		_type {shader._type}
	{}

	Shader::Shader(Shader&& shader) noexcept :
		_id {std::move(shader._id)},
		_type {std::move(shader._type)}
	{}

	Shader::Shader(QXstring file, EShaderType type) noexcept :
		_id {(QXuint)-1},
		_type {type}
	{
		switch (_type)
		{
			case EShaderType::VERTEX: CreateVertexShader(file);	break;
			case EShaderType::GEOMETRY: CreateGeometryShader(file); break;
			case EShaderType::FRAGMENT: CreateFragmentShader(file); break;
			default: break;
		}
	}

	Shader::~Shader() noexcept
	{
		glDeleteShader(_id);
	}

#pragma region Functions

	void Shader::CreateFragmentShader(QXstring file) noexcept
	{
		QXstring code = ReadFile(file);

		_id = glCreateShader(GL_FRAGMENT_SHADER);
		const char* str = code.c_str();
		glShaderSource(_id, 1, &str, nullptr);
		glCompileShader(_id);

		int  success;
		char info_log[512];
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, info_log);
			LOG(ERROR, QXstring("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n") + info_log);
		}
	}

	void Shader::CreateVertexShader(QXstring file) noexcept
	{
		QXstring code = ReadFile(file);
		_id = glCreateShader(GL_VERTEX_SHADER);
		const char* str = code.c_str();
		glShaderSource(_id, 1, &str, nullptr);
		glCompileShader(_id);

		int  success;
		char info_log[512];
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, info_log);
			LOG(ERROR, QXstring("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n") + info_log);
		}
	}

	void Shader::CreateGeometryShader(QXstring file) noexcept
	{
		QXstring code = ReadFile(file);
		_id = glCreateShader(GL_GEOMETRY_SHADER);
		const char* str = code.c_str();
		glShaderSource(_id, 1, &str, nullptr);
		glCompileShader(_id);

		int  success;
		char info_log[512];
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, info_log);
			LOG(ERROR, QXstring("ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n") + info_log);
		}
	}

	QXstring Shader::ReadFile(QXstring file) noexcept
	{
		std::ifstream shader(file, std::ios::ate);
		if (!shader.is_open())
			return nullptr;

		QXsizei file_size = (QXsizei)shader.tellg();
		QXstring buffer(file_size, ' ');

		shader.seekg(0);
		shader.read(&buffer[0], file_size);
		shader.close();

		buffer[file_size] = '\0';

		const QXchar* code = buffer.c_str();

		return code;
	}

#pragma endregion
}
