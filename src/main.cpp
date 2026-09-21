#include "../include/ScriptHookV/main.h"
#include "Superman/Superman.h"

void ScriptMain()
{
    Superman::Initialize();

    while (true)
    {
        Superman::Update();
        WAIT(0);
    }
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        scriptRegister(hModule, ScriptMain);
        break;

    case DLL_PROCESS_DETACH:
        scriptUnregister(hModule);
        break;
    }

    return TRUE;
}
