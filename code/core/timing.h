#pragma once
#if !defined(_TIMING_H_)
#define _TIMING_H_

#define DEFAULT_FPS 30
#define TARGET_MILLISECONDS_PER_FRAME(FPS) (float)((1.f/(float)FPS) * 1000.f)

static Uint64 StartTime;
static Uint64 EndTime;

static Uint64 NowTime;
static Uint64 LastTime;

double DeltaTime;

void TimingStart()
{
    StartTime = SDL_GetTicks();
}

void TimingEnd()
{
    EndTime = SDL_GetTicks();
    
    static float SleepTime = 0;
    SleepTime = TARGET_MILLISECONDS_PER_FRAME(DEFAULT_FPS) - (float)(EndTime - StartTime);                
    if(SleepTime > 0.f)
    {
        SDL_Delay(SleepTime);
    }
    
    LastTime = NowTime;
    NowTime = SDL_GetPerformanceCounter();
    DeltaTime = (double)((NowTime - LastTime) * 1000.f / SDL_GetPerformanceFrequency());
}

#endif
