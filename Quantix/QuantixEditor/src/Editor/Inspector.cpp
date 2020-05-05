#include <rttr/registration>
#include <Core/MathHeader.h>
#include <Resources/Sound.h>
#include <Core/Components/SoundEmitter.h>
#include <Core/Components/SoundListener.h>
#include <Core/DataStructure/Component.h>

#include "Inspector.h"
#include <Core/UserEntry/InputManager.h>
#include <filesystem>


Inspector::Inspector(Quantix::Physic::Transform3D* transform) :
	_transform{ transform },
	_enable{ true }
{
}

static void TreeNodeImage(const QXstring& name, const QXstring& imgPath, Quantix::Core::Platform::Application* app, ImVec2 pos)
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

void Inspector::Update(Quantix::Core::Platform::Window& win, Quantix::Core::Platform::Application* app)
{
	if (_enable)
	{
		QXstring name;
		QXchar currName[64];

		memcpy(currName, _transform->GetObject()->GetName().c_str(), _transform->GetObject()->GetName().size() + 1);
		ImGui::Text("GameObject: "); ImGui::SameLine();
		if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			_transform->GetObject()->SetName(currName);

		ImVec2 cursorPos = ImGui::GetCursorPos();
		QXbool open = ImGui::TreeNodeEx("##Transform", ImGuiTreeNodeFlags_Framed);
		TreeNodeImage("Transform", "media/IconEditor/Simulation/Transform.png", app, cursorPos);

		if (open)
		{
			Math::QXvec3		pos = _transform->GetPosition();
			Math::QXvec3		rot = _transform->GetRotation().QuaternionToEuler();
			Math::QXvec3		rotTmp = _transform->GetRotation().QuaternionToEuler();
			Math::QXvec3		scale = _transform->GetScale();

			ImGui::Text("Position");	ImGui::SameLine(150.f); ImGui::DragFloat3("##Position", pos.e, 0.25f);
			ImGui::Text("Rotation");	ImGui::SameLine(150.f); ImGui::DragFloat3("##Rotation", rot.e, 0.25f);
			ImGui::Text("Scale");		ImGui::SameLine(150.f); ImGui::DragFloat3("##Scale", scale.e, 0.25f);

			_transform->SetPosition(pos);
			_transform->Rotate(Math::QXquaternion::EulerToQuaternion(rot - rotTmp));
			_transform->SetScale(scale);

			ImGui::TreePop();
		}

		for (int i = 0; i < _transform->GetObject()->GetComponents().size(); i++)
		{
			ImGui::PushID(i);
			auto currentComp = _transform->GetObject()->GetComponents()[i];

			if (_transform->GetObject()->GetComponents()[i] != nullptr)
			{
				rttr::type t = _transform->GetObject()->GetComponents()[i]->get_type();
				GetInstance(currentComp, t, app);
			}

			PopUpMenuItem(_transform->GetObject()->GetComponents()[i]);
			ImGui::PopID(); 
		}

		AddComponent();
	}
}

void Inspector::PopUpMenuItem(Quantix::Core::DataStructure::Component* component)
{
	if (ImGui::BeginPopupContextItem("Context Item"))
	{
		QXbool selection = false;
		
		ImGui::Selectable("Remove Component", &selection);
		if (selection)
			_transform->GetObject()->RemoveComponent(component);

		ImGui::EndPopup();
	}
}

void Inspector::ShowComponent()
{
	if (ImGui::BeginPopup("Item Component"))
	{
		rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
		QXuint i = 0;
		for (auto it : componentsAvailable)
		{
			QXbool enable = false;
			ImGui::PushID(i);

			ImGui::Selectable(it.get_name().to_string().c_str(), &enable);
			if (enable)
			{
				_transform->GetObject()->AddComponent(it.invoke("Copy", it.create(), {}).get_value<Quantix::Core::DataStructure::Component*>());
				_transform->GetObject()->GetComponents().back()->Init(_transform->GetObject());
			}

			ImGui::PopID();
		}
		ImGui::EndPopup();
	}

}

void Inspector::AddComponent()
{
	ImVec2 ButtonSize = ImVec2(150, 0);
	float size = ImGui::GetWindowContentRegionWidth() / 2;
	ImGui::SetCursorPos(ImVec2(size - ButtonSize.x / 2.f + 8.f, ImGui::GetCursorPosY()));
	if (ImGui::Button("Add Component", ButtonSize))
	{
		ImGui::OpenPopup("Item Component");
	}
	ShowComponent();
}

void Inspector::DrawMaterialPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app)
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(155.f);
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
			if (pathTmp.find(".mat") != QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Material* material = app->manager.CreateMaterial(path);
			currentProp.set_value(inst, material);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawModelPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app)
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(155.f);
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
			if (pathTmp.find(".obj") != QXstring::npos && pathTmp.find(".quantix") == QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Model* model = app->manager.CreateModel(path);
			currentProp.set_value(inst, model);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawMTexturePath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app)
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(155.f);
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
			if (pathTmp.find(".png") != QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Texture* texture = app->manager.CreateTexture(path);
			currentProp.set_value(inst, texture);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

void Inspector::DrawSoundEmitterPath(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app)
{
	QXstring name = currentProp.get_name().to_string();
	ImGui::PushID(&currentProp);
	ImGui::Text("%s Path: ", name.c_str()); ImGui::SameLine(155.f);
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
			if (pathTmp.find(".mp3") != QXstring::npos)
				path = pathTmp;
			Quantix::Resources::Sound* sound = app->manager.CreateSound(path);
			currentProp.set_value(inst, sound);
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::PopID();
}

static void PlaySound(rttr::instance inst, rttr::type t)
{
	ImGui::Indent(ImGui::GetWindowSize().x / 3);
	if (ImGui::Button("Play", ImVec2(100.f, 25.f)))
		t.invoke("PlaySound", inst, {}).get_value<QXbool>();
	ImGui::Indent();
}

void Inspector::SetAttributesListener(rttr::instance inst, rttr::type t)
{
	auto tmpInst = inst.get_derived_type();

	tmpInst.invoke("AttributesListener", inst, {});
}

void Inspector::SetSound(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app)
{
	if (inst.get_derived_type() == rttr::type::get<Quantix::Core::Components::SoundEmitter>())
	{
		if (currentProp.get_name().to_string() == "Sound")
		{
			DrawSoundEmitterPath(inst, t, currentProp, app);
		}
	}
	if (inst.get_derived_type() == rttr::type::get<Quantix::Core::Components::SoundListener>())
	{
		SetAttributesListener(inst, t);
	}
}

void Inspector::GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app)
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
			QXint index = 0;
			for (auto it = t.get_properties().begin(); it != t.get_properties().end(); ++it)
			{
				rttr::property currentProp = *(it);
				rttr::type type = currentProp.get_type();
				ImGui::PushID(index);
				DrawVariable(inst, currentProp, type, app);
				ImGui::PopID();
				index++;
			}
			if (t == rttr::type::get<Quantix::Core::Components::SoundEmitter>())
				PlaySound(inst, t);
			ImGui::TreePop();
		}
	}
}

static QXint GetValueLightEnum(Quantix::Core::Components::ELightType type)
{
	if (type == Quantix::Core::Components::ELightType::DEFAULT)
		return 0;
	else if (type == Quantix::Core::Components::ELightType::DIRECTIONAL)
		return 1;
	else if (type == Quantix::Core::Components::ELightType::POINT)
		return 2;
	else if (type == Quantix::Core::Components::ELightType::SPOT)
		return 3;
}

static Quantix::Core::Components::ELightType SetValueLightEnum(QXint value)
{
	if (value == 0)
		return Quantix::Core::Components::ELightType::DEFAULT;
	else if (value == 1)
		return Quantix::Core::Components::ELightType::DIRECTIONAL;
	else if (value == 2)
		return Quantix::Core::Components::ELightType::POINT;
	else if (value == 3)
		return Quantix::Core::Components::ELightType::SPOT;
}

void Inspector::ShowLightEnum(rttr::property currentProp, rttr::instance inst, rttr::type type)
{
	Quantix::Core::Components::ELightType LightType = currentProp.get_value(inst).get_value<Quantix::Core::Components::ELightType>();
	const QXchar* items[] = { "Default", "Directonal", "Point", "Spot" };
	QXint item_current = GetValueLightEnum(LightType);

	ImGui::Text("Light Type"); ImGui::SameLine(155.f);
	ImGui::Combo("##Light Type: ", &item_current, items, IM_ARRAYSIZE(items));

	LightType = SetValueLightEnum(item_current);
	currentProp.set_value(inst, LightType);
}

static QXint GetValueSoundModeEnum(Quantix::Resources::ESoundMode type)
{
	if (type == Quantix::Resources::ESoundMode::QX_2D)
		return 0;
	else if (type == Quantix::Resources::ESoundMode::QX_3D)
		return 1;
}

static Quantix::Resources::ESoundMode SetValueSoundModeEnum(QXint value)
{
	if (value == 0)
		return Quantix::Resources::ESoundMode::QX_2D;
	else if (value == 1)
		return Quantix::Resources::ESoundMode::QX_3D;
}

void Inspector::ShowSoundModeEnum(rttr::property currentProp, rttr::instance inst, rttr::type type)
{
	Quantix::Resources::ESoundMode SoundMode = currentProp.get_value(inst).get_value<Quantix::Resources::ESoundMode>();
	if (SoundMode == Quantix::Resources::ESoundMode::QX_3D)
	{
		auto tmpInst = inst.get_derived_type();

		tmpInst.invoke("AttributesEmitter", inst, {});
	}
	const QXchar* items[] = { "QX_2D", "QX_3D" };
	QXint item_current = GetValueSoundModeEnum(SoundMode);

	ImGui::Text("Sound Mode"); ImGui::SameLine(155.f);
	ImGui::Combo("##Sound Mode: ", &item_current, items, IM_ARRAYSIZE(items));

	SoundMode = SetValueSoundModeEnum(item_current);
	currentProp.set_value(inst, SoundMode);
}

void Inspector::LookType(rttr::instance inst, rttr::type type, rttr::property currentProp, Quantix::Core::Platform::Application* app)
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

void Inspector::DrawVariable(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app)
{
	if (type == rttr::type::get<QXbool>())
	{
		QXbool enable = currentProp.get_value(inst).to_bool();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::Checkbox("", &enable);
		currentProp.set_value(inst, enable);
	}
	else if (type == rttr::type::get<QXfloat>())
	{
		QXfloat value = currentProp.get_value(inst).to_float();
		if (currentProp.get_name().to_string() == "Volume")
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::SliderFloat("", &value, 0.f, 1.f);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::DragFloat("", &value);
		}
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXdouble>())
	{
		QXdouble value = currentProp.get_value(inst).to_double();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::InputDouble("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXint>())
	{
		QXint value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXsizei>())
	{
		int value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXstring>() && currentProp.get_name() != "Path")
	{
		QXstring value = currentProp.get_value(inst).to_string();
		ImGui::Text(value.c_str());
	}
	else if (type == rttr::type::get<Math::QXvec2>())
	{
		Math::QXvec2 value = currentProp.get_value(inst).get_value<Math::QXvec2>();
		ImGui::DragFloat2(currentProp.get_name().to_string().c_str(), value.e);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<Math::QXvec3>())
	{
		Math::QXvec3 value = currentProp.get_value(inst).get_value<Math::QXvec3>();
		if ((inst.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
			|| (inst.get_type() == rttr::type::get<Quantix::Resources::Material>()))
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::ColorEdit3("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::DragFloat3("", value.e);
		}
		currentProp.set_value(inst, value);
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
	}
	else if (type == rttr::type::get<Math::QXquaternion>())
	{
		Math::QXquaternion q = currentProp.get_value(inst).get_value<Math::QXquaternion>();
		Math::QXvec3 value = q.QuaternionToEuler();
		
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::DragFloat3("", value.e);

		q = Math::QXquaternion::EulerToQuaternion(value);
		currentProp.set_value(inst, q);
	}
	else if (type == rttr::type::get<Quantix::Resources::ESoundMode>())
	{
		ShowSoundModeEnum(currentProp, inst, type);
	}
	else if (type == rttr::type::get<Quantix::Core::Components::ELightType>())
	{
		ShowLightEnum(currentProp, inst, type);
	}
	else if (currentProp.get_type().is_class() || (currentProp.get_type().is_pointer() && currentProp.get_type().get_raw_type().is_class()))
	{
		LookType(inst, inst.get_type(), currentProp, app);
		
		if (type != rttr::type::get<QXstring>() && type != rttr::type::get<Quantix::Resources::Sound*>() && type != rttr::type::get<FMOD::ChannelGroup*>() 
			&& type != rttr::type::get<Quantix::Resources::Model*>())
			GetInstance(currentProp.get_value(inst), type, app);
	}
	//	else
	//		ImGui::Text("Type: % s\nName : % s\nValue : % s\n\n",  currentProp.get_type().get_name().to_string().c_str(), currentProp.get_name().to_string().c_str(), currentProp.get_value(inst).to_string().c_str());
}
