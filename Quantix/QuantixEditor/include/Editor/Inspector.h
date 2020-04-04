#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Type.h>
#include <Node.h>
#include <Core/DataStructure/GameObject3D.h>

class Inspector
{
public:
	Inspector() = default;
	Inspector(Node node);
	//Inspector(Core::DataStructure::GameComponent* gc);
	Inspector(const Inspector& inspector) = default;
	Inspector(Inspector&& inspector) = default;
	~Inspector() = default;

	inline void	SetEnable(bool enable) { _enable = enable; };
	inline void SetNode(Node node) { _node = node; };

	void		Update();
private:
	Node								_node;
	//Core::DataStructure::GameComponent*	_gc;
	QXbool								_enable;

};

#endif // !_INSPECTOR_H_
