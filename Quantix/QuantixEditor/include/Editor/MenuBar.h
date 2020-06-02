#ifndef _MENUBAR_H_
#define _MENUBAR_H_

#include <Core/Platform/Application.h>
#include <Core/DataStructure/GameObject3D.h>

#include <vector>
#include <string>

#include "Type.h"

class MenuBar
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Menu Bar object
	 * 
	 */
	MenuBar() = default;

	/**
	 * @brief Construct a new Menu Bar object by copy
	 * 
	 * @param menu 
	 */
	MenuBar(const MenuBar& menu) = default;

	/**
	 * @brief Construct a new Menu Bar object by move
	 * 
	 * @param menu 
	 */
	MenuBar(MenuBar&& menu) = default;

	/**
	 * @brief Destroy the Menu Bar object
	 * 
	 */
	~MenuBar() = default;
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	/**
	 * @brief Update 
	 * 
	 * @param app Application*
	 */
	void			Update(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Create a Game Object object
	 * 
	 * @param name QXstring
	 * @param selection QXbool&
	 * @param app Application*
	 */
	void			CreateGameObject(QXstring name, QXbool& selection, Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Create a Object object
	 * 
	 * @param selection QXbool*
	 * @param objectName std::vector<QXstring>
	 * @param app Application*
	 */
	void			CreateObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Create a Shape Object object
	 *
	 * @param selection QXbool*
	 * @param objectName std::vector<QXstring>
	 * @param app Application*
	 */
	void			CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Create a Component Light with a GameObject3D object
	 *
	 * @param obj GameObject3D*
	 * @param objectName std::vector<QXstring>
	 * @param i QXuint
	 */
	void			CreateComponentLight(Quantix::Core::DataStructure::GameObject3D* obj, std::vector<QXstring> objectName, QXuint i) noexcept;

	/**
	 * @brief Create a Light Object
	 *
	 * @param selection QXbool*
	 * @param objectName std::vector<QXstring>
	 * @param app Application*
	 */
	void			CreateLightObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Load Scene
	 *
	 * @param app
	 */
	void			LoadScene(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief File Button in Menu Bar
	 *
	 */
	void			FileButton(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Show a Window with the PhysX Settings
	 *
	 */
	void			PhysXSettings() noexcept;

	/**
	 * @brief Get the Matrix Line Color Correction object
	 *
	 * @param i index of the row of the matrix
	 * @param mat matrix of Color Correction
	 * @return Math::QXvec4
	 */
	Math::QXvec4	GetMatrixLineColorCorrection(QXint i, Math::QXmat4 mat) noexcept;

	/**
	 * @brief Set the Matrix Line Color Correction object
	 *
	 * @param i index of the row of the matrix
	 * @param mat matrix of Color Correction
	 * @param rgba Color
	 */
	void			SetMatrixLineColorCorrection(QXint i, Math::QXmat4& mat, Math::QXvec4 rgba) noexcept;

	/**
	 * @brief Check Primitive Type of the property
	 *
	 * @param inst
	 * @param currentProp
	 * @param type
	 * @param app
	 */
	void			CheckPrimitiveType(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app) noexcept;

	/**
	* @brief Show Window with the Post Process Settings
	*
	* @param app
	*/
	void			PostProcessSettings(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Dispatch the Settings function
	 *
	 * @param selection QXbool*
	 */
	void			Settings(QXbool* selection) noexcept;

	/**
	 * @brief Edit Button in Menu Bar
	 *
	 */
	void			EditButton() noexcept;

	/**
	 * @brief Open Explorer in Root Media Project
	 *
	 * @param selection QXbool
	 */
	void			OpenExplorer(QXbool selection) noexcept;

	/**
	 * @brief Asset Button in Menu Bar
	 *
	 */
	void			AssetButton() noexcept;

	/**
	 * @brief GameObject Button to create it
	 *
	 * @param app Application*
	 */
	void			GameObjectButton(Quantix::Core::Platform::Application* app) noexcept;
	#pragma endregion Methods

private:
	#pragma region Attributes
	QXbool		_winPhysX{ QX_FALSE };
	QXbool		_postProcess{ QX_FALSE };
	#pragma endregion Attributes
};

#endif // !_MENUBAR_H_
