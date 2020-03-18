#include "Core/DataStructures/ResourcesManager.h"

namespace Quantix::Core::DataStructure
{
#pragma region Constructors

	ResourcesManager::~ResourcesManager()
	{
		for (auto it = _materials.begin(); it != _materials.end(); ++it)
			delete it->second;

		for (auto it = _models.begin(); it != _models.end(); ++it)
			delete it->second;

		for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
			delete it->second;

		for (auto it = _programs.begin(); it != _programs.end(); ++it)
			delete it->second;

		for (auto it = _textures.begin(); it != _textures.end(); ++it)
			delete it->second;
	}

#pragma endregion

#pragma region Functions

	Material* ResourcesManager::CreateMaterial(const QXstring& filePath)
	{
		auto it = _materials.find(filePath);
		if (it != _materials.end())
		{
			return it->second;
		}

		Material* material = new Material(CreateShaderProgram("../QuantixEngine/Media/Shader/vertexShader.vert", "../QuantixEngine/Media/Shader/fragmentShader.frag"));
		material->diffuse = { 0.5, 0.5, 0.5 };
		material->specular = { 1, 1, 1 };
		material->ambient = { 0.2, 0.2, 0.2 };
		material->shininess = 32;

		return material;
	}

	Components::Mesh* ResourcesManager::CreateMesh(const QXstring& modelPath, const QXstring& vertexPath, const QXstring& fragmentPath)
	{
		Components::Mesh* mesh = new Components::Mesh(CreateModel(modelPath), CreateMaterial(vertexPath));

		return mesh;
	}

	Model* ResourcesManager::CreateModel(const QXstring& filePath)
	{
		auto it = _models.find(filePath);
		if (it != _models.end())
		{
			return it->second;
		}

		Model* model = new Model(filePath);
		_models[filePath] = model;
		return model;
	}

	ShaderProgram* ResourcesManager::CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath)
	{
		auto it = _programs.find(vertexPath + fragmentPath);
		if (it != _programs.end())
		{
			return it->second;
		}

		ShaderProgram* program = new ShaderProgram(CreateShader(vertexPath, EShaderType::VERTEX), CreateShader(fragmentPath, EShaderType::FRAGMENT));
		_programs[vertexPath + fragmentPath] = program;
		return program;
	}

	Shader* ResourcesManager::CreateShader(const QXstring& filePath, EShaderType type)
	{
		auto it = _shaders.find(filePath);
		if (it != _shaders.end())
		{
			return it->second;
		}

		Shader* shader = new Shader(filePath, type);
		_shaders[filePath] = shader;
		return shader;
	}

#pragma endregion
}