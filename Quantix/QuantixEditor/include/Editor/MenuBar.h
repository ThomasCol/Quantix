#ifndef _MENUBAR_H_
#define _MENUBAR_H_

#include <vector>
#include <string>
#include <Node.h>

class MenuBar
{
public:
	MenuBar() = default;
	MenuBar(const MenuBar& menu) = default;
	MenuBar(MenuBar&& menu) = default;
	~MenuBar() = default;

	void Update(std::vector<Node>& object);
	void CreateGameObject(std::string name, std::vector<Node>& object, bool& selection);
	void CreateObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object);
	void CreateShapeObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object);
	void CreateLightObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object);

	void FileButton();
	void EditButton();
	void AssetButton();
	void GameObjectButton(std::vector<Node>& object);

private:

};

#endif // !_MENUBAR_H_