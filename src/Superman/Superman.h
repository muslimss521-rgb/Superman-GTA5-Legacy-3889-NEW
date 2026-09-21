#pragma once

#include "../../include/ScriptHookV/script.h"

namespace Superman
{
    void Initialize();
    void Update();

    bool IsEnabled();
    void SetEnabled(bool enabled);

    Player GetPlayer();
    Ped GetPlayerPed();
}
