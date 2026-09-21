#include "Flight.h"
#include <cmath>

static float clampf(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
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

    if (forward) {
        speed_ += accel * dt;
    }
    else if (back) {
        speed_ -= accel * 0.75f * dt;
    }
    else {
        speed_ *= std::pow(0.90f, dt * 60.0f);
    }

    speed_ = clampf(speed_, -12.0f, maxSpeed);

    Native::Vec3 forwardVector = Native::ForwardVector(ped);

    float vx = forwardVector.x * speed_;
    float vy = forwardVector.y * speed_;
    float vz = 0.0f;

    if (up)
        vz += 24.0f;

    if (down)
        vz -= 24.0f;

    Native::Vec3 current = Native::EntityVelocity(ped);

    const float blend = clampf(dt * 8.0f, 0.0f, 1.0f);

    vx = current.x + (vx - current.x) * blend;
    vy = current.y + (vy - current.y) * blend;
    vz = current.z + (vz - current.z) * blend;

    // Плавное удержание высоты во время горизонтального полёта.
    if (!up && !down) {
        vz += (0.0f - current.z) *
              clampf(dt * 3.5f, 0.0f, 1.0f);
    }

    Native::SetEntityVelocity(
        ped,
        vx,
        vy,
        vz
    );

    // Управление поворотом в воздухе.
    if (left || right) {
        float heading = Native::Heading(ped);

        float direction = right ? 1.0f : -1.0f;

        float turnSpeed = 2.2f;

        if (boost)
            turnSpeed *= 0.65f;

        heading += direction * turnSpeed * dt * 60.0f;

        Native::SetHeading(
            ped,
            heading
        );
    }
}
