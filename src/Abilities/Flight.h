#pragma once

#include "../../include/ScriptHookV/main.h"
#include "../../include/ScriptHookV/natives.h"
#include "../../include/ScriptHookV/types.h"

namespace Flight
{
    void Initialize();
    void Enable();
    void Disable();
    void Update(Ped playerPed);

    bool IsEnabled();
}
