#ifndef __MODEL_H__
#define __MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>
#include <rttrEnabled.h>
#include <vector>
#include <Vec2.h>
#include <Vec3.h>
#include <Type.h>
#include <Core/DLLHeader.h>

#include "Resource.h"

namespace Quantix::Resources
{
	struct QUANTIX_API Vertex
	{
		#pragma region Attributes

		Math::QXvec3 position;
		Math::QXvec2 uv;
		Math::QXvec3 normal;

		#pragma endregion

		#pragma region Operators

		/**
		 * @brief Operator < to compoare vertex
		 * 
		 * @param other vertex to compare
		 * @return true vertex is smaller
		 * @return false vertex is bigger
		 */
		bool operator<(const Vertex& other) const noexcept
		{
			return position < other.position && normal < other.normal && uv < other.uv;
		}

		/**
		 * @brief Operator == to compoare vertex
		 * 
		 * @param other vertex to compare
		 * @return true vertex is equal
		 * @return false vertex is not equal
		 */
		bool operator==(const Vertex& other) const noexcept
		{
			return position == other.position && normal == other.normal && uv == other.uv;
		}

		#pragma endregion
	};

	class QUANTIX_API Model : public Resource
	{
	private:
#pragma region Attributes

		std::vector<Vertex> _vertices;
		std::vector<QXuint>	_indices;
		QXuint				_VAO = 0;

		QXstring			_path;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Load model from quantix file
		 * 
		 * @param file file to load
		 * @return QXbool load successfully
		 */
		QXbool LoadFromCache(const QXstring& file) noexcept;

		/**
		 * @brief Load model from .fbx or .obj files
		 * 
		 * @param file path to the file
		 */
		void LoadWithLib(const QXstring& file) noexcept;

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
		Model(const std::vector<Vertex>& vertices, const std::vector<QXuint>& indices) noexcept;

		/**
		 * @brief Destroy the Model object
		 */
		~Model() = default;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Load a Model
		 * 
		 * @param file path to the file to load
		 */
		void Load(const QXstring& file) noexcept override;

		/**
		 * @brief Init Model for rendering
		 * 
		 */
		void Init() noexcept override;

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
		inline QXuint GetVAO() noexcept { return _VAO; }

		/**
		 * @brief Get the Indices array
		 * 
		 * @return const std::vector<QXuint>& Indices array reference
		 */
		inline std::vector<QXuint>& GetIndices() noexcept { return _indices; }

		/**
		 * @brief Get the Indices array
		 *
		 * @return const std::vector<QXuint>& Indices array reference
		 */
		inline std::vector<Vertex>& GetVertices() noexcept { return _vertices; }

		/**
		 * @brief Get the Path object
		 * 
		 * @return QXstring Path
		 */
		inline QXstring					GetPath() noexcept { return _path; }

		/**
		 * @brief Set the Path object
		 * 
		 * @param path Path to set
		 */
		inline void						SetPath(QXstring path) noexcept { _path = path; }

#pragma endregion

#pragma endregion

		CLASS_REGISTRATION()
	};
}

namespace std
{
	template<>
	struct hash<Quantix::Resources::Vertex>
	{
		size_t operator()(const Quantix::Resources::Vertex& vertex) const noexcept
		{
			return ((hash<Math::QXvec3>()(vertex.position) ^
					(hash<Math::QXvec3>()(vertex.normal) << 1)) >> 1) ^
					(hash<Math::QXvec2>()(vertex.uv) << 1);
		}
	};
}

#endif // __MODEL_H__
