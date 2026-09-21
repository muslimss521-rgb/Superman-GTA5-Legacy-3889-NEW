#pragma once

#include "../../include/ScriptHookV/main.h"

namespace Flight
{
    enum class State
    {
        Disabled,
        Takeoff,
        Flying,
        Boost,
        Landing
    };

    void Initialize();

    void Enable();
    void Disable();

    void Update(Ped playerPed);

    bool IsEnabled();

    State GetState();
}
