#include <windows.h>
#include "../include/ScriptHookV/main.h"
#include "Superman.h"

static Superman g_superman;

void ScriptMain() {
    while (true) {
        g_superman.Update();
        WAIT(0);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        scriptRegister(hModule, ScriptMain);
    } else if (reason == DLL_PROCESS_DETACH) {
        scriptUnregister(hModule);
    }
    return TRUE;
}
