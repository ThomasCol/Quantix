#ifndef __PHYSICHANDLER_H__
#define __PHYSICHANDLER_H__

#include <map>

#include <PxPhysicsAPI.h>
#include <PxActor.h>
#include <PxRigidActorExt.h>
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Physic/PhysicSetting.h"

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

		PxCollection* collection;

		PxReal mAccumulator = 0.0f;
		PxReal mStepSize = 1.0f / 60.0f;

		std::map<Core::DataStructure::GameComponent*, IPhysicType*>		_physObject;

		SceneFlag sceneFlag;

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

		PxShape* CreateCubeCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		PxShape* CreateSphereCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		PxShape* CreateCapsuleCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		void		InitSystem();
		void		ReleaseSystem();
		void		InitScene();

		void		UpdateSystem(double deltaTime);
		void		UpdatePhysicActor(bool isPlaying = false);

#pragma region Operators

		PhysicHandler& operator=(const PhysicHandler& other) = delete;
		PhysicHandler& operator=(PhysicHandler&& other) = delete;

#pragma endregion


#pragma region Accessors

		bool GetFlagAdaptiveForce()				{ return sceneFlag.adaptiveForce; }
		bool GetFlagDisableCCDResweep()			{ return sceneFlag.disableCCDResweep; }
		bool GetFlagDisableContactCache()		{ return sceneFlag.disableContactCache; }
		bool GetFlagDisableContactReport()		{ return sceneFlag.disableContactReportResize; }
		bool GetFlagActiveActors()				{ return sceneFlag.activeActors; }
		bool GetFlagAveragePoint()				{ return sceneFlag.averagePoint; }
		bool GetFlagCCD()						{ return sceneFlag.ccd; }
		bool GetFlagEnhancedDeterminism()		{ return sceneFlag.enhancedDeterminism; }
		bool GetFlagFrictionEveryIt()			{ return sceneFlag.frictionEveryIteration; }
		bool GetFlagGPUDynamics()				{ return sceneFlag.gpuDynamics; }
		bool GetFlagPCM()						{ return sceneFlag.pcm; }
		bool GetFlagStabilization()				{ return sceneFlag.stabilization; }
		bool GetFlagExcludeKineActiverActors()	{ return sceneFlag.excludeKineActiveActors; }
		bool GetFlagMutable()					{ return sceneFlag.mutableFlags; }
		bool GetFlagRequireRWLock()				{ return sceneFlag.requireRWLock; }


		void SetFlagAdaptiveForce(bool b);
		void SetFlagDisableCCDResweep(bool b);
		void SetFlagDisableContactCache(bool b);
		void SetFlagDisableContactReport(bool b);
		void SetFlagActiveActors(bool b);
		void SetFlagAveragePoint(bool b);
		void SetFlagCCD(bool b);
		void SetFlagEnhancedDeterminism(bool b);
		void SetFlagFrictionEveryIt(bool b);
		void SetFlagGPUDynamics(bool b);
		void SetFlagPCM(bool b);
		void SetFlagStabilization(bool b);
		void SetFlagExcludeKineActiverActors(bool b);
		void SetFlagMutable(bool b);
		void SetFlagRequireRWLock(bool b);
#pragma endregion


#pragma endregion

		CLASS_REGISTRATION()
	};
}
#endif

