#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <Vec2.h>
#include <Vec3.h>

#include "Core/Type.h"

namespace Quantix::Resources
{
	struct Vertex
	{
		Math::QXvec3 position;
		Math::QXvec2 uv;
		Math::QXvec3 normal;

		bool operator<(const Vertex& other) const
		{
			return position < other.position && normal < other.normal && uv < other.uv;
		}

		bool operator==(const Vertex& other) const
		{
			return position == other.position && normal == other.normal && uv == other.uv;
		}
	};

	class Model
	{
	private:
#pragma region Attributes

		std::vector<Vertex> _vertices;
		std::vector<QXuint>	_indices;
		QXuint				_VAO;

#pragma endregion
		
	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Model object
		 */
		Model() = default;

		/**
		 * @brief Construct a new Model object
		 * 
		 * @param model Model to copy
		 */
		Model(const Model& model) = default;

		/**
		 * @brief Construct a new Model object
		 * 
		 * @param model Model to move
		 */
		Model(Model&& model) = default;

		/**
		 * @brief Construct a new Model object
		 * 
		 * @param attrib Model attributes
		 * @param shapes Shapes for the model
		 */
		Model(const std::vector<Vertex>& vertices, const std::vector<QXuint> indices);

		/**
		 * @brief Destroy the Model object
		 */
		~Model() = default;

#pragma endregion

#pragma region Operators

		/**
		 * @brief Operator = for models
		 * 
		 * @param model Model to copy
		 * @return Model& Reference to the current model
		 */
		Model& operator=(const Model& model) = default;

#pragma endregion

#pragma region Accessor

		/**
		 * @brief Get VAO for the model
		 * 
		 * @return QXuint VAO value
		 */
		inline QXuint GetVAO() { return _VAO; }

		/**
		 * @brief Get the Indices array
		 * 
		 * @return const std::vector<QXuint>& Indices array reference
		 */
		inline const std::vector<QXuint>& GetIndices() { return _indices; }

		/**
		 * @brief Get the Indices array
		 *
		 * @return const std::vector<QXuint>& Indices array reference
		 */
		inline const std::vector<Vertex>& GetVertices() { return _vertices; }

#pragma endregion

#pragma endregion
	};
}

namespace std
{
	template<>
	struct hash<Quantix::Resources::Vertex>
	{
		size_t operator()(const Quantix::Resources::Vertex& vertex) const
		{
			return ((hash<Math::QXvec3>()(vertex.position) ^
					(hash<Math::QXvec3>()(vertex.normal) << 1)) >> 1) ^
					(hash<Math::QXvec2>()(vertex.uv) << 1);
		}
	};
}

#endif // __MODEL_H__
