#ifndef _GUIZMO_H_
#define _GUIZMO_H_

#include <vector>
#include "Inspector.h"
#include <imGuizmo.h>

class Guizmo
{
public:

	#pragma region Constructors&Destructor
	/**
	* @brief Construct a new Guizmo object
	* 
	*/
	Guizmo() noexcept;

	/**
	 * @brief Destroy the Guizmo object
	 *
	 */
	~Guizmo() noexcept;
#pragma endregion Constructors&Destructor

#pragma region Methods
	/**
	 * @brief Init Guizmo Artifact
	 *
	 * @param app
	 */
	void Init(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Change Guizmo Operation (Position/Rotation/Scale)
	 *
	 * @param index
	 */
	void ChangeGuizmoOperation(QXuint index) noexcept;

	/**
	 * @brief Change Guizmo Space (World/Local)
	 *
	 * @param pos
	 */
	void LocalWorldGuizmo(QXint pos) noexcept;

	/**
	 * @brief UI Guizmo
	 *
	 */
	void GuizmoUI() noexcept;

	/**
	 * @brief Move Object
	 *
	 * @param transform
	 * @param matrix
	 * @param matrixTmp
	 */
	void MoveObject(Quantix::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp) noexcept;

	/**
	 * @brief Show Guizmo Object
	 *
	 * @param transform
	 */
	void ShowGuizmoObject(Quantix::Physic::Transform3D* transform) noexcept;

	/**
	 * @brief Draw Guizmo
	 *
	 * @param inspector
	 * @param root
	 */
	void DrawGuizmo(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root) noexcept;

	/**
	 * @brief Update Guizmo Artifact
	 *
	 * @param inspector
	 * @param root
	 * @param camera
	 */
	void Update(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root, Quantix::Core::Components::Camera* camera) noexcept;
	#pragma endregion Methods

private:
	#pragma region Attributes
	Quantix::Core::Components::Camera*					_camera{ nullptr };

	std::vector<Quantix::Resources::Texture*>			_imgGuizmo;
	ImGuizmo::OPERATION									_guizmoType;
	ImGuizmo::MODE										_guizmoMode;
	Quantix::Core::Platform::AppInfo					_info;
	#pragma endregion Attributes
};

#endif _GUIZMO_H_