#include "Core/Components//Behaviours//Cube.h"

#include <Physic/Raycast.h>
#include "Core/UserEntry/InputManager.h"
#include "Core/Components/Rigidbody.h"

namespace Quantix::Gameplay
{
	void Cube::Awake()
	{}

	void Cube::Start()
	{}

	void Cube::Update(QXdouble deltaTime)
	{
		switch (_state)
		{
			case ECubeState::MAGNET_POS:	Attract(deltaTime); break;
			case ECubeState::MAGNET_NEG:	Reject(deltaTime); break;
			default: break;
		}
	}

	void Cube::Attract(QXdouble deltaTime)
	{

		//With list of gameobjects or Rigidbodies
		//foreach member of list
		// rigidbody->AddForce((actualpos - rigidbodypos))
	}

	void Cube::Reject(QXdouble deltaTime)
	{}

	void Cube::ChangeState(ECubeState newState)
	{
		_state = newState;
	}

	//Questions to ask my teammates
	/*
	* Comment accéder à tout les cubes de la scène, ou à la limite tout ceux d'une certaine zone ?
	*/

	//TODO:
	/*
	* 
	*/
}