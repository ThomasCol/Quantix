#include "Core/DataStructure/ResourcesManager.h"

#include <istream>

#include "Core/Debugger/Logger.h"
#include "Core/Threading/TaskSystem.hpp"
#include "Core/SoundCore.h"

namespace Quantix::Core::DataStructure
{
#pragma region Constructors

	ResourcesManager::~ResourcesManager()
	{
		for (auto it = _materials.begin(); it != _materials.end();)
		{
			if (it->first.find(".fbx") == QXstring::npos && it->first.find(".FBX") == QXstring::npos)
				SaveMaterialToCache(it->first, it->second);
			delete it->second;
			it = _materials.erase(it);
		}

		for (auto it = _models.begin(); it != _models.end();)
		{
			if (it->first.find(".fbx") == QXstring::npos && it->first.find(".FBX") == QXstring::npos)
				SaveModelToCache(it->first, it->second);
			delete it->second;
			it = _models.erase(it);
		}

		for (auto it = _shaders.begin(); it != _shaders.end();)
		{
			delete it->second;
			it = _shaders.erase(it);
		}

		for (auto it = _programs.begin(); it != _programs.end();)
		{
			delete it->second;
			it = _programs.erase(it);
		}

		for (auto it = _textures.begin(); it != _textures.end();)
		{
			delete it->second;
			it = _textures.erase(it);
		}

		for (auto it = _meshes.begin(); it != _meshes.end();)
		{
			delete it->second;
			it = _meshes.erase(it);
		}

		for (auto it = _sounds.begin(); it != _sounds.end();)
		{
			delete it->second;
			it = _sounds.erase(it);
		}

		Core::SoundCore::GetInstance()->Destroy();
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

		Material* material;
		if (filePath.find(".fbx") != QXstring::npos || filePath.find(".FBX") != QXstring::npos)
			material = LoadMaterial(filePath, QX_TRUE);
		else
			material = LoadMaterial(filePath);

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
		QXbool isFbx = (modelPath.find(".fbx") != QXstring::npos ? true : false);

		mesh->SetModel(CreateModel(modelPath));
		if (isFbx)
			mesh->SetMaterial(CreateMaterial(modelPath));
		else
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

		Model* model = new Model;
		Threading::TaskSystem::GetInstance()->AddTask(&Model::Load, model, filePath);
		_resourcesToBind.push_back(model);
		_models[filePath] = model;
		return model;
	}

	Scene* ResourcesManager::CreateScene(const QXstring& filepath) noexcept
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

	ShaderProgram* ResourcesManager::CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath, const QXstring& geometryPath) noexcept
	{
		auto it = _programs.find(vertexPath + fragmentPath + geometryPath);
		if (it != _programs.end() && it->second != nullptr)
		{
			return it->second;
		}

		ShaderProgram* program = new ShaderProgram(	CreateShader(vertexPath, EShaderType::VERTEX),
													CreateShader(fragmentPath, EShaderType::FRAGMENT),
													CreateShader(geometryPath, EShaderType::GEOMETRY));
		program->AddShaderPath(vertexPath);
		program->AddShaderPath(fragmentPath);
		if (geometryPath != "")
		{
			program->AddShaderPath(geometryPath);
			_programs[vertexPath + fragmentPath + geometryPath] = program;
		}
		else
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

		Shader* shader;

		if (filePath != "")
			shader = new Shader(filePath, type);
		else
			return nullptr;

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

	Material* ResourcesManager::LoadMaterialFromFbx(const QXstring& filePath) noexcept
	{
		Assimp::Importer Importer;
		const aiScene* pScene = Importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		QXstring diffuse_path, emissive_path;
		Material* material = new Material(CreateShaderProgram(DEFAULTVERTEX, DEFAULTFRAGMENT));
		const aiMaterial* pMaterial = pScene->mMaterials[pScene->mMeshes[0]->mMaterialIndex];

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				diffuse_path = DEFAULTTEXTURESPATH;
				diffuse_path += Path.data;
				material->SetDiffuseTexture(CreateTexture(diffuse_path));
			}
		}

		if (pMaterial->GetTextureCount(aiTextureType_EMISSIVE) > 0)
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				emissive_path = DEFAULTTEXTURESPATH;
				emissive_path += Path.data;
				material->SetEmissiveTexture(CreateTexture(emissive_path));
			}
		}
		return material;
	}

	Material* ResourcesManager::LoadMaterialFromFile(const QXstring& filePath) noexcept
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

			material->SetEmissiveTexture(CreateTexture(emissive_path));
		}

		fclose(file);
		return material;
	}

	Material* ResourcesManager::LoadMaterial(const QXstring& filePath, const QXbool& isFbx) noexcept
	{
		if (isFbx)
			return LoadMaterialFromFbx(filePath);
		Material* mat = LoadMaterialFromFile(filePath);

		if (mat)
		{
			mat->SetPath(filePath);
			return mat;
		}
		else
			return CreateDefaultMaterial();
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
		const Texture* emissive = material->GetEmissiveTexture();

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

	void ResourcesManager::SaveScene(Scene* scene) noexcept
	{
		std::ofstream stream("../QuantixEngine/Media/scene.quantix");

		Tool::Serializer serializer;
		stream << serializer.Serialize(scene);
	}

	Scene* ResourcesManager::LoadScene(const QXstring& path) noexcept
	{
		Tool::Serializer* serializer = new Tool::Serializer;
		Scene* scene = new Scene();
		//serializer.Deserialize(path, scene, *this);
		Threading::TaskSystem::GetInstance()->AddTask(&Tool::Serializer::Deserialize, serializer, path, scene, this);
		return scene;
	}

	void ResourcesManager::UpdateResourcesState() noexcept
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
