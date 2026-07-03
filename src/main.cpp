#include "core/core.hpp"


int main(int ArgC, char* ArgV[])
{
    SNZ::Initialize();
    SNZ::MainLoop();
    SNZ::FreeResources();

    return 0;
}