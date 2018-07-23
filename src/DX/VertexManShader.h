// Light shader.h
// Basic single light shader setup
#ifndef _VERTEXMANSHADER_H_
#define _VERTEXMANSHADER_H_

#include "BaseShader.h"
#include "light.h"
#include <vector>

using namespace std;
using namespace DirectX;

#define NUM_LIGHTS 1

class VertexManShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse[NUM_LIGHTS];
		XMFLOAT4 ambient[NUM_LIGHTS];
		XMFLOAT4 position[NUM_LIGHTS];
	};

	struct TimeBufferType
	{
		float time;
		float height;
		float frequency;
		float padding;
	};

public:
	float dt;

	VertexManShader(ID3D11Device* device, HWND hwnd);
	~VertexManShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, std::vector<Light*> light, float time);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_timeBuffer;
};

#endif