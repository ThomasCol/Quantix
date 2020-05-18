#include "Gameplay/Grabbing.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"

namespace Quantix::Gameplay
{
	void Grabbing::Awake()
	{}

	void Grabbing::Start()
	{}

	void Grabbing::Update(QXdouble deltaTime)
	{
		if (GetKey(QX_KEY_E) == Core::UserEntry::EKeyState::PRESSED)
			Use();
	}

	void Grabbing::Use()
	{
		if (_isUsed)
			return Drop();
		else
			return Grab();
	}

	void Grabbing::Grab()
	{
		//Grab

		Core::DataStructure::GameObject3D* go = static_cast<Core::DataStructure::GameObject3D*>(_object);

		if (go)
		{
			Physic::Raycast	ray{ go->GetGlobalPosition(), go->GetTransform()->GetForward(), 10.f };

			if (ray.actorClosestBlock->GetLayer() == 8/*Layer?*/)// is a Cube
			{
				//Change hierarchy of the object
				_originOfObject = ray.actorClosestBlock->GetTransform()->GetParent();
				go->AddChild(ray.actorClosestBlock);

				_grabbedObject = ray.actorClosestBlock;

				//Set new pos of Object
				_grabbedObject->SetGlobalPosition(go->GetGlobalPosition() + Math::QXvec3(0.f, 0.f, 5.f));
			}
			else
				return;
		}
		else
			return;

		_isUsed = QX_TRUE;
	}

	void Grabbing::Drop()
	{
		//Drop

		//Turn back Hierarchy
		_grabbedObject->GetTransform()->SetParent(_originOfObject);

		_grabbedObject = nullptr;
		_originOfObject = nullptr;

		_isUsed = QX_FALSE;
	}

	//Questions to ask my teammates
	/*
	* Comment j'accède à la liste des layers pour comparer le layer actuel à ceux existants ?
	*/ 

	//TODO:
	/* 
	* 
	*/
}