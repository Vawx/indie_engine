#include "core/global.h"

int main(int ArgumentCount, char* ArgumentValues[])
{
    IString::IString_Test::RunTests();
    if(DisplayInit(ArgumentCount, ArgumentValues))
    {
        
    }
    return 1;
}