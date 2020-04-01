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

	int							InitFormatFolder();
	
	void						CheckRootFolder(int& index);
	void						ModifyFolder(std::string name);
	void						OpenSoftware(std::string name);
	void						PushId(QXuint img, std::string name, int& index);

	void						DrawFolder(int& index);
	void						DrawFile(int& index);
	void						DrawImg(int& index);
	void						DrawRepository(int& index);

	void						MenuRename(std::string file);
	void						MenuItem(bool* selection, std::vector<std::string> itemMenu, std::string file);

	void						PopUpMenuItem(std::string& itemFile);
	void						PopUpMenu();

	void						CreateItemFolder(std::string item);
	void						CreateItemFile(std::string item);
	void						CreateItem(std::vector<std::string> itemMenu);

	void						Update(Quantix::Core::DataStructure::ResourcesManager& cache, std::string name, ImGuiWindowFlags flags);

private:
	Folder						_folder;
	std::string					_path;
};

#endif // !_EXPLORER_H_