#ifndef __SHADER_H__
#define __SHADER_H__

#include <vector>

#include "Core/Type.h"

namespace Quantix::Resources
{
	enum class EShaderType
	{
		DEFAULT,
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		COUNT
	};

	class Shader
	{
	private:
#pragma region Attributes

		QXuint 		_id;
		EShaderType	_type;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Compile shader
		 * 
		 * @param file File to the shader
		 * @param shaderKind Type for the shader, can be Vertex, Fragment, Geometry
		 * @return std::vector<QXuint> Shader compiled code
		 */
		std::vector<QXuint>	Compile(const QXchar* file, EShaderType shaderKind) noexcept;

		/**
		 * @brief Create a Fragment Shader object
		 * 
		 * @param file Path to the shader
		 */
		void 				CreateFragmentShader(const QXchar* file) noexcept;

		/**
		 * @brief Create a Vertex Shader object
		 * 
		 * @param file Path to the shader
		 */
		void 				CreateVertexShader(const QXchar* file) noexcept;

		/**
		 * @brief Read shader file and put it into a string
		 * 
		 * @param file Path to the shader
		 * @return QXstring Shader data
		 */
		QXstring			ReadFile(const QXchar* file) noexcept;
		
#pragma endregion

	public:
#pragma region Constructors

		/**
		 * @brief [DELETED] Construct a new Shader object
		 */
		Shader() = delete;

		/**
		 * @brief Construct a new Shader object
		 * 
		 * @param shader Shader to copy
		 */
		Shader(const Shader& shader) noexcept;

		/**
		 * @brief Construct a new Shader object
		 * 
		 * @param shader Shader to move
		 */
		Shader(Shader&& shader) noexcept;

		/**
		 * @brief Construct a new Shader object
		 * 
		 * @param file Path to the shader
		 * @param type Type for the shader, can be Vertex, Fragment, Geometry
		 */
		Shader(const QXstring& file, EShaderType type) noexcept;

		/**
		 * @brief Destroy the Shader object
		 */
		~Shader() noexcept;

#pragma endregion

#pragma region Functions

#pragma region Accessor

		/**
		 * @brief Get Shader ID
		 * 
		 * @return QXuint ID value
		 */
		inline QXuint GetId() noexcept { return _id; }

#pragma endregion

#pragma endregion
	};
}

#endif // __SHADER_H__