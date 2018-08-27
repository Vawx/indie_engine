#pragma once
#if !defined(_STRING_H_)
#define _STRING_H_

#include <cstdlib>

namespace IString
{
#define EOL(C) (C == '\n' || C == '\0')
#define MAX_STRING_LENGTH MAX_PACKET_SIZE
    
    struct IString
    {
        char* Buffer;
        int Length;
    };
    
    int ToInt(IString& Source)
    {
        return atoi(Source.Buffer);
    }
    
    IString NewString(const char* From)
    {
        IString Result = {};
        Result.Length = strlen(From);
        
        Assert(Result.Length < MAX_PACKET_SIZE);
        
        Result.Buffer = (char*)PlatformAlloc(Result.Length);
        memcpy(Result.Buffer, &From[0], Result.Length);
        return Result;
    }
    
    IString NewString()
    {
        IString Result = {};
        return Result;
    }
    
    void Concat(IString& Dest, IString& Source)
    {
        const int NewSize = strlen(Dest.Buffer) + strlen(Source.Buffer);        
        Dest.Length = NewSize;
        
        const char* Origin = &Dest.Buffer[0];
        Dest.Buffer = (char*)PlatformAlloc(NewSize);
        strcpy(Dest.Buffer, Origin);
        strcat(Dest.Buffer, Source.Buffer);
        
        PlatformFree(Origin, strlen(Origin));
    }
    
    bool Compare(IString& A, IString& B)
    {
        return (strcmp(A.Buffer, B.Buffer) == 0);
    }
    
    IString Substring(IString& Source, const char* Sub)
    {
        IString Result = {};
        char* SubPtr = strstr(Source.Buffer, Sub);
        const int SubPtrLength = strlen(Sub);
        strncpy(SubPtr, Sub, SubPtrLength);
        
        Result.Buffer = &SubPtr[0];
        Result.Length = SubPtrLength;
        return Result;
    }
    
    IString ReplaceSubstring(IString& Source, const char* Sub, const char* Replacement)
    {        
        IString Result = {};        
        char* SubStringPtr = strstr(Source.Buffer, Sub);
        char* SourcePtr = &Source.Buffer[0];
        
        const int32 SubstringIndex = SubStringPtr - SourcePtr;
        if(SubstringIndex > 0)
        {
            char* RemainingSource = &Source.Buffer[strlen(Sub) + SubstringIndex];
            const int32 NewLength = SubstringIndex + strlen(Replacement) + (strlen(RemainingSource) - strlen(Sub));
            
            if(NewLength > 0)
            {
                Result.Buffer = (char*)PlatformAlloc(NewLength);
                Result.Length = NewLength;
                
                memcpy(Result.Buffer, Source.Buffer, SubstringIndex);
                strcat(Result.Buffer, Replacement);
                strcat(Result.Buffer, RemainingSource);
            }
        }        
        
        return Result;
    }
    
    IString** Split(IString& Source, const char Deliminator)
    {
        Math::iV2 Ranges[255] = {};
        int RangesIndex = 0;
        
        int SourceIndex = 0;
        int LastOccuranceIndex = 0;
        
        char* SourceBuffer = &Source.Buffer[0]; 
        
        bool bEndSearch = false;
        while(!bEndSearch) 
        {            
            if(EOL(*SourceBuffer))
            {
                bEndSearch = true;
            }
            
            if(*SourceBuffer == Deliminator || bEndSearch)
            {   
                Ranges[RangesIndex].Last = LastOccuranceIndex;
                Ranges[RangesIndex].Next = SourceIndex;
                
                RangesIndex++;
                
                bool bFoundWhiteSpace = bEndSearch;
                while(!bFoundWhiteSpace)
                {
                    if(*SourceBuffer++ == ' ')
                    {
                        bFoundWhiteSpace = true;
                    }
                    SourceIndex++;
                }
                
                LastOccuranceIndex = SourceIndex;
            }
            SourceIndex++;
            *SourceBuffer++;                                    
        }            
        
        IString** Results = (IString**)PlatformAlloc(RangesIndex);
        for(int ResultsIndex = 0; ResultsIndex < RangesIndex; ++ResultsIndex)
        {
            Results[ResultsIndex] = (IString*)PlatformAlloc(sizeof(IString));
            
            const int32 Length = (Ranges[ResultsIndex].Next - Ranges[ResultsIndex].Last);
            Results[ResultsIndex]->Buffer = (char*)PlatformAlloc(Length);
            Results[ResultsIndex]->Length = Length;
            memcpy(Results[ResultsIndex]->Buffer, &Source.Buffer[Ranges[ResultsIndex].Last], Length);
        }
        return Results;
    }
    
    void RemoveLeadingSpaces(IString& Source)
    {
        char* SourceBuffer = &Source.Buffer[0];
        char Buffer[8096] = {};
        int32 BufferIndex = 0;
        
        int32 SourceIndex = 0;
        bool bFoundFirstCharacter = false;
        for(; SourceIndex < Source.Length; ++SourceIndex)
        {
            if(Source.Buffer[SourceIndex] == ' ' && !bFoundFirstCharacter)
            {
                continue;
            }
            bFoundFirstCharacter = true;
            Buffer[BufferIndex++] = Source.Buffer[SourceIndex];
        }
        PlatformFree(Source.Buffer, Source.Length);
        Source.Buffer = (char*)PlatformAlloc(SourceIndex);
        memcpy(Source.Buffer, &Buffer[0], SourceIndex);
    }
    
    void RemoveTrailingSpaces(IString& Source)
    {        
        char* SourceBuffer = &Source.Buffer[0];
        char Buffer[8096] = {};
        int32 BufferIndex = 0;
        
        int32 SourceIndex = Source.Length - 1;
        bool bFoundFirstCharacter = false;
        for(; SourceIndex >= 0; --SourceIndex)
        {
            if(Source.Buffer[SourceIndex] == ' ' && !bFoundFirstCharacter)
            {
                BufferIndex = SourceIndex - 1;
                continue;
            }
            bFoundFirstCharacter = true;
            Buffer[BufferIndex--] = Source.Buffer[SourceIndex];
        }
        PlatformFree(Source.Buffer, Source.Length);
        
        const int32 NewLength = strlen(&Buffer[0]);
        Source.Buffer = (char*)PlatformAlloc(NewLength);
        Source.Length = NewLength;
        memcpy(Source.Buffer, &Buffer[0], NewLength);
    }
    
#if RUN_INDIE_TESTS
#include "test.h"
    namespace IString_Test
    {
        void RunTests()
        {   
            // New string
            Test::StartNewTest("New String");
            IString New = NewString("New String");
            Test::Compare((char*)New.Buffer, "New String");
            Test::Compare(New.Length, strlen("New String"));
            
            // Concat
            Test::StartNewTest("String Concat");
            IString A = NewString("Testing");
            IString B = NewString(" Concat");
            
            Concat(A, B);
            
            Test::Compare((char*)A.Buffer, "Testing Concat");
            
            // Compare strings
            Test::StartNewTest("String Compare");
            IString C = NewString("Compare");
            IString D = NewString("Compared");
            
            bool bStringCompare = Compare(C, D);        
            Test::Compare(bStringCompare, false);
            
            IString E = NewString("Super Strings");
            IString F = NewString("Super Strings");
            
            bStringCompare = Compare(E, F);        
            Test::Compare(bStringCompare, true);
            
            // Get substring
            Test::StartNewTest("String Substring");
            IString G = NewString("Hello from planet Mars");
            IString H = Substring(G, "Mars");
            
            Test::Compare((char*)H.Buffer, "Mars");
            
            // Replace substring
            Test::StartNewTest("String Replace");
            IString I = NewString("Hello from planet Mars, friend.");
            IString J = ReplaceSubstring(I, "Mars", "Earth");
            
            Test::Compare((char*)J.Buffer, "Hello from planet Earth, friend.");
            
            // To Int
            Test::StartNewTest("String to Int");
            IString K = NewString("93723");
            int Int = ToInt(K);
            
            Test::Compare(Int, 93723);
            
            // Split
            Test::StartNewTest("String Split Comma");
            IString L = NewString("Testing, Split, By, Comma");
            IString** M = Split(L, ',');
            
            Test::Compare((char*)M[0]->Buffer, "Testing");
            Test::Compare((char*)M[1]->Buffer, "Split");
            Test::Compare((char*)M[2]->Buffer, "By");
            Test::Compare((char*)M[3]->Buffer, "Comma");            
                        
            Test::StartNewTest("String Split Space");
            IString N = NewString("Split Testing By Space");
            IString** O = Split(N, ' ');
            
            Test::Compare((char*)O[0]->Buffer, "Split");
            Test::Compare((char*)O[1]->Buffer, "Testing");
            Test::Compare((char*)O[2]->Buffer, "By");
            Test::Compare((char*)O[3]->Buffer, "Space");
            
            // Remove Leading spaces
            Test::StartNewTest("Remove Leading Spaces");
            IString P = NewString("      ...Ahhhhh!");
            RemoveLeadingSpaces(P);
            
            Test::Compare((char*)P.Buffer, "...Ahhhhh!");
            
            // Remove trailing spaces
            Test::StartNewTest("Remove trailing spaces");
            IString Q = NewString("It feels like time continues on and on and...            ");
            RemoveTrailingSpaces(Q);
            
            Test::Compare((char*)Q.Buffer, "It feels like time continues on and on and...");
        }
    }
#endif
};
#endif