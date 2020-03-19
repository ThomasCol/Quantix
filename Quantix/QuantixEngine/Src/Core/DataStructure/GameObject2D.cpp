#include "Core/DataStructure/GameObject2D.h"

Core::DataStructure::GameObject2D::GameObject2D() noexcept : 
		GameObject()//,
		//_transform{ Transform2D() }
{
}

Core::DataStructure::GameObject2D::GameObject2D(const GameObject2D& g2d) noexcept :
		GameObject(g2d)//,
		//_transform{ g2d._transform }
{
}

Core::DataStructure::GameObject2D::GameObject2D(GameObject2D&& g2d) noexcept :
	GameObject(g2d)//,
	//_transform{ std::move(g2d._transform) }
{
}

Core::DataStructure::GameObject2D::~GameObject2D()
{
}
