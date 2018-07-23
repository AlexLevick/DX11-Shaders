// Light shader.h
// Basic single light shader setup
#ifndef _LIGHTSHADERP_H_
#define _LIGHTSHADERP_H_

#include "BaseShader.h"
#include "light.h"
#include <vector>

#define NUM_LIGHTS 1

using namespace std;
using namespace DirectX;


class LightShaderP : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse[NUM_LIGHTS];
		XMFLOAT4 ambient[NUM_LIGHTS];
		XMFLOAT4 position[NUM_LIGHTS];
	};

	

public:

	LightShaderP(ID3D11Device* device, HWND hwnd);
	~LightShaderP();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, std::vector<Light*> light);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
};

#endif