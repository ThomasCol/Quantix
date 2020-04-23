#include <rttr/registration>
#include <Core/MathHeader.h>
#include <Resources/Material.h>
#include <Core/DataStructure/Component.h>

#include "Inspector.h"

Inspector::Inspector(Quantix::Physic::Transform3D* transform) :
	_transform{ transform },
	_enable{ true }
{
}

void Inspector::Update()
{
	if (_enable)
	{
		QXstring name;
		QXchar currName[64];

		memcpy(currName, _transform->GetObject()->GetName().c_str(), _transform->GetObject()->GetName().size() + 1);
		ImGui::Text("GameObject: "); ImGui::SameLine();
		if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			_transform->GetObject()->SetName(currName);

		if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_Framed))
		{
			Math::QXvec3	pos = _transform->GetPosition();
			Math::QXvec3	rot = _transform->GetRotation().QuaternionToEuler();
			Math::QXvec3	scale = _transform->GetScale();

			ImGui::Text("Position");	ImGui::SameLine(150.f);	ImGui::DragFloat3("##Position", pos.e, 0.25f);
			ImGui::Text("Rotation");	ImGui::SameLine(150.f); ImGui::DragFloat3("##Rotation", rot.e, 0.25f);
			ImGui::Text("Scale");		ImGui::SameLine(150.f); ImGui::DragFloat3("##Scale", scale.e, 0.25f);

			//Math::QXquaternion q = Math::QXquaternion::EulerToQuaternion(rot);

			_transform->SetPosition(pos);
			_transform->SetRotation(Math::QXquaternion::EulerToQuaternion(rot));
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
				GetInstance(currentComp, t);
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
				_transform->GetObject()->AddComponent(it.invoke("Copy", it.create(), {}).get_value<Quantix::Core::DataStructure::Component*>());

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

void Inspector::GetInstance(rttr::instance inst, rttr::type t)
{
	QXstring name;
	if (t.is_pointer())
	{
		name = t.get_name().to_string();
		name.pop_back();
	}
	else
		name = t.get_name().to_string();
	if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Framed))
	{
		QXint index = 0;
		for (auto it = t.get_properties().begin(); it != t.get_properties().end(); ++it)
		{
			rttr::property currentProp = *(it);

			rttr::type type = currentProp.get_type();
			ImGui::PushID(index);
			DrawVariable(inst, currentProp, type);
			ImGui::PopID();
			index++;
		}
		ImGui::TreePop();
	}
}

void Inspector::DrawVariable(rttr::instance inst, rttr::property currentProp, rttr::type type)
{
	if (type == rttr::type::get<QXbool>())
	{
		QXbool enable = currentProp.get_value(inst).to_bool();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::Checkbox("", &enable);
		currentProp.set_value(inst, enable);
	}
	else if (type == rttr::type::get<QXfloat>())
	{
		QXfloat value = currentProp.get_value(inst).to_float();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::DragFloat("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXdouble>())
	{
		QXdouble value = currentProp.get_value(inst).to_double();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::InputDouble("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXint>())
	{
		QXint value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXsizei>())
	{
		int value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXstring>())
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
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::ColorEdit3("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(150.f); ImGui::DragFloat3("", value.e);
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
		static Math::QXquaternion value = currentProp.get_value(inst).get_value<Math::QXquaternion>();
	}
	else if (currentProp.get_type().is_class() || (currentProp.get_type().is_pointer() && currentProp.get_type().get_raw_type().is_class()))
	{
		GetInstance(currentProp.get_value(inst), type);
	}
	//	else
	//		ImGui::Text("Type: % s\nName : % s\nValue : % s\n\n",  currentProp.get_type().get_name().to_string().c_str(), currentProp.get_name().to_string().c_str(), currentProp.get_value(inst).to_string().c_str());
}
