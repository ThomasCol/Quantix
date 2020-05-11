#ifndef _GUIZMO_H_
#define _GUIZMO_H_

#include <vector>
#include <Inspector.h>
#include <imGuizmo.h>

class Guizmo
{
public:
	Guizmo();
	~Guizmo();

	void Init(Quantix::Core::Platform::Application* app);
	void ChangeGuizmoOperation(QXuint index);
	void LocalWorldGuizmo(QXint pos);
	void GuizmoUI();
	void MoveObject(Quantix::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp);
	void ShowGuizmoObject(Quantix::Physic::Transform3D* transform);
	void DrawGuizmo(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root);
	void Update(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root, Quantix::Core::Components::Camera* camera);

private:
	Quantix::Core::Components::Camera*					_camera;

	std::vector<Quantix::Resources::Texture*>			_imgGuizmo;
	ImGuizmo::OPERATION									_guizmoType;
	ImGuizmo::MODE										_guizmoMode;
	Quantix::Core::Platform::AppInfo					_info;

};

#endif _GUIZMO_H_