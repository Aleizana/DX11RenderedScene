#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"
#include "ShaderColorLightTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;		//Need to delete this later

	size_t pixel_width;

	//Replace these two with UREP and VREP later
	int terrainWidth;	//Saving the terrain width, V VALUE
	int terrainLength; //Saving terrain length, U VALUE

	int triCount;	//((n - 1) ^ 2) * 2

	Vect terrainNorm(Vect center, Vect north, Vect west, Vect SW, Vect south, Vect east, Vect NE);
	Vect faceNorm(Vect bRight, Vect bLeft, Vect top);

	Texture* myTex;

	ShaderColorLightTex* pShader;

public:
	TerrainModel(ID3D11Device* dev, ShaderColorLightTex* newShader, LPCWSTR heightmapFile, int len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	TerrainModel();

	~TerrainModel();

	void Render(ID3D11DeviceContext* context, Matrix worl);

	void setTex(Texture* newTex);

	//Self added functions
	int TexelIndex(int side, int i, int j) const;
	int VertIndex(int side, int i, int j) const;
};



#endif _TerrainModel