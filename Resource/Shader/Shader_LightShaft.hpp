float4 g_vLightShaftValue;
//x : 샘플링할수의 스케일값을 지정 이값을 키울경우 샘플사이의 간격을 줄여서 더 짧은 범위에 밝은 빛줄기를 만듬.
//y : 0 ~ 1 범위에서 각 샘플의 영향도를 광선이 광원으로 부터 진행하면서 분산시킨다.
//z : 각 샘플에 대한 강도.
//w : 포스트 프로세스의 전체 강도.

//Density
//Decay
//Weight
//Exposure

float4 g_vLightPos_WVP;
float4x4 g_matViewProj;

texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture	= g_SceneTexture;
};

struct VS_IN  
{
	float4 vPosition	: POSITION;
	float2 vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition	: POSITION;
	float2 vTexUV		: TEXCOORD0;
};

VS_OUT Pass0_VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	Out.vPosition	= In.vPosition;
	Out.vTexUV		= In.vTexUV;

	return Out;
}

struct PS_IN
{
	float2 vTexUV	: TEXCOORD0;
};

struct PS_OUT
{
	float4 vColor : COLOR0;
};

PS_OUT Pass0_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;
			
	int iNumSamples = 64;

	float4 vLightPos = mul(g_vLightPos_WVP, g_matViewProj);

	float2 vScreenLightPos = vLightPos.xy / vLightPos.w * 0.5f - 0.5f;
	vScreenLightPos.y = 1.f - vLightPos.y;

	float2 vDeltaTexCoord = In.vTexUV.xy - vScreenLightPos.xy;

	vDeltaTexCoord *= 1.f / iNumSamples * g_vLightShaftValue.x;

	float3 vColor = tex2D(SceneSampler, In.vTexUV);

	float flluminationDecay = 1.f;

	for(int i = 0; i < iNumSamples; ++i)
	{
		In.vTexUV -= vDeltaTexCoord;

		float3 vSample = tex2D(SceneSampler, In.vTexUV);

		vSample *= flluminationDecay * g_vLightShaftValue.z;

		vColor += vSample;

		flluminationDecay *= g_vLightShaftValue.y;
	}

	Out.vColor = saturate(float4(vColor * g_vLightShaftValue.w, 1.f));

	return Out;
}

technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}
}