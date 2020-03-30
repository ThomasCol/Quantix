#include "Core/DataStructures/ResourcesManager.h"

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

	Material* ResourcesManager::CreateDefaultMaterial()
	{
		Material* material = new Material(CreateShaderProgram("../QuantixEngine/Media/Shader/vertexShader.vert", "../QuantixEngine/Media/Shader/fragmentShader.frag"));
		material->diffuse = { 0.5, 0.5, 0.5 };
		material->specular = { 1, 1, 1 };
		material->ambient = { 0.2, 0.2, 0.2 };
		material->shininess = 32;

		QXstring path = "../QuantixEngine/Media/Material/DefaultMaterial";
		QXstring tmp_path;


		if (_materials.size() == 0)
		{
			_materials[path + std::to_string(0) + ".mat"] = material;
			return material;
		}

		for (QXuint i = 0; i < _materials.size(); ++i)
		{
			tmp_path = path + std::to_string(i) + ".mat";
			
			if (_materials.find(tmp_path) == _materials.end())
			{
				_materials[tmp_path] = material;
				break;
			}
		}

		return material;
	}

	Material* ResourcesManager::CreateMaterial(const QXstring& filePath)
	{
		if (filePath == "")
			return CreateDefaultMaterial();

		auto it = _materials.find(filePath);
		if (it != _materials.end() && it->second != nullptr)
		{
			return it->second;
		}

		return LoadMaterial(filePath);
	}

	Components::Mesh* ResourcesManager::CreateMesh(const QXstring& modelPath, const QXstring& materialPath)
	{

		QXstring key = modelPath + materialPath;

		if (_meshes[key] != nullptr)
		{
			return _meshes[key];
		}

		Components::Mesh* mesh = new Components::Mesh(CreateModel(modelPath), CreateMaterial(materialPath));

		_meshes[key] = mesh;

		return mesh;
	}

	Model* ResourcesManager::CreateModel(const QXstring& filePath)
	{
		auto it = _models.find(filePath);
		if (it != _models.end() && it->second != nullptr)
		{
			return it->second;
		}

		std::vector<Vertex> vertices;
		std::vector<QXuint> indices;
		LoadModel(filePath, vertices, indices);
		Model* model = new Model(vertices, indices);
		_models[filePath] = model;
		return model;
	}

	ShaderProgram* ResourcesManager::CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath)
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

	Shader* ResourcesManager::CreateShader(const QXstring& filePath, EShaderType type)
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

	Texture* ResourcesManager::CreateTexture(const QXstring& filePath)
	{
		auto it = _textures.find(filePath);
		if (it != _textures.end() && it->second != nullptr)
		{
			return it->second;
		}

		Texture* texture = new Texture;
		texture->Load(filePath.c_str());
		_textures[filePath] = texture;
		return texture;
	}

	Material* ResourcesManager::LoadMaterial(const QXstring& filePath)
	{
		FILE* file;

		fopen_s(&file, filePath.c_str(), "rb");

		if (file == nullptr)
			return nullptr;

		QXstring vertex_path, fragment_path, texture_path;
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
		texture_path.resize(char_count);
		fread(texture_path.data(), sizeof(QXchar), char_count, file);

		material->SetMainTexture(CreateTexture(texture_path));

		fclose(file);

		return material;
	}

	Material* ResourcesManager::LoadMaterial(tinyobj::material_t& material)
	{
		Material* mat = new Material;

		mat->ambient.x = material.ambient[0];
		mat->ambient.y = material.ambient[1];
		mat->ambient.z = material.ambient[2];

		mat->diffuse.x = material.diffuse[0];
		mat->diffuse.y = material.diffuse[1];
		mat->diffuse.z = material.diffuse[2];

		mat->specular.x = material.specular[0];
		mat->specular.y = material.specular[1];
		mat->specular.z = material.specular[2];

		mat->shininess = material.shininess;

		return mat;
	}

	void ResourcesManager::LoadModel(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices)
	{
		if (!LoadModelFromCache(filePath, vertices, indices))
			LoadModelFromFile(filePath, vertices, indices);
	}

	QXbool ResourcesManager::LoadModelFromCache(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices)
	{
		QXstring cache_file = filePath + ".quantix";
		FILE* file;

		fopen_s(&file, cache_file.c_str(), "rb");

		if (file == nullptr)
			return false;

		QXsizei vertex_count, index_count;

		fread(&vertex_count, sizeof(QXsizei), 1, file);
		vertices.resize(vertex_count);
		fread(vertices.data(), sizeof(Vertex), vertex_count, file);

		fread(&index_count, sizeof(QXsizei), 1, file);
		indices.resize(index_count);
		fread(indices.data(), sizeof(QXuint), index_count, file);

		fclose(file);

		return true;
	}

	void ResourcesManager::LoadModelFromFile(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str()))
		{
			std::cout << warn + err << std::endl;
			return;
		}

		std::unordered_map<Vertex, QXuint> uniqueVertices;

		bool has_normals = !attrib.normals.empty();
		bool has_tex_coords = !attrib.texcoords.empty();

		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				Vertex vertex = {};

				vertex.position = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				if (has_tex_coords)
				{
					vertex.uv = {
						attrib.texcoords[2 * index.texcoord_index + 0],
						attrib.texcoords[2 * index.texcoord_index + 1]
					};
				}

				if (has_normals)
				{
					vertex.normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2]
					};
				}

				if (uniqueVertices.count(vertex) == 0)
				{
					uniqueVertices[vertex] = static_cast<QXuint>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}
	}

	void ResourcesManager::SaveMaterialToCache(const QXstring& filePath, const Material* material)
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

		const Texture* texture = material->GetMainTexture();

		for (auto it = _textures.begin(); it != _textures.begin(); ++it)
		{
			if (it->second == texture)
			{
				char_count = it->first.length();

				fwrite(&char_count, sizeof(QXsizei), 1, file);
				fwrite(&it->first, sizeof(QXstring), char_count, file);
			}
		}
	}

	void ResourcesManager::SaveModelToCache(const QXstring& filePath, Model* model)
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

	void ResourcesManager::DeleteMaterial(const QXstring& filePath)
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

	void ResourcesManager::DeleteTexture(const QXstring& filePath)
	{
		Texture* texture = _textures[filePath];

		if (texture == nullptr)
			return;

		Material* mat;

		for (auto it = _materials.begin(); it != _materials.end(); ++it)
		{
			mat = it->second;
			if (mat->GetMainTexture() == texture)
			{
				mat->SetMainTexture(nullptr);
				break;
			}
		}

		delete texture;
		_textures[filePath] = nullptr;
	}

#pragma endregion
}