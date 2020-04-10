#ifndef __MESH_H__
#define __MESH_H__

#include "Core/Type.h"
#include "Resources/Model.h"
#include "Resources/Material.h"
#include "Core/Platform/AppInfo.h"
#include "Light.h"
#include "Camera.h"

namespace Quantix::Core::Components
{
	class QUANTIX_API Mesh
	{
	private:
#pragma region Attributes

		Resources::Model*		_model;
		Resources::Material*	_material;

#pragma endregion
		
	public:

		union
		{
			struct
			{
				QXuint32	shaderID : 8;
				QXuint32	textureID : 8;
				QXuint32	transparent : 1;
			};

			QXuint32 key;
		};
#pragma region Constructors

		/**
		 * @brief Construct a new Mesh object
		 * 
		 * @param objFile Path to the model
		 * @param vertexShader Path to the vertex shader
		 * @param fragmentShader Path to the fragment shader
		 */
		Mesh(Resources::Model* model, Resources::Material* material);

		/**
		 * @brief Construct a new Mesh object
		 * 
		 * @param mesh Mesh to copy
		 */
		Mesh(const Mesh& mesh) = default;

		/**
		 * @brief Construct a new Mesh object
		 * 
		 * @param mesh Mesh to move
		 */
		Mesh(Mesh&& mesh) = default;

		/**
		 * @brief Destroy the Mesh object
		 */
		~Mesh() = default;

#pragma endregion

#pragma region Functions
		
#pragma region Accessor

		inline QXuint GetVAO() { return _model->GetVAO(); }
		inline const std::vector<QXuint>& GetIndices() { return _model->GetIndices(); }
		inline Resources::Material* GetMaterial() { return _material; }
		inline void SetMaterial(Resources::Material* material) { _material = material; }

		/**
		 * @brief Set the Main Texture object
		 *
		 * @param texture new main texture pointer
		 */
		inline void SetMaterialMainTexture(Resources::Texture* texture) noexcept { _material->SetMainTexture(texture); textureID = texture->GetId(); }

#pragma endregion

#pragma endregion
	};
}

#endif // __MESH_H__
