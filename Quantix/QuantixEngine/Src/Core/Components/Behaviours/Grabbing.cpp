#include "Core/Components/Behaviours/Grabbing.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core/Components/Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Gameplay::Grabbing>("Grabbing")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Gameplay::Grabbing&>()
		.constructor<Quantix::Gameplay::Grabbing&&>();
}

namespace Quantix::Gameplay
{
	Grabbing::Grabbing(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	Grabbing* Grabbing::Copy() const
	{
		return new Grabbing(*this);
	}

	void Grabbing::Awake()
	{
		go = static_cast<Core::DataStructure::GameObject3D*>(_object);
	}

	void Grabbing::Start()
	{}

	void Grabbing::Update(QXdouble deltaTime)
	{
		if (GetKey(QX_KEY_E) == Core::UserEntry::EKeyState::PRESSED)
		{
			Use();
		}

		if (_isUsed)
		{
			_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetKinematicTarget(go->GetGlobalPosition() + go->GetTransform()->GetForward() * 2);
			_grabbedObject->SetGlobalPosition(go->GetGlobalPosition() + go->GetTransform()->GetForward() * 2);
		}
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
		if (go)
		{
			Physic::Raycast	ray{ go->GetGlobalPosition()+ go->GetTransform()->GetForward() * 2, go->GetTransform()->GetForward(), 100.f};

			if (ray.actorClosestBlock && ray.actorClosestBlock->GetLayer() == Quantix::Core::DataStructure::Layer::SELECTABLE/*Layer?*/)// is a Cube
			{
				//Change hierarchy of the object
				_originOfObject = ray.actorClosestBlock->GetTransform()->GetParent();
				_grabbedObject = ray.actorClosestBlock;
				
				_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(true);
				_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(true);
				_isUsed = QX_TRUE;
			}
			else
				return;
		}
		else
			return;

	}

	void Grabbing::Drop()
	{
		//Drop
		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKinematic(false);
		_grabbedObject->GetComponent<Core::Components::Rigidbody>()->SetRigidFlagKineForQueries(false);

		_grabbedObject = nullptr;
		_originOfObject = nullptr;

		_isUsed = QX_FALSE;
	}

	//Questions to ask my teammates
	/*
	* Comment j'acc�de � la liste des layers pour comparer le layer actuel � ceux existants ?
	*/ 

	//TODO:
	/* 
	* 
	*/
}
