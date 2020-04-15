#include <rttr/registration>
#include <Core/MathHeader.h>

#include "Inspector.h"

/*Inspector::Inspector(Node node) :
	_node { node },
	_enable { true }
{
}*/

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

		/*rttr::type t = rttr::type::get(_transform->GetObject()->GetComp());
		if (ImGui::TreeNodeEx(QXstring(t.get_name()).c_str(), ImGuiTreeNodeFlags_Framed))
		{
			rttr::method meth = rttr::type::get(_transform->GetObject()->GetComp()[0]).get_method("GetMaterial");
			ImGui::ColorEdit3("ambient", meth.invoke(_transform->GetObject()->GetComp()[0]).get_value())
			ImGui::TreePop();
		}*/

		for (int i = 0; i < _transform->GetObject()->GetComp().size(); i++)
		{
			auto currentComp = _transform->GetObject()->GetComp()[i];

			rttr::type t = _transform->GetObject()->GetComp()[i]->get_type();

			InspectVariable(currentComp, t);
		}

		/*rttr::type t = rttr::type::get(_transform->GetObject()->GetComp()[0]);
		if (ImGui::TreeNodeEx(t.get_name().to_string().c_str(), ImGuiTreeNodeFlags_Framed))
		{
			rttr::method meth = rttr::type::get(_transform->GetObject()->GetComp()[0]).get_method("GetMaterial");
			ImGui::ColorEdit3("ambient", meth.invoke(_transform->GetObject()->GetComp()[0]).get_value())
				ImGui::TreePop();
		};*/
	}
}

void Inspector::InspectVariable(rttr::instance inst, rttr::type t)
{
	for (auto it = t.get_properties().begin(); it != t.get_properties().end(); ++it)
	{
		rttr::property currentProp = *(it);

		rttr::type type = currentProp.get_type();
		if (type.is_class())
		{
			InspectVariable(currentProp, type);
		}
		else if (type == rttr::type::get<QXbool>())
		{ 

		}
		else if (type == rttr::type::get<QXfloat>())
		{

		}
		else if (type == rttr::type::get<QXdouble>())
		{

		}
		else if (type == rttr::type::get<QXint>())
		{

		}
		else if (type == rttr::type::get<QXuint>())
		{

		}
		/*else if (type == rttr::type::get<QXsizei>())
		{

		}*/
		else if (type == rttr::type::get<QXstring>())
		{

		}
		else if (type == rttr::type::get<Math::QXvec2>())
		{

		}
		else if (type == rttr::type::get<Math::QXvec3>())
		{

		}
		else if (type == rttr::type::get<Math::QXvec4>())
		{

		}
		else if (type == rttr::type::get<Math::QXmat>())
		{

		}
		else if (type == rttr::type::get<Math::QXmat4>())
		{

		}
		else if (type == rttr::type::get<Math::QXquaternion>())
		{

		}
	}
}

