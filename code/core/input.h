#pragma once 
#if !defined(_INPUT_H_)
#define _INPUT_H_

namespace Input
{
#define KEY_PRESSES 64
#define KEY_NONE 0
    
    enum KeyAction
    {
        NONE,
        PRESSED,
        RELEASED,
    };
    
    struct KeyData
    {
        SDL_Keycode Key;
        KeyAction Action;
    };
    
    KeyData Keys[KEY_PRESSES];
    
    bool Process();
    void PrintKeys();
};


#endif