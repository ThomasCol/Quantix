#ifndef __RESOURCESMANAGER_H__
#define __RESPURCESMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "Resources/Model.h"
#include "Resources/Shader.h"
#include "Resources/ShaderProgram.h"
#include "Resources/Texture.h"
#include "Resources/Material.h"
#include "Resources/Scene.h"
#include "Core/Components/Mesh.h"
#include "Core/Tool/Serializer.h"


namespace Quantix::Core::DataStructure
{
	using namespace Resources;

	class QUANTIX_API ResourcesManager
	{
	private:
#pragma region Attributes

		std::unordered_map<QXstring, Material*>			_materials;
		std::unordered_map<QXstring, Model*>			_models;
		std::unordered_map<QXstring, Shader*>			_shaders;
		std::unordered_map<QXstring, ShaderProgram*>	_programs;
		std::unordered_map<QXstring, Texture*>			_textures;
		std::unordered_map<QXstring, Components::Mesh*>	_meshes;
		std::unordered_map<QXstring, Scene*>			_scenes;

		std::list<Resource*>							_resourcesToBind;
			
#pragma endregion

#pragma region Functions

		/*template<class Archive>
		void save(Archive& archive) const
		{
			archive(x, vec.y, vec.z);
		}

		template<class Archive>
		void load(Archive& archive)
		{
			archive(data._name, data._objects);
		}*/

		/**
		 * @brief Create a Default Material object
		 * 
		 * @return Material* new material
		 */
		Material*			CreateDefaultMaterial() noexcept;

		Scene*				CreateDefaultScene() noexcept;

		/**
		 * @brief Load a material
		 * 
		 * @param filePath Path to the material
		 * @return Material* new material
		 */
		Material*			LoadMaterial(const QXstring& filePath) noexcept;

		/**
		 * @brief Load a model
		 * 
		 * @param filePath Path to the model
		 * @param vertices Vertices array to fill
		 * @param indices Indices array to fill
		 */
		void				LoadModel(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices) noexcept;

		/**
		 * @brief Load a model from cache file
		 * 
		 * @param filePath PAth to the Model
		 * @param vertices Vertices array to fill
		 * @param indices Indices array to fill
		 * @return QXbool True if cahce file exist and model is loaded, False if cache file doesn't exist
		 */
		QXbool				LoadModelFromCache(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices) noexcept;

		/**
		 * @brief Load a model from model Loader lib
		 * 
		 * @param filePath Path to the model
		 * @param vertices Vertices array to fill
		 * @param indices Indices array to fill
		 */
		void				LoadModelFromFile(const QXstring& filePath, std::vector<Vertex>& vertices, std::vector<QXuint>& indices) noexcept;

		/**
		 * @brief Save a material to a cache file
		 * 
		 * @param filePath Path to the material
		 * @param mat material to save
		 */
		void				SaveMaterialToCache(const QXstring& filePath, const Material* mat) noexcept;

		/**
		 * @brief Save a model to a cache file
		 * 
		 * @param filePath Path to the model
		 * @param model model to save
		 */
		void				SaveModelToCache(const QXstring& filePath, Model* model) noexcept;


#pragma endregion
		
	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Resources Manager object
		 */
		ResourcesManager() = default;

		/**
		 * @brief Construct a new Resources Manager object (DELETED)
		 * 
		 * @param manager resources manager to copy
		 */
		ResourcesManager(const ResourcesManager& manager) = delete;

		/**
		 * @brief Construct a new Resources Manager object (DELETED)
		 * 
		 * @param manager resources manager to move 
		 */
		ResourcesManager(ResourcesManager&& manager) = delete;

		/**
		 * @brief Destroy the Resources Manager object
		 */
		~ResourcesManager();

#pragma endregion

#pragma region Operators

		/**
		 * @brief Operator for copy (DELETED)
		 * 
		 * @param manager resources manager to copy 
		 * @return ResourcesManager& reference to the new manager
		 */
		ResourcesManager& operator=(const ResourcesManager& manager) = delete;

		/**
		 * @brief Operator for move
		 * 
		 * @param manager resources manager to move 
		 * @return ResourcesManager& reference to the new manager
		 */
		ResourcesManager& operator=(ResourcesManager&& manager) = delete;

#pragma endregion

#pragma region Functions
		
		/**
		 * @brief Create a Material object
		 * 
		 * @param filePath Path to the material to load if invalid or null path create a default material
		 * @return Material* If the material already exist return it or return a new one
		 */
		Material*			CreateMaterial(const QXstring& filePath) noexcept;

		/**
		 * @brief Create a Mesh object
		 * 
		 * @param modelPath Path to the model to load
		 * @param materialPath Path to the material to load if invalid or null path create a default material
		 * @return Components::Mesh* new mesh
		 */
		Components::Mesh*	CreateMesh(Components::Mesh * mesh, const QXstring & modelPath, const QXstring & materialPath = "") noexcept;

		/**
		 * @brief Create a Model object
		 * 
		 * @param filePath Path to the model to load
		 * @return Model* If the model already exist return it or return a new one
		 */
		Model*				CreateModel(const QXstring& filePath) noexcept;

		Scene*				CreateScene(const QXstring& filePath);

		/**
		 * @brief Create a Shader object
		 * 
		 * @param filePath Path to the shader to load
		 * @param type Type of the shader, can be VERTEX or FRAGMENT
		 * @return Shader* If the shader already exist return it or return a new one
		 */
		Shader*				CreateShader(const QXstring& filePath, EShaderType type) noexcept;

		/**
		 * @brief Create a Shader Program object
		 * 
		 * @param vertexPath Path to the vertex shader to load
		 * @param fragmentPath Path to the fragment shader to load
		 * @return ShaderProgram* If the shader program already exist return it or return a new one
		 */
		ShaderProgram*		CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath) noexcept;

		/**
		 * @brief Create a Texture object
		 * 
		 * @param filePath Path to the Texture to load
		 * @return Texture* If the shader program already exist return it or return a new one
		 */
		Texture*			CreateTexture(const QXstring& filePath) noexcept;

		/**
		 * @brief Create a Texture object from HDR file
		 * 
		 * @param filePath Path to the HDR Texture to load
		 * @return Texture* If the shader program already exist return it or return a new one
		 */
		Texture*			CreateHDRTexture(const QXstring& filePath) noexcept;

		/**
		 * @brief Delete a material
		 * 
		 * @param filePath path to the material to delete
		 */
		void				DeleteMaterial(const QXstring& filePath) noexcept;

		/**
		 * @brief Delete a texture
		 * 
		 * @param filePath path to the texture to delete
		 */
		void				DeleteTexture(const QXstring& filePath) noexcept;

		void				SaveScene(Scene* scene);
		Scene*				LoadScene(const QXstring& path);
		void				UpdateResourcesState();

		inline std::unordered_map<QXstring, ShaderProgram*>&			GetShaders() { return _programs; };
		inline std::unordered_map<QXstring, Model*>&					GetModels() { return _models; };
		inline std::unordered_map<QXstring, Material*>&					GetMaterials() { return _materials; };
		inline std::unordered_map<QXstring, Texture*>&					GetTextures() { return _textures; };

#pragma endregion
	};
}

namespace cereal
{
	
}

#endif // __RESOURCESMANAGER_H__
