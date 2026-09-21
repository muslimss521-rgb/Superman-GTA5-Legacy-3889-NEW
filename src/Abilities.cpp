#include "Abilities.h"
#include <cmath>

void Abilities::SetHeatVision(bool v) {
    Native::SetSeethrough(v);
    lastHeat_ = v;
}

void Abilities::Update(int ped, bool enabled, bool heatVision, bool freezeBreath) {
    if (!enabled) {
        if (lastHeat_) SetHeatVision(false);
        return;
    }

    if (heatVision != lastHeat_)
        SetHeatVision(heatVision);

    if (heatVision) {
        // Heat vision keeps the visual mode active. Actual ray damage can be
        // expanded later with shape-test natives and a particle/beam asset.
        Native::DisableControlAction(0, 24);
    }

    if (freezeBreath) {
        // Hold the attack control while freeze-breath mode is active.
        Native::DisableControlAction(0, 24);
    }
}
