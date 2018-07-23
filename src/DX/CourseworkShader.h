// Light shader.h
// Basic single light shader setup
#ifndef _COURSEWORKSHADER_H_
#define _COURSEWORKSHADER_H_

#include "BaseShader.h"
#include <vector>
#include "light.h"

#define NUM_LIGHTS 1

using namespace std;
using namespace DirectX;


class CourseworkShader : public BaseShader
{
private:
	struct TessellationBufferType
	{
		float tessellationFactor;
		XMFLOAT3 padding;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuse[NUM_LIGHTS];
		XMFLOAT4 ambient[NUM_LIGHTS];
		XMFLOAT4 position[NUM_LIGHTS];
	};

public:

	CourseworkShader(ID3D11Device* device, HWND hwnd);
	~CourseworkShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* gradient, ID3D11ShaderResourceView* normal, float tessFactor, std::vector<Light*> light);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_tessellationBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif