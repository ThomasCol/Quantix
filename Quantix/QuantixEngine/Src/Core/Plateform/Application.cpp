#include "Core/Platform/Application.h"

#include "Resources/ShaderProgram.h"
#include "Core/Components/Mesh.h"

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
	}

	void Application::Run()
	{
		/*Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Run");
		Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Mesh");
		Core::Components::Mesh* mesh = manager.CreateMesh("../QuantixEngine/Media/Mesh/fantasy_game_inn.obj");
		mesh->GetMaterial()->SetMainTexture(manager.CreateTexture("../QuantixEngine/Media/Textures/fantasy_game_inn_diffuse.png"));
		Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Mesh");

		std::vector<Core::Components::Mesh*> meshes;
		meshes.push_back(mesh);

		Core::Components::Light* light = new Core::Components::Light;
		light->ambient = { 0.5f, 0.5f, 0.5f };
		light->diffuse = { 0.7f, 0.7f, 0.7f };
		light->specular = { 1.0f, 1.0f, 1.0f };
		light->position = { 0.0f, 0.0f, 10.f };
		light->direction = { 0.0f, 0.0f, -1.f };
		light->constant = 0.5f;
		light->linear = 0.09f;
		light->quadratic = 0.032f;
		light->cutOff = cos(0.70f);
		light->outerCutOff = cos(0.76f);
		light->type = Core::Components::ELightType::SPOT;

		Core::Components::Light* light2 = new Core::Components::Light;
		light2->ambient = { 0.5f, 0.5f, 0.5f };
		light2->diffuse = { 0.7f, 0.7f, 0.7f };
		light2->specular = { 1.0f, 1.0f, 1.0f };
		light2->position = { 0.0f, 12.f, 5.f };
		light2->direction = { 0.0f, 0.0f, -1.f };
		light2->constant = 0.5f;
		light2->linear = 0.09f;
		light2->quadratic = 0.032f;
		light2->cutOff = cos(0.70f);
		light2->outerCutOff = cos(0.76f);
		light2->type = Core::Components::ELightType::POINT;

		std::vector<Core::Components::Light*> lights;
		lights.push_back(light);
		lights.push_back(light2);
		
		while (!window.ShouldClose() && !GetKeyState(VK_SPACE))
		{
			Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Draw");
			renderer.Draw(meshes, lights, info); 
			Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Draw");

			Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Refresh");
			window.Refresh(info);
			Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Refresh");
			Quantix::Core::Profiling::Profiler::GetInstance()->FrameCounter();
		}*/

		//Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Run");
		
	/*	for (int i = 0; i < meshes.size(); ++i)
			delete meshes[i];
		for (int i = 0; i < meshes.size(); ++i)
			delete lights[i];*/
	}
}
