// Engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Engine.h"


// This is an example of an exported variable
ENGINE_API int nEngine=0;

// This is an example of an exported function.
ENGINE_API int fnEngine(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see Engine.h for the class definition
CEngine::CEngine()
{
    return;
}
