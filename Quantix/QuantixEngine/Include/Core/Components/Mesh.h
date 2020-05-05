#ifndef __MESH_H__
#define __MESH_H__

#include <Type.h>
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

		QXbool					_isMaterialInit;

		#pragma endregion
		
	public:
		#pragma region Attributes

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

		#pragma endregion

		#pragma region Constructors

		/**
		 * @brief Construct a new Mesh object
		 * 
		 */
		Mesh() = default;

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

		/**
		 * @brief Copy mesh
		 * 
		 * @return Mesh* new mesh
		 */
		Mesh*	Copy() const noexcept override;
		
		/**
		 * @brief Init mesh
		 * 
		 * @param object Game component attached
		 */
		void	Init(Core::DataStructure::GameComponent* object) noexcept override;

		/**
		 * @brief Destroy Mesh
		 * 
		 */
		void 	Destroy() noexcept override {};

		#pragma region Accessor

		/**
		 * @brief Set the Model
		 * 
		 * @param model model to use
		 */
		inline void							SetModel(Resources::Model* model) noexcept { _model = model; }

		/**
		 * @brief Get the Model
		 * 
		 * @return Resources::Model* current model
		 */
		inline Resources::Model*			GetModel() noexcept { return _model; }

		/**
		 * @brief Get model VAO
		 * 
		 * @return QXuint VAO value
		 */
		inline QXuint 						GetVAO() noexcept { return _model->GetVAO(); }

		/**
		 * @brief Get the Indices vector
		 * 
		 * @return const std::vector<QXuint>& vector of indices
		 */
		inline const std::vector<QXuint>&	GetIndices() noexcept { return _model->GetIndices(); }

		/**
		 * @brief Get the Material object
		 * 
		 * @return Resources::Material* current material
		 */
		inline Resources::Material* 		GetMaterial() noexcept { return _material; }

		/**
		 * @brief Set the Material
		 * 
		 * @param material material to use
		 */
		inline void 						SetMaterial(Resources::Material* material) noexcept { _material = material; }

		/**
		 * @brief Set the Main Texture object
		 *
		 * @param texture new main texture pointer
		 */
		inline void 						SetMaterialDiffuseTexture(Resources::Texture* texture) noexcept { _material->SetDiffuseTexture(texture); }

		/**
		 * @brief Check if mesh is enabled
		 * 
		 * @return QXbool true mesh is enabled false it's not
		 */
		QXbool								IsEnable() noexcept override;

		/**
		 * @brief Set the Active object
		 * 
		 * @param enable Value to use
		 */
		void								SetActive(QXbool enable) noexcept override;

		#pragma endregion

		#pragma endregion

		CLASS_REGISTRATION(Core::DataStructure::Component)
	};
}

#endif // __MESH_H__
