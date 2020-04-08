#ifndef _EXPLORER_H_
#define _EXPLORER_H_

#include <string>
#include <iostream>
#include <Folder.h>

class Explorer
{
public:
	Explorer();
	~Explorer() = default;

	QXint						InitFormatFolder();
	
	void						CheckRootFolder(QXint& index);
	void						ModifyFolder(QXstring name);
	void						OpenSoftware(QXstring name);
	void						PushId(QXuint img, QXstring name, QXint& index);

	void						DrawFolder(QXint& index);
	void						DrawFile(QXint& index);
	void						DrawImg(QXint& index);
	void						DrawRepository(QXint& index);

	void						MenuRename(QXstring file);
	void						MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, QXstring file);

	void						PopUpMenuItem(QXstring& itemFile);
	void						PopUpMenu();

	void						CreateItemFolder(QXstring item);
	void						CreateItemFile(QXstring item);
	void						CreateItem(std::vector<QXstring> itemMenu);

	void						Update(Quantix::Core::DataStructure::ResourcesManager& cache, QXstring name, ImGuiWindowFlags flags);

private:
	Folder						_folder;
	QXstring					_path;
};

#endif // !_EXPLORER_H_