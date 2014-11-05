// NewInDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NewInDll.h"
#include "heap2.h"

// This is an example of an exported variable
NEWINDLL_API int nNewInDll=0;

// This is an example of an exported function.
NEWINDLL_API int fnNewInDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see NewInDll.h for the class definition
/*CNewInDll::CNewInDll()
{
	return;
}
*/
int* Heap2::p = new int(5);