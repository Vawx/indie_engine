#pragma once
#if !defined(_TEST_H_)
#define _TEST_H_

#include "console.h"

namespace Test
{   
    void StartNewTest(const char* Name)
    {
        Console::SetColor(Console::ConsoleColors::LIGHTBLUE);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "Starting Test: %s", Name);
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
    
    void Compare(int A, int Expects)
    {
        bool bResult = (A == Expects);
        
        Console::SetColor(bResult ? Console::ConsoleColors::LIGHTGREEN : Console::ConsoleColors::LIGHTRED);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,"Result is [%s] expected [%d] got [%d].", (bResult) ? "Successful" : "NOT Successful", Expects, A);        
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
    
    void Compare(float A, float Expects)
    {
        bool bResult = (A == Expects);
        Console::SetColor(bResult ? Console::ConsoleColors::LIGHTGREEN : Console::ConsoleColors::LIGHTRED);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,"Result is [%s] expected [%f] got [%f].", (bResult) ? "Successful" : "NOT Successful", Expects, A);
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
    
    void Compare(bool A, bool Expects)
    {
        bool bResult = (A == Expects);
        Console::SetColor(bResult ? Console::ConsoleColors::LIGHTGREEN : Console::ConsoleColors::LIGHTRED);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,"Result is [%s] expected [%s] got [%s].", (bResult) ? "Successful" : "NOT Successful", (A) ? "TRUE" : "FALSE", (Expects) ? "TRUE" : "FALSE");
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
    
    void Compare(char* A, char* Expects)
    {
        bool bResult = (strcmp(Expects, A) == 0);
        Console::SetColor(bResult ? Console::ConsoleColors::LIGHTGREEN : Console::ConsoleColors::LIGHTRED);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,"Result is [%s] expected [%s] got [%s].", (bResult) ? "Successful" : "NOT Successful", Expects, A);
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
    
    void Compare(char A, char Expects)
    {
        bool bResult = (A == Expects);
        Console::SetColor(bResult ? Console::ConsoleColors::LIGHTGREEN : Console::ConsoleColors::LIGHTRED);
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,"Result is [%s] expected [%c] got [%c].", (bResult) ? "Successful" : "NOT Successful", Expects, A);
        Console::SetColor(Console::ConsoleColors::WHITE);
    }
};

#endif