#include <rttr/registration>
#include <Core/MathHeader.h>
#include <Resources/Sound.h>
#include <Core/Components/SoundEmitter.h>
#include <Core/Components/SoundListener.h>
#include <Core/Components/DeformableMesh.h>
#include <Core/DataStructure/Component.h>
#include <Core/Components/Behaviour.h>
#include <Core/Components/Behaviours/CubeGenerator.h>
#include <Core/Components//Behaviours//Killzone.h>

#include "Inspector.h"
#include <Core/UserEntry/InputManager.h>
#include <Core/Profiler/Profiler.h>
#include <filesystem>


Inspector::Inspector(Quantix::Core::DataStructure::GameComponent* object)  noexcept :
	_object{ object },
	_enable{ QX_TRUE },
	_is3D{ QX_FALSE },
	_is2D{ QX_FALSE }
{
}

static void TreeNodeImage(const QXstring& name, const QXstring& imgPath, Quantix::Core::Platform::Application* app, ImVec2 pos) noexcept
{
	QXuint		idImg;

	pos.x += 25.f;

	if (std::filesystem::exists(imgPath))
	{
		ImGui::SetCursorPos(pos);
		idImg = app->manager.CreateTexture(imgPath)->GetId();
		ImGui::Image((ImTextureID)idImg, ImVec2(25, 25), ImVec2(0, 1), ImVec2(1, 0));
		pos.x += 30.f;
	}
	pos.y += 4.f;
	ImGui::SetCursorPos(pos);
	ImGui::Text(name.c_str());
}

void Inspector::ShowTransform3D(Quantix::Core::Platform::Application* app) noexcept
{
	ImVec2 cursorPos = ImGui::GetCursorPos();
	QXbool open = ImGui::TreeNodeEx("##Transform", ImGuiTreeNodeFlags_Framed);
	TreeNodeImage("Transform 3D", "Other/IconEditor/Simulation/Transform.png", app, cursorPos);

	if (open)
	{
		Math::QXvec3		pos = ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->GetPosition();
		Math::QXvec3		rot = ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->GetRotation().QuaternionToEuler();
		Math::QXvec3		rotTmp = ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->GetRotation().QuaternionToEuler();
		Math::QXvec3		scale = ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->GetScale();

		ImGui::Text("Position");	ImGui::SameLine(150.f); ImGui::DragFloat3("##Position", pos.e, 0.25f);
		ImGui::Text("Rotation");	ImGui::SameLine(150.f); ImGui::DragFloat3("##Rotation", rot.e, 0.25f);
		ImGui::Text("Scale");		ImGui::SameLine(150.f); ImGui::DragFloat3("##Scale", scale.e, 0.25f);

		((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->SetPosition(pos);
		((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->Rotate(Math::QXquaternion::EulerToQuaternion(rot - rotTmp));
		((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform()->SetScale(scale);

		ImGui::TreePop();
	}
}

void Inspector::ShowTransform2D(Quantix::Core::Platform::Application* app) noexcept
{
	ImVec2 cursorPos = ImGui::GetCursorPos();
	QXbool open = ImGui::TreeNodeEx("##Transform", ImGuiTreeNodeFlags_Framed);
	TreeNodeImage("Transform 2D", "Other/IconEditor/Simulation/Transform.png", app, cursorPos);

	if (open)
	{
		Math::QXvec2		pos = ((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->GetPosition();
		QXfloat				rot = ((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->GetRotationAngle();
		Math::QXvec2		scale = ((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->GetScale();

		ImGui::Text("Position");	ImGui::SameLine(150.f); ImGui::DragFloat2("##Position", pos.e, 0.25f);
		ImGui::Text("Rotation");	ImGui::SameLine(150.f); ImGui::DragFloat("##Rotation", &rot, 0.25f);
		ImGui::Text("Scale");		ImGui::SameLine(150.f); ImGui::DragFloat2("##Scale", scale.e, 0.25f);

		((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->SetPosition(pos);
		((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->SetRotationAngle(rot);
		((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform()->SetScale(scale);

		ImGui::TreePop();
	}
}

void Inspector::LayerObject(rttr::property currentProp, rttr::instance inst) noexcept
{
	auto value = currentProp.get_enumeration().value_to_name(currentProp.get_value(inst)).to_string();

	ImGui::Text("%s", currentProp.get_enumeration().get_name().to_string().c_str()); ImGui::SameLine();
	if (ImGui::BeginCombo("##", value.c_str()))
	{
		for (auto it = currentProp.get_enumeration().get_names().begin(); it != currentProp.get_enumeration().get_names().end(); ++it)
			if (ImGui::Selectable((*it).to_string().c_str()))
				currentProp.set_value(inst, currentProp.get_enumeration().name_to_value((*it).to_string()));
		ImGui::EndCombo();
	}
}

void Inspector::Update(Quantix::Core::Platform::Window& win, Quantix::Core::Platform::Application* app) noexcept
{
	if (_enable)
	{
		QXstring name;
		QXchar currName[64];

		memcpy(currName, _object->GetName().c_str(), _object->GetName().size() + 1);
		ImGui::Text("GameObject: "); ImGui::SameLine();
		if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			_object->SetName(currName);

		LayerObject(_object->get_type().get_property("layer"), _object);

		if (_is3D)
			ShowTransform3D(app);
		else if (_is2D)
			ShowTransform2D(app);

		for (int i = 0; i < _object->GetComponents().size(); i++)
		{
			ImGui::PushID(i);
			auto currentComp = _object->GetComponents()[i];

			if (_object->GetComponents()[i] != nullptr)
			{
				rttr::type t = _object->GetComponents()[i]->get_type();
				GetInstance(currentComp, t, app);
			}

			PopUpMenuItem(_object->GetComponents()[i]);
			ImGui::PopID();
		}

		AddComponent(app);
	}
}

void Inspector::PopUpMenuItem(Quantix::Core::DataStructure::Component* component) noexcept
{
	if (ImGui::BeginPopupContextItem("Context Item"))
	{
		QXbool selection = QX_FALSE;

		ImGui::Selectable("Remove Component", &selection);
		if (selection)
			_object->RemoveComponent(component);

		ImGui::EndPopup();
	}
}

void Inspector::SelectComponent(const QXstring name, rttr::type type, QXbool& enable, Quantix::Core::Platform::Application* app, QXbool behaviour) noexcept
{
	ImGui::Selectable(name.c_str(), &enable);
	if (enable)
	{
		QXbool activate = QX_TRUE;
		if (behaviour)
		{
			if (type.is_derived_from(rttr::type::get<Quantix::Core::Components::Behaviour>()))
			{
				if (!_object->Get3D())
				{
					activate = QX_FALSE;
					QXstring message = "Cannot create " + name + " with a non GameObject3D";
					LOG(WARNING, message);
				}
			}
		}
		if (enable && activate)
		{
			_object->AddComponent(type.invoke("Copy", type.create(), {}).get_value<Quantix::Core::DataStructure::Component*>());
			_object->GetComponents().back()->Init(_object);
			if (behaviour)
			{
				if (name == "Cube Generator")
					_object->GetComponent<Quantix::Core::Components::Behaviours::CubeGenerator>(true)->SetSceneAndResourcesManager(app->scene, &app->manager);
			}
		}
	}
}

void Inspector::ShowBehaviour(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app) noexcept
{
	rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
	QXuint i = 0;
	if (ImGui::TreeNode("Behaviour"))
	{
		for (auto it = componentsName.begin(); it != componentsName.end(); ++it)
		{
			QXbool enable = QX_FALSE;
			ImGui::PushID(i);

			for (auto itCompo : componentsAvailable)
			{
				if (itCompo.get_name().to_string() == (*it))
				{
					if (itCompo.is_derived_from(rttr::type::get<Quantix::Core::Components::Behaviour>()) && (*it) != "Behaviour")
						SelectComponent((*it), itCompo, enable, app, QX_TRUE);
					else
						break;
				}
			}
			ImGui::PopID();
			i++;
		}
		ImGui::TreePop();
	}
}

void Inspector::ShowSoundComponents(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app) noexcept
{
	rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
	QXuint i = 0;
	if (ImGui::TreeNode("Sound"))
	{
		for (auto it = componentsName.begin(); it != componentsName.end(); ++it)
		{
			QXbool enable = QX_FALSE;
			ImGui::PushID(i);

			for (auto itCompo : componentsAvailable)
			{
				if ((*it).find("Sound") != QXstring::npos)
				{
					if (itCompo.get_name().to_string() == (*it))
						SelectComponent((*it), itCompo, enable, app);
				}
			}
			ImGui::PopID();
			i++;
		}
		ImGui::TreePop();
	}
}

void Inspector::ShowPhysicsComponents(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app) noexcept
{
	rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
	QXuint i = 0;
	if (ImGui::TreeNode("Physics"))
	{
		for (auto it = componentsName.begin(); it != componentsName.end(); ++it)
		{
			QXbool enable = QX_FALSE;
			ImGui::PushID(i);

			for (auto itCompo : componentsAvailable)
			{
				if (((*it).find("Collider") != QXstring::npos && (*it) != "Collider") || (*it).find("Deformable") != QXstring::npos
					|| (*it).find("Controller") != QXstring::npos || (*it).find("Rigidbody") != QXstring::npos)
				{
					if (itCompo.get_name().to_string() == (*it))
						SelectComponent((*it), itCompo, enable, app);
				}
			}
			ImGui::PopID();
			i++;
		}
		ImGui::TreePop();
	}
}

void Inspector::ShowAddComponent(Quantix::Core::Platform::Application* app) noexcept
{
	rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
	std::list<QXstring> componentsName;

	QXuint i = 0;
	for (auto it : componentsAvailable)
		componentsName.push_back(it.get_name().to_string());
	componentsName.sort();

	for (auto it = componentsName.begin(); it != componentsName.end(); ++it)
	{
		QXbool enable = QX_FALSE;
		if ((*it).find("Collider") == QXstring::npos && (*it).find("Sound") == QXstring::npos && (*it).find("Deformable") == QXstring::npos
			&& (*it).find("Controller") == QXstring::npos && (*it).find("Rigidbody") == QXstring::npos)
		{
			ImGui::PushID(i);
			for (auto itCompo : componentsAvailable)
			{
				if (itCompo.get_name().to_string() == (*it))
				{
					if (!itCompo.is_derived_from(rttr::type::get<Quantix::Core::Components::Behaviour>()))
						SelectComponent((*it), itCompo, enable, app);
				}
			}
			ImGui::PopID();
			i++;
		}
	}

	ShowPhysicsComponents(componentsName, app);
	ShowSoundComponents(componentsName, app);
	ShowBehaviour(componentsName, app);
}

void Inspector::ShowComponent(Quantix::Core::Platform::Application* app) noexcept
{
	if (ImGui::BeginPopup("Item Component"))
	{
		ShowAddComponent(app);
		ImGui::EndPopup();
	}

}

void Inspector::AddComponent(Quantix::Core::Platform::Application* app) noexcept
{
	ImVec2 ButtonSize = ImVec2(150, 0);
	float size = ImGui::GetWindowContentRegionWidth() / 2;
	ImGui::SetCursorPos(ImVec2(size - ButtonSize.x / 2.f + 8.f, ImGui::GetCursorPosY()));
	if (ImGui::Button("Add Component", ButtonSize))
	{
		ImGui::OpenPopup("Item Component");
	}
	ShowComponent(app);
}

void Inspector::DrawMaterialPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(165.f);
	Quantix::Resources::Material* mat = currentProp.get_value(inst).get_value<Quantix::Resources::Material*>();
	QXstring path;
	for (auto it = app->manager.GetMaterials().begin(); it != app->manager.GetMaterials().end(); ++it)
	{
		if (it->second == mat)
			path = it->first;
	}
	if (path.empty())
		ImGui::ButtonEx(path.c_str(), ImVec2(100, 0), ImGuiButtonFlags_Disabled);
	else
		ImGui::ButtonEx(path.c_str(), ImVec2(0, 0), ImGuiButtonFlags_Disabled);
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
		{
			QXstring pathTmp = (const QXchar*)payload->Data;
			if (pathTmp.find(".mat") != QXstring::npos || pathTmp.find(".FBX") != QXstring::npos || pathTmp.find(".fbx") != QXstring::npos
				|| pathTmp.find(".max") != QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Material* material = app->manager.CreateMaterial(path);
			currentProp.set_value(inst, material);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawModelPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(165.f);
	Quantix::Resources::Model* mod = currentProp.get_value(inst).get_value<Quantix::Resources::Model*>();
	QXstring path;
	for (auto it = app->manager.GetModels().begin(); it != app->manager.GetModels().end(); ++it)
	{
		if (it->second == mod)
			path = it->first;
	}
	if (path.empty())
		ImGui::ButtonEx(path.c_str(), ImVec2(100, 0), ImGuiButtonFlags_Disabled);
	else
		ImGui::ButtonEx(path.c_str(), ImVec2(0, 0), ImGuiButtonFlags_Disabled);
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
		{
			QXstring pathTmp = (const QXchar*)payload->Data;
			if ((pathTmp.find(".obj") != QXstring::npos && pathTmp.find(".quantix") == QXstring::npos)
				|| (pathTmp.find(".FBX") != QXstring::npos || pathTmp.find(".fbx") != QXstring::npos)
				|| pathTmp.find(".max") != QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Model* model = app->manager.CreateModel(path);
			currentProp.set_value(inst, model);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawMTexturePath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(165.f);
	Quantix::Resources::Texture* text = currentProp.get_value(inst).get_value<Quantix::Resources::Texture*>();
	QXstring path;

	for (auto it = app->manager.GetTextures().begin(); it != app->manager.GetTextures().end(); ++it)
	{
		if (it->second == text)
			path = it->first;
	}
	if (path.empty())
		ImGui::ButtonEx(path.c_str(), ImVec2(100, 0), ImGuiButtonFlags_Disabled);
	else
		ImGui::ButtonEx(path.c_str(), ImVec2(0, 0), ImGuiButtonFlags_Disabled);
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
		{
			QXstring pathTmp = (const QXchar*)payload->Data;
			if (pathTmp.find(".png") != QXstring::npos || pathTmp.find(".jpg") != QXstring::npos || pathTmp.find(".jpeg") != QXstring::npos)
			{
				path = pathTmp;
				inst.get_type().invoke("SetChanged", inst, { QX_TRUE });
			}
			Quantix::Resources::Texture* texture = app->manager.CreateTexture(path);
			currentProp.set_value(inst, texture);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawSoundEmitterPath(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(165.f);
	Quantix::Resources::Sound* sound = currentProp.get_value(inst).get_value<Quantix::Resources::Sound*>();
	QXstring path;
	for (auto it = app->manager.GetSounds().begin(); it != app->manager.GetSounds().end(); ++it)
	{
		if (it->second == sound)
			path = it->first;
	}

	if (path == "")
		ImGui::ButtonEx(path.c_str(), ImVec2(100, 0), ImGuiButtonFlags_Disabled);
	else
		ImGui::ButtonEx(path.c_str(), ImVec2(100, 0), ImGuiButtonFlags_Disabled);

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
		{
			QXstring pathTmp = (const QXchar*)payload->Data;
			if (pathTmp.find(".mp3") != QXstring::npos || pathTmp.find(".wav") != std::string::npos || pathTmp.find(".ogg") != std::string::npos
				|| pathTmp.find(".flac") != std::string::npos || pathTmp.find(".aif") != std::string::npos)
				path = pathTmp;
			Quantix::Resources::Sound* sound = app->manager.CreateSound(path);
			currentProp.set_value(inst, sound);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

static void PlaySound(rttr::instance inst, rttr::type t) noexcept
{
	ImGui::Indent(ImGui::GetWindowSize().x / 3);
	if (ImGui::Button("Play", ImVec2(100.f, 25.f)))
		t.invoke("PlaySound", inst, {}).get_value<QXbool>();
	ImGui::Indent();
}

void Inspector::SetAttributesListener(rttr::instance inst, rttr::type t) noexcept
{
	auto tmpInst = inst.get_derived_type();

	tmpInst.invoke("AttributesListener", inst, {});
}

void Inspector::SetSound(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	if (inst.get_derived_type() == rttr::type::get<Quantix::Core::Components::SoundEmitter>())
		if (currentProp.get_name().to_string() == "Sound")
			DrawSoundEmitterPath(inst, t, currentProp, app);
}

void Inspector::GenerateDeformableMesh(rttr::type t, rttr::instance inst, Quantix::Core::Platform::Application* app) noexcept
{
	QXfloat posY = ImGui::GetCursorPosY();
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 3, posY));
	if (ImGui::Button("Generate", ImVec2(100.f, 25.f)))
	{
		auto tmpInst = inst.get_derived_type();

		tmpInst.invoke("Generate", inst, { app->scene, &app->manager, false });
	}
}

void Inspector::CheckSpecClass(rttr::type t, rttr::instance inst, Quantix::Core::Platform::Application* app) noexcept
{
	if (t == rttr::type::get<Quantix::Core::Components::SoundListener>())
		SetAttributesListener(inst, inst.get_type());
	if (t == rttr::type::get<Quantix::Core::Components::SoundEmitter>())
		PlaySound(inst, t);
	if (t == rttr::type::get<Quantix::Core::Components::DeformableMesh>())
		GenerateDeformableMesh(t, inst, app);
}

void Inspector::ShowXYZ(QXbool& isOpen, QXstring& name) noexcept
{
	if (isOpen && name == "RigidLock Flags")
	{
		ImGui::Text("");
		ImGui::SameLine(172.f);
		ImGui::Text("X");
		ImGui::SameLine(222.f);
		ImGui::Text("Y");
		ImGui::SameLine(272.f);
		ImGui::Text("Z");
	}
}

QXbool Inspector::DrawRigidLock(rttr::instance inst, rttr::property currentProp, QXstring& name) noexcept
{
	if (name == "RigidLock Flags")
	{
		static QXfloat indent = 165.f;
		if (currentProp.get_type() == rttr::type::get<QXbool>())
		{
			QXbool enable = currentProp.get_value(inst).to_bool();
			if (currentProp.get_name().to_string().find("Position X") != QXstring::npos)
			{
				indent = 165.f;
				ImGui::Text("Position"); ImGui::SameLine(indent);
			}
			else if (currentProp.get_name().to_string().find("Rotation X") != QXstring::npos)
			{
				indent = 165.f;
				ImGui::Text("Rotation"); ImGui::SameLine(indent);
			}
			else
				ImGui::SameLine(indent);
			ImGui::Checkbox("", &enable);
			currentProp.set_value(inst, enable);
			indent += 50.f;
		}
		return QX_TRUE;
	}

	return QX_FALSE;
}

void Inspector::GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app) noexcept
{
	if (t != rttr::type::get<Quantix::Resources::Texture*>())
	{
		QXstring name;
		if (t.is_pointer())
		{
			name = t.get_name().to_string();
			name.pop_back();
		}
		else
			name = t.get_name().to_string();

		ImVec2 pos = ImGui::GetCursorPos();
		QXbool open = ImGui::TreeNodeEx(("##" + name).c_str(), ImGuiTreeNodeFlags_Framed);
		TreeNodeImage(name, PATHIMG + name + PNG, app, pos);

		if (open)
		{
			static QXbool node = false;
			static QXstring nodeName;
			QXbool isOpen = false;
			QXuint index = 0;
			for (auto it = t.get_properties().begin(); it != t.get_properties().end(); ++it)
			{
				rttr::property currentProp = *(it);
				rttr::type type = currentProp.get_type();
				rttr::variant meta = currentProp.get_metadata("Description");
				if (meta.is_valid() && meta.get_value<QXstring>() != "End")
				{
					nodeName = meta.get_value<QXstring>();
					isOpen = ImGui::TreeNodeEx(nodeName.c_str(), ImGuiTreeNodeFlags_Framed);
					ShowXYZ(isOpen, nodeName);
					node = true;
				}

				ImGui::PushID(index);
				if (node)
				{
					if (isOpen)
					{
						if (!DrawRigidLock(inst, currentProp, nodeName))
							DrawVariable(inst, currentProp, type, app);
					}
				}
				else
					DrawVariable(inst, currentProp, type, app);

				ImGui::PopID();
				index++;
				if (meta.is_valid() && meta.get_value<QXstring>() == "End")
				{
					node = false;
					if (isOpen)
						ImGui::TreePop();
				}

			}
			CheckSpecClass(t, inst, app);
			ImGui::TreePop();
		}
	}
}

void Inspector::ShowEnum(rttr::property currentProp, rttr::instance inst) noexcept
{
	auto value = currentProp.get_enumeration().value_to_name(currentProp.get_value(inst)).to_string();

	ImGui::Text("%s", currentProp.get_enumeration().get_name().to_string().c_str()); ImGui::SameLine(165.f);
	if (ImGui::BeginCombo("##", value.c_str()))
	{
		for (auto it = currentProp.get_enumeration().get_names().begin(); it != currentProp.get_enumeration().get_names().end(); ++it)
			if (ImGui::Selectable((*it).to_string().c_str()))
				currentProp.set_value(inst, currentProp.get_enumeration().name_to_value((*it).to_string()));
		ImGui::EndCombo();
	}
}

void Inspector::LookType(rttr::instance inst, rttr::type type, rttr::property currentProp, Quantix::Core::Platform::Application* app) noexcept
{
	if ((type.get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
		|| (type == rttr::type::get<Quantix::Resources::Material>()))
		DrawMTexturePath(inst, currentProp, app);
	else if (currentProp.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Model*>().get_raw_type())
		DrawModelPath(inst, currentProp, app);
	else if (currentProp.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
		DrawMaterialPath(inst, currentProp, app);

	SetSound(inst, type, currentProp, app);
}

QXbool Inspector::CheckPrimitiveType(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app) noexcept
{
	if (type == rttr::type::get<QXbool>())
	{
		QXbool enable = currentProp.get_value(inst).to_bool();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::Checkbox("", &enable);
		currentProp.set_value(inst, enable);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXfloat>())
	{
		QXfloat value = currentProp.get_value(inst).to_float();
		if (currentProp.get_name().to_string() == "Volume")
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::SliderFloat("", &value, 0.f, 1.f);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::DragFloat("", &value);
		}
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXdouble>())
	{
		QXdouble value = currentProp.get_value(inst).to_double();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::InputDouble("", &value);
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXint>())
	{
		QXint value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXuint>())
	{
		QXint value = currentProp.get_value(inst).to_uint32();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, (QXuint)value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXsizei>())
	{
		int value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<QXstring>() && currentProp.get_name() != "Path")
	{
		QXstring value = currentProp.get_value(inst).to_string();
		ImGui::Text(value.c_str());
		return QX_TRUE;
	}
	else if (type == rttr::type::get<Math::QXvec2>())
	{
		Math::QXvec2 value = currentProp.get_value(inst).get_value<Math::QXvec2>();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::DragFloat2("", value.e);
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<Math::QXvec3>())
	{
		Math::QXvec3 value = currentProp.get_value(inst).get_value<Math::QXvec3>();
		if ((inst.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
			|| (inst.get_type() == rttr::type::get<Quantix::Resources::Material>()))
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::ColorEdit3("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::DragFloat3("", value.e);
		}
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<Math::QXvec4>())
	{
		Math::QXvec4 value = currentProp.get_value(inst).get_value<Math::QXvec4>();
		if ((inst.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
			|| (inst.get_type() == rttr::type::get<Quantix::Resources::Material>()))
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::ColorEdit4("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::DragFloat4("", value.e);
		}
		currentProp.set_value(inst, value);
		return QX_TRUE;
	}
	else if (type == rttr::type::get<Math::QXquaternion>())
	{
		Math::QXquaternion q = currentProp.get_value(inst).get_value<Math::QXquaternion>();
		Math::QXvec3 value = q.QuaternionToEuler();

		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::DragFloat3("", value.e);

		q = Math::QXquaternion::EulerToQuaternion(value);
		currentProp.set_value(inst, q);
		return QX_TRUE;
	}
	return QX_FALSE;
}

void Inspector::DrawVariable(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app) noexcept
{
	if (!CheckPrimitiveType(inst, currentProp, type, app))
	{
		if (currentProp.is_enumeration())
		{
			ShowEnum(currentProp, inst);
		}
		else if (type.is_class() || (type.is_pointer() && type.get_raw_type().is_class()))
		{
			LookType(inst, inst.get_type(), currentProp, app);

			if (type != rttr::type::get<QXstring>() && type != rttr::type::get<Quantix::Resources::Sound*>() && type != rttr::type::get<FMOD::ChannelGroup*>()
				&& type != rttr::type::get<Quantix::Resources::Model*>())
			{
				GetInstance(currentProp.get_value(inst), type, app);
			}
		}
		//	else
		//		ImGui::Text("Type: % s\nName : % s\nValue : % s\n\n",  currentProp.get_type().get_name().to_string().c_str(), currentProp.get_name().to_string().c_str(), currentProp.get_value(inst).to_string().c_str());
	}
}