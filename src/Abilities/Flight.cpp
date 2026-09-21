#include "Flight.h"
#include <windows.h>
#include <cmath>

namespace Flight
{
    static bool g_enabled = false;

    static float g_speed = 0.0f;
    static float g_verticalSpeed = 0.0f;

    static constexpr float MAX_SPEED = 22.0f;
    static constexpr float BOOST_SPEED = 65.0f;

    static constexpr float ACCELERATION = 0.8f;
    static constexpr float BRAKING = 1.2f;
    static constexpr float VERTICAL_ACCELERATION = 0.7f;

    static float Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;

        if (value > max)
            return max;

        return value;
    }

    void Initialize()
    {
        g_enabled = false;
        g_speed = 0.0f;
        g_verticalSpeed = 0.0f;
    }

    void Enable()
    {
        g_enabled = true;
        g_speed = 0.0f;
        g_verticalSpeed = 0.0f;

        Ped playerPed = PLAYER::PLAYER_PED_ID();

        if (ENTITY::DOES_ENTITY_EXIST(playerPed))
        {
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

    void Disable()
    {
        g_enabled = false;
        g_speed = 0.0f;
        g_verticalSpeed = 0.0f;

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

        Vector3 forward =
            ENTITY::GET_ENTITY_FORWARD_VECTOR(
                playerPed
            );

        bool movingForward =
            (GetAsyncKeyState('W') & 0x8000) != 0;

        bool movingBackward =
            (GetAsyncKeyState('S') & 0x8000) != 0;

        bool boost =
            (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;

        bool movingUp =
            (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

        bool movingDown =
            (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

        float targetSpeed = 0.0f;

        if (movingForward)
        {
            targetSpeed =
                boost ? BOOST_SPEED : MAX_SPEED;
        }
        else if (movingBackward)
        {
            targetSpeed = -MAX_SPEED * 0.45f;
        }

        if (g_speed < targetSpeed)
        {
            g_speed += ACCELERATION;
        }
        else if (g_speed > targetSpeed)
        {
            g_speed -= BRAKING;
        }

        g_speed = Clamp(
            g_speed,
            -MAX_SPEED * 0.45f,
            BOOST_SPEED
        );

        if (movingUp)
        {
            g_verticalSpeed +=
                VERTICAL_ACCELERATION;
        }
        else if (movingDown)
        {
            g_verticalSpeed -=
                VERTICAL_ACCELERATION;
        }
        else
        {
            g_verticalSpeed *= 0.85f;
        }

        g_verticalSpeed = Clamp(
            g_verticalSpeed,
            -12.0f,
            12.0f
        );

        Vector3 velocity;

        velocity.x =
            forward.x * g_speed;

        velocity.y =
            forward.y * g_speed;

        velocity.z =
            forward.z * g_speed +
            g_verticalSpeed;

        ENTITY::SET_ENTITY_VELOCITY(
            playerPed,
            velocity.x,
            velocity.y,
            velocity.z
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
