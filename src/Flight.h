#pragma once
#include "Native.h"

class FlightSystem {
public:
    void Update(int ped, float dt, bool enabled, bool boost);
private:
    float speed_ = 0.0f;
};
