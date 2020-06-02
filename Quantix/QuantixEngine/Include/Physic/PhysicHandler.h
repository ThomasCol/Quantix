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
		QXbool recordMemoryAllocations = true;
		PxPhysics* mSDK = nullptr;
		PxCooking* mCooking = nullptr;
		PxDefaultErrorCallback pDefaultErrorCallback;
		PxDefaultAllocator pDefaultAllocatorCallback;
		PxFoundation* pDefaultFundation = nullptr;
		PxPvd* pPvd = nullptr;
		PxDefaultCpuDispatcher* mCpuDispatcher = nullptr;
		PxScene* mScene = nullptr;
		PxMaterial* mMaterial = nullptr;
		PxControllerManager* manager = nullptr;
		
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
		~PhysicHandler();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Get the Instance object
		 * 
		 * @return PhysicHandler* return a pointer on the PhysicHandler Instance
		 */
		static PhysicHandler* GetInstance() noexcept;

		/**
		 * @brief Init Physic System
		 * 
		 */
		void		InitSystem() noexcept;
		
		/**
		 * @brief Init Physic Scene
		 * 
		 */
		void		InitScene() noexcept;

		/**
		 * @brief Release System Physic
		 * 
		 */
		void		ReleaseSystem() noexcept;

		/**
		 * @brief Delete Singleton
		 *
		 */
		void Destroy() noexcept;

		/**
		 * @brief Return PhysicType Linked to the GameComponent
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return IPhysicType* PhysicType Linked
		 */
		IPhysicType* GetObject(Core::DataStructure::GameComponent* object, QXbool hasRigidbody = false) noexcept;

		/**
		 * @brief Create a And Link Actor Physic object
		 * 
		 * @param object GameComponent linked in map
		 * @param dynamic 
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */
		IPhysicType* CreateAndLinkActorPhysic(Core::DataStructure::GameComponent* object, QXbool dynamic) noexcept;

		/**
		 * @brief Swap ActorPhysic in static to dynamic
		 * 
		 * @param object GameComponent linked in map
		 * @param staticActor ActorPhysic Static
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */ 
		IPhysicType* SwapActorPhysicStaticToDynamic(Core::DataStructure::GameComponent* object, PhysicStatic* staticActor) noexcept;

		/**
		 * @brief  Swap ActorPhysic in dynamic to static
		 * 
		 * @param object GameComponent linked in map
		 * @param dynamicActor ActorPhysic dynamic
		 * @return IPhysicType* Pointer on IPhysicType Linked in map
		 */
		IPhysicType* SwapActorPhysicDynamicToStatic(Core::DataStructure::GameComponent* object, PhysicDynamic* dynamicActor) noexcept;


		/**
		 * @brief Create a Cube Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateCubeCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept;

		/**
		 * @brief Create a Sphere Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateSphereCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept;

		/**
		 * @brief Create a Capsule Collider object
		 * 
		 * @param object GameComponent linked in map
		 * @param hasRigidbody 
		 * @return PxShape* New Shape
		 */
		PxShape* CreateCapsuleCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept;

		/**
		 * @brief Create a CharacterController object
		 * 
		 * @param object Gamecomponent who will be link to the future charactercontroller
		 * @return PxCapsuleController* New Controller
		 */
		PxCapsuleController* CreateController(Core::DataStructure::GameComponent* object) noexcept;

		/**
		 * @brief Create a Joint object between object and other
		 * 
		 * @param object 
		 * @param other 
		 * @param vec Position of Joint between the object
		 * @param joint Struct who have some information for the future joint
		 * @return PxJoint* new joint
		 */
		PxJoint* CreateJoint(Core::DataStructure::GameComponent* object, Core::DataStructure::GameComponent* other, Math::QXvec3 vec, const Physic::Joint& joint) noexcept;

		// Update
		/**
		 * @brief Update and simulate System Physic
		 * 
		 * @param deltaTime 
		 */
		void		UpdateSystem(double deltaTime) noexcept;

		/**
		 * @brief Synchronize Physic Actor with GameObject
		 * 
		 * @param isPlaying 
		 */
		void		UpdatePhysicActor(QXbool isPlaying = false) noexcept;

		/**
		 * @brief Update Actor in playing
		 * 
		 */
		void UpdatePlayingActor() noexcept;

		/**
		 * @brief Update Actor in Editor
		 * 
		 */
		void UpdateEditorActor() noexcept;

		/**
		 * @brief generate a raycast and return the information
		 * 
		 * @param origin Origin of the raycast
		 * @param unitDir Direction of the raycast
		 * @param distMax Distance Maximum of the raycast
		 * @param ownRaycast Structure who will have the information of the raycast
		 */
		void Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax, Raycast& ownRaycast) noexcept;

		/**
		 * @brief Generate an overlap of a sphere and return a list of the GameObject who intersect with it
		 * 
		 * @param radius Radius of the Overlap Sphere
		 * @param transform Transform of the Sphere (Position and rotation)
		 * @return std::vector<Core::DataStructure::GameObject3D*> List of GameObject3D who intersect
		 */
		std::vector<Core::DataStructure::GameObject3D*> OverlapSphere(QXfloat radius, Physic::Transform3D* transform) noexcept;

		/**
		 * @brief Reboot the PxScene
		 * 
		 */
		void CleanScene() noexcept;

		/**
		* @brief Remove a controller of the PxScene
		*
		* @param controller Controller to remove
		*
		*/
		void CleanController(PxCapsuleController* controller) noexcept;

#pragma region Operators

		/**
		 * @brief Operator = per copy , delete
		 */
		PhysicHandler& operator=(const PhysicHandler& other) = delete;

		/**
		 * @brief Operator = per move , delete
		 */
		PhysicHandler& operator=(PhysicHandler&& other) = delete;

#pragma endregion

#pragma region Accessors

		/**
		 * @brief Get the Flag Adaptive Force object
		 * 
		 * @return Value of the Flag
		 */
		QXbool GetFlagAdaptiveForce()				noexcept	{ return sceneFlag.adaptiveForce; }
		QXbool GetFlagDisableCCDResweep()			noexcept	{ return sceneFlag.disableCCDResweep; }
		QXbool GetFlagDisableContactCache()			noexcept	{ return sceneFlag.disableContactCache; }
		QXbool GetFlagDisableContactReport()		noexcept	{ return sceneFlag.disableContactReportResize; }
		QXbool GetFlagActiveActors()				noexcept	{ return sceneFlag.activeActors; }
		QXbool GetFlagAveragePoint()				noexcept	{ return sceneFlag.averagePoint; }
		QXbool GetFlagCCD()							noexcept	{ return sceneFlag.ccd; }
		QXbool GetFlagEnhancedDeterminism()			noexcept	{ return sceneFlag.enhancedDeterminism; }
		QXbool GetFlagFrictionEveryIt()				noexcept	{ return sceneFlag.frictionEveryIteration; }
		QXbool GetFlagGPUDynamics()					noexcept	{ return sceneFlag.gpuDynamics; }
		QXbool GetFlagPCM()							noexcept	{ return sceneFlag.pcm; }
		QXbool GetFlagStabilization()				noexcept	{ return sceneFlag.stabilization; }
		QXbool GetFlagExcludeKineActiverActors()	noexcept	{ return sceneFlag.excludeKineActiveActors; }
		QXbool GetFlagMutable()						noexcept	{ return sceneFlag.mutableFlags; }
		QXbool GetFlagRequireRWLock()				noexcept	{ return sceneFlag.requireRWLock; }

		void SetFlagAdaptiveForce(QXbool b)				noexcept;
		void SetFlagDisableCCDResweep(QXbool b)			noexcept;
		void SetFlagDisableContactCache(QXbool b)		noexcept;
		void SetFlagDisableContactReport(QXbool b)		noexcept;
		void SetFlagActiveActors(QXbool b)				noexcept;
		void SetFlagAveragePoint(QXbool b)				noexcept;
		void SetFlagCCD(QXbool b)						noexcept;
		void SetFlagEnhancedDeterminism(QXbool b)		noexcept;
		void SetFlagFrictionEveryIt(QXbool b)			noexcept;
		void SetFlagGPUDynamics(QXbool b)				noexcept;
		void SetFlagPCM(QXbool b)						noexcept;
		void SetFlagStabilization(QXbool b)				noexcept;
		void SetFlagExcludeKineActiverActors(QXbool b)	noexcept;
		void SetFlagMutable(QXbool b)					noexcept;
		void SetFlagRequireRWLock(QXbool b)				noexcept;
#pragma endregion


#pragma endregion

		CLASS_REGISTRATION()
	};
}
#endif

