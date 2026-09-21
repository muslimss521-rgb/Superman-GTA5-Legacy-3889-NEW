#pragma once

#include "../../include/ScriptHookV/script.h"

namespace Flight
{
    void Initialize();
    void Enable();
    void Disable();
    void Update(Ped playerPed);

    bool IsEnabled();
}
