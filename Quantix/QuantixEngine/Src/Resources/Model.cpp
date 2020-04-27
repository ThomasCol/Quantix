#include "Resources/Model.h"

#include <glad/glad.h>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <tiny_obj_loader.h>

#include "Core/Debugger/Logger.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Resources::Model>("Model")
	.constructor<>()
	.constructor<const std::vector<Quantix::Resources::Vertex>&, const std::vector<QXuint>&>()
	.method("GetPath", &Quantix::Resources::Model::GetPath);
}

namespace Quantix::Resources
{
#pragma region Constructors

	Model::Model(const std::vector<Vertex>& vertices, const std::vector<QXuint>& indices) :
		_vertices {vertices},
		_indices {indices}
	{}

#pragma endregion

#pragma region Functions

	void Model::Init()
	{
		QXuint VBO, EBO;
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);
		glGenBuffers(1, &VBO);
		/* bind VBO */
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/* send data */
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)
			* _vertices.size(), (QXfloat*)_vertices.data(), GL_STATIC_DRAW);

		/* set VBO properties */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)(3 * sizeof(QXfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)(5 * sizeof(QXfloat)));
		glEnableVertexAttribArray(2);
		/* create EBO */
		glGenBuffers(1, &EBO);

		/* set EBO */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QXuint) * _indices.size(),
			_indices.data(), GL_STATIC_DRAW);

		glBindVertexArray(0);

		_status.store(EResourceStatus::READY);
	}

	void Model::Load(const QXstring& file)
	{
		_path = file;

		if (!LoadFromCache(file))
			LoadWithLib(file);
	}

	QXbool Model::LoadFromCache(const QXstring& filePath)
	{
		QXstring cache_file = filePath + ".quantix";
		FILE* file;

		fopen_s(&file, cache_file.c_str(), "rb");

		if (file == nullptr)
			return false;

		QXsizei vertex_count, index_count;

		fread(&vertex_count, sizeof(QXsizei), 1, file);
		_vertices.resize(vertex_count);
		fread(_vertices.data(), sizeof(Vertex), vertex_count, file);

		fread(&index_count, sizeof(QXsizei), 1, file);
		_indices.resize(index_count);
		fread(_indices.data(), sizeof(QXuint), index_count, file);

		fclose(file);

		_status.store(EResourceStatus::LOADED);

		return true;
	}

	void Model::LoadWithLib(const QXstring& file)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file.c_str()))
		{
			LOG(ERROR, warn + err);
			_status.store(EResourceStatus::FAILED);
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
					attrib.vertices[3 * (QXsizei)index.vertex_index + 0],
					attrib.vertices[3 * (QXsizei)index.vertex_index + 1],
					attrib.vertices[3 * (QXsizei)index.vertex_index + 2]
				};

				if (has_tex_coords)
				{
					vertex.uv = {
						attrib.texcoords[2 * (QXsizei)index.texcoord_index + 0],
						attrib.texcoords[2 * (QXsizei)index.texcoord_index + 1]
					};
				}

				if (has_normals)
				{
					vertex.normal = {
						attrib.normals[3 * (QXsizei)index.normal_index + 0],
						attrib.normals[3 * (QXsizei)index.normal_index + 1],
						attrib.normals[3 * (QXsizei)index.normal_index + 2]
					};
				}

				if (uniqueVertices.count(vertex) == 0)
				{
					uniqueVertices[vertex] = static_cast<QXuint>(_vertices.size());
					_vertices.push_back(vertex);
				}

				_indices.push_back(uniqueVertices[vertex]);
			}
		}

		_status.store(EResourceStatus::LOADED);
	}

#pragma endregion
}