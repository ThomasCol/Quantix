#include "Core/Platform/Application.h"

#include <stb_image.h>

#include "Resources/ShaderProgram.h"
#include "Core/Components/Mesh.h"
#include "Physic/PhysicHandler.h"
#include "Core/Threading/TaskSystem.hpp"
#include "Core/SoundCore.h"

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
		std::vector<Components::Light>& lights, QXbool isPlaying)
	{
		Threading::TaskSystem::GetInstance()->Update();
		manager.UpdateResourcesState();

		if (isPlaying && _firstFrame)
		{
			scene->Start();
			_firstFrame = false;
		}
		if (!isPlaying)
		{
			if (!_firstFrame)
			{
				_firstFrame = true;
				scene->Stop();
			}
		}

		scene->Update(meshes, colliders, lights, info, isPlaying);

		// Updatye Physic
		if (isPlaying)
			Physic::PhysicHandler::GetInstance()->UpdateSystem(info.deltaTime);
		Physic::PhysicHandler::GetInstance()->UpdatePhysicActor(isPlaying);

		scene->CheckDestroy(info);
	}
}
