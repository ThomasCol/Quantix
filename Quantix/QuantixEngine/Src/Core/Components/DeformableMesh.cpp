#include "Core/Components/DeformableMesh.h"
#include "Core/Physic/PhysicHandler.h"
#include "Core/Components/Rigidbody.h"
#include "Core/Components/CubeCollider.h"


RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::DeformableMesh>("DeformableMesh")
	.constructor<>()
	.constructor<const Quantix::Core::Components::DeformableMesh&>()
	.constructor<Quantix::Core::Components::DeformableMesh&&>()
	.property("cubeSize", &Quantix::Core::Components::DeformableMesh::cubeSize)
	.property("numCubeInWidth", &Quantix::Core::Components::DeformableMesh::GetNumWidth, &Quantix::Core::Components::DeformableMesh::SetNumWidth)
	.property("numCubeInHeight", &Quantix::Core::Components::DeformableMesh::numCubeInHeight)
	.property("numCubeInDepth", &Quantix::Core::Components::DeformableMesh::numCubeInDepth)
	.property("BreakForce", &Quantix::Core::Components::DeformableMesh::GetBreakForce, &Quantix::Core::Components::DeformableMesh::SetBreakForce)
		(rttr::metadata("Description", "Joint"))
	.property("BreakTorque Z", &Quantix::Core::Components::DeformableMesh::GetBreakTorque, &Quantix::Core::Components::DeformableMesh::SetBreakTorque)
		(rttr::metadata("Description", "End"))
	.method("Generate", &Quantix::Core::Components::DeformableMesh::Generate);
}
namespace Quantix::Core::Components
{
	DeformableMesh::~DeformableMesh()
	{
		Destroy();
	}

	DeformableMesh* DeformableMesh::Copy() const
	{
		return new DeformableMesh(*this);
	}

	void DeformableMesh::Init(DataStructure::GameComponent* par)
	{
		_object = par;
		_isDestroyed = false;
		_isEnable = true;
	}

	void DeformableMesh::Generate(Resources::Scene* scene, Core::DataStructure::ResourcesManager* manager, QXbool fromLoad)
	{
		Core::DataStructure::GameObject3D* gameobject = (Core::DataStructure::GameObject3D*)_object;

		if (gameobjects && gameobjects[0][0][1])
		{
			for (QXuint i = 0; i < numCubeInWidth; i++)
			{
				for (QXuint j = 0; j < numCubeInHeight; j++)
				{
					for (QXuint k = 0; k < numCubeInDepth; k++)
					{
						std::list<Physic::Transform3D*> list = gameobject->GetTransform()->GetParent()->GetChilds();
						for (auto it = list.begin(); it != list.end(); ++it)
						{
							if ((*it)->GetObject() == gameobjects[i][j][k])
							{
								// Destroy all components (except DeformableMesh Comp)
								for (QXint index = 0; index < (*it)->GetObject()->GetComponents().size(); index++)
								{
									if ((*it)->GetObject()->GetComponents()[index]->get_type().get_name().to_string() != "DeformableMesh")
									{
										(*it)->GetObject()->RemoveComponent((*it)->GetObject()->GetComponents()[index]);
										index--;
									}
								}
							}
						}
					}
				}
			}
			MoveCube(scene, manager);
			return;
		}

		// Malloc
		gameobjects = (Core::DataStructure::GameObject3D****)malloc(sizeof(Core::DataStructure::GameObject3D*) * numCubeInWidth);
		for (QXuint i = 0; i < numCubeInWidth; i++)
		{
			gameobjects[i] = (Core::DataStructure::GameObject3D***)malloc(sizeof(Core::DataStructure::GameObject3D*) * numCubeInHeight);
			for (QXuint j = 0; j < numCubeInHeight; j++)
			{
				gameobjects[i][j] = (Core::DataStructure::GameObject3D**)malloc(sizeof(Core::DataStructure::GameObject3D*) * numCubeInDepth);
				for (QXuint k = 0; k < numCubeInHeight; k++)
				{
					gameobjects[i][j][k] = nullptr;
				}
			}
		}

		CreateCube(scene, manager, fromLoad);
	}

	void DeformableMesh::MoveCube(Resources::Scene* scene, Core::DataStructure::ResourcesManager* manager) noexcept
	{
		Physic::PhysicHandler* handler = Physic::PhysicHandler::GetInstance();
		for (QXuint i = 0; i < numCubeInWidth; i++)
		{
			for (QXuint j = 0; j < numCubeInHeight; j++)
			{
				for (QXuint k = 0; k < numCubeInDepth; k++)
				{
					if (i == 0 && j == 0 && k == 0)
					{
						gameobjects[i][j][k] = (Core::DataStructure::GameObject3D*)_object;

						gameobjects[i][j][k]->SetLocalScale(cubeSize);
						// Add Comp
						AddComponent(gameobjects[i][j][k], manager);
					}
					else
					{
						gameobjects[i][j][k]->SetLocalPosition(Math::QXvec3(i * (cubeSize.x + 0.01f), j * (cubeSize.y + 0.01f), k * (cubeSize.z + 0.01f)) + gameobjects[0][0][0]->GetLocalPosition());

						gameobjects[i][j][k]->SetLocalScale(cubeSize);
						// Add Comp
						AddComponent(gameobjects[i][j][k], manager);

						// Add Joint
						if (i != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i - 1][j][k], Math::QXvec3(cubeSize.x * 0.5f, 0, 0), joint);
						if (j != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j - 1][k], Math::QXvec3(0, cubeSize.y * 0.5f, 0), joint);
						if (k != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j][k - 1], Math::QXvec3(0, 0, cubeSize.z * 0.5f), joint);
					}
				}
			}
		}
	}

	void DeformableMesh::CreateCube(Resources::Scene* scene, Core::DataStructure::ResourcesManager* manager, QXbool fromLoad) noexcept
	{
		Physic::PhysicHandler* handler = Physic::PhysicHandler::GetInstance();
		Core::DataStructure::GameObject3D* gameobject = (Core::DataStructure::GameObject3D*)_object;
		for (QXuint i = 0; i < numCubeInWidth; i++)
		{
			for (QXuint j = 0; j < numCubeInHeight; j++)
			{
				for (QXuint k = 0; k < numCubeInDepth; k++)
				{

					if (i == 0 && j == 0 && k == 0)
					{
						gameobjects[i][j][k] = (Core::DataStructure::GameObject3D*)_object;

						// Add Comp
						gameobjects[i][j][k]->SetLocalScale(cubeSize);
						if (!fromLoad)
							AddComponent(gameobjects[i][j][k], manager);
					}
					else
					{
						gameobjects[i][j][k] = scene->AddGameObject(QXstring("Cube " + std::to_string(i) + std::to_string(j) + std::to_string(k)), gameobject->GetTransform()->GetParent()->GetObject());
						gameobjects[i][j][k]->SetLocalPosition(Math::QXvec3(i * (cubeSize.x + 0.01f), j * (cubeSize.y + 0.01f), k * (cubeSize.z + 0.01f)) + gameobjects[0][0][0]->GetLocalPosition());
						gameobjects[i][j][k]->SetLocalScale(cubeSize);
						// Add Comp
						AddComponent(gameobjects[i][j][k], manager);

						// Add Joint
						if (i != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i - 1][j][k], Math::QXvec3(cubeSize.x * 0.5f, 0, 0), joint);
						if (j != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j - 1][k], Math::QXvec3(0, cubeSize.y * 0.5f, 0), joint);
						if (k != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j][k - 1], Math::QXvec3(0, 0, cubeSize.z * 0.5f), joint);
					}
				}
			}
		}
	}

	void DeformableMesh::AddComponent(DataStructure::GameObject3D* object, Core::DataStructure::ResourcesManager* manager) noexcept
	{
		// Add Mesh
		Core::Components::Mesh* mesh = object->AddComponent<Mesh>();
		mesh->Init(object);
		manager->CreateMesh(mesh, "media/Mesh/cube.obj");
		mesh->SetMaterial(manager->CreateMaterial(PATHMATERIAL));

		// Add Rigid
		object->AddComponent<Rigidbody>()->Init(object);

		// Add Cubecollider
		Core::Components::CubeCollider* collider = object->AddComponent<CubeCollider>();
		collider->Init(object);
		collider->SetHalfExtents(cubeSize/2);

		object->SetLayer(Core::DataStructure::Layer::DESTRUCTIBLEMESH);
	}

	void DeformableMesh::Destroy() noexcept
	{
		if (gameobjects)
		{
			for (QXuint i = 0; i < numCubeInWidth; i++)
			{
				for (QXuint j = 0; j < numCubeInHeight; j++)
				{
					for (QXuint k = 0; k < numCubeInHeight; k++)
					{
						gameobjects[i][j][k] = nullptr;
					}
					free(gameobjects[i][j]);
				}
				free(gameobjects[i]);
			}
			free(gameobjects);
		}
	}
}
