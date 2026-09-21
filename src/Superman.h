#pragma once
#include "Native.h"
#include "Flight.h"
#include "Abilities.h"

class Superman {
public:
    void Update();
private:
    bool enabled_ = false;
    bool flight_ = false;
    bool heat_ = false;
    bool freeze_ = false;
    FlightSystem flightSystem_;
    Abilities abilities_;

    void Toggle();
    void HandlePowers(int ped);
};
