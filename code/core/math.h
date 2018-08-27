#pragma once
#if !defined(_MATH_H_)
#define _MATH_H_

namespace Math
{
    union iV2
    {        
        struct
        {
            int Size, Count;  
        };
        struct 
        {
            int X, Y;
        };
        struct 
        {
            int Last, Next;
        };
    };
    
};

#endif