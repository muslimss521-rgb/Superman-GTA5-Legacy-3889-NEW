#include "Superman/Superman.h"

void ScriptMain()
{
    Superman::Initialize();

    while (true)
    {
        Superman::Update();
        WAIT(0);
    }
}
