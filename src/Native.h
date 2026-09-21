#pragma once
#include <windows.h>
#include <cstdint>
#include <cmath>
#include "../include/ScriptHookV/main.h"

namespace Native {
    inline void Begin(uint64_t hash) {
        nativeInit(hash);
    }

    template<typename T>
    inline void Push(T value) {
        nativePush64(*reinterpret_cast<uint64_t*>(&value));
    }

    inline void PushInt(int value) {
        nativePush64(static_cast<uint64_t>(value));
    }

    inline void PushFloat(float value) {
        uint32_t bits;
        static_assert(sizeof(float) == sizeof(uint32_t), "float size");
        memcpy(&bits, &value, sizeof(bits));
        nativePush64(bits);
    }

    inline uint64_t Call() {
        return *nativeCall();
    }

    inline int Int() { return static_cast<int>(Call()); }
    inline bool Bool() { return Call() != 0; }
    inline float Float() {
        uint32_t bits = static_cast<uint32_t>(Call());
        float f;
        memcpy(&f, &bits, sizeof(f));
        return f;
    }

    struct Vec3 { float x, y, z; };

    inline Vec3 GetVec3() {
        uint64_t r = Call();
        return *reinterpret_cast<Vec3*>(r);
    }

    inline int PlayerPed() {
        Begin(0xD80958FC74E988A6ULL);
        return Int();
    }

    inline Vec3 EntityCoords(int e) {
        Begin(0x3FEF770D40960D5AULL);
        PushInt(e); PushInt(0);
        return GetVec3();
    }

    inline Vec3 EntityVelocity(int e) {
        Begin(0x4805D2DD1D4B6F8DULL);
        PushInt(e);
        return GetVec3();
    }

    inline void SetEntityVelocity(int e, float x, float y, float z) {
        Begin(0xFF5A1988ULL); // SET_ENTITY_VELOCITY
        PushInt(e); PushFloat(x); PushFloat(y); PushFloat(z);
        Call();
    }

    inline Vec3 ForwardVector(int e) {
        Begin(0x0A794A5B9E7B6DFAULL); // GET_ENTITY_FORWARD_VECTOR
        PushInt(e);
        return GetVec3();
    }

    inline float Heading(int e) {
        Begin(0xE83D4F9BA2A3890CULL); // GET_ENTITY_HEADING
        PushInt(e);
        return Float();
    }

    inline void SetHeading(int e, float h) {
        Begin(0x8E2530AA8ADA980EULL); // SET_ENTITY_HEADING
        PushInt(e); PushFloat(h);
        Call();
    }

    inline void SetInvincible(int e, bool v) {
        Begin(0x3882114BDE571AD4ULL);
        PushInt(e); PushInt(v ? 1 : 0);
        Call();
    }

    inline bool IsControlPressed(int group, int control) {
        Begin(0xF3A21BCD95725A4AULL);
        PushInt(group); PushInt(control);
        return Bool();
    }

    inline bool IsControlJustPressed(int group, int control) {
        Begin(0x580417101DD78D9CULL);
        PushInt(group); PushInt(control);
        return Bool();
    }

    inline void DisableControlAction(int group, int control) {
        Begin(0xFE99B66D079CF6BCULL);
        PushInt(group); PushInt(control); PushInt(1);
        Call();
    }

    inline void SetEntityCollision(int e, bool toggle) {
        Begin(0xF1AC3F8E6AC5B9F0ULL);
        PushInt(e); PushInt(toggle ? 1 : 0); PushInt(0);
        Call();
    }

    inline void ApplyForce(int e, float x, float y, float z) {
        Begin(0xC5F68BE9613E2D18ULL);
        PushInt(e); PushInt(1);
        PushFloat(x); PushFloat(y); PushFloat(z);
        PushFloat(0); PushFloat(0); PushFloat(0);
        PushInt(0); PushInt(0); PushInt(1); PushInt(1); PushInt(0); PushInt(1);
        Call();
    }

    inline void SetRunSprintMultiplier(int p, float v) {
        Begin(0x825423C2D15D8F1AULL);
        PushInt(p); PushFloat(v);
        Call();
    }

    inline void SetSeethrough(bool enabled) {
        Begin(0x7E08924259E08CE0ULL);
        PushInt(enabled ? 1 : 0);
        Call();
    }

    inline bool IsPedInAnyVehicle(int ped) {
        Begin(0x997ABD671D25CA0BULL);
        PushInt(ped); PushInt(0);
        return Bool();
    }
}
