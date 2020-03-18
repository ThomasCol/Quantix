#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <Mat4.h>

#include "ShaderProgram.h"
#include "Texture.h"

namespace Quantix::Resources
{
	class Material
	{
	private:
#pragma region Attributes

		ShaderProgram* 	_program;
		Texture*		_mainTexture;

#pragma endregion

	public:
#pragma region Attributes

		Math::QXvec3	ambient;
		Math::QXvec3	diffuse;
		Math::QXvec3	specular;

		QXfloat			shininess;

#pragma endregion

#pragma region Constructors

		Material() = default;
		/**
		 * @brief Construct a new Material object
		 * 
		 * @param vertexShader Vertex shader for the material
		 * @param fragmentShader Fragment shader for the material
		 */
		Material(ShaderProgram* program);

		/**
		 * @brief Destroy the Material object
		 */
		~Material();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Send Material data to the shader
		 */
		void SendData();

		/**
		 * @brief Set a float in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat(QXstring location, QXfloat value);

		/**
		 * @brief Set a float2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat2(QXstring location, const QXfloat* value);

		/**
		 * @brief Set a float3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat3(QXstring location, const QXfloat* value);

		/**
		 * @brief Set a float4 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetFloat4(QXstring location, const QXfloat* value);

		/**
		 * @brief Set a int in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt(QXstring location, QXint value);
		
		/**
		 * @brief Set a int2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt2(QXstring location, const QXint* value);
		
		/**
		 * @brief Set a int3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetInt3(QXstring location, const QXint* value);
		
		/**
		 * @brief Set a mat4 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetMat4(QXstring location, Math::QXmat4 value);
		
		/**
		 * @brief Set a texture in the shaders
		 * 
		 * @param location Location for the texture to set in the shader
		 * @param texture Texture to send to the shader
		 */
		void SetTexture(QXstring location, const Texture& texture);
		
		/**
		 * @brief Set a uint in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint(QXstring location, QXuint value);
		
		/**
		 * @brief Set a uint2 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint2(QXstring location, const QXuint* value);
		
		/**
		 * @brief Set a uint3 in a shader
		 * 
		 * @param location Location for the value to set in the shader
		 * @param value Value to send
		 */
		void SetUint3(QXstring location, const QXuint* value);

#pragma region Inline

		/**
		 * @brief Use material's shader program
		 */
		inline void UseShader() { _program->Use(); }

		/**
		 * @brief Unuse material's shader program
		 */
		inline void UnuseShader() { _program->Unuse(); }

#pragma endregion

#pragma region Accessor

		/**
		 * @brief Get the Main Texture object
		 * 
		 * @return const Texture& Main texture reference
		 */
		inline const Texture* GetMainTexture() const noexcept { return _mainTexture; }

		/**
		 * @brief Set the Main Texture object
		 * 
		 * @param texture new main texture pointer
		 */
		inline void SetMainTexture(Texture* texture) noexcept { _mainTexture = texture; };

#pragma endregion

#pragma endregion
	};
}

#endif // __MATERIAL_H__

