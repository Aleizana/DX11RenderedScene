#pragma once
#ifndef _Skybox
#define _Skybox

#include "Matrix.h"
#include "ShaderTexture.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
private:
	Model* pPlane;
	ShaderTexture* pShader;
	Texture* pTex;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;						// Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(ID3D11Device* dev, float len, Texture* newTex, ShaderTexture* newShader);

	void Render(ID3D11DeviceContext* context, Matrix world, Matrix view, Matrix proj);
};

#endif _Skybox