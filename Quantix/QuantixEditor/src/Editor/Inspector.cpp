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

void Inspector::Update(Quantix::Core::Platform::Application* app)
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

void Inspector::DrawMaterialPath(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app)
{
	/*for (auto it = app->manager.GetMaterials().begin(); it != app->manager.GetMaterials().end(); ++it)
			{
				rttr::variant tmpInst(it->second);
				if (tmpInst == t.get_property("Material").get_value(inst))
				{
					ImGui::Text("Material Path: "); ImGui::SameLine(155.f);
					QXstring path = it->first;
					ImGui::ButtonEx(path.c_str(), ImVec2(0, 0), ImGuiButtonFlags_Disabled);
					if (ImGui::BeginDragDropTarget())
					{
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
						{
							path = (const QXchar*)payload->Data;
							if (path.find(".mat") == QXstring::npos)
								path = it->first;
							Quantix::Resources::Material* material = app->manager.CreateMaterial(path);
							t.get_property("Material").set_value(inst, material);
							ImGui::EndDragDropTarget();
						}
					}
				}
			}*/
}

void Inspector::DrawModelPath(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app)
{
	for (auto it = app->manager.GetModels().begin(); it != app->manager.GetModels().end(); ++it)
	{
		rttr::variant tmpInst(it->second);
		if (tmpInst == t.get_property("Model").get_value(inst))
		{
			ImGui::Text("Model Path: "); ImGui::SameLine(155.f);
			QXstring path = it->first;
			ImGui::ButtonEx(path.c_str(), ImVec2(0,0), ImGuiButtonFlags_Disabled);
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("path", ImGuiDragDropFlags_SourceAllowNullID))
				{
					path = (const QXchar*)payload->Data;
					if (path.find(".obj") == QXstring::npos)
						path = it->first;
					Quantix::Resources::Model* model = app->manager.CreateModel(path);
					t.get_property("Model").set_value(inst, model);
					ImGui::EndDragDropTarget();
				}
			}
		}
	}
}

void Inspector::GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app)
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
		if (t == rttr::type::get<Quantix::Core::Components::Mesh>())
		{
			DrawMaterialPath(inst, t, app);
			DrawModelPath(inst, t, app);
		}
		QXint index = 0;
		for (auto it = t.get_properties().begin(); it != t.get_properties().end(); ++it)
		{
			rttr::property currentProp = *(it);
			if (currentProp.get_type() != rttr::type::get<Quantix::Resources::Model*>())
			{
				rttr::type type = currentProp.get_type();
				ImGui::PushID(index);
				DrawVariable(inst, currentProp, type, app);
				ImGui::PopID();
				index++;
			}
		}
		ImGui::TreePop();
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

	ImGui::Text("Light Type"); ImGui::SameLine(150.f);
	ImGui::Combo("##Light Type: ", &item_current, items, IM_ARRAYSIZE(items));

	LightType = SetValueLightEnum(item_current);
	currentProp.set_value(inst, LightType);
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
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(155.f); ImGui::DragFloat("", &value);
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
	else if (type == rttr::type::get<Quantix::Core::Components::ELightType>())
	{
		ShowLightEnum(currentProp, inst, type);
	}
	else if (currentProp.get_type().is_class() || (currentProp.get_type().is_pointer() && currentProp.get_type().get_raw_type().is_class()))
	{
		GetInstance(currentProp.get_value(inst), type, app);
	}
	//	else
	//		ImGui::Text("Type: % s\nName : % s\nValue : % s\n\n",  currentProp.get_type().get_name().to_string().c_str(), currentProp.get_name().to_string().c_str(), currentProp.get_value(inst).to_string().c_str());
}
