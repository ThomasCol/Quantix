#ifndef __SHADER_H__
#define __SHADER_H__

#include <vector>

#include <Type.h>

#include "Core/DLLHeader.h"

#define DEFAULTVERTEX "../QuantixEngine/Media/Shader/vertexShader.vert"
#define DEFAULTFRAGMENT "../QuantixEngine/Media/Shader/fragmentShader.frag"

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

	class QUANTIX_API Shader
	{
	private:
#pragma region Attributes

		QXuint 		_id;
		EShaderType	_type;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Create a Fragment Shader object
		 * 
		 * @param file Path to the shader
		 */
		void 				CreateFragmentShader(QXstring file) noexcept;

		/**
		 * @brief Create a Vertex Shader object
		 * 
		 * @param file Path to the shader
		 */
		void 				CreateVertexShader(QXstring file) noexcept;

		/**
		 * @brief Create a Vertex Shader object
		 *
		 * @param file Path to the shader
		 */
		void 				CreateGeometryShader(QXstring file) noexcept;

		/**
		 * @brief Read shader file and put it into a string
		 * 
		 * @param file Path to the shader
		 * @return QXstring Shader data
		 */
		QXstring			ReadFile(QXstring file) noexcept;
		
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
		Shader(QXstring file, EShaderType type) noexcept;

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