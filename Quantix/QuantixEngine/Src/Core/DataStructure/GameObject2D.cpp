#include "Core/DataStructure/GameObject2D.h"

Core::DataStructure::GameObject2D::GameObject2D() noexcept : 
	GameComponent()//,
		//_transform{ Transform2D() }
{
}

Core::DataStructure::GameObject2D::GameObject2D(const GameObject2D& g2d) noexcept :
	GameComponent(g2d)//,
		//_transform{ g2d._transform }
{
}

Core::DataStructure::GameObject2D::GameObject2D(GameObject2D&& g2d) noexcept :
	GameComponent(g2d)//,
	//_transform{ std::move(g2d._transform) }
{
}

Core::DataStructure::GameObject2D::~GameObject2D()
{
}

void Core::DataStructure::GameObject2D::AddChild(GameObject2D* object)
{
	//_transform.AddChild(object->_transform);
}

void	Core::DataStructure::GameObject2D::SetGlobalPosition(Math::QXvec2 pos)
{
	//_transform.SetGlobalPosition(pos);
}

void	Core::DataStructure::GameObject2D::SetGlobalRotation(QXfloat rot)
{
	//_transform.SetGlobalRotation(pos);
}

void	Core::DataStructure::GameObject2D::SetLocalPosition(Math::QXvec2 pos)
{
	//_transform.SetLocalPosition(pos);
}

void	Core::DataStructure::GameObject2D::SetLocalRotation(QXfloat rot)
{
	//_transform.SetLocalRotation(pos);
}

void	Core::DataStructure::GameObject2D::SetLocalScale(Math::QXvec2 scale)
{
	//_transform.SetLocalScale(pos);
}

void	Core::DataStructure::GameObject2D::SetTransform(const Math::QXmat4& mat)
{
	//_transform.SetTransform(mat);
}

void	Core::DataStructure::GameObject2D::SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale)
{
	//_transform.SetTransform(pos, rot, scale);
}
