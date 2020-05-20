#ifndef __PHYSICHANDLER_H__
#define __PHYSICHANDLER_H__

#include <map>

#include <PxPhysicsAPI.h>
#include <PxActor.h>
#include <PxRigidActorExt.h>
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Physic/PhysicSetting.h"
#include "Physic/Raycast.h"
#include "Physic/Joint.h"

#include "Core/DataStructure/GameComponent.h"

namespace Quantix::Physic
{
	using namespace physx;
	class IPhysicType;

	class QUANTIX_API PhysicHandler
	{
	private:
		/**
		 * @brief Construct a new Physic Handler object
		 * 
		 */
		PhysicHandler() = default;


#pragma region Attributes

#pragma region Singleton
		static PhysicHandler* _instance;
#pragma endregion

#pragma region PhysX
		bool recordMemoryAllocations = true;
		PxPhysics* mSDK = NULL;
		PxCooking* mCooking = NULL;
		PxDefaultErrorCallback pDefaultErrorCallback;
		PxDefaultAllocator pDefaultAllocatorCallback;
		PxFoundation* pDefaultFundation;
		PxPvd* pPvd;
		PxSimulationFilterShader pDefaultFilterShader = PxDefaultSimulationFilterShader;
		PxDefaultCpuDispatcher* mCpuDispatcher;
		PxScene* mScene = nullptr;
		PxMaterial* mMaterial = nullptr;
		PxControllerManager* manager = nullptr;
		PxCollection* collection = nullptr;

		// To Delete
		PxReal mAccumulator = 0.0f;
		PxReal mStepSize = 1/240.f;
#pragma endregion

		std::map<Core::DataStructure::GameComponent*, IPhysicType*>		_physObject;

#pragma region Flag
		SceneFlag sceneFlag;
#pragma endregion

#pragma endregion
	public:
#pragma region Constructors

		PhysicHandler(const PhysicHandler& src) = delete;
		PhysicHandler(PhysicHandler&& src) = delete;

		/**
		 * @brief Destroy the Physic Handler object
		 * 
		 */
		~PhysicHandler() = default;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Get the Instance object
		 * 
		 * @return PhysicHandler* return a pointer on the PhysicHandler Instance
		 */
		static PhysicHandler* GetInstance();

		/**
		 * @brief Init Physic System
		 * 
		 */
		void		InitSystem();
		
		/**
		 * @brief Init Physic Scene
		 * 
		 */
		void		InitScene();

		/**
		 * @brief Release System Physic
		 * 
		 */
		void		ReleaseSystem();

		/**
		 * @brief Delete Singleton
		 *
		 */
		void Destroy();

		/**
		 * @brief Return PhysicType Linked to the GameComponent
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return IPhysicType* PhysicType Linked
		 */
		IPhysicType* GetObject(Core::DataStructure::GameComponent* object, bool hasRigidbody = false);

		/**
		 * @brief Create a And Link Actor Physic object
		 * 
		 * @param object GameComponent linked in map
		 * @param dynamic 
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */
		IPhysicType* CreateAndLinkActorPhysic(Core::DataStructure::GameComponent* object, bool dynamic);

		/**
		 * @brief Swap ActorPhysic in static to dynamic
		 * 
		 * @param object GameComponent linked in map
		 * @param staticActor ActorPhysic Static
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */
		IPhysicType* SwapActorPhysicStaticToDynamic(Core::DataStructure::GameComponent* object, PhysicStatic* staticActor);

		/**
		 * @brief  Swap ActorPhysic in dynamic to static
		 * 
		 * @param object GameComponent linked in map
		 * @param dynamicActor ActorPhysic dynamic
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */
		IPhysicType* SwapActorPhysicDynamicToStatic(Core::DataStructure::GameComponent* object, PhysicDynamic* dynamicActor);


		/**
		 * @brief Create a Cube Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateCubeCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		/**
		 * @brief Create a Sphere Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateSphereCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		/**
		 * @brief Create a Capsule Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateCapsuleCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody);

		PxCapsuleController* CreateController(Core::DataStructure::GameComponent* object);
		PxJoint* CreateJoint(Core::DataStructure::GameComponent* object, Core::DataStructure::GameComponent* other, Math::QXvec3 vec, Physic::Joint joint);

		// Update
		/**
		 * @brief Update and simulate System Physic
		 * 
		 * @param deltaTime 
		 */
		void		UpdateSystem(double deltaTime);

		/**
		 * @brief Synchronize Physic Actor with GameObject
		 * 
		 * @param isPlaying 
		 */
		void		UpdatePhysicActor(bool isPlaying = false);

		/**
		 * @brief Update Actor in playing
		 * 
		 */
		void UpdatePlayingActor();

		/**
		 * @brief Update Actor in Editor
		 * 
		 */
		void UpdateEditorActor();

		void Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax, Raycast& ownRaycast);
		std::vector<Core::DataStructure::GameObject3D*> OverlapSphere(QXfloat radius, Physic::Transform3D* transform);

		void CleanScene();

#pragma region Operators

		PhysicHandler& operator=(const PhysicHandler& other) = delete;
		PhysicHandler& operator=(PhysicHandler&& other) = delete;

#pragma endregion


#pragma region Accessors

		/**
		 * @brief Get the Flag Adaptive Force object
		 * 
		 * @return Value of the Flag
		 */
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

