//#ifndef _ShaderTexture
//#define _ShaderTexture

#include "ShaderBase.h"
#include "DirectXTex.h"

#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(ID3D11Device* device);
	~ShaderTexture();

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	//For changing textures
	void SetTextureResourceAndSampler(Texture* tex);

	//Sending data to constant buffers
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderTexture::SendWorld(const Matrix& world);

private:
	// add your own material

	//Constant buffer data
	ID3D11Buffer* mpcbViewProj;

	struct ViewProjData
	{
		Matrix mView;
		Matrix mProjection;
	};

	ID3D11Buffer* mpcbWorld;

	struct WorldData
	{
		Matrix World;
		// The texture might change too, but that's done through mpTextureRV
	};
};

//#endif _ShaderTexture