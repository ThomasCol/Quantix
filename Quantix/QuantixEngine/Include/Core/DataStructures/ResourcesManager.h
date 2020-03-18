#ifndef __RESOURCESMANAGER_H__
#define __RESPURCESMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "Resources/Model.h"
#include "Resources/Shader.h"
#include "Resources/ShaderProgram.h"
#include "Resources/Texture.h"
#include "Resources/Material.h"
#include "Core/Components/Mesh.h"

namespace Quantix::Core::DataStructure
{
	using namespace Resources;

	class ResourcesManager
	{
	private:
#pragma region Attributes

		std::unordered_map<QXstring, Material*>			_materials;
		std::unordered_map<QXstring, Model*>			_models;
		std::unordered_map<QXstring, Shader*>			_shaders;
		std::unordered_map<QXstring, ShaderProgram*>	_programs;
		std::unordered_map<QXstring, Texture*>			_textures;

#pragma endregion
		
	public:
#pragma region Constructors

		ResourcesManager() = default;
		ResourcesManager(const ResourcesManager& manager) = delete;
		ResourcesManager(ResourcesManager&& manager) = delete;
		~ResourcesManager();

#pragma endregion

#pragma region Functions

		Material*			CreateMaterial(const QXstring& filePath);
		Components::Mesh*	CreateMesh(const QXstring& modelPath, const QXstring& vertexPath, const QXstring& fragmentPath);
		Model*				CreateModel(const QXstring& filePath);
		Shader*				CreateShader(const QXstring& filePath, EShaderType type);
		ShaderProgram*		CreateShaderProgram(const QXstring& vertexPath, const QXstring& fragmentPath);
		Texture*			CreateTexture(const QXstring& filePath);

#pragma endregion
	};
}

#endif // __RESOURCESMANAGER_H__
