#include "Core/DataStructure/GameObject3D.h"

Core::DataStructure::GameObject3D::GameObject3D() noexcept :
	GameObject()//,
	//_transform{ Transform3D() }
{
}

Core::DataStructure::GameObject3D::GameObject3D(const GameObject3D& g3d) noexcept :
	GameObject(g3d)//,
	//_transform{ g3d._transform }
{
}

Core::DataStructure::GameObject3D::GameObject3D(GameObject3D&& g3d) noexcept :
	GameObject(g3d)//,
	//_transform{ std::move(g3d._transform) }
{
}

Core::DataStructure::GameObject3D::~GameObject3D()
{
}
