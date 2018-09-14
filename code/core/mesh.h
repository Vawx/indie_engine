#pragma once
#if !defined(_MESH_H_)
#define _MESH_H_

#include "renderable.h"

class Mesh : public Renderable
{
    public:
    
    virtual void Update(float DeltaTime) override;
}

#endif