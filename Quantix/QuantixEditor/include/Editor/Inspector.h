#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Type.h>
#include <Node.h>
#include <Core/DataStructure/GameObject3D.h>

#include "Type.h"

class Inspector
{
public:
	Inspector() = default;
	//Inspector(Node node);
	Inspector(Quantix::Physic::Transform3D* transform);
	Inspector(const Inspector& inspector) = default;
	Inspector(Inspector&& inspector) = default;
	~Inspector() = default;

	inline void	SetEnable(QXbool enable) { _enable = enable; };
	//inline void SetNode(Node node) { _node = node; };
	inline void SetNode(Quantix::Physic::Transform3D* transform) { _transform = transform; };

	void		Update();
private:
	Node								_node;
	Quantix::Physic::Transform3D*		_transform;
	QXbool								_enable;

};

#endif // !_INSPECTOR_H_
