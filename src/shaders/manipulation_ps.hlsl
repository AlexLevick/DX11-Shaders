// Light pixel shader
// Calculate ambient and diffuse lighting for a single light (also texturing)

Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

#define NUM_LIGHTS 1

cbuffer LightBuffer : register(cb0)
{
	float4 diffuseColour[NUM_LIGHTS];
	float4 ambientColour[NUM_LIGHTS];
	float4 position[NUM_LIGHTS];
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 position3D : TEXCOORD2;
};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float3 lightDir[4];
	float lightIntensity[4];
	float4 colour[4];
	float4 finalColour = float4(0, 0, 0, 0);
	float3 lightposition[4];

	// Sample the pixel color from the texture using the sampler at this texture 	coordinate location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);

	// Set the default output color to the ambient light value for all pixels.
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		lightposition[i].x = position[i].x;
		lightposition[i].y = position[i].y;
		lightposition[i].z = position[i].z;

		colour[i] = ambientColour[i];

		// Invert the light direction for calculations.
		lightDir[i] = normalize(input.position3D - position[i]);

		// Calculate the amount of light on this pixel.
		lightIntensity[i] = saturate(dot(input.normal, -lightDir[i]));

		if (lightIntensity[i] > 0.0f)
		{
			// Determine the final diffuse color based on the diffuse color and the amount 	of light intensity.
			colour[i] += (diffuseColour[i] * lightIntensity[i]);

			// Saturate the ambient and diffuse color.
			colour[i] = saturate(colour[i]);
		}

		finalColour += colour[i];
	}

	// Multiply the texture pixel and the final diffuse colour

	finalColour = saturate(finalColour) *textureColour;

	return finalColour;
}
