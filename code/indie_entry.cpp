#include "core/global.h"

int main(int ArgumentCount, char* ArgumentValues[])
{
    if(DisplayInit(ArgumentCount, ArgumentValues))
    {
        RenderLoop::Render();
    }
    return 1;
}