#include "Resources/Model.h"

#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <glad/glad.h>

namespace Quantix::Resources
{
#pragma region Attributes

	Model::Model(const std::vector<Vertex>& vertices, const std::vector<QXuint> indices) :
		_vertices {vertices},
		_indices {indices}
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
	}

#pragma endregion
}