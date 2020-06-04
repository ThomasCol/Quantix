#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <rttrEnabled.h>
#include <Mat4.h>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Core/Components/Light.h"

namespace Quantix::Resources
{
	class QUANTIX_API Material
	{
	private:
#pragma region Attributes

		ShaderProgram* 	_program = nullptr;
		Texture*		_diffuse = nullptr;
		Texture*		_emissive = nullptr;

		QXstring		_path;


#pragma endregion

	public:
#pragma region Attributes

		Math::QXvec3	ambient{51, 51, 51};
		Math::QXvec3	diffuse{ 1, 1, 1 };
		Math::QXvec3	specular{ 1, 1, 1 };

		QXfloat			shininess = 0;
		Math::QXvec2	tile;

		QXbool			isTransparent = false;

		QXbool			textureHasChanged = false;

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Material object
		 * 
		 */
		Material() = default;

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param vertexShader Vertex shader for the material
		 * @param fragmentShader Fragment shader for the material
		 */
		Material(ShaderProgram* program) noexcept;

		/**
		 * @brief Destroy the Material object
		 */
		~Material();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Is Material ready
		 * 
		 * @return QXbool true if ready false if not
		 */
		QXbool	IsReady() noexcept;

		/**
		 * @brief Send Material data to the shader
		 */
		void SendData(QXuint shadowTexture, QXbool isPointLight = false) noexcept;

		/**
		 * @brief Send Textures to shader
		 * 
		 */
		void SendTextures() noexcept;

		/**
		 * @brief Set a float in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat(QXstring location, QXfloat value) noexcept;

		/**
		 * @brief Set a float2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat2(QXstring location, const QXfloat* value) noexcept;

		/**
		 * @brief Set a float3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat3(QXstring location, const QXfloat* value) noexcept;

		/**
		 * @brief Set a float4 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat4(QXstring location, const QXfloat* value) noexcept;

		/**
		 * @brief Set a int in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt(QXstring location, QXint value) noexcept;
		
		/**
		 * @brief Set a int2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt2(QXstring location, const QXint* value) noexcept;
		
		/**
		 * @brief Set a int3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt3(QXstring location, const QXint* value) noexcept;
		
		/**
		 * @brief Set a mat4 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetMat4(QXstring location, Math::QXmat4 value) noexcept;
		
		/**
		 * @brief Set a texture in the shaders
		 * 
		 * @param location Location for the texture to set in the shader
		 * @param texture Texture to send to the shader
		 */
		void SetTexture(QXstring location, const Texture& texture) noexcept;
		
		/**
		 * @brief Set a uint in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint(QXstring location, QXuint value) noexcept;
		
		/**
		 * @brief Set a uint2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint2(QXstring location, const QXuint* value) noexcept;
		
		/**
		 * @brief Set a uint3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint3(QXstring location, const QXuint* value) noexcept;

#pragma region Inline

		/**
		 * @brief Use material's shader program
		 */
		inline void UseShader() noexcept { _program->Use(); }

		/**
		 * @brief Unuse material's shader program
		 */
		inline void UnuseShader() noexcept { _program->Unuse(); }

#pragma endregion

#pragma region Accessor

		/**
		 * @brief Get the Diffuse Texture object
		 * 
		 * @return const Texture& Diffuse texture reference
		 */
		inline Texture*					GetDiffuseTexture() const noexcept { return _diffuse; }

		/**
		 * @brief Get the Emissive Texture object
		 * 
		 * @return Texture* emissive
		 */
		inline Texture*					GetEmissiveTexture() const noexcept { return _emissive; }

		/**
		 * @brief Get the Program Path object
		 * 
		 * @return std::vector<QXstring> program path
		 */
		inline std::vector<QXstring>	GetProgramPath() const noexcept { return _program->GetPath(); }

		/**
		 * @brief Get the Shader Program object
		 * 
		 * @return ShaderProgram* current program
		 */
		inline ShaderProgram*			GetShaderProgram() noexcept { return _program; }

		/**
		 * @brief Get the Path object
		 * 
		 * @return QXstring material path
		 */
		inline QXstring					GetPath() noexcept { return _path; }

		/**
		 * @brief Set the Path object
		 * 
		 * @param path path to set
		 */
		inline void						SetPath(QXstring path) noexcept { _path = path; }

		/**
		 * @brief Set the Diffuse Texture object
		 * 
		 * @param texture Texture to use
		 */
		inline void						SetDiffuseTexture(Texture* texture) noexcept { _diffuse = texture; }

		/**
		 * @brief Set the Emissive Texture object
		 * 
		 * @param texture Texture to use
		 */
		inline void						SetEmissiveTexture(Texture* texture) noexcept { _emissive = texture; }

		/**
		 * @brief Material has changed
		 * 
		 * @param changed true has changed false has not
		 */
		void							HasChanged(QXbool changed) noexcept;
#pragma endregion

#pragma endregion
		CLASS_REGISTRATION()
	};
}

#endif // __MATERIAL_H__

