#include "Resources/Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <iostream>

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

	Shader::Shader(const QXstring& file, EShaderType type) noexcept :
		_id {(QXuint)-1},
		_type {type}
	{
		switch (_type)
		{
			case EShaderType::VERTEX: CreateVertexShader(file.c_str());	break;
			case EShaderType::FRAGMENT: CreateFragmentShader(file.c_str()); break;
		
			default: break;
		}
	}

	Shader::~Shader() noexcept
	{
		glDeleteShader(_id);
	}

#pragma region Functions

	std::vector<QXuint>	Shader::Compile(const QXchar* file, EShaderType shaderKind) noexcept
	{
		QXstring code { ReadFile(file) };

		std::vector<QXuint> vec;
		return vec;
	}

	void Shader::CreateFragmentShader(const QXchar* file) noexcept
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
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
		}
	}

	void Shader::CreateVertexShader(const QXchar* file) noexcept
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
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
		}
	}

	QXstring Shader::ReadFile(const QXchar* file) noexcept
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
