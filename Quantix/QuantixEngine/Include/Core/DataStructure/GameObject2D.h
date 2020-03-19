#ifndef _GAMEOBJECT2D_H_
#define _GAMEOBJECT2D_H_

#include "Core/DataStructure/GameObject.h"

namespace Core::DataStructure
{
	class GameObject2D : GameObject
	{
	protected:
		//Transform2D		_transform;
	public:
		GameObject2D() noexcept;
		GameObject2D(const GameObject2D& g2d) noexcept;
		GameObject2D(GameObject2D&& g2d) noexcept;
		~GameObject2D();
	};
}

#endif // !_GAMEOBJECT3D_H_