#include "Physic/PhysicHandler.h"
#include "Physic/PhysicStatic.h"
#include "Physic/PhysicDynamic.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure/GameObject3D.h"

#include <vector>

#define PVD_HOST "127.0.0.1"	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.


using namespace physx;
namespace Quantix::Physic
{
	PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)

	{
		if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		// generate contacts for all that were not filtered above
		std::cout << "Not Trigger" << std::endl;
		pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
		//pairFlags |= physx::PxPairFlag::eDETECT_DISCRETE_CONTACT;
		//pairFlags |= physx::PxPairFlag::eDETECT_CCD_CONTACT;

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

	void		PhysicHandler::Print(std::vector<Core::DataStructure::GameComponent*> go)
	{
		for (size_t i = 0; i < go.size(); i++)
		{
			std::cout << "Object" << i << " ";
			_physObject[go[i]]->print();
		}
	}

	IPhysicType* PhysicHandler::GetObject(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		auto it = _physObject.find(object);
		if (!hasRigidbody)
		{
			if (it == _physObject.end())
			{
				PhysicStatic* tmp = new PhysicStatic(mSDK);
				mScene->addActor(*tmp->GetRigid());
				tmp->GetRigid()->userData = dynamic_cast<Core::DataStructure::GameObject3D*>(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::DYNAMIC))
			{
				// creer a partir dun dyna plus tard
				PhysicStatic* tmp = new PhysicStatic(mSDK, dynamic_cast<PhysicDynamic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
		else
		{
			if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::STATIC))
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, dynamic_cast<PhysicStatic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK);
				mScene->addActor(*tmp->GetRigid());
				tmp->GetRigid()->userData = dynamic_cast<Core::DataStructure::GameObject3D*>(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
	}
	//ADD ENUM + Constructor type of shape
	IPhysicType* PhysicHandler::CreateCubeCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		auto it = _physObject.find(object);
		if (!hasRigidbody)
		{
			if (it == _physObject.end())
			{
				PhysicStatic* tmp = new PhysicStatic(mSDK, EPhysXShape::CUBE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::DYNAMIC))
			{
				// creer a partir dun dyna plus tard
				PhysicStatic* tmp = new PhysicStatic(mSDK, dynamic_cast<PhysicDynamic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
		else
		{
			if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::STATIC))
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, dynamic_cast<PhysicStatic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, EPhysXShape::CUBE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
	}

	IPhysicType* PhysicHandler::CreateSphereCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		auto it = _physObject.find(object);
		if (!hasRigidbody)
		{
			if (it == _physObject.end())
			{
				PhysicStatic* tmp = new PhysicStatic(mSDK, EPhysXShape::SPHERE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::DYNAMIC))
			{
				// creer a partir dun dyna plus tard
				PhysicStatic* tmp = new PhysicStatic(mSDK, dynamic_cast<PhysicDynamic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
		else
		{
			if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::STATIC))
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, dynamic_cast<PhysicStatic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, EPhysXShape::SPHERE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
	}

	IPhysicType* PhysicHandler::CreateCapsuleCollider(Core::DataStructure::GameComponent* object, bool hasRigidbody)
	{
		auto it = _physObject.find(object);
		if (!hasRigidbody)
		{
			if (it == _physObject.end())
			{
				PhysicStatic* tmp = new PhysicStatic(mSDK, EPhysXShape::CAPSULE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::DYNAMIC))
			{
				// creer a partir dun dyna plus tard
				PhysicStatic* tmp = new PhysicStatic(mSDK, dynamic_cast<PhysicDynamic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectDynamic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
		else
		{
			if (it != _physObject.end()
				&& (it->second->GetType() == ETypePhysic::STATIC))
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, dynamic_cast<PhysicStatic*>(_physObject[object]));
				mScene->removeActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				mScene->addActor(*_physObject[object]->GetObjectStatic()->GetRigid());
				_physObject.erase(object);
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}
			else
			{
				PhysicDynamic* tmp = new PhysicDynamic(mSDK, EPhysXShape::CAPSULE);
				mScene->addActor(*tmp->GetRigid());
				_physObject.insert(std::make_pair((Core::DataStructure::GameComponent*)object, tmp));
			}

			return _physObject[object];
		}
	}

	void PhysicHandler::InitSystem()
	{
		pDefaultFundation = PxCreateFoundation(PX_PHYSICS_VERSION, pDefaultAllocatorCallback, pDefaultErrorCallback);

		if (!pDefaultFundation)
			std::cerr << "PxCreateFoundation failed!" << std::endl;

		pPvd = PxCreatePvd(*pDefaultFundation);
		PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		pPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

		mSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *pDefaultFundation, PxTolerancesScale(), recordMemoryAllocations, pPvd);
		if (!mSDK)
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		if (!PxInitExtensions(*mSDK, pPvd))
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		mCooking = PxCreateCooking(PX_PHYSICS_VERSION, mSDK->getFoundation(), PxCookingParams(mSDK->getTolerancesScale()));
		if (!mCooking)
		{
			std::cerr << "An error has happened." << std::endl;
			exit(1);
		}

		collection = PxCreateCollection();            // Create a collection

		//pSimulationEvent = new MySimulationCallback();

		InitScene();

		mMaterial = mSDK->createMaterial(0.5f, 0.5f, 0.1f);
		if (!mMaterial)
			std::cerr << "createMaterial failed!";

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

		/*sceneDesc.staticKineFilteringMode = PxPairFilteringMode::eKEEP;
		sceneDesc.kineKineFilteringMode = PxPairFilteringMode::eKEEP;
		sceneDesc.flags = PxSceneFlag::eENABLE_CCD;*/

		//sceneDesc.simulationEventCallback = new MySimulationCallback();

		sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVE_ACTORS;
		sceneDesc.flags |= PxSceneFlag::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS;
		//sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
		//sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;
		//sceneDesc.flags |= PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION;

		//physx::PxCudaContextManagerDesc cudaContextManagerDesc;
		//sceneDesc.cudaContextManager = PxCreateCudaContextManager(*pDefaultFundation, cudaContextManagerDesc);

		sceneDesc.filterShader = &contactReportFilterShader;
		//sceneDesc.simulationEventCallback = new MySimulationCallback();
		sceneDesc.broadPhaseType = physx::PxBroadPhaseType::eGPU;

		mCpuDispatcher = PxDefaultCpuDispatcherCreate(4);
		if (!mCpuDispatcher)
			std::cerr << "PxDefaultCpuDispatcherCreate failed!";
		sceneDesc.cpuDispatcher = mCpuDispatcher;

		//sceneDesc.simulationEventCallback = new MySimulationCallback();
		mScene = mSDK->createScene(sceneDesc);
		if (!mScene)
			std::cerr << "createScene failed!";
	}

	void PhysicHandler::ReleaseSystem()
	{
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

	void PhysicHandler::UpdateSystem(std::vector<Core::DataStructure::GameComponent*> go, double deltaTime)
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

		mAccumulator += deltaTime;
		if (mAccumulator < mStepSize)
			return;

		mAccumulator -= 0.0f;
		mScene->simulate(mStepSize);

		mScene->fetchResults(true);
	}

	void PhysicHandler::UpdatePhysicActor()
	{
		PxU32 nbActors;
		PxActor** listActor = mScene->getActiveActors(nbActors);

		for (PxU32 index = 0; index < nbActors; index++)
		{
			PxRigidDynamic* currentActor = (PxRigidDynamic*)listActor[index];
			if (currentActor)
			{
				PxTransform transformPhysic = currentActor->getGlobalPose();
				Transform3D* transform = ((Core::DataStructure::GameObject3D*)currentActor->userData)->GetTransform();

				//transform->SetPosition(Math::QXvec3(transformPhysic.p.x, transformPhysic.p.y, transformPhysic.p.z));
				//transform->SetRotation(Math::QXquaternion(transformPhysic.q.w, transformPhysic.q.x, transformPhysic.q.y, transformPhysic.q.z));
			}
		}
	}
}