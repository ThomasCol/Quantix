#ifndef __MESH_H__
#define __MESH_H__

#include "Core/Type.h"
#include "Resources/Model.h"
#include "Resources/Material.h"
#include "Core/Platform/AppInfo.h"
#include "Light.h"
#include "Camera.h"
#include "Core/DataStructure/Component.h"

namespace Quantix::Core::Components
{
	class QUANTIX_API Mesh : public virtual Core::DataStructure::Component
	{
	private:
#pragma region Attributes

		Resources::Model*		_model;
		Resources::Material*	_material;

#pragma endregion
		
	public:
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

		Mesh(Core::DataStructure::GameComponent* object);

		/**
		 * @brief Destroy the Mesh object
		 */
		~Mesh() = default;

#pragma endregion

#pragma region Functions

		void SendDataToShader(Core::Platform::AppInfo& info, std::vector<Light*>& light, Components::Camera* cam);
		
#pragma region Accessor

		inline void	 SetModel(Resources::Model* model) { _model = model; };
		inline QXuint GetVAO() { return _model->GetVAO(); }
		inline const std::vector<QXuint>& GetIndices() { return _model->GetIndices(); }
		inline Resources::Material* GetMaterial() { return _material; }
		inline void SetMaterial(Resources::Material* material) { _material = material; }

#pragma endregion

#pragma endregion

		CLASS_REGISTRATION(Core::DataStructure::Component)
	};
}

#endif // __MESH_H__
