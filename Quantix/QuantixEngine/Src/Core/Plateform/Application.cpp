#include "Core/Platform/Application.h"

#include <stb_image.h>

#include "Resources/ShaderProgram.h"
#include "Core/Components/Mesh.h"
#include "Physic/PhysicHandler.h"
#include "Core/Threading/TaskSystem.hpp"

namespace Quantix::Core::Platform
{
	Application::Application(QXuint width, QXuint height) :
		info{ width, height },
		renderer { info, manager },
		sceneManager {},
		scene {new Resources::Scene()}
	{
		stbi_set_flip_vertically_on_load(true);
		Physic::PhysicHandler::GetInstance()->InitSystem();
		scene->Init(manager);
	}

	Application::~Application()
	{
		Physic::PhysicHandler::GetInstance()->ReleaseSystem();
		Physic::PhysicHandler::GetInstance()->Destroy();
		Threading::TaskSystem::Destroy();
		delete scene;
	}

	void Application::Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
		std::vector<Components::Light>& lights, bool isPlaying)
	{
		static QXbool firstPlay = true;
		if (firstPlay && isPlaying)
		{
			scene->Start();
			firstPlay = false;
		}
		Threading::TaskSystem::GetInstance()->Update();
		manager.UpdateResourcesState();

		scene->Update(meshes, colliders, lights, info);

		// Updatye Physic
		if (isPlaying)
			Physic::PhysicHandler::GetInstance()->UpdateSystem(info.deltaTime);
		else
			firstPlay = true;
		Physic::PhysicHandler::GetInstance()->UpdatePhysicActor(isPlaying);
	}
}
