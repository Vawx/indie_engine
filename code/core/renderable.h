#pragma once
#if !defined(_RENDERABLE_H_)
#define _RENDERABLE_H_

typedef void (*Update)(float);
#define BindUpdateRenderable(Func) Update = &Func;

#endif