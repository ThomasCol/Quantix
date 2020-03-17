#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <unordered_map>

#include "Core/Type.h"

namespace Quantix::Resources
{
	class ShaderProgram
	{
	private:
#pragma region Attributes

		QXuint _id;

		std::unordered_map<QXstring, QXuint> _locations;

#pragma endregion
	public:
#pragma region Constructors

		/**
		 * @brief [DELETED] Construct a new Shader Program object
		 */
		ShaderProgram() = delete;

		/**
		 * @brief Construct a new Shader Program object
		 * 
		 * @param program Program to copy
		 */
		ShaderProgram(const ShaderProgram& program) noexcept;

		/**
		 * @brief Construct a new Shader Program object
		 * 
		 * @param program Program to move
		 */
		ShaderProgram(ShaderProgram&& program) noexcept;

		/**
		 * @brief Construct a new Shader Program object
		 * 
		 * @param vertexShader Path to the vertex shader
		 * @param fragmentShader Path to the Fragment shader
		 */
		ShaderProgram(const QXchar* vertexShader, const QXchar* fragmentShader) noexcept;

		/**
		 * @brief Destroy the Shader Program object
		 */
		~ShaderProgram();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Use the program
		 */
		void Use() noexcept;

		/**
		 * @brief Unuse the program
		 */
		void Unuse() noexcept;

#pragma region Accessor

		/**
		 * @brief Get the Location ID
		 * 
		 * @param location Location in the shader
		 * @return QXuint Location ID
		 */
		QXuint GetLocation(QXstring location) noexcept;

#pragma endregion

#pragma endregion
	};
}

#endif // __SHADERPROGRAM_H__
