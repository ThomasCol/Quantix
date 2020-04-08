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
	Folder() = default;
	Folder(Quantix::Core::DataStructure::ResourcesManager& cache, const fs::path& p) noexcept;
	Folder(const Folder& folder) = default;
	Folder(Folder&& folder) = default;
	~Folder() = default;

	inline std::vector<QXstring>		GetFolder() const { return _folder; };
	inline std::vector<QXstring>		GetFile() const { return _file; };
	inline std::vector<QXstring>		GetImg() const { return _imgFile; };

	inline ImVec2						GetSizeFile() const { return _sizeFile; };
	inline QXint						GetSizeFolder() const { return _sizeFolder; };

	inline QXuint						GetIDFolder() const { return _folderGLu->GetId(); };
	inline QXuint						GetIDCPP() const { return _cppGLu->GetId();
	};
	inline QXuint						GetIDH() const { return _hGLu->GetId(); };
	inline QXuint						GetIDSLN() const { return _slnGLu->GetId(); };
	inline QXuint						GetIDVCXPROJ() const { return _vcxprojGLu->GetId(); };
	inline QXuint						GetIDFile() const { return _fileGLu->GetId(); };
	inline QXuint						GetIDImg() const { return _imgFileGLu->GetId(); };

	inline void							SetSizeFolder(int value) { _sizeFolder = value; };
	inline void							SetSizeFile(ImVec2 value) { _sizeFile = value; };

	Folder&								operator=(const Folder& folder);

private:
	std::vector<QXstring>			_folder;
	std::vector<QXstring>			_file;
	std::vector<QXstring>			_imgFile;

	ImVec2							_sizeFile;
	QXint							_sizeFolder;

	Quantix::Resources::Texture*	_folderGLu;
	Quantix::Resources::Texture*	_cppGLu;
	Quantix::Resources::Texture*	_hGLu;
	Quantix::Resources::Texture*	_slnGLu;
	Quantix::Resources::Texture*	_vcxprojGLu;
	Quantix::Resources::Texture*	_fileGLu;
	Quantix::Resources::Texture*	_imgFileGLu;
};

#endif // !_FOLDER_H_