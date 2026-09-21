#include "Superman.h"
#include "../Abilities/Flight.h"

namespace Superman
{
    static bool g_enabled = false;

    void Initialize()
    {
        g_enabled = false;
        Flight::Initialize();
    }

    void Update()
    {
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            g_enabled = !g_enabled;

            if (g_enabled)
                Flight::Enable();
            else
                Flight::Disable();
        }

        if (!g_enabled)
            return;

        Ped playerPed = GetPlayerPed();

        if (!ENTITY::DOES_ENTITY_EXIST(playerPed))
            return;

        Flight::Update(playerPed);
    }

    bool IsEnabled()
    {
        return g_enabled;
    }

    void SetEnabled(bool enabled)
    {
        g_enabled = enabled;

        if (g_enabled)
            Flight::Enable();
        else
            Flight::Disable();
    }

    Player GetPlayer()
    {
        return PLAYER::PLAYER_ID();
    }

    Ped GetPlayerPed()
    {
        return PLAYER::PLAYER_PED_ID();
    }
}
