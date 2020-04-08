// RendererTest.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <Core/Components/Camera.h>

#include <Editor.h>
#include <Profiler.h>
#include <Window.h>

int main()
{
	try
	{
		//Quantix::Core::Platform::Application app();
		//app.Run(); 
		Editor*  editor = new Editor(1280, 920);

		Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Run");
		Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Mesh");
		Quantix::Core::Components::Mesh* mesh = editor->GetApp()->manager.CreateMesh("../QuantixEngine/Media/Mesh/fantasy_game_inn.obj");
		mesh->GetMaterial()->SetMainTexture(editor->GetApp()->manager.CreateTexture("../QuantixEngine/Media/Textures/fantasy_game_inn_diffuse.png"));
		Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Mesh");

		std::vector<Quantix::Core::Components::Mesh*> meshes;
		meshes.push_back(mesh);

		Quantix::Core::Components::Camera* cam = new Quantix::Core::Components::Camera({ 0, 7, 10 }, { 0, -1, -1 }, Math::QXvec3::up);

		Quantix::Core::Components::Light* light = new Quantix::Core::Components::Light;
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
		light->type = Quantix::Core::Components::ELightType::SPOT;

		Quantix::Core::Components::Light* light2 = new Quantix::Core::Components::Light;
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
		light2->type = Quantix::Core::Components::ELightType::POINT;

		std::vector<Quantix::Core::Components::Light*> lights;
		lights.push_back(light);
		lights.push_back(light2);



		while (!editor->GetWin().ShouldClose())
		{
			Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Draw");
			
			Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Draw");
			
			Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Refresh");
			Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Refresh");
			Quantix::Core::Profiling::Profiler::GetInstance()->FrameCounter();

			//Init Editor
			if (editor->Init())
			{
				//Editor Update
				editor->Update(editor->GetApp()->renderer.Draw(meshes, lights, editor->GetApp()->info, cam));
			}
			editor->GetWin().Refresh(editor->GetApp()->info);
		}
		for (int i = 0; i < meshes.size(); ++i)
			delete meshes[i];
		for (int i = 0; i < meshes.size(); ++i)
			delete lights[i];
		delete cam;
	}
	catch (const std::exception& e)
	{
		std::cout << "Crash : " << std::endl;
		std::cout << e.what() << std::endl;
	}

	Quantix::Core::Debugger::Logger::GetInstance()->CloseLogger();
	return 0;
}
