#include "Superman.h"
#include <windows.h>

void Superman::Toggle() {
    enabled_ = !enabled_;
    int ped = Native::PlayerPed();

    Native::SetInvincible(ped, enabled_);
    if (!enabled_) {
        flight_ = false;
        heat_ = false;
        freeze_ = false;
        Native::SetSeethrough(false);
    }
}

void Superman::HandlePowers(int ped) {
    // F3
    if (Native::IsControlJustPressed(0, 170))
        Toggle();

    if (!enabled_)
        return;

    // F4
    if (Native::IsControlJustPressed(0, 115))
        flight_ = !flight_;

    // E
    if (Native::IsControlJustPressed(0, 69))
        heat_ = !heat_;

    // Q
    if (Native::IsControlJustPressed(0, 81))
        freeze_ = !freeze_;

    // Sprint becomes a temporary ground-speed boost.
    bool sprint = Native::IsControlPressed(0, 21);
    Native::SetRunSprintMultiplier(0, sprint ? 1.49f : 1.0f);

    // Super punch / impact force while attacking.
    if (Native::IsControlPressed(0, 24)) {
        auto f = Native::ForwardVector(ped);
        Native::ApplyForce(ped, f.x * 3.0f, f.y * 3.0f, 1.5f);
    }
}

void Superman::Update() {
    int ped = Native::PlayerPed();

    HandlePowers(ped);

    if (!enabled_)
        return;

    bool boost = Native::IsControlPressed(0, 160);
    flightSystem_.Update(ped, 1.0f / 60.0f, flight_, boost);
    abilities_.Update(ped, enabled_, heat_, freeze_);

    // Reduce accidental vehicle/weapon control conflicts during flight.
    if (flight_) {
        Native::DisableControlAction(0, 23);
        Native::DisableControlAction(0, 75);
    }
}
