// RendererTest.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <Core/Plateform/Application.h>

int main()
{
	try
	{
		Quantix::Core::Plateform::Application app(900, 600);
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
    
	return 0;
}