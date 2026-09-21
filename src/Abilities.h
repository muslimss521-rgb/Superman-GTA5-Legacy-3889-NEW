#pragma once
#include "Native.h"

class Abilities {
public:
    void Update(int ped, bool enabled, bool heatVision, bool freezeBreath);
    void SetHeatVision(bool v);
private:
    bool lastHeat_ = false;
};
