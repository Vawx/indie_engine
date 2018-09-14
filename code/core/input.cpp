#include "input.h"

namespace Input
{
    static void AddKeyByAction(SDL_Keycode Key, KeyAction Action)
    {
        for(int KeyIndex = 0; KeyIndex < KEY_PRESSES; ++KeyIndex)
        {
            if(Action == KeyAction::PRESSED)
            {
                if(Keys[KeyIndex].Action == NONE)
                {
                    Keys[KeyIndex].Key = Key;
                    Keys[KeyIndex].Action = Action;
                    return;
                }
            }
            else if(Action == KeyAction::RELEASED)
            {
                if(Keys[KeyIndex].Key == Key)
                {
                    Keys[KeyIndex].Action = KeyAction::RELEASED;
                }
            }
        }
    }
    
    static void ClearLastReleased()
    {        
        for(int KeyIndex = 0; KeyIndex < KEY_PRESSES; ++KeyIndex)
        {
            if(Keys[KeyIndex].Action == KeyAction::RELEASED)
            {
                Keys[KeyIndex].Key = KEY_NONE;
                Keys[KeyIndex].Action = KeyAction::NONE;
            }
        }
    }
    
    void PrintKeys()
    {        
        for(int KeyIndex = 0; KeyIndex < KEY_PRESSES; ++KeyIndex)
        {
            if(Keys[KeyIndex].Action != KeyAction::NONE)
            {
                SDL_Log("Key %d, Action %s", Keys[KeyIndex].Key, Keys[KeyIndex].Action == KeyAction::PRESSED ? "PRESSED" : "RELEASED");
            }
        }
    }
    
    bool Process()
    {
        ClearLastReleased();
        
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return false;
            }
            else if(Event.type == SDL_KEYDOWN)
            {
                AddKeyByAction(Event.key.keysym.sym, KeyAction::PRESSED);
            }
            else if(Event.type == SDL_KEYUP)
            {
                AddKeyByAction(Event.key.keysym.sym, KeyAction::RELEASED);
            }
        }
        return true;
    }
};