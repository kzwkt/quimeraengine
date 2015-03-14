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
ID3DXMesh* pSphereMesh;
Camera TheCamera(Camera::AIRCRAFT);
D3DLIGHT9* pLuz = 0;
D3DMATERIAL9* pMaterial = 0;

bool Setup();
bool InitD3D(HWND hwnd, int width, int height, bool windowed,
			 D3DDEVTYPE deviceType, IDirect3DDevice9** device);

void InitializeAll(HWND wnd)
{
    if(!InitD3D(wnd, 800, 600, true, 
					 D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FALLÓ", 0, 0);
	}

	if(!Setup())
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

bool Setup()
{
	CreatePlaneGizmo(Table, Device, 10, 10, 1.0f, 1.0f, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));

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
	Device->LightEnable(0, true);

	TheCamera.walk(-3.0f);
	TheCamera.pitch(0.5f);
	TheCamera.walk(-7.0f);
	D3DXMATRIX Mpersp;
	D3DXMatrixPerspectiveFovLH(
								&Mpersp,
								D3DXToRadian(45),
								(float)800 / (float)600,
								1,
								1000);
	Device->SetTransform(D3DTS_PROJECTION, &Mpersp);


    Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	Device->SetRenderState(D3DRS_LIGHTING, true);

	//////////////////////

	Device->CreateVertexBuffer(sizeof(CVertice) * 8, 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &pVertex, NULL);
	Device->CreateIndexBuffer(sizeof(short) * 36, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndex, NULL);

	CVertice* pV = NULL;
	pVertex->Lock(0,0,(void**)&pV, 0);

	pV[0].x = -1.0f; pV[0].y = 1.0f;  pV[0].z = 1.0f;
	pV[1].x = -1.0f; pV[1].y = 1.0f;  pV[1].z = -1.0f;
	pV[2].x = -1.0f; pV[2].y = -1.0f; pV[2].z = -1.0f;
	pV[3].x = -1.0f; pV[3].y = -1.0f; pV[3].z = 1.0f;
	pV[4].x = 1.0f;  pV[4].y = 1.0f;  pV[4].z = 1.0f;
	pV[5].x = 1.0f;  pV[5].y = 1.0f;  pV[5].z = -1.0f;
	pV[6].x = 1.0f;  pV[6].y = -1.0f; pV[6].z = -1.0f;
	pV[7].x = 1.0f;  pV[7].y = -1.0f; pV[7].z = 1.0f;

	pVertex->Unlock();


	short* pI = NULL;
	pIndex->Lock(0,0, (void**)&pI, 0);

	pI[0] = 2; pI[1] = 1; pI[2] = 0; 
	pI[3] = 0; pI[4] = 3; pI[5] = 2; 
	pI[6] = 6; pI[7] = 5; pI[8] = 1; 
	pI[9] = 1; pI[10] = 2; pI[11] = 6; 
	pI[12] = 5; pI[13] = 4; pI[14] = 0; 
	pI[15] = 0; pI[16] = 1; pI[17] = 5; 
	pI[18] = 2; pI[19] = 3; pI[20] = 7; 
	pI[21] = 7; pI[22] = 6; pI[23] = 2; 
	pI[24] = 4; pI[25] = 5; pI[26] = 6; 
	pI[27] = 6; pI[28] = 7; pI[29] = 4; 
	pI[30] = 3; pI[31] = 0; pI[32] = 4; 
	pI[33] = 4; pI[34] = 7; pI[35] = 3; 

	pIndex->Unlock();

    D3DXCreateSphere(Device, 1.0f, 20, 16, &pSphereMesh, NULL);

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
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,8,0,12);

    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,8,0,12);
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

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER |D3DCLEAR_STENCIL, 0x00ffffff, 1.0f, 0);

		Device->BeginScene();
        
        CVertice* pV = NULL;

#ifdef QLINESEGMENT3D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = LineSegment3D1.A.x + 0.0001f; pV[0].y = LineSegment3D1.A.y; pV[0].z = LineSegment3D1.A.z;
            pV[1].x = LineSegment3D1.A.x + 0.0001f; pV[1].y = LineSegment3D1.A.y; pV[1].z = LineSegment3D1.A.z;
            pV[2].x = LineSegment3D1.A.x;           pV[2].y = LineSegment3D1.A.y; pV[2].z = LineSegment3D1.A.z + 0.0001f;
            pV[3].x = LineSegment3D1.A.x;           pV[3].y = LineSegment3D1.A.y; pV[3].z = LineSegment3D1.A.z + 0.0001f;
            pV[4].x = LineSegment3D1.B.x + 0.0001f; pV[4].y = LineSegment3D1.B.y; pV[4].z = LineSegment3D1.B.z;
            pV[5].x = LineSegment3D1.B.x + 0.0001f; pV[5].y = LineSegment3D1.B.y; pV[5].z = LineSegment3D1.B.z;
            pV[6].x = LineSegment3D1.B.x;           pV[6].y = LineSegment3D1.B.y; pV[6].z = LineSegment3D1.B.z + 0.0001f;
            pV[7].x = LineSegment3D1.B.x;           pV[7].y = LineSegment3D1.B.y; pV[7].z = LineSegment3D1.B.z + 0.0001f;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.2f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = LineSegment3D2.A.x + 0.0001f; pV[0].y = LineSegment3D2.A.y; pV[0].z = LineSegment3D2.A.z;
            pV[1].x = LineSegment3D2.A.x + 0.0001f; pV[1].y = LineSegment3D2.A.y; pV[1].z = LineSegment3D2.A.z;
            pV[2].x = LineSegment3D2.A.x;           pV[2].y = LineSegment3D2.A.y; pV[2].z = LineSegment3D2.A.z + 0.0001f;
            pV[3].x = LineSegment3D2.A.x;           pV[3].y = LineSegment3D2.A.y; pV[3].z = LineSegment3D2.A.z + 0.0001f;
            pV[4].x = LineSegment3D2.B.x + 0.0001f; pV[4].y = LineSegment3D2.B.y; pV[4].z = LineSegment3D2.B.z;
            pV[5].x = LineSegment3D2.B.x + 0.0001f; pV[5].y = LineSegment3D2.B.y; pV[5].z = LineSegment3D2.B.z;
            pV[6].x = LineSegment3D2.B.x;           pV[6].y = LineSegment3D2.B.y; pV[6].z = LineSegment3D2.B.z + 0.0001f;
            pV[7].x = LineSegment3D2.B.x;           pV[7].y = LineSegment3D2.B.y; pV[7].z = LineSegment3D2.B.z + 0.0001f;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.2f, 0.2f);

#endif
#ifdef QRAY3D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            const float_q RAY_LENGTH = 15.0f;
            pV[0].x = Ray3D1.Origin.x + (Ray3D1.Direction.x + 0.0001f) * RAY_LENGTH;     pV[0].y = Ray3D1.Origin.y + Ray3D1.Direction.y * RAY_LENGTH;   pV[0].z = Ray3D1.Origin.z + Ray3D1.Direction.z * RAY_LENGTH;
            pV[1].x = Ray3D1.Origin.x + (Ray3D1.Direction.x + 0.0001f) * RAY_LENGTH;     pV[1].y = Ray3D1.Origin.y + Ray3D1.Direction.y * RAY_LENGTH;   pV[1].z = Ray3D1.Origin.z + Ray3D1.Direction.z * RAY_LENGTH;
            pV[2].x = Ray3D1.Origin.x + Ray3D1.Direction.x * RAY_LENGTH;                 pV[2].y = Ray3D1.Origin.y + Ray3D1.Direction.y * RAY_LENGTH;   pV[2].z = Ray3D1.Origin.z + (Ray3D1.Direction.z + 0.0001f) * RAY_LENGTH;
            pV[3].x = Ray3D1.Origin.x + Ray3D1.Direction.x * RAY_LENGTH;                 pV[3].y = Ray3D1.Origin.y + Ray3D1.Direction.y * RAY_LENGTH;   pV[3].z = Ray3D1.Origin.z + (Ray3D1.Direction.z + 0.0001f) * RAY_LENGTH;
            pV[4].x = Ray3D1.Origin.x + 0.0001f;                                         pV[4].y = Ray3D1.Origin.y;                                     pV[4].z = Ray3D1.Origin.z;
            pV[5].x = Ray3D1.Origin.x + 0.0001f;                                         pV[5].y = Ray3D1.Origin.y;                                     pV[5].z = Ray3D1.Origin.z;
            pV[6].x = Ray3D1.Origin.x;                                                   pV[6].y = Ray3D1.Origin.y;                                     pV[6].z = Ray3D1.Origin.z + 0.0001f;
            pV[7].x = Ray3D1.Origin.x;                                                   pV[7].y = Ray3D1.Origin.y;                                     pV[7].z = Ray3D1.Origin.z + 0.0001f;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 1.0f, 1.0f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            const float_q RAY_LENGTH = 15.0f;
            pV[0].x = Ray3D2.Origin.x + (Ray3D2.Direction.x + 0.0001f) * RAY_LENGTH;     pV[0].y = Ray3D2.Origin.y + Ray3D2.Direction.y * RAY_LENGTH;   pV[0].z = Ray3D2.Origin.z + Ray3D2.Direction.z * RAY_LENGTH;
            pV[1].x = Ray3D2.Origin.x + (Ray3D2.Direction.x + 0.0001f) * RAY_LENGTH;     pV[1].y = Ray3D2.Origin.y + Ray3D2.Direction.y * RAY_LENGTH;   pV[1].z = Ray3D2.Origin.z + Ray3D2.Direction.z * RAY_LENGTH;
            pV[2].x = Ray3D2.Origin.x + Ray3D2.Direction.x * RAY_LENGTH;                 pV[2].y = Ray3D2.Origin.y + Ray3D2.Direction.y * RAY_LENGTH;   pV[2].z = Ray3D2.Origin.z + (Ray3D2.Direction.z + 0.0001f) * RAY_LENGTH;
            pV[3].x = Ray3D2.Origin.x + Ray3D2.Direction.x * RAY_LENGTH;                 pV[3].y = Ray3D2.Origin.y + Ray3D2.Direction.y * RAY_LENGTH;   pV[3].z = Ray3D2.Origin.z + (Ray3D2.Direction.z + 0.0001f) * RAY_LENGTH;
            pV[4].x = Ray3D2.Origin.x + 0.0001f;                                         pV[4].y = Ray3D2.Origin.y;                                     pV[4].z = Ray3D2.Origin.z;
            pV[5].x = Ray3D2.Origin.x + 0.0001f;                                         pV[5].y = Ray3D2.Origin.y;                                     pV[5].z = Ray3D2.Origin.z;
            pV[6].x = Ray3D2.Origin.x;                                                   pV[6].y = Ray3D2.Origin.y;                                     pV[6].z = Ray3D2.Origin.z + 0.0001f;
            pV[7].x = Ray3D2.Origin.x;                                                   pV[7].y = Ray3D2.Origin.y;                                     pV[7].z = Ray3D2.Origin.z + 0.0001f;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.7f, 0.2f);

#endif
#ifdef QTRIANGLE3D

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Triangle3D1.A.x; pV[0].y = Triangle3D1.A.y; pV[0].z = Triangle3D1.A.z;
            pV[1].x = Triangle3D1.A.x; pV[1].y = Triangle3D1.A.y; pV[1].z = Triangle3D1.A.z;
            pV[2].x = Triangle3D1.B.x; pV[2].y = Triangle3D1.B.y; pV[2].z = Triangle3D1.B.z;
            pV[3].x = Triangle3D1.B.x; pV[3].y = Triangle3D1.B.y; pV[3].z = Triangle3D1.B.z;
            pV[4].x = Triangle3D1.A.x; pV[4].y = Triangle3D1.A.y; pV[4].z = Triangle3D1.A.z;
            pV[5].x = Triangle3D1.A.x; pV[5].y = Triangle3D1.A.y; pV[5].z = Triangle3D1.A.z;
            pV[6].x = Triangle3D1.C.x; pV[6].y = Triangle3D1.C.y; pV[6].z = Triangle3D1.C.z;
            pV[7].x = Triangle3D1.C.x; pV[7].y = Triangle3D1.C.y; pV[7].z = Triangle3D1.C.z;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 0.7f, 0.7f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Triangle3D2.A.x; pV[0].y = Triangle3D2.A.y; pV[0].z = Triangle3D2.A.z;
            pV[1].x = Triangle3D2.A.x; pV[1].y = Triangle3D2.A.y; pV[1].z = Triangle3D2.A.z;
            pV[2].x = Triangle3D2.B.x; pV[2].y = Triangle3D2.B.y; pV[2].z = Triangle3D2.B.z;
            pV[3].x = Triangle3D2.B.x; pV[3].y = Triangle3D2.B.y; pV[3].z = Triangle3D2.B.z;
            pV[4].x = Triangle3D2.A.x; pV[4].y = Triangle3D2.A.y; pV[4].z = Triangle3D2.A.z;
            pV[5].x = Triangle3D2.A.x; pV[5].y = Triangle3D2.A.y; pV[5].z = Triangle3D2.A.z;
            pV[6].x = Triangle3D2.C.x; pV[6].y = Triangle3D2.C.y; pV[6].z = Triangle3D2.C.z;
            pV[7].x = Triangle3D2.C.x; pV[7].y = Triangle3D2.C.y; pV[7].z = Triangle3D2.C.z;
            
            pVertex->Unlock();
        }

		Draw(0.6f, 0.9f, 0.4f);

#endif
#ifdef QHEXAHEDRON

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Hexahedron1.A.x; pV[0].y = Hexahedron1.A.y; pV[0].z = Hexahedron1.A.z;
            pV[1].x = Hexahedron1.B.x; pV[1].y = Hexahedron1.B.y; pV[1].z = Hexahedron1.B.z;
            pV[2].x = Hexahedron1.C.x; pV[2].y = Hexahedron1.C.y; pV[2].z = Hexahedron1.C.z;
            pV[3].x = Hexahedron1.D.x; pV[3].y = Hexahedron1.D.y; pV[3].z = Hexahedron1.D.z;
            pV[4].x = Hexahedron1.E.x; pV[4].y = Hexahedron1.E.y; pV[4].z = Hexahedron1.E.z;
            pV[5].x = Hexahedron1.H.x; pV[5].y = Hexahedron1.H.y; pV[5].z = Hexahedron1.H.z;
            pV[6].x = Hexahedron1.G.x; pV[6].y = Hexahedron1.G.y; pV[6].z = Hexahedron1.G.z;
            pV[7].x = Hexahedron1.F.x; pV[7].y = Hexahedron1.F.y; pV[7].z = Hexahedron1.F.z;
            
            pVertex->Unlock();
        }

		Draw(0.2f, 1.0f, 0.2f);

        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = Hexahedron2.A.x; pV[0].y = Hexahedron2.A.y; pV[0].z = Hexahedron2.A.z;
            pV[1].x = Hexahedron2.B.x; pV[1].y = Hexahedron2.B.y; pV[1].z = Hexahedron2.B.z;
            pV[2].x = Hexahedron2.C.x; pV[2].y = Hexahedron2.C.y; pV[2].z = Hexahedron2.C.z;
            pV[3].x = Hexahedron2.D.x; pV[3].y = Hexahedron2.D.y; pV[3].z = Hexahedron2.D.z;
            pV[4].x = Hexahedron2.E.x; pV[4].y = Hexahedron2.E.y; pV[4].z = Hexahedron2.E.z;
            pV[5].x = Hexahedron2.H.x; pV[5].y = Hexahedron2.H.y; pV[5].z = Hexahedron2.H.z;
            pV[6].x = Hexahedron2.G.x; pV[6].y = Hexahedron2.G.y; pV[6].z = Hexahedron2.G.z;
            pV[7].x = Hexahedron2.F.x; pV[7].y = Hexahedron2.F.y; pV[7].z = Hexahedron2.F.z;
            
            pVertex->Unlock();
        }

		Draw(0.5f, 0.5f, 0.5f);

#endif
#ifdef QSPHERE

        D3DXMATRIX transformation, translation, scaling;

        D3DXMatrixTranslation(&translation, Sphere1.Center.x, Sphere1.Center.y, Sphere1.Center.z);
        D3DXMatrixScaling(&scaling, Sphere1.Radius, Sphere1.Radius, Sphere1.Radius);
        transformation = scaling * translation;
        DrawMesh(0.5f, 1.0f, 0.2f, transformation, pSphereMesh);

        
        D3DXMatrixTranslation(&translation, Sphere2.Center.x, Sphere2.Center.y, Sphere2.Center.z);
        D3DXMatrixScaling(&scaling, Sphere2.Radius, Sphere2.Radius, Sphere2.Radius);
        transformation = scaling * translation;
        DrawMesh(1.0f, 0.0f, 0.5f, transformation, pSphereMesh);

#endif

        // Axis
        // ----------
        // X
        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = -20.0f; pV[0].y = 0.001f;  pV[0].z = 0.001f;
            pV[1].x = -20.0f; pV[1].y = 0.001f;  pV[1].z = -0.001f;
            pV[2].x = -20.0f; pV[2].y = -0.001f; pV[2].z = -0.001f;
            pV[3].x = -20.0f; pV[3].y = -0.001f; pV[3].z = 0.001f;
            pV[4].x = 20.0f;  pV[4].y = 0.001f;  pV[4].z = 0.001f;
            pV[5].x = 20.0f;  pV[5].y = 0.001f;  pV[5].z = -0.001f;
            pV[6].x = 20.0f;  pV[6].y = -0.001f; pV[6].z = -0.001f;
            pV[7].x = 20.0f;  pV[7].y = -0.001f; pV[7].z = 0.001f;
            
            pVertex->Unlock();
        }

        Draw(1.0f, 0.0f, 0.0f);

        // Y
        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = -0.001f; pV[0].y = 20.0f;  pV[0].z = 0.001f;
            pV[1].x = -0.001f; pV[1].y = 20.0f;  pV[1].z = -0.001f;
            pV[2].x = -0.001f; pV[2].y = -20.0f; pV[2].z = -0.001f;
            pV[3].x = -0.001f; pV[3].y = -20.0f; pV[3].z = 0.001f;
            pV[4].x = 0.001f;  pV[4].y = 20.0f;  pV[4].z = 0.001f;
            pV[5].x = 0.001f;  pV[5].y = 20.0f;  pV[5].z = -0.001f;
            pV[6].x = 0.001f;  pV[6].y = -20.0f; pV[6].z = -0.001f;
            pV[7].x = 0.001f;  pV[7].y = -20.0f; pV[7].z = 0.001f;
            
            pVertex->Unlock();
        }

        Draw(1.0f, 0.0f, 0.0f);

        // Z
        if( SUCCEEDED( pVertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD) ) )
        {
            pV[0].x = -0.001f; pV[0].y = 0.001f;  pV[0].z = 20.0f;
            pV[1].x = -0.001f; pV[1].y = 0.001f;  pV[1].z = -20.0f;
            pV[2].x = -0.001f; pV[2].y = -0.001f; pV[2].z = -20.0f;
            pV[3].x = -0.001f; pV[3].y = -0.001f; pV[3].z = 20.0f;
            pV[4].x = 0.001f;  pV[4].y = 0.001f;  pV[4].z = 20.0f;
            pV[5].x = 0.001f;  pV[5].y = 0.001f;  pV[5].z = -20.0f;
            pV[6].x = 0.001f;  pV[6].y = -0.001f; pV[6].z = -20.0f;
            pV[7].x = 0.001f;  pV[7].y = -0.001f; pV[7].z = 20.0f;
            
            pVertex->Unlock();
        }

		Draw(1.0f, 0.0f, 0.0f);



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
	float fOrigenZ = fAlto / -2.0f;


	CGizmo::CVerticeGizmo* v = 0;
	gizmo.pVB->Lock(0, 0, (void**)&v, 0);

	// Lineas verticales | | | | |
	int j = 0;

	for(j = 0; j < (nColumnas+1) * nFilas * 2; j += 2)
	{
		v[j].x = fOrigenX + (float)((j/2) % (nColumnas+1))* fTamC;
		v[j].z = fOrigenZ + (float)((j/2) / (nColumnas+1))* fTamF;
		v[j].y = 0;
		v[j].color = color;

		v[j+1].x = fOrigenX + (float)(((nColumnas+1)+j/2) % (nColumnas+1))* fTamC;
		v[j+1].z = fOrigenZ + (float)(((nColumnas+1)+j/2) / (nColumnas+1))* fTamF;
		v[j+1].y = 0;
		v[j+1].color = color;
	}

	// Lineas horizontales -- -- --

	for(int k = j; k < gizmo.m_nNumLineas*2; k += 2)
	{
		v[k].x = fOrigenX + (float)(((k-j)/2 + ((k-j)/2)/nColumnas) % (nColumnas+1))* fTamC;
		v[k].z = fOrigenZ + (float)(((k-j)/2 + ((k-j)/2)/nColumnas) / (nColumnas+1))* fTamF;
		v[k].y = 0;
		v[k].color = color;

		v[k+1].x = fOrigenX + (float)(((k-j)/2 + ((k-j)/2)/nColumnas +1) % (nColumnas+1))* fTamC;
		v[k+1].z = fOrigenZ + (float)(((k-j)/2 + ((k-j)/2)/nColumnas +1) / (nColumnas+1))* fTamF;
		v[k+1].y = 0;
		v[k+1].color = color;
	}

	gizmo.pVB->Unlock();
}

#endif