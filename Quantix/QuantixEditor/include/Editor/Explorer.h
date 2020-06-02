#ifndef _EXPLORER_H_
#define _EXPLORER_H_

#include <string>
#include <iostream>
#include <Folder.h>

class Explorer
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Explorer object
	 * 
	 */
	Explorer() noexcept;

	/**
	 * @brief Destroy the Explorer object
	 *
	 */
	~Explorer() = default;
#pragma endregion Constructors&Destructor

#pragma region Methods
	/**
	 * @brief Init Format Folder
	 *
	 * @return QXint
	 */
	QXint						InitFormatFolder() noexcept;

	/**
	 * @brief Check Root Folder
	 *
	 * @param index QXint
	 */
	void						CheckRootFolder(QXint & index) noexcept;

	/**
	 * @brief Modify Folder
	 *
	 * @param name QXstring
	 */
	void						ModifyFolder(QXstring name) noexcept;

	/**
	 * @brief Open File in Windows Explorer
	 *
	 * @param name QXstring
	 */
	void						OpenSoftware(QXstring name) noexcept;

	/**
	 * @brief Push Id
	 *
	 * @param img QXint
	 * @param name QXstring
	 * @param index QXint
	 */
	void						PushId(QXuint img, QXstring name, QXint & index) noexcept;

	/**
	 * @brief Draw Folder
	 *
	 * @param index QXint
	 */
	void						DrawFolder(QXint & index) noexcept;

	/**
	 * @brief Draw File
	 *
	 * @param index QXint
	 */
	void						DrawFile(QXint & index) noexcept;

	/**
	 * @brief Draw Image
	 *
	 * @param index QXint
	 */
	void						DrawImg(QXint & index) noexcept;

	/**
	 * @brief Draw Repository
	 *
	 * @param index QXint
	 */
	void						DrawRepository(QXint & index) noexcept;

	/**
	 * @brief Rename Menu
	 *
	 * @param file QXstring
	 */
	void						MenuRename(QXstring file) noexcept;

	/**
	 * @brief Menu Item
	 *
	 * @param selection QXbool
	 * @param itemMenu std::vector<QXstring>
	 * @param file QXstring
	 */
	void						MenuItem(QXbool * selection, std::vector<QXstring> itemMenu, QXstring file) noexcept;

	/**
	 * @brief Popup Menu Item
	 *
	 * @param itemFile QXstring
	 */
	void						PopUpMenuItem(QXstring & itemFile) noexcept;

	/**
	 * @brief Popup Menu
	 *
	 */
	void						PopUpMenu() noexcept;

	/**
	 * @brief Create a Item Folder object
	 *
	 * @param item QXstring
	 */
	void						CreateItemFolder(QXstring item) noexcept;

	/**
	 * @brief Create a Item File object
	 *
	 * @param item QXstring
	 */
	void						CreateItemFile(QXstring item) noexcept;

	/**
	 * @brief Create a Item object
	 *
	 * @param itemMenu std::vector<QXstring>
	 */
	void						CreateItem(std::vector<QXstring> itemMenu) noexcept;

	/**
	 * @brief Update
	 *
	 * @param cache Quantix::Core::DataStructure::ResourcesManager&
	 * @param name QXstring
	 * @param flags ImGuiWindowFlags
	 */
	void						Update(Quantix::Core::DataStructure::ResourcesManager & cache, QXstring name, ImGuiWindowFlags flags) noexcept;
	#pragma endregion Methods

private:
	#pragma region Attributes
	Folder						_folder;
	QXstring					_path;
	#pragma endregion Attributes
};

#endif // !_EXPLORER_H_