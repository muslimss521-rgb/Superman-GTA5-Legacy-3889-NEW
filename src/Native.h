#pragma once

#include <windows.h>
#include <cstdint>
#include <cstring>

#include "../include/ScriptHookV/main.h"
#include "../include/ScriptHookV/natives.h"

namespace Native
{
    struct Vec3
    {
        float x;
        float y;
        float z;
    };

    inline int PlayerPed()
    {
        return PLAYER::PLAYER_PED_ID();
    }

    inline Vec3 EntityCoords(int entity)
    {
        Vector3 v = ENTITY::GET_ENTITY_COORDS(entity, true);
        return { v.x, v.y, v.z };
    }

    inline Vec3 EntityVelocity(int entity)
    {
        Vector3 v = ENTITY::GET_ENTITY_VELOCITY(entity);
        return { v.x, v.y, v.z };
    }

    inline void SetEntityVelocity(
        int entity,
        float x,
        float y,
        float z)
    {
        ENTITY::SET_ENTITY_VELOCITY(entity, x, y, z);
    }

    inline Vec3 ForwardVector(int entity)
    {
        Vector3 v = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
        return { v.x, v.y, v.z };
    }

    inline float Heading(int entity)
    {
        return ENTITY::GET_ENTITY_HEADING(entity);
    }

    inline void SetHeading(int entity, float heading)
    {
        ENTITY::SET_ENTITY_HEADING(entity, heading);
    }

    inline void SetInvincible(int entity, bool enabled)
    {
        ENTITY::SET_ENTITY_INVINCIBLE(entity, enabled);
    }

    inline bool IsControlPressed(
        int group,
        int control)
    {
        return PAD::IS_CONTROL_PRESSED(group, control);
