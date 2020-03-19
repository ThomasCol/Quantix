#ifndef _GAMEOBJECT3D_H_
#define _GAMEOBJECT3D_H_

#include "Core/DataStructure/GameObject.h"

namespace Core::DataStructure
{
	class GameObject3D : GameObject
	{
	protected:
		//Transform3D		_transform;
	public:
		GameObject3D() noexcept;
		GameObject3D(const GameObject3D& g3d) noexcept;
		GameObject3D(GameObject3D&& g3d) noexcept;
		~GameObject3D();
	};
}

#endif // !_GAMEOBJECT3D_H_
