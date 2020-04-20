#ifndef __PHYSICHANDLER_H__
#define __PHYSICHANDLER_H__

#include <map>

#include <PxPhysicsAPI.h>
#include <PxActor.h>
#include <PxRigidActorExt.h>
#include "Core/DLLHeader.h"

#include "Core/DataStructure/GameComponent.h"

namespace Quantix::Physic
{
	using namespace physx;
	class IPhysicType;

	class QUANTIX_API PhysicHandler
	{
	private:
		PhysicHandler() = default;


#pragma region Attributes

		static PhysicHandler* _instance;

		bool recordMemoryAllocations = true;
		PxPhysics* mSDK = NULL;
		PxCooking* mCooking = NULL;
		PxDefaultErrorCallback pDefaultErrorCallback;
		PxDefaultAllocator pDefaultAllocatorCallback;
		PxFoundation* pDefaultFundation;
		PxPvd* pPvd;
		PxSimulationFilterShader pDefaultFilterShader = PxDefaultSimulationFilterShader;
		PxDefaultCpuDispatcher* mCpuDispatcher;
		PxScene* mScene;
		PxMaterial* mMaterial;

		//MySimulationCallback* pSimulationEvent;

		PxCollection* collection;

		PxReal mAccumulator = 0.0f;
		PxReal mStepSize = 1.0f / 60.0f;

		std::map<Core::DataStructure::GameComponent*, IPhysicType*>		_physObject;

#pragma endregion
	public:
#pragma region Constructors
		PhysicHandler(const PhysicHandler& src) = delete;
		PhysicHandler(PhysicHandler&& src) = delete;
		~PhysicHandler() = default;
#pragma endregion

#pragma region Functions

		static PhysicHandler* GetInstance();


		void		Print(std::vector<Core::DataStructure::GameComponent*> go);

		IPhysicType* GetObject(Core::DataStructure::GameComponent* object, bool hasRigidbody = false);

		IPhysicType* CreateCubeCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		IPhysicType* CreateSphereCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		IPhysicType* CreateCapsuleCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		void		InitSystem();
		void		ReleaseSystem();
		void		InitScene();

		void		UpdateSystem(std::vector<Core::DataStructure::GameComponent*> go, double deltaTime);

#pragma region Operators

		PhysicHandler& operator=(const PhysicHandler& other) = delete;
		PhysicHandler& operator=(PhysicHandler&& other) = delete;

#pragma endregion

#pragma endregion
	};
}
#endif

