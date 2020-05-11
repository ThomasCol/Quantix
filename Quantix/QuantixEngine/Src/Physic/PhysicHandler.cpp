#include "Physic/PhysicHandler.h"
#include "Physic/PhysicStatic.h"
#include "Physic/PhysicDynamic.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Physic/SimulationCallback.h"
#include <vector>

#define PVD_HOST "127.0.0.1"	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
rttr::registration::class_<Quantix::Physic::PhysicHandler>("PhysicHandler")
.constructor<>();
	/*.property("AdaptiveForce", &Quantix::Physic::PhysicHandler::GetFlagAdaptiveForce, &Quantix::Physic::PhysicHandler::SetFlagAdaptiveForce)
	.property("DisableCCDResweep", &Quantix::Physic::PhysicHandler::GetFlagDisableCCDResweep, &Quantix::Physic::PhysicHandler::SetFlagDisableCCDResweep)
	.property("DisableContactCache", &Quantix::Physic::PhysicHandler::GetFlagDisableContactCache, &Quantix::Physic::PhysicHandler::SetFlagDisableContactCache)
	.property("DisableContactReport", &Quantix::Physic::PhysicHandler::GetFlagDisableContactReport, &Quantix::Physic::PhysicHandler::SetFlagDisableContactReport)
	.property("ActiveActors", &Quantix::Physic::PhysicHandler::GetFlagActiveActors, &Quantix::Physic::PhysicHandler::SetFlagActiveActors)
	.property("AveragePoint", &Quantix::Physic::PhysicHandler::GetFlagAveragePoint, &Quantix::Physic::PhysicHandler::SetFlagAveragePoint)
	.property("CCD", &Quantix::Physic::PhysicHandler::GetFlagCCD, &Quantix::Physic::PhysicHandler::SetFlagCCD)
	.property("EnhancedDeterminism", &Quantix::Physic::PhysicHandler::GetFlagEnhancedDeterminism, &Quantix::Physic::PhysicHandler::SetFlagEnhancedDeterminism)
	.property("FrictionEveryIt", &Quantix::Physic::PhysicHandler::GetFlagFrictionEveryIt, &Quantix::Physic::PhysicHandler::SetFlagFrictionEveryIt)
	.property("GPUDynamics", &Quantix::Physic::PhysicHandler::GetFlagGPUDynamics, &Quantix::Physic::PhysicHandler::SetFlagGPUDynamics)
	.property("PCM", &Quantix::Physic::PhysicHandler::GetFlagPCM, &Quantix::Physic::PhysicHandler::SetFlagPCM)
	.property("Stabilization", &Quantix::Physic::PhysicHandler::GetFlagStabilization, &Quantix::Physic::PhysicHandler::SetFlagStabilization)
	.property("ExcludeKineActiverActors", &Quantix::Physic::PhysicHandler::GetFlagExcludeKineActiverActors, &Quantix::Physic::PhysicHandler::SetFlagExcludeKineActiverActors)
	.property("Mutable", &Quantix::Physic::PhysicHandler::GetFlagMutable, &Quantix::Physic::PhysicHandler::SetFlagMutable)
	.property("RequireRWLock", &Quantix::Physic::PhysicHandler::GetFlagRequireRWLock, &Quantix::Physic::PhysicHandler::SetFlagRequireRWLock);*/
}

using namespace physx;
namespace Quantix::Physic
{
	PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)

	{
		// If it is a trigger
		if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
		{
			//if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
				pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		// generate contacts for all that were not filtered above
		std::cout << "Not Trigger" << std::endl;

		//if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
			pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
		}
		return physx::PxFilterFlag::eDEFAULT;
	}

	PhysicHandler* PhysicHandler::_instance = nullptr;

	PhysicHandler* PhysicHandler::GetInstance()
	{
		if (!_instance)
		{
			_instance = new PhysicHandler();
		}
		return _instance;
	}

	IPhysicType* PhysicHandler::GetObject(Core::DataStructure::GameComponent* object, bool hasRigidbody)
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

	IPhysicType* PhysicHandler::CreateAndLinkActorPhysic(Core::DataStructure::GameComponent* object, bool dynamic)
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

	IPhysicType* PhysicHandler::SwapActorPhysicStaticToDynamic(Core::DataStructure::GameComponent* object, PhysicStatic* staticActor)
	{
		PhysicDynamic* tmp = new PhysicDynamic(mSDK, staticActor);
		mScene->removeActor(*staticActor->GetRigid());
		mScene->addActor(*tmp->GetRigid());
		_physObject.erase(object);
		_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
		return tmp;
	}

	IPhysicType* PhysicHandler::SwapActorPhysicDynamicToStatic(Core::DataStructure::GameComponent* object, PhysicDynamic* dynamicActor)
	{
		PhysicStatic* tmp = new PhysicStatic(mSDK, dynamicActor);
		mScene->removeActor(*dynamicActor->GetRigid());
		mScene->addActor(*tmp->GetRigid());
		_physObject.erase(object);
		_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
		return tmp;
	}

	PxShape* PhysicHandler::CreateCubeCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With BoxGeometrie
		PxShape* s = mSDK->createShape(PxBoxGeometry(0.5f, 0.5f, 0.5f), *mMaterial, true);
		
		// Attach the shape to the actor
		if (hasRigidbody)
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	PxShape* PhysicHandler::CreateSphereCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With SphereGeometrie
		PxShape* s = mSDK->createShape(PxSphereGeometry(1.f), *mMaterial, true);
		
		// Attach the shape to the actor
		if (hasRigidbody)
		{
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		}
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	PxShape* PhysicHandler::CreateCapsuleCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		// Take ActorPhysic Link to the GameComponent
		IPhysicType* physicType = GetObject(object, hasRigidbody);

		// Create Shape With CapsuleGeometrie
		PxShape* s = mSDK->createShape(PxCapsuleGeometry(1.f, 1.f), *mMaterial, true);
		
		// Attach the shape to the actor
		if (hasRigidbody)
			physicType->GetObjectDynamic()->GetRigid()->attachShape(*s);
		else
			physicType->GetObjectStatic()->GetRigid()->attachShape(*s);

		return s;
	}

	void PhysicHandler::InitSystem()
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

		// Create a collection
		collection = PxCreateCollection();            

		InitScene();

		// Init Default Material
		mMaterial = mSDK->createMaterial(0.5f, 0.5f, 0.1f);
		if (!mMaterial)
			std::cerr << "createMaterial failed!";

		// Link PVD
		PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
	}

	void PhysicHandler::InitScene()
	{
		PxSceneDesc sceneDesc(mSDK->getTolerancesScale());
		sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

		sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVE_ACTORS;
		sceneDesc.flags |= PxSceneFlag::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS;

		//physx::PxCudaContextManagerDesc cudaContextManagerDesc;
		//sceneDesc.cudaContextManager = PxCreateCudaContextManager(*pDefaultFundation, cudaContextManagerDesc);

		sceneDesc.filterShader = &contactReportFilterShader;
		sceneDesc.simulationEventCallback = new SimulationCallback();
		//sceneDesc.broadPhaseType = physx::PxBroadPhaseType::;

		mCpuDispatcher = PxDefaultCpuDispatcherCreate(4);
		if (!mCpuDispatcher)
			std::cerr << "PxDefaultCpuDispatcherCreate failed!";
		sceneDesc.cpuDispatcher = mCpuDispatcher;

		mScene = mSDK->createScene(sceneDesc);
		if (!mScene)
			std::cerr << "createScene failed!";
	}

	void PhysicHandler::ReleaseSystem()
	{
		collection->release();
		mCooking->release();
		PxCloseExtensions();
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

	void PhysicHandler::Destroy()
	{
		delete _instance;
	}

	void PhysicHandler::UpdateSystem(double deltaTime)
	{
		/*PhysicStatic* tmp = _physObject.at(go[1])->GetObjectStatic();

		PxShape* shape;
		PxBoxGeometry overlapGeometrie;
		tmp->GetRigid()->getShapes(&shape, sizeof(8) * 1);
		shape->getBoxGeometry(overlapGeometrie);*/

		/* Chose a abstraire */

		// ========= Ray cast ==============
		/*PxVec3 origin = PxVec3(0, 0, 0);                 // Origin du ray cast
		PxVec3 unitDir = PxVec3(0, -1, 0);                // direction du ray cast
		PxReal maxDistance = 100;            // distance max du ray cast
		PxRaycastBuffer hitRaycast;                 // resultat du ray cast apres test

		bool status1 = mScene->raycast(origin, unitDir, maxDistance, hitRaycast);
		if (status1 && hitRaycast.hasBlock)
			std::cout << hitRaycast.block.actor << std::endl; // closest actor hit

		PxVec3 unitDir2 = PxVec3(0, 1, 0);                // direction du ray cast

		status1 = mScene->raycast(origin, unitDir2, maxDistance, hitRaycast);
		if (status1 && hitRaycast.hasBlock)
			std::cout << hitRaycast.block.actor << std::endl; // closest actor hit

		PxVec3 unitDir3 = PxVec3(-1, 1, 0);                // direction du ray cast

		status1 = mScene->raycast(origin, unitDir2, maxDistance, hitRaycast);
		if (status1 && hitRaycast.hasBlock)
			std::cout << hitRaycast.block.actor->getName() << std::endl; // closest actor hit*/

			// ========= Overlap with the closest actor in result (Block) ============
			// PxTransform ET PxGeometrie de base ne fonctionne pas, donne une erreur comme quoi c'est invalide
			/*PxTransform shapePosition = tmp->GetRigid()->getGlobalPose();    // Need position of PhysX Actor
			//std::cout << << std::endl;

			PxQueryFilterData fd;
			fd.flags |= PxQueryFlag::eDYNAMIC; // note the OR with the default value
			fd.flags.set(PxQueryFlag::eDYNAMIC);

			// possibilité de que dynamic et non bloquant dans l'enum.

			//PxOverlapHit
			PxOverlapHit* temp;


			bool status2 = mScene->overlap(overlapGeometrie, shapePosition, temp, fd);
			//std::cout << "avant test" << std::endl;
			if (status2 )
			{
				if (hitOverlap.hasBlock)
					std::cout << hitOverlap.block.actor->getName() << std::endl; // closest actor who overlap
			}*/

			/*
				Multiple block pas fait
				possibilité de rajouter des filtres dans les overlap et raycast (genre que les dynamic ou que les static)
			*/

			// =====================================================

		/*mAccumulator += (physx::PxReal)deltaTime;
		if (mAccumulator < mStepSize)
			return;

		mAccumulator -= 0.0f;*/

		mScene->simulate(PxReal(deltaTime));

		mScene->fetchResults(true);
	}

	void PhysicHandler::UpdatePhysicActor(bool isPlaying)
	{
		if (isPlaying)
		{
			UpdatePlayingActor();
		}
		else
		{		
			UpdateEditorActor();
		}
	}

	void PhysicHandler::UpdatePlayingActor()
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
					//transformPhysic.q = transformPhysic.q.getConjugate() * transformPhysic.q.getNormalized();
					transform->SetPosition(Math::QXvec3(transformPhysic.p.x, transformPhysic.p.y, transformPhysic.p.z));
					transform->SetRotation(Math::QXquaternion(transformPhysic.q.w, transformPhysic.q.x, transformPhysic.q.y, transformPhysic.q.z));
				}
			}
		}
	}

	void PhysicHandler::UpdateEditorActor()
	{
		for (auto it = _physObject.begin(); it != _physObject.end(); ++it)
		{
			if (it->second && it->first)
			{
				// Set RigidBody Transform On GameOject Transform
				Math::QXvec3 pos = ((Core::DataStructure::GameObject3D*)it->first)->GetTransform()->GetPosition();
				Math::QXquaternion quat = ((Core::DataStructure::GameObject3D*)it->first)->GetTransform()->GetRotation();
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
	}

	void PhysicHandler::Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax, Physic::Raycast& ownRaycast)
	{
		PxRaycastBuffer hitRaycast;                 // resultat du ray cast apres test

		ownRaycast.status = mScene->raycast(PxVec3(origin.x, origin.y, origin.z), PxVec3(unitDir.x, unitDir.y, unitDir.z), distMax, hitRaycast);
		if (ownRaycast.status && hitRaycast.hasBlock)
		{
			ownRaycast.normalClosestBlock = Math::QXvec3(hitRaycast.block.normal.x, hitRaycast.block.normal.y, hitRaycast.block.normal.z);
			ownRaycast.positionClosestBlock = Math::QXvec3(hitRaycast.block.position.x, hitRaycast.block.position.y, hitRaycast.block.position.z);
			ownRaycast.distanceClosestBlock = hitRaycast.block.distance;
			ownRaycast.actorClosestBlock = (Core::DataStructure::GameObject3D*)hitRaycast.block.actor->userData;
		}
	}

	void PhysicHandler::CleanScene()
	{
		int numActorsDynamic = mScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);
		PxActor** actorsDyna = (PxActor**)malloc(sizeof(PxActor*) * numActorsDynamic);
		mScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, actorsDyna, numActorsDynamic);

		mScene->removeActors(actorsDyna, numActorsDynamic);

		int numActorsStatic = mScene->getNbActors(PxActorTypeFlag::eRIGID_STATIC);
		PxActor** actorsStat = (PxActor**)malloc(sizeof(PxActor*) * numActorsStatic);
		mScene->getActors(PxActorTypeFlag::eRIGID_STATIC, actorsStat, numActorsStatic);

		mScene->removeActors(actorsStat, numActorsStatic);
	}

#pragma region FlagSetters
	void PhysicHandler::SetFlagAdaptiveForce(bool b)
	{
		sceneFlag.adaptiveForce = b;
		mScene->setFlag(PxSceneFlag::eADAPTIVE_FORCE, b);
	}

	void PhysicHandler::SetFlagDisableCCDResweep(bool b)
	{
		sceneFlag.disableCCDResweep = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CCD_RESWEEP, b);
	}

	void PhysicHandler::SetFlagDisableContactCache(bool b)
	{
		sceneFlag.disableContactCache = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CONTACT_CACHE, b);
	}

	void PhysicHandler::SetFlagDisableContactReport(bool b)
	{
		sceneFlag.disableContactReportResize = b;
		mScene->setFlag(PxSceneFlag::eDISABLE_CONTACT_REPORT_BUFFER_RESIZE, b);
	}

	void PhysicHandler::SetFlagActiveActors(bool b)
	{
		sceneFlag.activeActors = b;
		mScene->setFlag(PxSceneFlag::eENABLE_ACTIVE_ACTORS, b);
	}

	void PhysicHandler::SetFlagAveragePoint(bool b)
	{
		sceneFlag.averagePoint = b;
		mScene->setFlag(PxSceneFlag::eENABLE_AVERAGE_POINT, b);
	}

	void PhysicHandler::SetFlagCCD(bool b)
	{
		sceneFlag.ccd = b;
		mScene->setFlag(PxSceneFlag::eENABLE_CCD, b);
	}

	void PhysicHandler::SetFlagEnhancedDeterminism(bool b)
	{
		sceneFlag.enhancedDeterminism = b;
		mScene->setFlag(PxSceneFlag::eENABLE_ENHANCED_DETERMINISM, b);
	}

	void PhysicHandler::SetFlagFrictionEveryIt(bool b)
	{
		sceneFlag.frictionEveryIteration = b;
		mScene->setFlag(PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION, b);
	}

	void PhysicHandler::SetFlagGPUDynamics(bool b)
	{
		sceneFlag.gpuDynamics = b;
		mScene->setFlag(PxSceneFlag::eENABLE_GPU_DYNAMICS, b);
	}

	void PhysicHandler::SetFlagPCM(bool b)
	{
		sceneFlag.pcm = b;
		mScene->setFlag(PxSceneFlag::eENABLE_PCM, b);
	}

	void PhysicHandler::SetFlagStabilization(bool b)
	{
		sceneFlag.stabilization = b;
		mScene->setFlag(PxSceneFlag::eENABLE_STABILIZATION, b);
	}

	void PhysicHandler::SetFlagExcludeKineActiverActors(bool b)
	{
		sceneFlag.excludeKineActiveActors = b;
		mScene->setFlag(PxSceneFlag::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS, b);
	}

	void PhysicHandler::SetFlagMutable(bool b)
	{
		sceneFlag.mutableFlags = b;
		mScene->setFlag(PxSceneFlag::eMUTABLE_FLAGS, b);
	}

	void PhysicHandler::SetFlagRequireRWLock(bool b)
	{
		sceneFlag.requireRWLock = b;
		mScene->setFlag(PxSceneFlag::eREQUIRE_RW_LOCK, b);
	}
#pragma endregion
}