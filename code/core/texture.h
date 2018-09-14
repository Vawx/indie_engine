#pragma once
#if !defined(_TEXTURE_H_)
#define _TEXTURE_H_

struct Texture
{
    char* Data;  
    int32 Size;
    
    int32 Width;
    int32 Height;
};

static Texture* LoadTexture()
{
    Texture* Result = nullptr;
    return Result;
}

#endif