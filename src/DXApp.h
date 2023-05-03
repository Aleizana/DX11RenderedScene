// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColorLightTex.h"
#include "GraphicObject_LightTex.h"
#include "TerrainModel.h"
#include "SkyBox.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class ShaderColorLightTex;
class GraphicObject_LightTex;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	ID3D11RasterizerState* FrontFaceAsCCWRS;

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	Model* pModel1;
	Matrix mWorld1;	

	//Tree
	Model* treeMod;
	//Tiny Tree
	Model* treeTinyMod;
	Matrix treeMat1;
	Matrix treeMatLeft;
	Matrix treeMatBack;
	Matrix treeMatRight;
	Matrix treeTinyMatForward;
	Matrix treeTinyMatLeft;
	Matrix treeTinyMatBack;
	Matrix treeTinyMatRight;
	float treeOff;
	Texture* treeTex;

	//Lantern
	Model* lanternMod;
	Matrix lanWorld;
	Matrix tempLan;
	Vect lightMove;

	Model* stickMod;
	Matrix stickWorld;
	//Lantern textures
	Texture* lanTex;
	Texture* stickTex;

	//Bridge
	Matrix mWorld2;
	Matrix leftBridge;

	//Platform
	Model* pModel3;
	Matrix mWorld3;
	Matrix leftPlatform;

	//Crate Texture
	Model* pModel2;
	Texture* crateTex;
	Matrix crateWorld1;
	Matrix crateWorld2;
	Matrix crateWorld3;
	Matrix crateWorld4;

	//Pyramid
	Model* pyrMod;
	Matrix pyrWorld1;
	Matrix pyrWorld2;

	//Columns
	Model* columnModel;
	Model* twoLogs;
	Matrix rightPlat1;
	Matrix rightPlat2;
	Matrix leftPlat1;
	Matrix leftPlat2;

	Matrix colCabin1;
	Matrix colCabin2;
	Matrix colCabin3;
	Matrix colCabin4;
	Matrix colCabin5;
	Matrix colCabin6;

	FlatPlane* pPlane;
	Matrix planeMat1;
	Matrix planeMat2;

	ShaderTexture*			pShaderTex;
	ShaderColorLightTex* pShaderColLightTex;

	GraphicObject_LightTex* GraphObj1;

	Texture*				pTex1;
	Texture*				pTex2;
	Texture*				pTex3;
	Texture* columnTex;
	Texture* twoLogTex;

	//Terrain, ground floor
	TerrainModel* pTerrain;
	Matrix terrainWorld;
	Texture* terrainTex;

	//Water
	FlatPlane* waterMod;
	Matrix waterWorld;
	Texture* waterTex;

	//Skybox
	SkyBox* boxSky;
	Texture* skyTex;
	Matrix skyWorld;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp