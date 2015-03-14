#ifndef __CONTROLS__
#define __CONTROLS__

#include <Windows.h>
#include "camera.h"

void UpdateCamera(float timeDelta, Camera& theCamera)
{
		if( ::GetAsyncKeyState('W') & 0x8000f )
		theCamera.walk(4.0f * timeDelta);

		if( ::GetAsyncKeyState('S') & 0x8000f )
			theCamera.walk(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('A') & 0x8000f )
			theCamera.strafe(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('D') & 0x8000f )
			theCamera.strafe(4.0f * timeDelta);

		if( ::GetAsyncKeyState('R') & 0x8000f )
			theCamera.fly(4.0f * timeDelta);

		if( ::GetAsyncKeyState('F') & 0x8000f )
			theCamera.fly(-4.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			theCamera.pitch(1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			theCamera.pitch(-1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			theCamera.yaw(-1.0f * timeDelta);
			
		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			theCamera.yaw(1.0f * timeDelta);

		if( ::GetAsyncKeyState('N') & 0x8000f )
			theCamera.roll(1.0f * timeDelta);

		if( ::GetAsyncKeyState('M') & 0x8000f )
			theCamera.roll(-1.0f * timeDelta);
}


#endif