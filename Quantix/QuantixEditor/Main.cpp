// RendererTest.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <Editor.h>
#include <Core/Profiler/Profiler.h>

int WinMain()
{
	try
	{
		Editor							editor(1920, 900);
		editor.Init();
		editor.Update();
	}
	catch (const std::exception& e)
	{
		std::cout << "Crash : " << std::endl;
		std::cout << e.what() << std::endl;
	}

	Quantix::Core::Debugger::Logger::GetInstance()->CloseLogger();
	
	return 0;
}
