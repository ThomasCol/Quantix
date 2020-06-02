#include "Folder.h"

Folder::Folder(Quantix::Core::DataStructure::ResourcesManager& cache, const fs::path& p) noexcept
{
	_sizeFolder = 25;
	_sizeFile = { 70, 70 };

	_folderGLu = cache.CreateTexture("Other/ImgFolder/Folder.png");
	_cppGLu = cache.CreateTexture("Other/ImgFolder/iconeCPP.png");
	_hGLu = cache.CreateTexture("Other/ImgFolder/iconeH.png");
	_slnGLu = cache.CreateTexture("Other/ImgFolder/iconSLN.png");
	_vcxprojGLu = cache.CreateTexture("Other/ImgFolder/iconeVCXPROJ.png");
	_fileGLu = cache.CreateTexture("Other/ImgFolder/iconExtension.png");
	_imgFileGLu = cache.CreateTexture("Other/ImgFolder/jpgfile.png");
	_imgMp3GLu = cache.CreateTexture("Other/ImgFolder/iconmp3.png");

	fs::directory_iterator end_itr;
	fs::directory_iterator dir_itr(p);

	while (dir_itr != end_itr)
	{
		if (fs::is_directory(dir_itr->status()))
			_folder.push_back(dir_itr->path().filename().string());
		else if (fs::is_regular_file(dir_itr->status()))
		{
			if (dir_itr->path().filename().string().find(".quantix") == QXstring::npos)
				_file.push_back(dir_itr->path().filename().string());
		}
		else
			_imgFile.push_back(dir_itr->path().filename().string());
		++dir_itr;
	}
}

Folder& Folder::operator=(const Folder& folder) noexcept
{
	_folder = folder._folder;
	_file = folder._file;
	_imgFile = folder._imgFile;

	_sizeFolder = folder._sizeFolder;
	_sizeFile = folder._sizeFile;

	_folderGLu = folder._folderGLu;
	_cppGLu = folder._cppGLu;
	_hGLu = folder._hGLu;
	_slnGLu = folder._slnGLu;
	_vcxprojGLu = folder._vcxprojGLu;
	_fileGLu = folder._fileGLu;
	_imgFileGLu = folder._imgFileGLu;

	return *this;
}
