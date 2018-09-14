#pragma once 
#if !defined(_ASSET_INFO_H_)
#define _ASSET_INFO_H_

#define ASSET_INFO_PATH "../content/asset.info"

using namespace String;

enum AssetType
{
    Mesh,
    Texture,
    
    AT_MAX
};

struct AssetInfo
{
    char* FilePath;
    char* AssetName;
    AssetType Type;  
};

static IString AssetInfoFileBuffer;
IString GetAssetInfoFileBuffer() { return AssetInfoFileBuffer; }

bool AssetInfoInit()
{
    SDL_RWops *File = SDL_RWFromFile(ASSET_INFO_PATH, "r");
    if(File)
    {
        const int32 Size = SDL_RWsize(File);
        char* Result = (char*)PlatformAlloc(Size);        
        Assert(Size > 0);

        int32 ReadTotal = 0;
        int32 Read = 1;
        
        char* Buffer = Result;
        while(ReadTotal < Size && Read != 0)
        {
            Read = SDL_RWread(File, Buffer, 1, (Size - ReadTotal));
            ReadTotal += Read;
            Buffer += Read;
        }
        SDL_RWclose(File);
        Assert(ReadTotal == Size);
        AssetInfoFileBuffer = NewString(Result);
        
        return true;
    }
    return false;
}

#endif