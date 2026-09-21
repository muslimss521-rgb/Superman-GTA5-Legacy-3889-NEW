#pragma once

#include "../../include/ScriptHookV/main.h"
#include "../../include/ScriptHookV/natives.h"
#include "../../include/ScriptHookV/types.h"

namespace Superman
{
    void Initialize();
    void Update();

    bool IsEnabled();
    void SetEnabled(bool enabled);

    Player GetPlayer();
    Ped GetPlayerPed();
}
