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
        nativePush64(static_cast<uint64_t>(
            static_cast<int64_t>(value)
        ));
    }

    inline void PushFloat(float value)
    {
        uint32_t bits = 0;

        std::memcpy(
            &bits,
            &value,
            sizeof(float)
        );

        nativePush64(
            static_cast<uint64_t>(bits)
        );
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
        uint32_t bits =
            static_cast<uint32_t>(Call());

        float value = 0.0f;

        std::memcpy(
            &value,
            &bits,
            sizeof(float)
        );

        return value;
    }

    inline Vec3 GetVec3()
    {
        uint64_t result = Call();

        if (result == 0)
        {
            return {
                0.0f,
                0.0f,
                0.0f
            };
        }

        return *reinterpret_cast<Vec3*>(result);
    }


    // =========================================================
    // PLAYER
    // =========================================================

    // PLAYER_PED_ID
    // 0xD80958FC74E988A6
    inline int PlayerPed()
    {
        Begin(0xD80958FC74E988A6ULL);

        return Int();
    }


    // =========================================================
    // ENTITY
    // =========================================================

    // GET_ENTITY_COORDS
    // 0x3FEF770D40960D5A
    inline Vec3 EntityCoords(int entity)
    {
        Begin(0x3FEF770D40960D5AULL);

        PushInt(entity);
        PushInt(1);

        return GetVec3();
    }


    // GET_ENTITY_VELOCITY
    // 0x4805D2B1D8CF94A9
    inline Vec3 EntityVelocity(int entity)
    {
        Begin(0x4805D2B1D8CF94A9ULL);

        PushInt(entity);

        return GetVec3();
    }


    // SET_ENTITY_VELOCITY
    // 0x1C99E19C1E2F0A55
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


    // GET_ENTITY_FORWARD_VECTOR
    // 0x0A794A5A57F8DF91
    inline Vec3 ForwardVector(int entity)
    {
        Begin(0x0A794A5A57F8DF91ULL);

        PushInt(entity);

        return GetVec3();
    }


    // GET_ENTITY_HEADING
    // 0xE83D4F9BA2A38914
    inline float Heading(int entity)
    {
        Begin(0xE83D4F9BA2A38914ULL);

        PushInt(entity);

        return Float();
    }


    // SET_ENTITY_HEADING
    // 0x8E2530AA8ADA980E
    inline void SetHeading(
        int entity,
        float heading)
    {
        Begin(0x8E2530AA8ADA980EULL);

        PushInt(entity);
        PushFloat(heading);

        Call();
    }


    // SET_ENTITY_INVINCIBLE
    // 0x3882114BDE571AD4
    inline void SetInvincible(
        int entity,
        bool enabled)
    {
        Begin(0x3882114BDE571AD4ULL);

        PushInt(entity);
        PushInt(enabled ? 1 : 0);

        Call();
    }


    // SET_ENTITY_COLLISION
    // 0x1A9205C1B9EE827F
    inline void SetEntityCollision(
        int entity,
        bool enabled)
    {
        Begin(0x1A9205C1B9EE827FULL);

        PushInt(entity);
        PushInt(enabled ? 1 : 0);
        PushInt(1);

        Call();
    }


    // APPLY_FORCE_TO_ENTITY
    // 0xC5F68BE9613E2D18
    inline void ApplyForce(
        int entity,
        float x,
        float y,
        float z)
    {
        Begin(0xC5F68BE9613E2D18ULL);

        PushInt(entity);

        // forceFlags
        PushInt(1);

        // force vector
        PushFloat(x);
        PushFloat(y);
        PushFloat(z);

        // offset
        PushFloat(0.0f);
        PushFloat(0.0f);
        PushFloat(0.0f);

        // bone
        PushInt(0);

        // isDirectionRel
        PushInt(0);

        // ignoreUpVec
        PushInt(0);

        // isForceRel
        PushInt(1);

        // p12
        PushInt(1);

        // p13
        PushInt(0);

        Call();
    }


    // =========================================================
    // PAD / CONTROLS
    // =========================================================

    // IS_CONTROL_PRESSED
    // 0xF3A21BCD95725A4A
    inline bool IsControlPressed(
        int group,
        int control)
    {
        Begin(0xF3A21BCD95725A4AULL);

        PushInt(group);
        PushInt(control);

        return Bool();
    }


    // IS_CONTROL_JUST_PRESSED
    // 0x580417101DDB492F
    inline bool IsControlJustPressed(
        int group,
        int control)
    {
        Begin(0x580417101DDB492FULL);

        PushInt(group);
        PushInt(control);

        return Bool();
    }


    // DISABLE_CONTROL_ACTION
    // 0xFE99B66D079CF6BC
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


    // =========================================================
    // PLAYER
    // =========================================================

    // SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER
    // 0x6DB47AA77FD94E09
    inline void SetRunSprintMultiplier(
        int player,
        float value)
    {
        Begin(0x6DB47AA77FD94E09ULL);

        PushInt(player);
        PushFloat(value);

        Call();
    }


    // =========================================================
    // GRAPHICS
    // =========================================================

    // SET_SEETHROUGH
    // 0x7E08924259E08CE0
    inline void SetSeethrough(bool enabled)
    {
        Begin(0x7E08924259E08CE0ULL);

        PushInt(enabled ? 1 : 0);

        Call();
    }


    // =========================================================
    // PED
    // =========================================================

    // IS_PED_IN_ANY_VEHICLE
    // 0x997ABD671D25CA0B
    inline bool IsPedInAnyVehicle(int ped)
    {
        Begin(0x997ABD671D25CA0BULL);

        PushInt(ped);
        PushInt(0);

        return Bool();
    }
}
