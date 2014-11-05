#include <windows.h>
#include "TestConfiguration.h"
#include "DX9Stuff.h"
#include "TestHere.h"

HWND main_hWnd;

int EnterMsgLoop( bool (*ptr_display)(float timeDelta) )
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	static float lastTime = (float)timeGetTime();
	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			float currTime = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;
            if(timeDelta > 0.001f)
            {
                Test(timeDelta);
			    ptr_display(timeDelta); // call display function
			    lastTime = currTime;
            }
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
								LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}


HRESULT IniVentana(HINSTANCE hInstance)
{
	
	WNDCLASSEX	wc;		// clase de ventana
	
	// Rellenamos la estructura de clase de ventana
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0L;
	wc.cbWndExtra = 0L;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Math tests";
	wc.hIconSm = NULL;


	// Registramos la clase de vetana
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "No se pudo registrar la clase de ventana", "Error", MB_OK|MB_ICONEXCLAMATION);
		return E_FAIL;
	}

	// Creamos la ventana
	main_hWnd = CreateWindow("Math tests",			// nombre de la clase
						"Math tests",				// título de la ventana
						WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | 
                           WS_MINIMIZEBOX | WS_VISIBLE,	// tipo de ventana
						0,			// posición X de la ventana
						0,			// posición Y de a ventana
						800,				// ancho de la ventana
						600,				// alto de la ventana
						GetDesktopWindow(),		// ventana padre
						NULL,					// menú
						wc.hInstance,			// instancia de la aplicación
						NULL);					// no se suele usar

	if (!main_hWnd)
    {
        MessageBox(NULL,"No se creó el objeto main_hWnd","Error",MB_OK|MB_ICONEXCLAMATION);
		return E_FAIL;
    }

	return S_OK;
}

INT WINAPI WinMain(HINSTANCE hInstance,			// Instancia a nuestra aplicación
				   HINSTANCE hPrevInstance,		// Existen instancias previas de nuestra aplicación?
				   LPSTR lpCmdLine,				// Línea de comandos
				   int nShowCmd)				// Cómo se despliega nuestra ventana?
{

	if(!SUCCEEDED(IniVentana(hInstance)))
		return 0;

	// Mostrar nuestra ventana
	ShowWindow(main_hWnd, nShowCmd);
	UpdateWindow(main_hWnd);

    InitializeAll(main_hWnd);

	EnterMsgLoop( Display );
	Device->Release();

	UnregisterClass("Math tests",hInstance);

	return 0;
}
