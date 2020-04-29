#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Type.h>
#include <Node.h>
#include <Core/DataStructure/GameObject3D.h>
#include <Core/Platform/Application.h>

#include <rttr/registration.h>

#include "Type.h"

#define PATHIMG "media/IconEditor/Simulation/"
#define PNG ".png"

class Inspector
{
public:
	Inspector() = default;
	Inspector(Quantix::Physic::Transform3D* transform);
	Inspector(const Inspector& inspector) = default;
	Inspector(Inspector&& inspector) = default;
	~Inspector() = default;

	inline void												SetEnable(QXbool enable) { _enable = enable; };
	inline void												SetNode(Quantix::Physic::Transform3D* transform) { _transform = transform; };
	inline Quantix::Physic::Transform3D*					GetTransform() { return _transform; };

	void													Update(Quantix::Core::Platform::Window& win, Quantix::Core::Platform::Application* app);
	void													PopUpMenuItem(Quantix::Core::DataStructure::Component* component);
	void													ShowComponent();
	void													AddComponent();
	void													DrawMaterialPath(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app);
	void													DrawModelPath(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app);
	void													GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app);
	void													ShowLightEnum(rttr::property currentProp, rttr::instance inst, rttr::type type);
	void													DrawVariable(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app);

private:
	Quantix::Physic::Transform3D*							_transform;
	QXbool													_enable;

};

#endif // !_INSPECTOR_H_
