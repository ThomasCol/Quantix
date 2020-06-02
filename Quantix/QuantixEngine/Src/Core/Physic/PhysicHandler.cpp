#include "Core/Physic/PhysicHandler.h"
#include "Core/Physic/PhysicStatic.h"
#include "Core/Physic/PhysicDynamic.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Core/Physic/SimulationCallback.h"
#include "characterkinematic/PxController.h"

#include "Core/Physic/ControllerBehaviorCallback.h"
#include "Core/Physic/ControllerHitReport.h"

#include <vector>

#define PVD_HOST "127.0.0.1"	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
	rttr::registration::class_<Quantix::Core::Physic::PhysicHandler>("PhysicHandler")
	.constructor<>();
}

using namespace physx;
namespace Quantix::Core::Physic
{
	PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
	{
		// If it is a trigger
		if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
		{
			if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
				pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		// generate contacts for all that were not filtered above

		if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
			pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
		}
		return physx::PxFilterFlag::eDEFAULT;
	}

	PhysicHandler* PhysicHandler::_instance = nullptr;

	PhysicHandler* PhysicHandler::GetInstance() noexcept
	{
		if (!_instance)
			_instance = new PhysicHandler();

		return _instance;
	}

	PhysicHandler::~PhysicHandler()
	{
		for (auto it = _physObject.begin(); it != _physObject.end(); ++it)
			delete it->second;
	}

	IPhysicType* PhysicHandler::GetObject(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept
	{
		auto it = _physObject.find(object);

		// None ActorPhysic link at this GameObject
		if (it == _physObject.end())
			return CreateAndLinkActorPhysic(object, hasRigidbody);

		else if (!hasRigidbody && it->second->GetType() == ETypePhysic::DYNAMIC)
		{
			// One ActorPhysic link at this GameObject but it is Dynamic
			return SwapActorPhysicDynamicToStatic(object, it->second->GetObjectDynamic());
		}
		else if (hasRigidbody && it->second->GetType() == ETypePhysic::STATIC)
		{
			// One ActorPhysic link at this GameObject but it is Static
			return SwapActorPhysicStaticToDynamic(object, it->second->GetObjectStatic());
		}

		// Return PhysicActor Link to this GameComponent
		return it->second;
	}

	IPhysicType* PhysicHandler::CreateAndLinkActorPhysic(Core::DataStructure::GameComponent* object, QXbool dynamic) noexcept
	{
		if (dynamic)
		{
			// Create a ActorPhysic static linked to this GameComponent
			PhysicDynamic* tmp = new PhysicDynamic(mSDK);
			mScene->addActor(*tmp->GetRigid());
			tmp->GetRigid()->userData = dynamic_cast<Core::DataStructure::GameObject3D*>(object);
			_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			return tmp;
		}
		else
		{
			// Create a ActorPhysic static linked to this GameComponent
			PhysicStatic* tmp = new PhysicStatic(mSDK);
			tmp->GetRigid()->userData = dynamic_cast<Core::DataStructure::GameObject3D*>(object);
			mScene->addActor(*tmp->GetRigid());
			_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			return tmp;
		}
	}

	IPhysicType* PhysicHandler::SwapActorPhysicStaticToDynamic(Core::DataStructure::GameComponent* object, PhysicStatic* staticActor) noexcept
	{
		PhysicDynamic* tmp = new PhysicDynamic(mSDK, staticActor);
		mScene->removeActor(*staticActor->GetRigid());
		mScene->addActor(*tmp->GetRigid());
		_physObject.erase(object);
		_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
		return tmp;
	}

	IPhysicType* PhysicHandler::SwapActorPhysicDynamicToStatic(Core::DataStructure::GameComponent* object, PhysicDynamic* dynamicActor) noexcept
	{
		PhysicStatic* tmp = new PhysicStatic(mSDK, dynamicActor);
		mScene->removeActor(*dynamicActor->GetRigid());
		mScene->addActor(*tmp->GetRigid());
		_physObject.erase(object);
		_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
		return tmp;
	}

	PxShape* PhysicHandler::CreateCubeCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With BoxGeometrie
		PxShape* s = mSDK->createShape(PxBoxGeometry(0.5f, 0.5f, 0.5f), *mMaterial, QX_TRUE);
		
		// Attach the shape to the actor
		if (hasRigidbody)
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	PxShape* PhysicHandler::CreateSphereCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With SphereGeometrie
		PxShape* s = mSDK->createShape(PxSphereGeometry(1.f), *mMaterial, QX_TRUE);
		
		// Attach the shape to the actor
		if (hasRigidbody)
		{
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		}
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	PxShape* PhysicHandler::CreateCapsuleCollider(Core::DataStructure::GameComponent* object, QXbool hasRigidbody) noexcept
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With CapsuleGeometrie
		PxShape* s = mSDK->createShape(PxCapsuleGeometry(1.f, 1.f), *mMaterial, QX_TRUE);
		
		// Attach the shape to the actor
		if (hasRigidbody)
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	void PhysicHandler::InitSystem() noexcept
	{
		// Init Foundation
		pDefaultFundation = PxCreateFoundation(PX_PHYSICS_VERSION, pDefaultAllocatorCallback, pDefaultErrorCallback);
		if (!pDefaultFundation)
			std::cerr << "PxCreateFoundation failed!" << std::endl;

		// Init PVD
		pPvd = PxCreatePvd(*pDefaultFundation);
		PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		pPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

		// Init Physic
		mSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *pDefaultFundation, PxTolerancesScale(), recordMemoryAllocations, pPvd);
		if (!mSDK)
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		// Init Extensions
		if (!PxInitExtensions(*mSDK, pPvd))
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		// Create Cooking
		mCooking = PxCreateCooking(PX_PHYSICS_VERSION, mSDK->getFoundation(), PxCookingParams(mSDK->getTolerancesScale()));
		if (!mCooking)
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		InitScene();
		manager = PxCreateControllerManager(*mScene);

		// Init Default Material
		mMaterial = mSDK->createMaterial(0.5f, 0.5f, 0.1f);
		if (!mMaterial)
			std::cerr << "createMaterial failed!";

		// Link PVD
		PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, QX_TRUE);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, QX_TRUE);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, QX_TRUE);
		}
	}

	void PhysicHandler::InitScene() noexcept
	{
		PxSceneDesc sceneDesc(mSDK->getTolerancesScale());
		sceneDesc.gravity = PxVec3(0.0f, -15.f, 0.0f);

		sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVE_ACTORS;
		
		sceneDesc.filterShader = &contactReportFilterShader;
		sceneDesc.simulationEventCallback = new SimulationCallback();

		mCpuDispatcher = PxDefaultCpuDispatcherCreate(4);
		if (!mCpuDispatcher)
			std::cerr << "PxDefaultCpuDispatcherCreate failed!";
		sceneDesc.cpuDispatcher = mCpuDispatcher;

		mScene = mSDK->createScene(sceneDesc);
		if (!mScene)
			std::cerr << "createScene failed!";
	}

	void PhysicHandler::ReleaseSystem() noexcept
	{
		manager->purgeControllers();
		manager->release();
		mCooking->release();

		PxCloseExtensions();

		mCpuDispatcher->release();
		mSDK->release();

		if (pPvd)
		{
			PxPvdTransport* transport = pPvd->getTransport();
			pPvd->release();
			pPvd = NULL;
			transport->release();
			transport = NULL;
		}

		pDefaultFundation->release();
	}

	void PhysicHandler::Destroy() noexcept
	{
		delete _instance;
	}

	PxCapsuleController* PhysicHandler::CreateController(Core::DataStructure::GameComponent* object) noexcept
	{
		PxCapsuleControllerDesc desc;
		PxControllerDesc* cDesc;

		// Initial Position
		desc.position = PxExtendedVec3(0, 0, 0);
		// Controller skin within which contacts generated
		desc.contactOffset = 0.05f;
		// Max Obstacle hieght the caracther can climb
		desc.stepOffset = 0.01f;

		desc.slopeLimit = 0.5f; // max slope the character can walk
		desc.radius = 0.5f; // radius of the capsule
		desc.height = 2; // height of the capsule
		desc.upDirection = PxVec3(0, 1, 0); // Specifies the 'up'
		desc.material = mMaterial;

		desc.reportCallback = new ControllerHitReport();
		desc.behaviorCallback = new ControllerBehaviorCallback();

		desc.userData = (Core::DataStructure::GameObject3D*)object;

		cDesc = &desc;
		
		PxController* c = manager->createController(*cDesc); 
		
		return (PxCapsuleController*)c;
	}

	PxJoint* PhysicHandler::CreateJoint(Core::DataStructure::GameComponent* object, Core::DataStructure::GameComponent* other, Math::QXvec3 vec, const Physic::Joint& joint) noexcept
	{
		PhysicDynamic* type0 = GetObject(object, QX_TRUE)->GetObjectDynamic();

		PhysicDynamic* type1 = GetObject(other, QX_TRUE)->GetObjectDynamic();


		//PxRevoluteJointCreate
		PxRevoluteJoint* newJoint = PxRevoluteJointCreate(*mSDK, type0->GetRigid(), PxTransform(-physx::PxVec3(vec.x, vec.y, vec.z)), type1->GetRigid(), PxTransform(physx::PxVec3(vec.x, vec.y, vec.z)));

		newJoint->setBreakForce(joint.breakForce, joint.breakTorque);
		return newJoint;
	}

	void PhysicHandler::UpdateSystem(double deltaTime) noexcept
	{
		mAccumulator += (physx::PxReal)deltaTime;
		if (mAccumulator < mStepSize)
			return;

		mAccumulator = 0.0f;

		mScene->simulate(PxReal(mStepSize));

		mScene->fetchResults(QX_TRUE);
	}

	void PhysicHandler::UpdatePhysicActor(QXbool isPlaying) noexcept
	{
		if (isPlaying)
			UpdatePlayingActor();
		else
			UpdateEditorActor();
	}

	void PhysicHandler::UpdatePlayingActor() noexcept
	{
		PxU32 nbActors;
		PxActor** listActor = mScene->getActiveActors(nbActors);

		for (PxU32 index = 0; index < nbActors; index++)
		{
			PxRigidDynamic* currentActor = (PxRigidDynamic*)listActor[index];
			if (currentActor)
			{
				PxTransform transformPhysic = currentActor->getGlobalPose();
				transformPhysic.q = transformPhysic.q.getConjugate();

				if (((Core::DataStructure::GameObject3D*)currentActor->userData))
				{
					// Set Transform GameObject On PhysicActor Transform
					Transform3D* transform = ((Core::DataStructure::GameObject3D*)currentActor->userData)->GetTransform();
					transform->SetPosition(Math::QXvec3(transformPhysic.p.x, transformPhysic.p.y, transformPhysic.p.z));
					transform->SetRotation(Math::QXquaternion(transformPhysic.q.w, transformPhysic.q.x, transformPhysic.q.y, transformPhysic.q.z));
				}
			}
		}

		// Update Controller : his linked GameObject follow the Controller Physic  
		int numController = manager->getNbControllers();
		for (int i = 0; i < numController; i++)
		{
			PxController* controller = manager->getController(i);

			if (controller)
			{
				PxExtendedVec3 pos = controller->getPosition();
				((Core::DataStructure::GameObject3D*)controller->getUserData())->GetTransform()->SetPosition(Math::QXvec3((QXfloat)pos.x, (QXfloat)pos.y, (QXfloat)pos.z));
			}
		}
	}

	void PhysicHandler::UpdateEditorActor() noexcept
	{
		for (auto it = _physObject.begin(); it != _physObject.end(); ++it)
		{
			if (it->second && it->first)
			{
				// Set RigidBody Transform On GameOject Transform
				Math::QXvec3 pos = ((Core::DataStructure::GameObject3D*)it->first)->GetTransform()->GetGlobalPosition();
				Math::QXquaternion quat = ((Core::DataStructure::GameObject3D*)it->first)->GetLocalRotation();
				quat = quat.ConjugateQuaternion();
				if (it->second->GetType() == ETypePhysic::DYNAMIC)
				{
					PxTransform transform = it->second->GetObjectDynamic()->GetRigid()->getGlobalPose();

					transform.p = PxVec3(pos.x, pos.y, pos.z);
					transform.q = PxQuat(quat.v.x, quat.v.y, quat.v.z, quat.w);

					it->second->GetObjectDynamic()->GetRigid()->setGlobalPose(transform);
				}
				else
				{
					PxTransform transform = it->second->GetObjectStatic()->GetRigid()->getGlobalPose();

					transform.p = PxVec3(pos.x, pos.y, pos.z);
					transform.q = PxQuat(quat.v.x, quat.v.y, quat.v.z, quat.w);

					it->second->GetObjectStatic()->GetRigid()->setGlobalPose(transform);
				}
			}
		}

		// Update Controller : Controller Physic follow his linked GameObject
		int numController = manager->getNbControllers();
		for (int i = 0; i < numController; i++)
		{
			PxController* controller = manager->getController(i);

			if (controller)
			{
				Math::QXvec3 pos = ((Core::DataStructure::GameObject3D*)controller->getUserData())->GetTransform()->GetPosition();

				PxTransform transform = controller->getActor()->getGlobalPose();

				transform.p = PxVec3(pos.x, pos.y, pos.z);

				controller->getActor()->setGlobalPose(transform);
			}
		}
	}

	void PhysicHandler::Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax, Physic::Raycast& ownRaycast) noexcept 
	{
		PxRaycastBuffer hitRaycast; // resultat du ray cast apres test

		ownRaycast.status = mScene->raycast(PxVec3(origin.x, origin.y, origin.z), PxVec3(unitDir.x, unitDir.y, unitDir.z), distMax, hitRaycast);
		if (ownRaycast.status && hitRaycast.hasBlock)
		{
			// Load Own Raycast Struct
			ownRaycast.normalClosestBlock = Math::QXvec3(hitRaycast.block.normal.x, hitRaycast.block.normal.y, hitRaycast.block.normal.z);
			ownRaycast.positionClosestBlock = Math::QXvec3(hitRaycast.block.position.x, hitRaycast.block.position.y, hitRaycast.block.position.z);
			ownRaycast.distanceClosestBlock = hitRaycast.block.distance;
			ownRaycast.actorClosestBlock = (Core::DataStructure::GameObject3D*)hitRaycast.block.actor->userData;
		}
	}

	std::vector<Core::DataStructure::GameObject3D*> PhysicHandler::OverlapSphere(QXfloat radius, Physic::Transform3D* transform) noexcept 
	{
		Math::QXvec3 p = transform->GetGlobalPosition();
		Math::QXquaternion q = transform->GetGlobalRotation().ConjugateQuaternion();

		PxTransform shapePosition = PxTransform(p.x, p.y, p.z, PxQuat(q.v.x, q.v.y, q.v.z, q.w));

		PxSphereGeometry overlapGeometrie = PxSphereGeometry(radius);

		PxQueryFilterData fd;
		fd.flags |= PxQueryFlag::eNO_BLOCK;

		PxOverlapHit hitBuffer[256];
		PxOverlapBuffer hit(hitBuffer, 256);

		QXbool status = mScene->overlap(overlapGeometrie, shapePosition, hit, fd);
		std::vector<Core::DataStructure::GameObject3D*> list;
		for (QXint i = 0; i < hit.nbTouches; i++)
				list.push_back((Core::DataStructure::GameObject3D*)(hit.touches[i].actor->userData));
		return list;
	}

	void PhysicHandler::CleanScene() noexcept
	{
		// Remove Actor Dynamic
		int numActorsDynamic = mScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);
		PxActor** actorsDyna = (PxActor**)malloc(sizeof(PxActor*) * numActorsDynamic);
		mScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, actorsDyna, numActorsDynamic);

		mScene->removeActors(actorsDyna, numActorsDynamic);

		// Remove Actor Static
		int numActorsStatic = mScene->getNbActors(PxActorTypeFlag::eRIGID_STATIC);
		PxActor** actorsStat = (PxActor**)malloc(sizeof(PxActor*) * numActorsStatic);
		mScene->getActors(PxActorTypeFlag::eRIGID_STATIC, actorsStat, numActorsStatic);

		mScene->removeActors(actorsStat, numActorsStatic);

		// Remove Controller
		manager->purgeControllers();
	}

	void PhysicHandler::CleanController(PxCapsuleController* controller) noexcept
	{
		manager->purgeControllers();
	}

#pragma region FlagSetters
	void PhysicHandler::SetFlagAdaptiveForce(QXbool b) noexcept
	{
		sceneFlag.adaptiveForce = b;
		mScene->setFlag(PxSceneFlag::eADAPTIVE_FORCE, b);
	}

	void PhysicHandler::SetFlagDisableCCDResweep(QXbool b) noexcept
	{
		sceneFlag.disableCCDResweep = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CCD_RESWEEP, b);
	}

	void PhysicHandler::SetFlagDisableContactCache(QXbool b) noexcept
	{
		sceneFlag.disableContactCache = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CONTACT_CACHE, b);
	}

	void PhysicHandler::SetFlagDisableContactReport(QXbool b) noexcept
	{
		sceneFlag.disableContactReportResize = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CONTACT_REPORT_BUFFER_RESIZE, b);
	}

	void PhysicHandler::SetFlagActiveActors(QXbool b) noexcept
	{
		sceneFlag.activeActors = b;
		mScene->setFlag(PxSceneFlag::eENABLE_ACTIVE_ACTORS, b);
	}

	void PhysicHandler::SetFlagAveragePoint(QXbool b) noexcept
	{
		sceneFlag.averagePoint = b;
		mScene->setFlag(PxSceneFlag::eENABLE_AVERAGE_POINT, b);
	}

	void PhysicHandler::SetFlagCCD(QXbool b) noexcept
	{
		sceneFlag.ccd = b;
		mScene->setFlag(PxSceneFlag::eENABLE_CCD, b);
	}

	void PhysicHandler::SetFlagEnhancedDeterminism(QXbool b) noexcept
	{
		sceneFlag.enhancedDeterminism = b;
		mScene->setFlag(PxSceneFlag::eENABLE_ENHANCED_DETERMINISM, b);
	}

	void PhysicHandler::SetFlagFrictionEveryIt(QXbool b) noexcept
	{
		sceneFlag.frictionEveryIteration = b;
		mScene->setFlag(PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION, b);
	}

	void PhysicHandler::SetFlagGPUDynamics(QXbool b) noexcept
	{
		sceneFlag.gpuDynamics = b;
		mScene->setFlag(PxSceneFlag::eENABLE_GPU_DYNAMICS, b);
	}

	void PhysicHandler::SetFlagPCM(QXbool b) noexcept
	{
		sceneFlag.pcm = b;
		mScene->setFlag(PxSceneFlag::eENABLE_PCM, b);
	}

	void PhysicHandler::SetFlagStabilization(QXbool b) noexcept
	{
		sceneFlag.stabilization = b;
		mScene->setFlag(PxSceneFlag::eENABLE_STABILIZATION, b);
	}

	void PhysicHandler::SetFlagExcludeKineActiverActors(QXbool b) noexcept
	{
		sceneFlag.excludeKineActiveActors = b;
		mScene->setFlag(PxSceneFlag::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS, b);
	}

	void PhysicHandler::SetFlagMutable(QXbool b) noexcept
	{
		sceneFlag.mutableFlags = b;
		mScene->setFlag(PxSceneFlag::eMUTABLE_FLAGS, b);
	}

	void PhysicHandler::SetFlagRequireRWLock(QXbool b) noexcept
	{
		sceneFlag.requireRWLock = b;
		mScene->setFlag(PxSceneFlag::eREQUIRE_RW_LOCK, b);
	}
#pragma endregion
}