#include "Core/Platform/Application.h"

#include "Resources/ShaderProgram.h"
#include "Core/Components/Mesh.h"
#include "Physic/PhysicHandler.h"

namespace Quantix::Core::Platform
{
	//window{width, height},
		//renderer{ width, height, window.GetResizeCallback() },
	/*Application::Application(QXuint width, QXuint height) :
		info {width, height}
	{
	}*/

/*	Application::Application(QXstring name, QXuint width, QXuint height) :
		//window{ name, width, height },
		//renderer{ width, height, window.GetResizeCallback() },
		info{ width, height }
	{
	}*/

	Application::Application(QXuint width, QXuint height) :
		renderer { width, height, manager },
		info{ width, height },
		sceneManager {},
		scene {new Resources::Scene()}
	{
		scene->Init(manager);
		Physic::PhysicHandler::GetInstance()->InitSystem();
	}

	void Application::Update(std::vector<Core::Components::Mesh*>& meshes)
	{
		scene->Update(meshes);
	}
}
