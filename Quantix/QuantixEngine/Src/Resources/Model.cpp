#include "Resources/Model.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <tiny_obj_loader.h>
#include <glad/glad.h>

namespace Quantix::Resources
{
#pragma region Attributes

	Model::Model(const QXstring& filePath)
	{
		Load(filePath);

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
	}

	Model::~Model()
	{

	}

#pragma endregion

#pragma region Functions

	void Model::Load(const QXstring& filePath)
	{
		if (!LoadFromCache(filePath))
			LoadFromFile(filePath);
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

		return true;
	}

	void Model::LoadFromFile(const QXstring& filePath)
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
					uniqueVertices[vertex] = static_cast<QXuint>(_vertices.size());
					_vertices.push_back(vertex);
				}

				_indices.push_back(uniqueVertices[vertex]);
			}
		}

		SaveToCache(filePath);
	}

	void Model::SaveToCache(const QXstring& filePath)
	{
		QXstring cache_file = filePath + ".quantix";
		FILE* file;

		fopen_s(&file, cache_file.c_str(), "wb");

		QXsizei vertex_count = _vertices.size();
		QXsizei index_count = _indices.size();

		fwrite(&vertex_count, sizeof(QXsizei), 1, file);
		fwrite(_vertices.data(), sizeof(Vertex), vertex_count, file);

		fwrite(&index_count, sizeof(QXsizei), 1, file);
		fwrite(_indices.data(), sizeof(QXuint), index_count, file);

		fclose(file);
	}

#pragma endregion
}