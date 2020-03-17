#include "Resources/Model.h"

#include <unordered_map>
#include <glad/glad.h>

namespace Quantix::Resources
{
	Model::Model(const tinyobj::attrib_t& attrib, const std::vector<tinyobj::shape_t>& shapes)
	{
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

		QXuint VBO, EBO;
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);
		glGenBuffers(1, &VBO);
		/* bind VBO */
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/* send data */
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)
					* _vertices.size(), (GLfloat*)_vertices.data(), GL_STATIC_DRAW);

		/* set VBO properties */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
								(GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
								(GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
								(GLvoid*)(5 * sizeof(GLfloat)));
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
}