// dllmain.cpp : D�finit le point d'entr�e de l'application DLL.
#include <Windows.h>

#include <vld.h>

BOOL APIENTRY DllMain(	HMODULE hModule,
						DWORD  ul_reason_for_call,
						LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}