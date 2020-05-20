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
	.property("numCubeInWidth", &Quantix::Core::Components::DeformableMesh::GetNumWidth, &Quantix::Core::Components::DeformableMesh::SetNumWidth)
	.property("numCubeInHeight", &Quantix::Core::Components::DeformableMesh::numCubeInHeight)
	.property("numCubeInDepth", &Quantix::Core::Components::DeformableMesh::numCubeInDepth)
	.method("Generate", &Quantix::Core::Components::DeformableMesh::Generate);
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

		const int tmp = numCubeInHeight;

		//Core::DataStructure::GameObject3D**** gameobjects = nullptr;
		//std::vector<std::vector<std::vector<Core::DataStructure::GameObject3D*>>> gameobjects;
		Core::DataStructure::GameObject3D* gameobjects[4][4][4];
		for (QXint i = 0; i < 4; i++)
		{
			//gameobjects.push_back(new Core::DataStructure::GameObject3D());
			for (QXint j = 0; j < 4; j++)
			{
				for (QXint k = 0; k < 4; k++)
				{
					gameobjects[i][j][k] = new Core::DataStructure::GameObject3D();
				}
			}
		}

		for (QXint i = 0; i < 4; i++)
		{
			for (QXint j = 0; j < 4; j++)
			{
				for (QXint k = 0; k < 4; k++)
				{
					gameobjects[i][j][k] = scene->AddGameObject(QXstring("Cube" + std::to_string(i) + std::to_string(j) + std::to_string(k)), _object);
					gameobjects[i][j][k]->SetLocalPosition(Math::QXvec3(i * cubeSize.x, j * cubeSize.y, k * cubeSize.z));
					
					AddComponent(gameobjects[i][j][k]);

					if (i == 0 && j == 0 && k == 0)
						continue;
					else
					{
						if (i != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i-1][j][k], Math::QXvec3(cubeSize.x * 0.5, 0, 0));
						if (j != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j - 1][k], Math::QXvec3(0, cubeSize.y * 0.5, 0));
						if (k != 0)
							handler->CreateJoint(gameobjects[i][j][k], gameobjects[i][j][k - 1], Math::QXvec3(0, 0, cubeSize.z * 0.5));
					}
				}
			}
		}

		/*for (int i = 0; i < numCubeInWidth; i++)
		{
			for (int j = 0; j < numCubeInWidth; j++)
			{
				for (int k = 0; k < numCubeInWidth; k++)
					delete gameobjects[i][j][k];
			}
		}*/
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
		rigid->SetMass(0.001);
		object->AddComponent(rigid);

		// Add Cubecollider
		Core::Components::CubeCollider* collider = new CubeCollider();
		collider->Init(object);
		object->AddComponent(collider);

		// Add Joint
	}
}
