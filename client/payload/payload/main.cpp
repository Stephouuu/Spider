#include <string>

#include "Payload.h"

#define PAYLOAD __declspec(dllexport)

extern "C" PAYLOAD IPayload *entry(void)
{
	Payload::current = new Payload;
	Payload::current->init();
	return (Payload::current);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		Payload::Instance = hinstDLL;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}