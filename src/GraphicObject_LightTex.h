#ifndef _GraphicObject_LightTex
#define _GraphicObject_LightTex

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "Matrix.h"
#include "ShaderColorLightTex.h"
#include "Camera.h"
#include "Texture.h"

class GraphicObject_LightTex : public GraphicObject_Base
{

public:
	GraphicObject_LightTex(const GraphicObject_LightTex&) = delete;				 // Copy constructor
	GraphicObject_LightTex(GraphicObject_LightTex&&) = default;                    // Move constructor
	GraphicObject_LightTex& operator=(const GraphicObject_LightTex&) & = default;  // Copy assignment operator
	GraphicObject_LightTex& operator=(GraphicObject_LightTex&&) & = default;       // Move assignment operator
	~GraphicObject_LightTex();		  											 // Destructor

	GraphicObject_LightTex() = delete;

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* _tex);
	void SetMyModel(Model* _mod);
	void SetMyPlane(FlatPlane* plane);

	void SetModelWorldTex(Model* _mod, const Matrix& m, Texture* _tex);

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);

	virtual void Render() override;

	//void Render(ID3D11DeviceContext* devcon, Camera mCam, const Vect& ambWRLD, const Vect& difWRLD, const Vect& spWRLD);
	void RenderModel(const Vect& ambWLRD = Vect(.5f, .5f, .5f), const Vect& difWLRD = Vect(.5f, .5f, .5f), const Vect& spWRLD = Vect(.5f, .5f, .5f));
	void RenderPlane(const Vect& ambWLRD = Vect(.5f, .5f, .5f), const Vect& difWLRD = Vect(.5f, .5f, .5f), const Vect& spWRLD = Vect(.5f, .5f, .5f));
	void SendCamLight(ID3D11DeviceContext* devcon, Camera mCam);

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int lightIndex, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	//Defaulted to completely transparent fog
	void SendFogParameters(float _start = 0.0f, float _range = 0.0f, const Vect& col = Vect(0.0f, 0.0f, 0.0f, 0.0f));

	//Regular model
	GraphicObject_LightTex(ShaderColorLightTex* shader, Model* mod, Texture* _tex);

	//Flatplane model
	GraphicObject_LightTex(ShaderColorLightTex* shader, FlatPlane* plane, Texture* _tex);

private:
	ShaderColorLightTex* pShader;
	Matrix World;
	Texture* pTex;

	Vect* MeshColors;

	Vect eyepos;
};

#endif _GraphicObject_LightTex
