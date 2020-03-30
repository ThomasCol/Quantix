#include "Core/Platform/Application.h"

#include "Resources/ShaderProgram.h"
#include "Core/Components/Mesh.h"

namespace Quantix::Core::Platform
{
	Application::Application(QXuint width, QXuint height):
		_window{width, height},
		_renderer {width, height, _window.GetResizeCallback()},
		info {width, height}
	{}

	void Application::Run()
	{
		Core::Components::Mesh* mesh = _manager.CreateMesh("../QuantixEngine/Media/Mesh/fantasy_game_inn.obj");

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
		light->cutOff = cos(0.70);
		light->outerCutOff = cos(0.76);
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
		light2->cutOff = cos(0.70);
		light2->outerCutOff = cos(0.76);
		light2->type = Core::Components::ELightType::POINT;

		std::vector<Core::Components::Light*> lights;
		lights.push_back(light);
		lights.push_back(light2);
		
		while (!_window.ShouldClose())
		{
			_renderer.Draw(meshes, lights, info);
			_window.Refresh(info);
		}
		
		for (int i = 0; i < meshes.size(); ++i)
			delete meshes[i];
		for (int i = 0; i < meshes.size(); ++i)
			delete lights[i];
	}
}