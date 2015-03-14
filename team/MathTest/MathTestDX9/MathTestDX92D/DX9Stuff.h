#ifndef __DX9STUFF__
#define __DX9STUFF__

#include <d3d9.h>
#include <d3dx9.h>
#include "camera.h"
#include "Controls.h"
#include "TestConfiguration.h"

IDirect3DDevice9* Device = 0;
IDirect3DVertexBuffer9* pVertex;
IDirect3DIndexBuffer9* pIndex;
ID3DXMesh* pCircleMesh = NULL;
Camera TheCamera(Camera::AIRCRAFT);
D3DLIGHT9* pLuz = 0;
D3DMATERIAL9* pMaterial = 0;

bool Setup(HWND hwnd);
bool InitD3D(HWND hwnd, int width, int height, bool windowed,
			 D3DDEVTYPE deviceType, IDirect3DDevice9** device);

void InitializeAll(HWND wnd)
{
    if(!InitD3D(wnd, 800, 600, true, 
					 D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FALLÓ", 0, 0);
	}

	if(!Setup(wnd))
	{
		::MessageBox(0, "Setup() - FALLÓ", 0, 0);
	}
}

//--------------------------------------------------------------------
// Gizmo
//--------------------------------------------------------------------

class CGizmo
{
public:
	IDirect3DVertexBuffer9* pVB;
	IDirect3DIndexBuffer9* pIB;
	UINT m_nNumLineas;

	CGizmo(){m_nNumLineas = 0; pVB = 0; pIB = 0;};

	class CVerticeGizmo
	{
	public:
		CVerticeGizmo(){ x = y = z = color = 0;};
		float x, y, z;
		D3DCOLOR color;
	};

	void Draw(IDirect3DDevice9* pDev)
	{
		pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
		 
		pDev->SetStreamSource(0, pVB, 0, sizeof(CVerticeGizmo));
		pDev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		pDev->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLineas);

		pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	};
};

CGizmo Table;

struct CVertice
{
public:
	float x, y, z;
};


void CreatePlaneGizmo(CGizmo &gizmo, IDirect3DDevice9* pDev, 
					 UINT nFilas=10, UINT nColumnas=10, 
					 float fTamF=1.0, float fTamC=1.0, D3DCOLOR color=0);

bool InitD3D(HWND hwnd, int width, int height, bool windowed,
			 D3DDEVTYPE deviceType, IDirect3DDevice9** device)
{

	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT,	
						deviceType,			
						&caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed; 
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; 
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if( FAILED( d3d9->CreateDevice(
							D3DADAPTER_DEFAULT, 
							deviceType,
							hwnd,
							vp,
							&d3dpp,
							device)))
	{
		::MessageBox(0, "CreateDevice() - FALLÓ", 0, 0);
		return 0;
	}

	return true;
}

bool Setup(HWND hwnd)
{
	CreatePlaneGizmo(Table, Device, 20, 20, 1.0f, 1.0f, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));

	pMaterial = new D3DMATERIAL9;
    pMaterial->Emissive = D3DXCOLOR(0,0,0,1);
	pMaterial->Power = 2;

	pLuz = new D3DLIGHT9;
	pLuz->Type = D3DLIGHT_POINT;
	pLuz->Diffuse = D3DXCOLOR(1,1,1,1);
	pLuz->Ambient = D3DXCOLOR(1,1,1,1);
	pLuz->Position = D3DXVECTOR3(3, 2, -3);
	pLuz->Range = 50;
	pLuz->Attenuation0 = 0;
	pLuz->Attenuation1 = 0.5;
	pLuz->Attenuation2 = 0;
	pLuz->Falloff = 5;

	Device->SetLight(0, pLuz);
	Device->LightEnable(0, false);
    Device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1, 1, 1, 1));

	TheCamera.walk(-20.0f);
	D3DXMATRIX Mpersp;
	D3DXMatrixPerspectiveFovLH(
								&Mpersp,
								D3DXToRadian(30),
								(float)800 / (float)600,
								1,
								100);
	Device->SetTransform(D3DTS_PROJECTION, &Mpersp);

    Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	Device->SetRenderState(D3DRS_LIGHTING, false);

	//////////////////////

	Device->CreateVertexBuffer(sizeof(CVertice) * 4, 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &pVertex, NULL);
    Device->CreateIndexBuffer(sizeof(short) * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndex, NULL);

	CVertice* pV = NULL;
	pVertex->Lock(0,0,(void**)&pV, 0);

	pV[0].x = -1.0f; pV[0].y = 1.0f;  pV[0].z = 0.0f;
	pV[1].x = -1.0f; pV[1].y = 1.0f;  pV[1].z = 0.0f;
	pV[2].x = -1.0f; pV[2].y = -1.0f; pV[2].z = 0.0f;
	pV[3].x = -1.0f; pV[3].y = -1.0f; pV[3].z = 0.0f;

	pVertex->Unlock();
    
	short* pI = NULL;
	pIndex->Lock(0,0, (void**)&pI, 0);

	pI[0] = 2; pI[1] = 1; pI[2] = 0; 
	pI[3] = 0; pI[4] = 3; pI[5] = 2; 

	pIndex->Unlock();

    D3DXCreateSphere(Device, 1.0f, 20, 16, &pCircleMesh, NULL);

	return true;
}

void Draw(float r, float g, float b)
{
    D3DXMATRIX QuietoM;
	D3DXMatrixTranslation(&QuietoM,0,0,0);

    pMaterial->Diffuse = D3DXCOLOR(r,g,b,1);
    pMaterial->Ambient = D3DXCOLOR(r,g,b,1);

    Device->SetMaterial(pMaterial);

    Device->SetTransform(D3DTS_WORLD, &QuietoM);
    
	Device->SetStreamSource(0, pVertex, 0, sizeof(float) *3);
	Device->SetIndices(pIndex);
	Device->SetFVF(D3DFVF_XYZ);
    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,4,0,2);

    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,4,0,2);
}

void DrawMesh(float r, float g, float b, D3DXMATRIX transformation, ID3DXMesh* pMesh)
{
    pMaterial->Diffuse = D3DXCOLOR(r,g,b,1);
    pMaterial->Ambient = D3DXCOLOR(r,g,b,1);

    Device->SetMaterial(pMaterial);

    Device->SetTransform(D3DTS_WORLD, &transformation);
	Device->SetFVF(D3DFVF_XYZ);
    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    pMesh->DrawSubset(0);

    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    pMesh->DrawSubset(0);
}


bool Display(float timeDelta)
{
	static float Avance = 6;

	if( Device )
	{
        D3DXMATRIX Mcamara;
		UpdateCamera(timeDelta, TheCamera);
		TheCamera.getViewMatrix(&Mcamara);
		Device->SetTransform(D3DTS_VIEW, &Mcamara);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00ffffff, 1.0f, 0);

		Device->BeginScene();
        
        CVertice* pV = NULL;

#ifdef QRAY2D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Ray2D1.Origin.x + 0.0001f;            pV[0].y = Ray2D1.Origin.y;
            pV[1].x = Ray2D1.Origin.x + Ray2D1.Direction.x * 20.0f + 0.0001f; pV[1].y = Ray2D1.Origin.y + Ray2D1.Direction.y * 20.0f;
            pV[2].x = Ray2D1.Origin.x;                      pV[2].y = Ray2D1.Origin.y;
            pV[3].x = Ray2D1.Origin.x + Ray2D1.Direction.x * 20.0f;           pV[3].y = Ray2D1.Origin.y + Ray2D1.Direction.y * 20.0f;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.2f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Ray2D2.Origin.x + 0.0001f;            pV[0].y = Ray2D2.Origin.y;
            pV[1].x = Ray2D2.Origin.x + Ray2D2.Direction.x * 20.0f + 0.0001f; pV[1].y = Ray2D2.Origin.y + Ray2D2.Direction.y * 20.0f;
            pV[2].x = Ray2D2.Origin.x;                      pV[2].y = Ray2D2.Origin.y;
            pV[3].x = Ray2D2.Origin.x + Ray2D2.Direction.x * 20.0f;           pV[3].y = Ray2D2.Origin.y + Ray2D2.Direction.y * 20.0f;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.2f, 0.2f);

#endif
#ifdef QLINESEGMENT2D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = LineSegment2D1.A.x + 0.0001f; pV[0].y = LineSegment2D1.A.y;
            pV[1].x = LineSegment2D1.B.x + 0.0001f; pV[1].y = LineSegment2D1.B.y;
            pV[2].x = LineSegment2D1.A.x;           pV[2].y = LineSegment2D1.A.y;
            pV[3].x = LineSegment2D1.B.x;           pV[3].y = LineSegment2D1.B.y;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.2f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = LineSegment2D2.A.x + 0.0001f; pV[0].y = LineSegment2D2.A.y;
            pV[1].x = LineSegment2D2.B.x + 0.0001f; pV[1].y = LineSegment2D2.B.y;
            pV[2].x = LineSegment2D2.A.x;           pV[2].y = LineSegment2D2.A.y;
            pV[3].x = LineSegment2D2.B.x;           pV[3].y = LineSegment2D2.B.y;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.2f, 0.2f);

#endif
#ifdef QTRIANGLE2D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Triangle2D1.A.x + 0.0001f; pV[0].y = Triangle2D1.A.y;
            pV[1].x = Triangle2D1.B.x + 0.0001f; pV[1].y = Triangle2D1.B.y;
            pV[2].x = Triangle2D1.C.x;           pV[2].y = Triangle2D1.C.y;
            pV[3].x = Triangle2D1.A.x;           pV[3].y = Triangle2D1.A.y;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.2f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Triangle2D2.A.x + 0.0001f; pV[0].y = Triangle2D2.A.y;
            pV[1].x = Triangle2D2.B.x + 0.0001f; pV[1].y = Triangle2D2.B.y;
            pV[2].x = Triangle2D2.C.x;           pV[2].y = Triangle2D2.C.y;
            pV[3].x = Triangle2D2.A.x;           pV[3].y = Triangle2D2.A.y;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.2f, 0.2f);

#endif
#ifdef QQUADRILATERAL

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Quadrilateral1.A.x + 0.0001f; pV[0].y = Quadrilateral1.A.y;
            pV[1].x = Quadrilateral1.B.x + 0.0001f; pV[1].y = Quadrilateral1.B.y;
            pV[2].x = Quadrilateral1.C.x;           pV[2].y = Quadrilateral1.C.y;
            pV[3].x = Quadrilateral1.D.x;           pV[3].y = Quadrilateral1.D.y;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.2f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Quadrilateral2.A.x + 0.0001f; pV[0].y = Quadrilateral2.A.y;
            pV[1].x = Quadrilateral2.B.x + 0.0001f; pV[1].y = Quadrilateral2.B.y;
            pV[2].x = Quadrilateral2.C.x;           pV[2].y = Quadrilateral2.C.y;
            pV[3].x = Quadrilateral2.D.x;           pV[3].y = Quadrilateral2.D.y;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.2f, 0.2f);

#endif
#ifdef QCIRCLE

        D3DXMATRIX transformation, translation, scaling;

        D3DXMatrixTranslation(&translation, Circle1.Center.x, Circle1.Center.y, 0.0f);
        D3DXMatrixScaling(&scaling, Circle1.Radius, Circle1.Radius, Circle1.Radius);
        transformation = scaling * translation;
        DrawMesh(0.5f, 1.0f, 0.2f, transformation, pCircleMesh);

        
        D3DXMatrixTranslation(&translation, Circle2.Center.x, Circle2.Center.y, 0.0f);
        D3DXMatrixScaling(&scaling, Circle2.Radius, Circle2.Radius, Circle2.Radius);
        transformation = scaling * translation;
        DrawMesh(1.0f, 0.0f, 0.5f, transformation, pCircleMesh);

#endif

        // Axis
        // ----------
        // X
        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = -20.0f; pV[0].y = 0.001f;  pV[0].z =-0.002f;
            pV[1].x = -20.0f; pV[1].y = 0.001f;  pV[1].z =-0.001f;
            pV[2].x = 20.0f; pV[2].y = -0.001f; pV[2].z =-0.001f;
            pV[3].x = 20.0f; pV[3].y = -0.001f; pV[3].z =-0.002f;
            
            pVertex->Unlock();
        }

        Draw(0.0f, 1.0f, 0.0f);

        // Y
        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = -0.001f; pV[0].y = 20.0f;  pV[0].z =-0.002f;
            pV[1].x = -0.001f; pV[1].y = 20.0f;  pV[1].z =-0.001f;
            pV[2].x = -0.001f; pV[2].y = -20.0f; pV[2].z =-0.001f;
            pV[3].x = -0.001f; pV[3].y = -20.0f; pV[3].z =-0.002f;
            
            pVertex->Unlock();
        }

        Draw(0.0f, 1.0f, 0.0f);

		Table.Draw(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void CreatePlaneGizmo(CGizmo &gizmo, IDirect3DDevice9* pDev,
					 UINT nFilas, UINT nColumnas, 
					 float fTamF, float fTamC, D3DCOLOR color)
{
	gizmo.m_nNumLineas = (nColumnas+1) * nFilas + (nFilas+1) * nColumnas;

	pDev->CreateVertexBuffer(
				gizmo.m_nNumLineas*2*sizeof(CGizmo::CVerticeGizmo),
				0,
				D3DFVF_XYZ | D3DFVF_DIFFUSE,
				D3DPOOL_MANAGED,
				&gizmo.pVB,
				0);


	float fAncho = (float)nColumnas * fTamC;
	float fAlto = (float)nFilas * fTamF;
	float fOrigenX = fAncho / -2.0f;
	float fOrigenY = fAlto / -2.0f;


	CGizmo::CVerticeGizmo* v = 0;
	gizmo.pVB->Lock(0, 0, (void**)&v, 0);

	// Lineas verticales | | | | |
	int j = 0;

	for(j = 0; j < (nColumnas+1) * nFilas * 2; j += 2)
	{
		v[j].x = fOrigenX + (float)((j/2) % (nColumnas+1))* fTamC;
		v[j].z = 0.1f;
		v[j].y = fOrigenY + (float)((j/2) / (nColumnas+1))* fTamF;
		v[j].color = color;

		v[j+1].x = fOrigenX + (float)(((nColumnas+1)+j/2) % (nColumnas+1))* fTamC;
		v[j+1].z = 0.1f;
		v[j+1].y = fOrigenY + (float)(((nColumnas+1)+j/2) / (nColumnas+1))* fTamF;
		v[j+1].color = color;
	}

	// Lineas horizontales -- -- --

	for(int k = j; k < gizmo.m_nNumLineas*2; k += 2)
	{
		v[k].x = fOrigenX + (float)(((k-j)/2 + ((k-j)/2)/nColumnas) % (nColumnas+1))* fTamC;
		v[k].z = 0.1f;
		v[k].y = fOrigenY + (float)(((k-j)/2 + ((k-j)/2)/nColumnas) / (nColumnas+1))* fTamF;
		v[k].color = color;

		v[k+1].x = fOrigenX + (float)(((k-j)/2 + ((k-j)/2)/nColumnas +1) % (nColumnas+1))* fTamC;
		v[k+1].z = 0.1f;
		v[k+1].y = fOrigenY + (float)(((k-j)/2 + ((k-j)/2)/nColumnas +1) / (nColumnas+1))* fTamF;
		v[k+1].color = color;
	}

	gizmo.pVB->Unlock();
}

#endif