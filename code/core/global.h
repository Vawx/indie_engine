#pragma once 
#if !defined(_GLOBAL_H_)
#define _GLOBAL_H_

#include "sdl/sdl.h"
#include "sdl/sdl_opengl.h"

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define Kilobytes(Value) ((Value) * 1024)
#define Megabytes(Value) ((Kilobytes(Value)) * 1024)
#define Gigabytes(Value) ((Megabytes(Value)) * 1024)
#define Terabytes(Value) ((Gigabytes(Value)) * 1024)

// Max UDP packet size (8 byte header + 65,527 bytes of data)
#define MAX_PACKET_SIZE Kilobytes(65.507)

#include <stdint.h>
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float real32;
typedef double real64;

#define VERY_LARGE_INT 9223372036854775807

#if INDIE_SLOW
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif

#if defined(_WIN32)
#define PlatformAlloc(Size) VirtualAlloc(0, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

#define PlatformFree(Buffer, Size) VirtualFree((LPVOID)Buffer, Size, MEM_RELEASE);
#endif

#include "core/math.h"
#include "core/istring.h"
#include "display.h"

#endif