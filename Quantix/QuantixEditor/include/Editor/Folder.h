#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <filesystem>
#include <vector>
#include <string>
#include <imgui.h>
#include <Core/Platform/Application.h>
#include <Resources/Texture.h>

#include "Type.h"

namespace fs = std::filesystem;

class Folder
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Folder object
	 * 
	 */
	Folder() = default;

	/**
	 * @brief Construct a new Folder object
	 * 
	 * @param cache 
	 * @param p 
	 */
	Folder(Quantix::Core::DataStructure::ResourcesManager& cache, const fs::path& p) noexcept;

	/**
	 * @brief Construct a new Folder object by copy
	 * 
	 * @param folder 
	 */
	Folder(const Folder& folder) = default;

	/**
	 * @brief Construct a new Folder object by move
	 * 
	 * @param folder 
	 */
	Folder(Folder&& folder) = default;
	
	/**
	 * @brief Destroy the Folder object
	 * 
	 */
	~Folder() = default;
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	#pragma region Getters&Setters
	/**
	 * @brief Get the Folder object
	 * 
	 * @return std::vector<QXstring> 
	 */
	inline std::vector<QXstring>		GetFolder() const  noexcept { return _folder; };

	/**
	 * @brief Get the File object
	 *
	 * @return std::vector<QXstring>
	 */
	inline std::vector<QXstring>		GetFile() const  noexcept { return _file; };

	/**
	 * @brief Get the Img object
	 *
	 * @return std::vector<QXstring>
	 */
	inline std::vector<QXstring>		GetImg() const  noexcept { return _imgFile; };

	/**
	* @brief Get the Size File object
	*
	* @return ImVec2
	*/
	inline ImVec2						GetSizeFile() const  noexcept { return _sizeFile; };

	/**
	 * @brief Get the Size Folder object
	 *
	 * @return QXint
	 */
	inline QXint						GetSizeFolder() const  noexcept { return _sizeFolder; };

	/**
	 * @brief Get the ID of image Folder
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDFolder() const  noexcept { return _folderGLu->GetId(); };

	/**
	 * @brief Get the ID of image CPP
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDCPP() const  noexcept { return _cppGLu->GetId(); };

	/**
	 * @brief Get the ID of image H
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDH() const  noexcept { return _hGLu->GetId(); };

	/**
	 * @brief Get the ID of image SLN
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDSLN() const  noexcept { return _slnGLu->GetId(); };

	/**
	 * @brief Get the ID of image VCXPROJ
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDVCXPROJ() const  noexcept { return _vcxprojGLu->GetId(); };

	/**
	 * @brief Get the ID of image File
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDFile() const  noexcept { return _fileGLu->GetId(); };

	/**
	 * @brief Get the ID of image
	 *
	 * @return QXuint
	 */
	inline QXuint						GetIDImg() const  noexcept { return _imgFileGLu->GetId(); };

	/**
	 * @brief Set the Size Folder object
	 *
	 * @param value
	 */
	inline void							SetSizeFolder(QXint value)  noexcept { _sizeFolder = value; };

	/**
	 * @brief Set the Size File object
	 *
	 * @param value ImVec2
	 */
	inline void							SetSizeFile(ImVec2 value)  noexcept { _sizeFile = value; };
#pragma endregion Getters&Setters

#pragma endregion Operator
	/**
	 * @brief operator by copy
	 *
	 * @param folder
	 * @return Folder&
	 */
	Folder& operator=(const Folder& folder) noexcept;
	#pragma endregion Operator
	#pragma endregion Methods

private:
	#pragma region Attributes
	std::vector<QXstring>			_folder;
	std::vector<QXstring>			_file;
	std::vector<QXstring>			_imgFile;

	ImVec2							_sizeFile{ 0.f, 0.f };
	QXint							_sizeFolder{ 0 };

	Quantix::Resources::Texture*	_folderGLu{ nullptr };
	Quantix::Resources::Texture*	_cppGLu{ nullptr };
	Quantix::Resources::Texture*	_hGLu{ nullptr };
	Quantix::Resources::Texture*	_slnGLu{ nullptr };
	Quantix::Resources::Texture*	_vcxprojGLu{ nullptr };
	Quantix::Resources::Texture*	_fileGLu{ nullptr };
	Quantix::Resources::Texture*	_imgFileGLu{ nullptr };
	Quantix::Resources::Texture*	_imgMp3GLu{ nullptr };
	#pragma endregion Attributes
};

#endif // !_FOLDER_H_