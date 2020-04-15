#include "Inspector.h"

#include <rttr/registration>

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

		rttr::type t = rttr::type::get(_transform->GetObject()->GetComp()[0]);
		if (ImGui::TreeNodeEx(t.get_name().to_string().c_str(), ImGuiTreeNodeFlags_Framed))
		{
			/*rttr::method meth = rttr::type::get(_transform->GetObject()->GetComp()[0]).get_method("GetMaterial");
			ImGui::ColorEdit3("ambient", meth.invoke(_transform->GetObject()->GetComp()[0]).get_value())*/
			ImGui::TreePop();
		};
	}
}
