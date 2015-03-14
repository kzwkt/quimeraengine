
#include "stdafx.h"

#include "ThrowingFromDll.h"

ThrowClass::ThrowClass(int i)
{
    //i += 2;
    throw i;
}