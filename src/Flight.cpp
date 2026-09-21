#include "Flight.h"
#include <algorithm>

static float clampf(float v, float lo, float hi) {
    return std::max(lo, std::min(v, hi));
}

void FlightSystem::Update(int ped, float dt, bool enabled, bool boost) {
    if (!enabled) {
        speed_ *= 0.90f;
        return;
    }

    if (Native::IsPedInAnyVehicle(ped))
        return;

    const float maxSpeed = boost ? 105.0f : 38.0f;
    const float accel = boost ? 30.0f : 18.0f;

    bool forward = Native::IsControlPressed(0, 32);
    bool back    = Native::IsControlPressed(0, 33);
    bool left    = Native::IsControlPressed(0, 34);
    bool right   = Native::IsControlPressed(0, 35);
    bool up      = Native::IsControlPressed(0, 22);
    bool down    = Native::IsControlPressed(0, 36);

    if (forward) speed_ += accel * dt;
    else if (back) speed_ -= accel * 0.75f * dt;
    else speed_ *= std::pow(0.90f, dt * 60.0f);

    speed_ = clampf(speed_, -12.0f, maxSpeed);

    auto f = Native::ForwardVector(ped);
    float vx = f.x * speed_;
    float vy = f.y * speed_;
    float vz = 0.0f;

    if (up) vz += 24.0f;
    if (down) vz -= 24.0f;

    auto current = Native::EntityVelocity(ped);
    const float blend = clampf(dt * 8.0f, 0.0f, 1.0f);

    vx = current.x + (vx - current.x) * blend;
    vy = current.y + (vy - current.y) * blend;
    vz = current.z + (vz - current.z) * blend;

    // Gentle lift keeps level flight natural instead of locking the player in place.
    if (!up && !down)
        vz += (0.0f - current.z) * clampf(dt * 3.5f, 0.0f, 1.0f);

    Native::SetEntityVelocity(ped, vx, vy, vz);

    if (left || right) {
        float h = Native::Heading(ped);
        float turn = (right ? 1.0f : -1.0f) * 2.2f * dt * (boost ? 0.65f : 1.0f);
        Native::SetHeading(ped, h + turn * 60.0f);
    }
}
