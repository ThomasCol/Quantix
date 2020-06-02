#include <MathDefines.h>
#include "Guizmo.h"
#include <Core/UserEntry/InputManager.h>

Guizmo::Guizmo() :
	_guizmoType{ ImGuizmo::OPERATION::TRANSLATE },
	_guizmoMode{ ImGuizmo::MODE::LOCAL }
{
}

Guizmo::~Guizmo()
{
}

void Guizmo::Init(Quantix::Core::Platform::Application* app)
{
	_info = app->info;
	_imgGuizmo.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/Translate.png"));
	_imgGuizmo.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/Rotate.png"));
	_imgGuizmo.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/Scale.png"));
}

void Guizmo::ChangeGuizmoOperation(QXuint index)
{
	if (index == 0)
		_guizmoType = ImGuizmo::OPERATION::TRANSLATE;
	else if (index == 1)
		_guizmoType = ImGuizmo::OPERATION::ROTATE;
	else
		_guizmoType = ImGuizmo::OPERATION::SCALE;
}

void Guizmo::LocalWorldGuizmo(QXint pos)
{
	pos += 20;
	ImGui::SetCursorPos(ImVec2((QXfloat)pos, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));

	if (_guizmoMode == ImGuizmo::MODE::LOCAL)
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));


	if (ImGui::Button("Local"))
		_guizmoMode = ImGuizmo::MODE::LOCAL;

	ImGui::PopStyleColor();
	pos += 50;
	ImGui::SetCursorPos(ImVec2((QXfloat)pos, 0.f));

	if (_guizmoMode == ImGuizmo::MODE::WORLD)
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));

	if (ImGui::Button("World"))
		_guizmoMode = ImGuizmo::MODE::WORLD;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}


void Guizmo::GuizmoUI()
{
	QXint pos = 0;
	for (QXuint i = 0; i < _imgGuizmo.size(); i++)
	{
		ImGui::SetCursorPos(ImVec2((QXfloat)pos, 0.f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));
		if (ImGui::ImageButton((ImTextureID)_imgGuizmo[i]->GetId(), ImVec2(20, 20)))
			ChangeGuizmoOperation(i);
		pos += 30;
		ImGui::PopStyleColor();
	}

	LocalWorldGuizmo(pos);
}

void Guizmo::MoveObject(Quantix::Core::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp)
{
	Math::QXmat4 matrixTmp2 = Math::QXmat4::CreateTRSMatrix(transform->GetPosition(), Math::QXquaternion(1, 0, 0, 0), transform->GetScale());
	Math::QXvec3 translation, transTmp, rotation, rotTmp, scale, scaleTmp;

	if (_guizmoType == ImGuizmo::OPERATION::TRANSLATE)
	{
		ImGuizmo::Manipulate(_camera->GetLookAt().array, _info.proj.array, ImGuizmo::OPERATION::TRANSLATE, _guizmoMode, matrix.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp.array, transTmp.e, rotation.e, scale.e);
		ImGuizmo::DecomposeMatrixToComponents(matrix.array, translation.e, rotation.e, scale.e);
		transform->Translate(translation - transTmp);
	}
	else if (_guizmoType == ImGuizmo::OPERATION::ROTATE)
	{
		ImGuizmo::Manipulate(_camera->GetLookAt().array, _info.proj.array, ImGuizmo::OPERATION::ROTATE, _guizmoMode, matrixTmp2.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp2.array, translation.e, rotTmp.e, scale.e);
		rotTmp = rotTmp * (Q_PI / 180);
		transform->Rotate(Math::QXquaternion::EulerToQuaternion(-rotTmp));
	}
	else
	{
		ImGuizmo::Manipulate(_camera->GetLookAt().array, _info.proj.array, ImGuizmo::OPERATION::SCALE, _guizmoMode, matrix.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp.array, translation.e, rotation.e, scaleTmp.e);
		ImGuizmo::DecomposeMatrixToComponents(matrix.array, translation.e, rotation.e, scale.e);
		transform->Scale(scale - scaleTmp);
	}
}

void Guizmo::ShowGuizmoObject(Quantix::Core::Physic::Transform3D* transform)
{
	Math::QXmat4 matrix, matrixTmp;
	/*if (_guizmoMode == ImGuizmo::MODE::WORLD)
	{
		transform->SetSpace(Quantix::Physic::Space::WORLD);
		matrixTmp = matrix = transform->GetTRS();
	}
	else if (_guizmoMode == ImGuizmo::MODE::LOCAL)
	{*/
		//transform->SetSpace(Quantix::Physic::Space::LOCAL);
		matrixTmp = matrix = transform->GetTRS();
	//}
	ImVec2 size = ImGui::GetWindowSize();
	ImVec2 pos = ImGui::GetWindowPos();
	ImGuiIO& io = ImGui::GetIO();

	QXfloat dist = (transform->GetPosition() - _camera->GetPos()).Length();

	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	pos.y += 25;
	ImGuizmo::ViewManipulate(_camera->GetLookAt().array, dist, pos, ImVec2(128, 128), 0x10101010);

	MoveObject(transform, matrix, matrixTmp);
}

void Guizmo::DrawGuizmo(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root)
{
	if (GetKey(QX_KEY_SPACE) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		if (_guizmoType == ImGuizmo::OPERATION::TRANSLATE)
			_guizmoType = ImGuizmo::OPERATION::ROTATE;
		else if (_guizmoType == ImGuizmo::OPERATION::ROTATE)
			_guizmoType = ImGuizmo::OPERATION::SCALE;
		else if (_guizmoType == ImGuizmo::OPERATION::SCALE)
			_guizmoType = ImGuizmo::OPERATION::TRANSLATE;
	}

	if (inspector != nullptr && root->GetTransform()->FindTransform(inspector->GetTransform3D()) == QX_TRUE)
		ShowGuizmoObject(inspector->GetTransform3D());
}

void Guizmo::Update(Inspector* inspector, Quantix::Core::DataStructure::GameObject3D* root, Quantix::Core::Components::Camera* camera)
{
	_camera = camera;
	if (inspector)
	{
		if (inspector->Get3D())
			DrawGuizmo(inspector, root);
	}
}
