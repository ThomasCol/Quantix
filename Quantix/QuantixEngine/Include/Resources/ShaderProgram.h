#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <unordered_map>

#include <Type.h>
#include "Resources/Shader.h"

namespace Quantix::Resources
{
	class QUANTIX_API ShaderProgram
	{
	private:
#pragma region Attributes

		QXuint									_id = 0;

		QXuint									_lightUniformBuffer = 0;

		std::vector<QXstring>					_shadersPath;

		std::unordered_map<QXstring, QXuint>	_locations;

#pragma endregion
	public:
#pragma region Attributes

		QXbool	needLights { true };

#pragma endregion

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
		 * @param geometryShader Path to the Fragment shader
		 */
		ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader = nullptr) noexcept;

		/**
		 * @brief Destroy the Shader Program object
		 */
		~ShaderProgram() noexcept;

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

		/**
		 * @brief Add shader past to the list
		 * 
		 * @param path path to add
		 */
		inline void AddShaderPath(const QXstring& path) noexcept { _shadersPath.push_back(path); }

		/**
		 * @brief Get the Path object
		 * 
		 * @return std::vector<QXstring> path
		 */
		inline std::vector<QXstring> GetPath() noexcept { return _shadersPath; }

		/**
		 * @brief Get program ID
		 * 
		 * @return QXuint ID
		 */
		inline QXuint GetID() noexcept { return _id; }

#pragma endregion

#pragma endregion
	};
}

#endif // __SHADERPROGRAM_H__
