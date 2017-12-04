texture	g_AlbedoTexture;
sampler AlbedoSampler = sampler_state
{
	texture = g_AlbedoTexture;
	minfilter = linear;
	magfilter = linear;
};

texture	g_ShadeTexture;
sampler ShadeSampler = sampler_state
{
	texture = g_ShadeTexture;
	minfilter = linear;
	magfilter = linear;
};

texture	g_SpecularAccTexture;
sampler SpecularAccSampler = sampler_state
{
	texture = g_SpecularAccTexture;
	minfilter = linear;
	magfilter = linear;
};

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass0_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;
	Output.vClipPosition = Input.vPosition;

	return Output;
}

struct Pass0_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass0_PS_MAIN(Pass0_PS_INPUT Input) : COLOR0
{
	float4 vAlbedo = tex2D(AlbedoSampler, Input.vTexUV);
	float4 vShade = tex2D(ShadeSampler, Input.vTexUV);
	float4 vSpecularAcc = tex2D(SpecularAccSampler, Input.vTexUV);
	
	return (vAlbedo * vShade + vSpecularAcc);
}

////////////////////////////////////////////////////////////////////////// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}
};