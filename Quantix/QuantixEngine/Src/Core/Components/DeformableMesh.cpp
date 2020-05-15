#include "Core/Components/DeformableMesh.h"
#include "Physic/PhysicHandler.h"
#include "Core/Components/Rigidbody.h"
#include "Core/Components/CubeCollider.h"


RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::DeformableMesh>("DeformableMesh")
	.constructor<>()
	.constructor<const Quantix::Core::Components::DeformableMesh&>()
	.constructor<Quantix::Core::Components::DeformableMesh&&>()
	.property("cubeSize", &Quantix::Core::Components::DeformableMesh::cubeSize)
	.property("numCubeInWidth", &Quantix::Core::Components::DeformableMesh::numCubeInWidth)
	.property("numCubeInHeight", &Quantix::Core::Components::DeformableMesh::numCubeInHeight)
	.property("numCubeInDepth", &Quantix::Core::Components::DeformableMesh::numCubeInDepth);
}
namespace Quantix::Core::Components
{
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

	void DeformableMesh::Generate(Resources::Scene* scene)
	{
		Physic::PhysicHandler* handler = Physic::PhysicHandler::GetInstance();
		Core::DataStructure::GameObject3D* gameobject = nullptr;

		for (QXint i = 0; i < numCubeInWidth; i++)
		{
			for (QXint j = 0; j < numCubeInHeight; j++)
			{
				for (QXint z = 0; z < numCubeInDepth; z++)
				{
					gameobject = scene->AddGameObject(QXstring("Cube" + std::to_string(i) + std::to_string(j) + std::to_string(z)), this);
					
					gameobject->SetLocalPosition(Math::QXvec3(i * numCubeInWidth, j * numCubeInHeight, z * numCubeInDepth));
					
					AddComponent(gameobject);

					if (i == 0 && j == 0 && z == 0)
						continue;
					else
					{
						//if (j != 0)

					}
				}
			}
		}
	}

	void DeformableMesh::AddComponent(DataStructure::GameObject3D* object)
	{
		// Add Mesh
		Core::Components::Mesh* mesh = new Mesh();
		mesh->Init(object);
		object->AddComponent(mesh);

		// Add Rigid
		Core::Components::Rigidbody* rigid = new Rigidbody();
		rigid->Init(object);
		object->AddComponent(rigid);

		// Add Cubecollider
		Core::Components::CubeCollider* collider = new CubeCollider();
		collider->Init(object);
		object->AddComponent(collider);

		// Add Joint
	}
}
