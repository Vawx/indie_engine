#pragma once
#if !defined(_RENDER_LOOP_H_)
#define _RENDER_LOOP_H_

#include "input.cpp"

namespace RenderLoop
{
    void Render()
    {
        while(Input::Process())
        {
            TimingStart();
            DisplayStartFrame();
            
            DisplayEndFrame();
            TimingEnd();
        }
    }    
};
#endif