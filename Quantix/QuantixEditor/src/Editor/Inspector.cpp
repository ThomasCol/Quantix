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
		ImGui::Text("Name: %s", _transform->GetObject()->GetName().c_str());

		if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_Framed))
		{
			static Math::QXvec3	pos = _transform->GetPosition();
			static Math::QXvec3	rot = _transform->GetRotation();
			static Math::QXvec3	scale = _transform->GetScale();
			ImGui::DragFloat3("Position", pos.e, -3000.f, 3000.f);
			ImGui::DragFloat3("Rotation", rot.e, -3000.f, 3000.f);
			ImGui::DragFloat3("Scale", scale.e, 0.f, 100.f);

			_transform->SetPosition(pos);
			_transform->SetRotation(rot);
			_transform->SetScale(scale);

			ImGui::TreePop();
		}

		for (int i = 0; i < _transform->GetObject()->GetComp().size(); i++)
		{
			auto currentComp = _transform->GetObject()->GetComp()[i];

			rttr::type t = _transform->GetObject()->GetComp()[i]->get_type();

			GetInstance(currentComp, t);
		}

		AddComponent();
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
			bool enable = false;
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
	if (ImGui::Button("Add Component"))
		ImGui::OpenPopup("Item Component");
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
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::DragFloat("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXdouble>())
	{
		QXdouble value = currentProp.get_value(inst).to_double();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::InputDouble("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXint>())
	{
		QXint value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::InputInt("", &value);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXsizei>())
	{
		int value = currentProp.get_value(inst).to_int();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::InputInt("", &value);
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
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::ColorEdit3("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::DragFloat3("", value.e);
		}
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<Math::QXvec4>())
	{
		Math::QXvec4 value = currentProp.get_value(inst).get_value<Math::QXvec4>();
		if ((inst.get_type().get_raw_type() == rttr::type::get<Quantix::Resources::Material*>().get_raw_type())
			|| (inst.get_type() == rttr::type::get<Quantix::Resources::Material>()))
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::ColorEdit4("", value.e);
		}
		else
		{
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(); ImGui::DragFloat4("", value.e);
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