#pragma once
#if !defined(_DISPLAY_H_)
#define _DISPLAY_H_

enum DisplaySwapInterval
{
    IMMEDIATE = 0,
    VSYNC = 1,
    
    MAX = 255,
};

static const char* WINDOW_NAME_COMMAND = "-WindowName=";
static const char* WINDOW_SIZE_COMMAND = "-WindowSize=";

#define DEFAULT_WINDOW_NAME "Indie Game"
#define DEFAULT_DISPLAY_WIDTH 1280
#define DEFAULT_DISPLAY_HEIGHT 720

static SDL_Window* Window;
static SDL_GLContext GLContext;

static Math::iV2 WindowDimensions;

static IString::IString WindowName;

bool DisplayInit(int ArgumentCount, char* ArgumentValues[])
{          
    for(int ArgIndex = 0; ArgIndex < ArgumentCount; ++ArgIndex)
    {
        if(strstr(ArgumentValues[ArgIndex], WINDOW_NAME_COMMAND) > 0)
        {
            const int32 WindowNameArgumentLength = strlen(WINDOW_NAME_COMMAND);            
            WindowName = IString::NewString(&ArgumentValues[ArgIndex][WindowNameArgumentLength]);
        }
        
        if(strstr(ArgumentValues[ArgIndex], WINDOW_SIZE_COMMAND) > 0)
        {
            const int32 WindowSizeArgumentLength = strlen(WINDOW_SIZE_COMMAND);
            IString::IString Sizes = IString::NewString(&ArgumentValues[ArgIndex][WindowSizeArgumentLength]);
            IString::IString** SplitSizes = IString::Split(Sizes, ',');
            
            WindowDimensions.Width = IString::ToInt(*SplitSizes[0]);
            WindowDimensions.Height = IString::ToInt(*SplitSizes[1]);
            
            Assert(WindowDimensions.Width > 0 && WindowDimensions.Height > 0);
        }
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    Window = SDL_CreateWindow(WindowName.Buffer, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              WindowDimensions.Width, WindowDimensions.Height, SDL_WINDOW_OPENGL);
    if(Window)
    {
        GLContext = SDL_GL_CreateContext(Window);
        if(GLContext)
        {
            SDL_GL_SetSwapInterval(DisplaySwapInterval::VSYNC);
            {
                return true;
            }            
        }
    }           
    return false;
}

void DisplayClose()
{
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

#endif