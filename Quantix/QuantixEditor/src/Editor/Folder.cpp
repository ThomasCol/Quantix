#include "Folder.h"

Folder::Folder(Quantix::Core::DataStructure::ResourcesManager& cache, const fs::path& p) noexcept
{
	_sizeFolder = 1.f;
	_sizeFile = { 70, 70 };

	_folderGLu = cache.CreateTexture("media/ImgFolder/Folder.png");
	_cppGLu = cache.CreateTexture("media/ImgFolder/iconeCPP.png");
	_hGLu = cache.CreateTexture("media/ImgFolder/iconeH.png");
	_slnGLu = cache.CreateTexture("media/ImgFolder/iconSLN.png");
	_vcxprojGLu = cache.CreateTexture("media/ImgFolder/iconeVCXPROJ.png");
	_fileGLu = cache.CreateTexture("media/ImgFolder/iconExtension.png");
	_imgFileGLu = cache.CreateTexture("media/ImgFolder/jpgfile.png");

	fs::directory_iterator end_itr;
	fs::directory_iterator dir_itr(p);

	while (dir_itr != end_itr)
	{
		if (fs::is_directory(dir_itr->status()))
			_folder.push_back(dir_itr->path().filename().string());
		else if (fs::is_regular_file(dir_itr->status()))
			_file.push_back(dir_itr->path().filename().string());
		else
			_imgFile.push_back(dir_itr->path().filename().string());
		++dir_itr;
	}
}

Folder& Folder::operator=(const Folder& folder)
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