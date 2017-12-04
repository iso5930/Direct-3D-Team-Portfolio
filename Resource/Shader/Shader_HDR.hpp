float4 g_vSampleOffest[9];
float4 g_vLumOffSets[4];
float4 g_vDownSamplerOffset[16];

float g_fThreshold;

float g_fBloomWeights[9];
float g_fBloomOffset[9];

float g_fExposure;
float g_fGaussianScalar;
float g_fBloom_w;
float g_fBloom_h;

texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture = g_SceneTexture;
};

texture g_HDRTexture;
sampler HDRSampler = sampler_state
{
	texture = g_HDRTexture;
	minfilter = linear;
	magfilter = linear;
};

texture g_LumTexture;
sampler LumSampler = sampler_state
{
	texture = g_LumTexture;
	minfilter = linear;
	magfilter = linear;
};

texture g_BloomTexture;
sampler BloomSampler = sampler_state
{
	texture = g_BloomTexture;
	minfilter = linear;
	magfilter = linear;
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

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	Out.vPosition	= In.vPosition;
	Out.vTexUV		= In.vTexUV;

	return Out;
}

struct PS_IN
{
	float2 vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	float4 vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float fAverage = 0.f;
	float fMax = -1e20;
	float4 vColor = 0.f;
	float3 vWeight = float3(0.299f, 0.587f, 0.114f);

	for(int i = 0; i < 4; ++i)
	{
		vColor = tex2D(SceneSampler, In.vTexUV + float2(g_vLumOffSets[i].x, g_vLumOffSets[i].y));
		float fGrayValue = max(vColor.r, max(vColor.g, vColor.b));

		fMax = max(fMax, fGrayValue);
		fAverage += (0.25f * log(1e-5 + fGrayValue));
	}

	fAverage = exp(fAverage);

	Out.vColor = float4(fAverage, fMax, 0.f, 1.f);
	
	return Out;
}

PS_OUT Pass1_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;
	
	float4 vColor = 0.f;
	float fMAX = -1e20;
	float fAverage = 0.f;

	for(int i = 0; i < 9; i++)
	{
		vColor = tex2D(SceneSampler, In.vTexUV + float2(g_vSampleOffest[i].x, g_vSampleOffest[i].y));
		fAverage += vColor.r;
		fMAX = max(fMAX, vColor.g);
	}

	fAverage /= 9.f;
	
	Out.vColor = float4(fAverage, fMAX, 0.f, 1.f);
	
	return Out;
}

PS_OUT Pass2_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vAverage = 0.f;

	for(int i = 0; i < 4; ++i)
	{
		vAverage += tex2D(SceneSampler, In.vTexUV + float2(g_vDownSamplerOffset[i].x, g_vDownSamplerOffset[i].y));
	}

	vAverage *= 0.25f;

	float fLuminance = max(vAverage.r, max(vAverage.g, vAverage.b));

	if(fLuminance < g_fThreshold)
	{
		vAverage = float4(0.f, 0.f, 0.f, 1.f);
	}

	Out.vColor = vAverage;

	return Out;
}

PS_OUT Pass3_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vAverage = float4(0.f, 0.f, 0.f, 0.f);

	for(int i = 0; i < 16; i++)
	{
		vAverage += tex2D(SceneSampler, In.vTexUV + float2(g_vDownSamplerOffset[i].x, g_vDownSamplerOffset[i].y));
	}

	vAverage *= (1.f / 16.f);

	Out.vColor = vAverage;

	return Out;
}

PS_OUT Pass4_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;
	
	float4 vColor = 0.f;

	for(int i = 0; i < 9; ++i)
	{
		vColor += (tex2D(SceneSampler, In.vTexUV + float2(g_fBloomOffset[i], 0.f)) * g_fBloomWeights[i]);
	}

	Out.vColor = float4(vColor.rgb, 1.f);

	return Out;
}

PS_OUT Pass5_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vColor = 0.f;

	for(int i = 0; i < 9; ++i)
	{
		vColor += (tex2D(SceneSampler, In.vTexUV + float2(0.f, g_fBloomOffset[i])) * g_fBloomWeights[i]);
	}

	Out.vColor = float4(vColor.rgb, 1.f);

	return Out;
}


PS_OUT Pass6_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vHDR = tex2D(HDRSampler, In.vTexUV);
	float4 vLum = tex2D(LumSampler, In.vTexUV);

	float fWeight_X = frac(In.vTexUV.x / g_fBloom_w) - 0.5f;
	float fDir_X = fWeight_X;
	fWeight_X = abs(fWeight_X);
	fDir_X /= fWeight_X;
	fDir_X *= g_fBloom_w;

	float fWeight_Y = frac(In.vTexUV.y / g_fBloom_h) - 0.5f;
	float fDir_Y = fWeight_Y;
	fWeight_Y = abs(fWeight_Y);
	fDir_Y /= fWeight_Y;
	fDir_Y *= g_fBloom_h;

	float4 vBloom = ((1.f - fWeight_X) * (1.f - fWeight_Y)) * tex2D(BloomSampler, In.vTexUV);
	vBloom += fWeight_X * (1.f - fWeight_Y) * tex2D(BloomSampler, In.vTexUV + float2(fDir_X, 0.f));
	vBloom += fWeight_Y * (1.f - fWeight_X) * tex2D(BloomSampler, In.vTexUV + float2(0.f, fDir_Y));
	vBloom += (fWeight_X * fWeight_Y) * tex2D(BloomSampler, In.vTexUV + float2(fDir_X, fDir_Y));

	float4 vColor = vHDR + 0.25f * vBloom;

	float Lp = (g_fExposure / vLum.r) * max(vColor.r, max(vColor.g, vColor.b));
	float LmSqr = (vLum.g + g_fGaussianScalar * vLum.g) * (vLum.g + g_fGaussianScalar * vLum.g);

	float fToneScalar = (Lp * (1.f + (Lp / (LmSqr)))) / (1.f + Lp);

	vHDR = vColor * fToneScalar;

	vHDR.a = 1.f;

	Out.vColor = vHDR;

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

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
	
	pass Pass1
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}

	pass Pass2
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass2_PS_MAIN();
	}

	pass Pass3
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass3_PS_MAIN();
	}

	pass Pass4
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass4_PS_MAIN();
	}

	pass Pass5
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass5_PS_MAIN();
	}

	pass Pass6
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 Pass6_PS_MAIN();
	}	
};