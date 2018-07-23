Texture2D heightTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D gradientTexture : register(t2);
SamplerState SampleType : register(s0);

cbuffer MatrixBuffer : register(cb0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct ConstantOutputType
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
};

struct InputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 position3D : TEXCOORD2;
	float3 gradient : TEXCOORD1;
};

[domain("tri")]

OutputType main(ConstantOutputType input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 3> patch)
{
	float3 vertexPosition;
	float3 normal;
	OutputType output;

	// Determine the position and tex coords of the new vertex.
	vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;
	output.tex = patch[0].tex * uvwCoord.x + patch[1].tex * uvwCoord.y + patch[2].tex * uvwCoord.z;

	float4 heightColour = heightTexture.SampleLevel(SampleType, output.tex, 0);
	float4 normalColour = normalTexture.SampleLevel(SampleType, output.tex, 0);

	// Determine normals from Normal Map
	normal.x = normalColour.x; 
	normal.y = -normalColour.y; 
	normal.z = normalColour.z;

	// Manipulate y value according to Height Map
	float heightValue = heightColour.x;
	vertexPosition.y = (heightValue * 1.f);

	// Calculate the position of the new vertex against the world, view, and projection matrices.
	output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// world position of vertex
	output.position3D = mul(output.position, worldMatrix);

	output.gradient = vertexPosition;

	return output;
}

