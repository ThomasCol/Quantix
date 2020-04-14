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
#include <Core/UserEntry/InputSystem.h>
#include <Vec3.h>

#define SPEED (0.1f)

QXuint indexPackE;
QXuint indexPackF;
QXuint indexPackB;
QXuint indexPackL;
QXuint indexPackR;

// Update platform IO from glfw
void PlatformUpdate(Editor* editor, Quantix::Core::Components::Camera* camera)
{
	// Mouse state
	{
		double MouseX, MouseY;
		glfwGetCursorPos(editor->GetWin().GetWindow(), &MouseX, &MouseY);

		editor->_mouseInput->DeltaMouseX = (float)MouseX - editor->_mouseInput->MouseX;
		editor->_mouseInput->DeltaMouseY = (float)MouseY - editor->_mouseInput->MouseY;

		editor->_mouseInput->MouseX = (float)MouseX;
		editor->_mouseInput->MouseY = (float)MouseY;

		if (editor->_mouseInput->DeltaMouseX != 0 && editor->_mouseInput->DeltaMouseY != 0)
			camera->ChangeView(MouseX, MouseY, editor->GetWin().GetWidth(), editor->GetWin().GetHeight(), editor->GetApp()->info.deltaTime);
	}

	// Screen size
	glfwGetWindowSize(editor->GetWin().GetWindow(), (QXint*)&editor->GetApp()->info.width, (QXint*)&editor->GetApp()->info.height);
}

void IsTriggered(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Quantix::Core::UserEntry::InputMgr::GetInstance()->CheckKeys(key, action);
}

void MouseButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods)
{
	MouseTest* mouseInput = (MouseTest*)glfwGetWindowUserPointer(Window);

	if (Button == GLFW_MOUSE_BUTTON_RIGHT && Action == GLFW_PRESS)
	{
		mouseInput->MouseCaptured = true;
		glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

QXuint	AddButton(Quantix::Core::UserEntry::EKey button, Quantix::Core::UserEntry::ETriggerType type)
{
	Quantix::Core::UserEntry::KeyPack pack;
	QXuint index = Quantix::Core::UserEntry::InputMgr::GetInstance()->AddPack(pack);
	Quantix::Core::UserEntry::Button key(button, type);
	Quantix::Core::UserEntry::InputMgr::GetInstance()->AddKeyToPack(index, key);

	return index;
}

void	CameraUpdate(Editor* editor, Quantix::Core::Components::Camera* camera)
{
	if (editor->_mouseInput->MouseCaptured)
	{
		PlatformUpdate(editor, camera);
		if (Quantix::Core::UserEntry::InputMgr::GetInstance()->GetPack(indexPackF).IsValid())
			camera->SetPos(camera->GetPos() + (camera->GetDir() * SPEED));
		if (Quantix::Core::UserEntry::InputMgr::GetInstance()->GetPack(indexPackB).IsValid())
			camera->SetPos(camera->GetPos() - (camera->GetDir() * SPEED));
		if (Quantix::Core::UserEntry::InputMgr::GetInstance()->GetPack(indexPackL).IsValid())
			camera->SetPos(camera->GetPos() - (camera->GetDir().Cross(camera->GetUp()) * SPEED));
		if (Quantix::Core::UserEntry::InputMgr::GetInstance()->GetPack(indexPackR).IsValid())
			camera->SetPos(camera->GetPos() + (camera->GetDir().Cross(camera->GetUp()) * SPEED));
		camera->UpdateLookAt(camera->GetPos());
	}
}

void InitScene(Editor* editor, std::vector<Quantix::Core::Components::Mesh*>& meshes, std::vector<Quantix::Core::Components::Light*>& lights)
{
	START_PROFILING("Mesh");
	Quantix::Core::Components::Mesh* mesh = editor->GetApp()->manager.CreateMesh("../QuantixEngine/Media/Mesh/fantasy_game_inn.obj");
	mesh->SetMaterialMainTexture(editor->GetApp()->manager.CreateTexture("../QuantixEngine/Media/Textures/fantasy_game_inn_diffuse.png"));
	STOP_PROFILING("Mesh");

	meshes.push_back(mesh);

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

	lights.push_back(light);
	lights.push_back(light2);
}

void InitPack()
{
	indexPackE = AddButton(Quantix::Core::UserEntry::EKey::QX_KEY_ESCAPE, Quantix::Core::UserEntry::ETriggerType::PRESSED);
	indexPackF = AddButton(Quantix::Core::UserEntry::EKey::QX_KEY_W, Quantix::Core::UserEntry::ETriggerType::DOWN);
	indexPackB = AddButton(Quantix::Core::UserEntry::EKey::QX_KEY_S, Quantix::Core::UserEntry::ETriggerType::DOWN);
	indexPackL = AddButton(Quantix::Core::UserEntry::EKey::QX_KEY_A, Quantix::Core::UserEntry::ETriggerType::DOWN);
	indexPackR = AddButton(Quantix::Core::UserEntry::EKey::QX_KEY_D, Quantix::Core::UserEntry::ETriggerType::DOWN);
}

int main()
{
	try
	{
		Editor*  editor = new Editor(1280, 920);

		glfwSetWindowUserPointer(editor->GetWin().GetWindow(), editor->_mouseInput);

		//Init Pack Input Manager
		InitPack();

		//Init Callback
		glfwSetKeyCallback(editor->GetWin().GetWindow(), IsTriggered);
		glfwSetMouseButtonCallback(editor->GetWin().GetWindow(), MouseButtonCallback);

		//Init Camera
		Quantix::Core::Components::Camera* cam = new Quantix::Core::Components::Camera({ 0, 7, 10 }, { 0, -1, -1 }, Math::QXvec3::up);

		std::vector<Quantix::Core::Components::Mesh*> meshes;
		std::vector<Quantix::Core::Components::Light*> lights;

		//Init Scene
		InitScene(editor, meshes, lights);

		//Init Editor
		editor->Init();

		while (!editor->GetWin().ShouldClose())
		{
			if (Quantix::Core::UserEntry::InputMgr::GetInstance()->GetPack(indexPackE).IsValid())
			{
				if (editor->_mouseInput->MouseCaptured)
				{
					glfwSetInputMode(editor->GetWin().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					editor->_mouseInput->MouseCaptured = false;
				}
			}

			//Editor Update
			editor->Update(editor->GetApp()->renderer.Draw(meshes, lights, editor->GetApp()->info, cam));
			START_PROFILING("Refresh");
			editor->GetWin().Refresh(editor->GetApp()->info);
			STOP_PROFILING("Refresh");
			CameraUpdate(editor, cam);
			Quantix::Core::Profiling::Profiler::GetInstance()->FrameCounter();
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
