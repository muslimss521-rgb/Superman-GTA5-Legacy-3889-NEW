#pragma once

#include <windows.h>
#include <cstdint>
#include <cstring>
#include "../include/ScriptHookV/main.h"

namespace Native
{
    struct Vec3
    {
        float x;
        float y;
        float z;
    };

    inline void Begin(uint64_t hash)
    {
        nativeInit(hash);
    }

    inline void PushInt(int value)
    {
        nativePush64(static_cast<uint64_t>(value));
    }

    inline void PushFloat(float value)
    {
        uint32_t bits;
        std::memcpy(&bits, &value, sizeof(bits));
        nativePush64(static_cast<uint64_t>(bits));
    }

    inline uint64_t Call()
    {
        return *nativeCall();
    }

    inline int Int()
    {
        return static_cast<int>(Call());
    }

    inline bool Bool()
    {
        return Call() != 0;
    }

    inline float Float()
    {
        uint32_t bits = static_cast<uint32_t>(Call());

        float value;
        std::memcpy(&value, &bits, sizeof(bits));

        return value;
    }

    inline Vec3 GetVec3()
    {
        uint64_t result = Call();

        if (!result)
            return {0.0f, 0.0f, 0.0f};

        return *reinterpret_cast<Vec3*>(result);
    }


    // PLAYER PED
    inline int PlayerPed()
    {
        Begin(0xD80958FC74E988A6ULL);
        return Int();
    }


    // ENTITY COORDS
    inline Vec3 EntityCoords(int entity)
    {
        Begin(0x3FEF770D40960D5AULL);

        PushInt(entity);
        PushInt(0);

        return GetVec3();
    }


    // ENTITY VELOCITY
    inline Vec3 EntityVelocity(int entity)
    {
        Begin(0x4805D2DD1D4B6F8DULL);

        PushInt(entity);

        return GetVec3();
    }


    // SET ENTITY VELOCITY
    inline void SetEntityVelocity(
        int entity,
        float x,
        float y,
        float z)
    {
        Begin(0x1C99E19C1E2F0A55ULL);

        PushInt(entity);
        PushFloat(x);
        PushFloat(y);
        PushFloat(z);

        Call();
    }


    // GET ENTITY FORWARD VECTOR
    inline Vec3 ForwardVector(int entity)
    {
        Begin(0x0A794A5B9E0B8A0EULL);

        PushInt(entity);

        return GetVec3();
    }


    // GET ENTITY HEADING
    inline float Heading(int entity)
    {
        Begin(0xE83D4F9BA2A3890CULL);

        PushInt(entity);

        return Float();
    }


    // SET ENTITY HEADING
    inline void SetHeading(int entity, float heading)
    {
        Begin(0x8E2530AA8ADA980EULL);

        PushInt(entity);
        PushFloat(heading);

        Call();
    }


    // SET ENTITY INVINCIBLE
    inline void SetInvincible(int entity, bool enabled)
    {
        Begin(0x3882114BDE571AD4ULL);

        PushInt(entity);
        PushInt(enabled ? 1 : 0);

        Call();
    }


    // IS CONTROL PRESSED
    inline bool IsControlPressed(
        int group,
        int control)
    {
        Begin(0xF3A21BCD95725A4AULL);

        PushInt(group);
        PushInt(control);

        return Bool();
    }


    // IS CONTROL JUST PRESSED
    inline bool IsControlJustPressed(
        int group,
        int control)
    {
        Begin(0x580417101DD7DFA9ULL);

        PushInt(group);
        PushInt(control);

        return Bool();
    }


    // DISABLE CONTROL ACTION
    inline void DisableControlAction(
        int group,
        int control)
    {
        Begin(0xFE99B66D079CF6BCULL);

        PushInt(group);
        PushInt(control);
        PushInt(1);

        Call();
    }


    // SET ENTITY COLLISION
    inline void SetEntityCollision(
        int entity,
        bool enabled)
    {
        Begin(0x1A9205C1B9EE827FULL);

        PushInt(entity);
        PushInt(enabled ? 1 : 0);
        PushInt(0);

        Call();
    }


    // APPLY FORCE
    inline void ApplyForce(
        int entity,
        float x,
        float y,
        float z)
    {
        Begin(0xC5F68BE9613E2D18ULL);

        PushInt(entity);
        PushInt(1);

        PushFloat(x);
        PushFloat(y);
        PushFloat(z);

        PushFloat(0.0f);
        PushFloat(0.0f);
        PushFloat(0.0f);

        PushInt(0);
        PushInt(0);
        PushInt(1);
        PushInt(1);
        PushInt(0);
        PushInt(1);

        Call();
    }


    // SET RUN SPRINT MULTIPLIER
    inline void SetRunSprintMultiplier(
        int player,
        float value)
    {
        Begin(0x825423C2D15D8F1AULL);

        PushInt(player);
        PushFloat(value);

        Call();
    }


    // SEETHROUGH
    inline void SetSeethrough(bool enabled)
    {
        Begin(0x7E08924259E08CE0ULL);

        PushInt(enabled ? 1 : 0);

        Call();
    }


    // IS PED IN ANY VEHICLE
    inline bool IsPedInAnyVehicle(int ped)
    {
        Begin(0x997ABD671D25CA0BULL);

        PushInt(ped);
        PushInt(0);

        return Bool();
    }
}
