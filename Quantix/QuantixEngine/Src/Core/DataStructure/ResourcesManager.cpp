#include "Core/DataStructure/ResourcesManager.h"

#include <istream>

#include "Core/Debugger/Logger.h"
#include "Core/Threading/TaskSystem.hpp"

namespace Quantix::Core::DataStructure
{
#pragma region Constructors

	ResourcesManager::~ResourcesManager()
	{
		for (auto it = _materials.begin(); it != _materials.end(); ++it)
		{
			SaveMaterialToCache(it->first, it->second);
			delete it->second;
		}

		for (auto it = _models.begin(); it != _models.end(); ++it)
		{
			SaveModelToCache(it->first, it->second);
			delete it->second;
		}

		for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
			delete it->second;

		for (auto it = _programs.begin(); it != _programs.end(); ++it)
			delete it->second;

		for (auto it = _textures.begin(); it != _textures.end(); ++it)
			delete it->second;
	}

#pragma endregion

#pragma region Functions

	Material* ResourcesManager::CreateDefaultMaterial() noexcept
	{
		Material* material = new Material(CreateShaderProgram("../QuantixEngine/Media/Shader/vertexShader.vert", "../QuantixEngine/Media/Shader/fragmentShader.frag"));
		material->diffuse = { 0.5f, 0.5f, 0.5f };
		material->specular = { 1.f, 1.f, 1.f };
		material->ambient = { 0.2f, 0.2f, 0.2f };
		material->shininess = 32.f;

		QXstring	path = "media/Material/DefaultMaterial";
		QXstring	tmp_path;
		bool		not_found = true;

		if (_materials.size() == 0)
		{
			_materials[path + std::to_string(0) + ".mat"] = material;
			material->SetPath(path + std::to_string(0) + ".mat");
			return material;
		}

		for (QXuint i = 0; i < _materials.size(); ++i)
		{
			tmp_path = path + std::to_string(i) + ".mat";
			
			if (_materials.find(tmp_path) == _materials.end())
			{
				_materials[tmp_path] = material;
				not_found = false;
				break;
			}
		}

		if (not_found)
		{
			tmp_path = path + std::to_string(_materials.size()) + ".mat";
			_materials[tmp_path] = material;
		}

		material->SetPath(tmp_path);

		return material;
	}

	Scene* ResourcesManager::CreateDefaultScene() noexcept
	{
		return new Scene();
	}

	Material* ResourcesManager::CreateMaterial(const QXstring& filePath) noexcept
	{
		if (filePath == "")
			return CreateDefaultMaterial();

		auto it = _materials.find(filePath);
		if (it != _materials.end() && it->second != nullptr)
		{
			return it->second;
		}

		Material* material = LoadMaterial(filePath);

		_materials[filePath] = material;

		return material;
	}

	Sound* ResourcesManager::CreateSound(const QXstring& filePath) noexcept
	{
		if (filePath == "")
			return nullptr;

		auto it = _sounds.find(filePath);
		if (it != _sounds.end() && it->second != nullptr)
		{
			return it->second;
		}

		Sound* sound = new Sound(filePath.c_str());

		_sounds[filePath] = sound;

		return sound;
	}

	Components::Mesh* ResourcesManager::CreateMesh(Components::Mesh* mesh, const QXstring& modelPath, const QXstring& materialPath) noexcept
	{
		QXstring key = modelPath + materialPath;

		mesh->SetModel(CreateModel(modelPath));
		mesh->SetMaterial(CreateMaterial(materialPath));

		_meshes[key] = mesh;

		mesh->shaderID = mesh->GetMaterial()->GetShaderProgram()->GetID();
		if (mesh->GetMaterial()->GetDiffuseTexture())
			mesh->textureID = mesh->GetMaterial()->GetDiffuseTexture()->GetId();
		
			
		return mesh;
	}

	Model* ResourcesManager::CreateModel(const QXstring& filePath) noexcept
	{
		auto it = _models.find(filePath);
		if (it != _models.end() && it->second != nullptr)
		{
			return it->second;
		}

		std::vector<Vertex> vertices;
		std::vector<QXuint> indices;
		Model* model = new Model;
		Threading::TaskSystem::GetInstance()->AddTask(&Model::Load, model, filePath);
		_resourcesToBind.push_back(model);
		_models[filePath] = model;
		return model;
	}

	Scene* ResourcesManager::CreateScene(const QXstring& filepath)
	{
		if (filepath == "")
			return CreateDefaultScene();

		auto it = _scenes.find(filepath);
		if (it != _scenes.end() && it->second != nullptr)
		{
			return it->second;
		}
		return LoadScene(filepath);
	}

	ShaderProgram* ResourcesManager::CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath) noexcept
	{
		auto it = _programs.find(vertexPath + fragmentPath);
		if (it != _programs.end() && it->second != nullptr)
		{
			return it->second;
		}

		ShaderProgram* program = new ShaderProgram(CreateShader(vertexPath, EShaderType::VERTEX), CreateShader(fragmentPath, EShaderType::FRAGMENT));
		program->AddShaderPath(vertexPath);
		program->AddShaderPath(fragmentPath);
		_programs[vertexPath + fragmentPath] = program;
		return program;
	}

	Shader* ResourcesManager::CreateShader(const QXstring& filePath, EShaderType type) noexcept
	{
		auto it = _shaders.find(filePath);
		if (it != _shaders.end() && it->second != nullptr)
		{
			return it->second;
		}

		Shader* shader = new Shader(filePath, type);
		_shaders[filePath] = shader;
		return shader;
	}

	Texture* ResourcesManager::CreateTexture(const QXstring& filePath) noexcept
	{
		auto it = _textures.find(filePath);
		if (it != _textures.end() && it->second != nullptr)
		{
			return it->second;
		}

		Texture* texture = new Texture;
		Threading::TaskSystem::GetInstance()->AddTask(&Texture::Load, texture, filePath);
		_resourcesToBind.push_back(texture);
		_textures[filePath] = texture;
		return texture;
	}

	Texture* ResourcesManager::CreateHDRTexture(const QXstring& filePath) noexcept
	{
		auto it = _textures.find(filePath);
		if (it != _textures.end() && it->second != nullptr)
		{
			return it->second;
		}

		Texture* texture = new Texture;
		Threading::TaskSystem::GetInstance()->AddTask(&Texture::LoadHDRTexture, texture, filePath);
		_resourcesToBind.push_back(texture);
		_textures[filePath] = texture;
		return texture;
	}

	Material* ResourcesManager::LoadMaterial(const QXstring& filePath) noexcept
	{
		FILE* file;

		fopen_s(&file, filePath.c_str(), "rb");

		if (file == nullptr)
			return nullptr;

		QXstring vertex_path, fragment_path, diffuse_path, emissive_path;
		QXsizei char_count;

		fread(&char_count, sizeof(QXsizei), 1, file);
		vertex_path.resize(char_count);
		fread(vertex_path.data(), sizeof(QXchar), char_count, file);

		fread(&char_count, sizeof(QXsizei), 1, file);
		fragment_path.resize(char_count);
		fread(fragment_path.data(), sizeof(QXchar), char_count, file);

		Material* material = new Material(CreateShaderProgram(vertex_path, fragment_path));

		fread(&material->ambient, sizeof(Math::QXvec3), 1, file);
		fread(&material->diffuse, sizeof(Math::QXvec3), 1, file);
		fread(&material->specular, sizeof(Math::QXvec3), 1, file);
		fread(&material->shininess, sizeof(QXfloat), 1, file);

		fread(&char_count, sizeof(QXsizei), 1, file);
		diffuse_path.resize(char_count);
		fread(diffuse_path.data(), sizeof(QXchar), char_count, file);

		material->SetDiffuseTexture(CreateTexture(diffuse_path));

		fread(&char_count, sizeof(QXsizei), 1, file);
		if (char_count != 0)
		{
			emissive_path.resize(char_count);
			fread(emissive_path.data(), sizeof(QXchar), char_count, file);

			material->SetDiffuseTexture(CreateTexture(emissive_path));
		}

		fclose(file);

		return material;
	}

	void ResourcesManager::SaveMaterialToCache(const QXstring& filePath, const Material* material) noexcept
	{
		FILE* file;

		fopen_s(&file, filePath.c_str(), "wb");

		QXsizei char_count;
		std::vector<QXstring> shader_path = material->GetProgramPath();

		for (QXuint i = 0; i < shader_path.size(); ++i)
		{
			char_count = shader_path[i].length();

			fwrite(&char_count, sizeof(QXsizei), 1, file);
			fwrite(shader_path[i].data(), sizeof(QXchar), char_count, file);
		}

		fwrite(&material->ambient, sizeof(Math::QXvec3), 1, file);
		fwrite(&material->diffuse, sizeof(Math::QXvec3), 1, file);
		fwrite(&material->specular, sizeof(Math::QXvec3), 1, file);
		fwrite(&material->shininess, sizeof(QXfloat), 1, file);

		const Texture* diffuse = material->GetDiffuseTexture();
		const Texture* emissive = material->GetDiffuseTexture();

		for (auto it = _textures.begin(); it != _textures.end(); ++it)
		{
			if (it->second == diffuse)
			{
				char_count = it->first.length();

				fwrite(&char_count, sizeof(QXsizei), 1, file);
				fwrite(it->first.data(), sizeof(QXchar), char_count, file);
				break;
			}
		}

		for (auto it = _textures.begin(); it != _textures.end(); ++it)
		{
			if (it->second == emissive)
			{
				char_count = it->first.length();

				fwrite(&char_count, sizeof(QXsizei), 1, file);
				fwrite(it->first.data(), sizeof(QXchar), char_count, file);
				break;
			}
		}
		fclose(file);
	}

	void ResourcesManager::SaveModelToCache(const QXstring& filePath, Model* model) noexcept
	{
		QXstring cache_file = filePath + ".quantix";
		FILE* file;

		fopen_s(&file, cache_file.c_str(), "wb");

		QXsizei vertex_count = model->GetVertices().size();
		QXsizei index_count = model->GetIndices().size();

		fwrite(&vertex_count, sizeof(QXsizei), 1, file);
		fwrite(model->GetVertices().data(), sizeof(Vertex), vertex_count, file);

		fwrite(&index_count, sizeof(QXsizei), 1, file);
		fwrite(model->GetIndices().data(), sizeof(QXuint), index_count, file);

		fclose(file);
	}

	void ResourcesManager::DeleteMaterial(const QXstring& filePath) noexcept
	{
		Material* material = _materials[filePath];

		if (material == nullptr)
			return;

		Components::Mesh* mesh;

		for (auto it = _meshes.begin(); it != _meshes.end(); ++it)
		{
			mesh = it->second;
			if (mesh->GetMaterial() == material)
			{
				mesh->SetMaterial(nullptr);
				break;
			}
		}

		delete material;
		_materials[filePath] = nullptr;
	}

	void ResourcesManager::DeleteTexture(const QXstring& filePath) noexcept
	{
		Texture* texture = _textures[filePath];

		if (texture == nullptr)
			return;

		Material* mat;

		for (auto it = _materials.begin(); it != _materials.end(); ++it)
		{
			mat = it->second;
			if (mat->GetDiffuseTexture() == texture)
			{
				mat->SetDiffuseTexture(nullptr);
				break;
			}
		}

		delete texture;
		_textures[filePath] = nullptr;
	}

	void ResourcesManager::SaveScene(Scene* scene)
	{
		std::ofstream stream("../QuantixEngine/Media/scene.quantix");

		Tool::Serializer serializer;
		stream << serializer.Serialize(scene);
	}

	Scene* ResourcesManager::LoadScene(const QXstring& path)
	{
		Tool::Serializer* serializer = new Tool::Serializer;
		Scene* scene = new Scene();
		//serializer.Deserialize(path, scene, *this);
		Threading::TaskSystem::GetInstance()->AddTask(&Tool::Serializer::Deserialize, serializer, path, scene, this);
		return scene;
	}

	void ResourcesManager::UpdateResourcesState()
	{
		if (_resourcesToBind.size() == 0)
			return;

		auto it = _resourcesToBind.begin();

		while (it != _resourcesToBind.end())
		{
			if ((*it)->IsLoaded())
			{
				(*it)->Init();
				it = _resourcesToBind.erase(it);
			}
			else if ((*it)->IsFailed() || (*it)->IsReady())
			{
				it = _resourcesToBind.erase(it);
			}
			else
				it++;
		}
	}

#pragma endregion
}
