// Light shader.h
// Basic single light shader setup
#ifndef _LIGHTSHADERS_H_
#define _LIGHTSHADERS_H_

#include "BaseShader.h"
#include "light.h"
#include "Camera.h"

using namespace std;
using namespace DirectX;


class LightShaderS : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT3 direction;
		float specularPower;
		XMFLOAT4 specularColour;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

public:

	LightShaderS(ID3D11Device* device, HWND hwnd);
	~LightShaderS();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light, Camera* camera);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;
};

#endif