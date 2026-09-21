#include "Flight.h"
#include <windows.h>
#include <cmath>

namespace Flight
{
    static bool g_enabled = false;
    static float g_speed = 1.0f;

    void Initialize()
    {
        g_enabled = false;
        g_speed = 1.0f;
    }

    void Enable()
    {
        g_enabled = true;
    }

    void Disable()
    {
        g_enabled = false;

        Ped playerPed = PLAYER::PLAYER_PED_ID();

        if (ENTITY::DOES_ENTITY_EXIST(playerPed))
        {
            ENTITY::SET_ENTITY_HAS_GRAVITY(
                playerPed,
                true
            );

            PED::SET_PED_CAN_RAGDOLL(
                playerPed,
                true
            );
        }
    }

    bool IsEnabled()
    {
        return g_enabled;
    }

    void Update(Ped playerPed)
    {
        if (!g_enabled)
            return;

        if (!ENTITY::DOES_ENTITY_EXIST(playerPed))
            return;

        Vector3 pos =
            ENTITY::GET_ENTITY_COORDS(
                playerPed,
                true
            );

        Vector3 forward =
            ENTITY::GET_ENTITY_FORWARD_VECTOR(
                playerPed
            );

        // W — вперёд
        if (GetAsyncKeyState('W') & 0x8000)
        {
            pos.x += forward.x * g_speed;
            pos.y += forward.y * g_speed;
            pos.z += forward.z * g_speed;
        }

        // S — назад
        if (GetAsyncKeyState('S') & 0x8000)
        {
            pos.x -= forward.x * g_speed;
            pos.y -= forward.y * g_speed;
            pos.z -= forward.z * g_speed;
        }

        // SPACE — вверх
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            pos.z += g_speed;
        }

        // CTRL — вниз
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
        {
            pos.z -= g_speed;
        }

        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(
            playerPed,
            pos.x,
            pos.y,
            pos.z,
            false,
            false,
            false
        );

        ENTITY::SET_ENTITY_HAS_GRAVITY(
            playerPed,
            false
        );

        PED::SET_PED_CAN_RAGDOLL(
            playerPed,
            false
        );
    }
}
        // S — назад
        if (GetAsyncKeyState('S') & 0x8000)
        {
            pos.x -= forward.x * g_speed;
            pos.y -= forward.y * g_speed;
            pos.z -= forward.z * g_speed;
        }

        // SPACE — вверх
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            pos.z += g_speed;
        }

        // CTRL — вниз
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
        {
            pos.z -= g_speed;
        }

        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(
            playerPed,
            pos.x,
            pos.y,
            pos.z,
            false,
            false,
            false
        );

        ENTITY::SET_ENTITY_HAS_GRAVITY(
            playerPed,
            false
        );

        PED::SET_PED_CAN_RAGDOLL(
            playerPed,
            false
        );
    }
}
