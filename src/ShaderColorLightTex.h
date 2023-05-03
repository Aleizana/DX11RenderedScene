#ifndef _ShaderColorLightTex
#define _ShaderColorLightTex

#include "ShaderBase.h"
#include "Matrix.h"
#include "DirectXTex.h"
#include <Windows.h>
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColorLightTex : public ShaderBase
{

public:
	ShaderColorLightTex(const ShaderColorLightTex&) = delete;				 // Copy constructor
	ShaderColorLightTex(ShaderColorLightTex&&) = default;                    // Move constructor
	ShaderColorLightTex& operator=(const ShaderColorLightTex&) & = default;  // Copy assignment operator
	ShaderColorLightTex& operator=(ShaderColorLightTex&&) & = default;       // Move assignment operator
	~ShaderColorLightTex();		  							         // Destructor

	//Constructor for only light
	//ShaderColorLightTex(ID3D11Device* device);

	//Try adjusting the HLSL file again next time.

	//Constructor for both light and texture
	ShaderColorLightTex(ID3D11Device* device, LPCWSTR filepath, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR, UINT isotropic_level = 1, bool ComputeMip = false, size_t miplevel = 0, DirectX::TEX_FILTER_FLAGS filterflags = DirectX::TEX_FILTER_LINEAR);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;
	void SetToContextSampler(ID3D11DeviceContext* devcon, int texResSlot, int sampSlot);

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int lightIndex, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	//Defaulted to completely transparent fog
	void SendFogParameters(float _start = 0.0f, float _range = 0.0f, const Vect& col = Vect(0.0f, 0.0f, 0.0f, 0.0f));


	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

	//For changing textures
	void SetTextureResourceAndSampler(Texture* tex);

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};



	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData[4];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight[4];
		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;

	//Texture devices for sampler and shader
	ID3D11ShaderResourceView* mpTextureRV;
	ID3D11SamplerState* mpSampler;

	//Fog data
	struct Data_FogParams
	{
		float fogStart;
		float fogRange;
		Vect fogColor;
	};

	ID3D11Buffer* mpBufferFogParams;
};

#endif _ShaderColorLightTex

