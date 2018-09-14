#pragma once
#if !defined(_CONSOLE_H_)
#define _CONSOLE_H_

#include "renderable.h"

namespace Console
{
#if defined(_WIN32)
    enum ConsoleColors
    {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGRAY,
        DARKGRAY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE,
    };
    
    static HANDLE GetConsoleHandle() { return GetStdHandle(STD_OUTPUT_HANDLE); }
    
    void SetColor(ConsoleColors Color) 
    {
        SetConsoleTextAttribute(GetConsoleHandle(), Color);
    }    
#endif

};

#endif