texture g_DepthTexture;
sampler DepthSampler = sampler_state
{
	texture = g_DepthTexture;
};

texture g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
};

texture g_BlurTexture;
sampler BlurSampler = sampler_state
{
	texture = g_BlurTexture;
};

texture g_SceneTexure;
sampler SceneSampler = sampler_state
{
	texture = g_SceneTexure;
};

float3 GetRandomNormal(float2 _vTex)
{
	float fNoiseX = (frac(sin(dot(_vTex, float2(15.8989f, 76.132f) * 1.0f)) * 46336.23745f)); 
	float fNoiseY = (frac(sin(dot(_vTex, float2(11.9899f, 62.223f) * 2.0f)) * 34748.34744f)); 
	float fNoiseZ = (frac(sin(dot(_vTex, float2(13.3238f, 63.122f) * 3.0f)) * 59998.47362f)); 

	float3 fResult = float3(fNoiseX, fNoiseY, fNoiseZ);

	fResult = normalize(fResult);

	return fResult;
}

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
	
	int iSamples = 16;
	float fSamplerRadius = 0.00005f;
	float fStrength = 1.f;
	float fTotalStrength = 3.f;
	float fFalloffMin = 0.00001f;
	float fFalloffMax = 0.006f;

	float3 fSampleSphere[] = 
	{
		float3( 0.2024537f, 0.841204f, -0.9060141f),
		float3(-0.2200423f, 0.6282339f,-0.8275437f), 
		float3( 0.3677659f, 0.1086345f,-0.4466777f), 
		float3( 0.8775856f, 0.4617546f,-0.6427765f), 
		float3( 0.7867433f,-0.141479f, -0.1567597f), 
		float3( 0.4839356f,-0.8253108f,-0.1563844f), 
		float3( 0.4401554f,-0.4228428f,-0.3300118f), 
		float3( 0.0019193f,-0.8048455f, 0.0726584f), 
		float3(-0.7578573f,-0.5583301f, 0.2347527f), 
		float3(-0.4540417f,-0.252365f, 0.0694318f), 
		float3(-0.0483353f,-0.2527294f, 0.5924745f), 
		float3(-0.4192392f, 0.2084218f,-0.3672943f), 
		float3(-0.8433938f, 0.1451271f, 0.2202872f), 
		float3(-0.4037157f,-0.8263387f, 0.4698132f), 
		float3(-0.6657394f, 0.6298575f, 0.6342437f), 
		float3(-0.0001783f, 0.2834622f, 0.8343929f)
	}; 

	float3 fRandomNormal = GetRandomNormal(In.vTexUV);
	float fDepth = tex2D(DepthSampler, In.vTexUV);
	float3 fNormal = tex2D(NormalSampler, In.vTexUV);

	float fRadius = fSamplerRadius / fDepth;

	float3 fCenterPos = float3(In.vTexUV, fDepth);

	float fOcc = 0.f;

	for(int i = 0; i < iSamples; ++i)
	{
		float3 fOffset = reflect(fSampleSphere[i], fRandomNormal);
		fOffset = sign(dot(fOffset, fNormal)) * fOffset;
		fOffset.y = -fOffset.y;

		float3 fRay = fCenterPos + fRadius * fOffset;

		if((saturate(fRay.x) != fRay.x) || (saturate(fRay.y) != fRay.y))
		{
			continue;
		}

		float fOccDepth = tex2D(DepthSampler, fRay.xy);
		float fOccNormal = tex2D(NormalSampler, fRay.xy);

		float fDepthDifference = fCenterPos.z - fOccDepth;
		float fNormalDifference = dot(fOccNormal, fNormal);

		float fNormalOcc = 1.f - saturate(fNormalDifference);
		float fDepthOcc = step(fFalloffMin, fDepthDifference)
		fDepthOcc = fDepthOcc * (1.f - smoothstep(fFalloffMin, fFalloffMax, fDepthDifference));

		fOcc += saturate(fDepthOcc * fNormalOcc * fStrength);
	}

	fOcc /= iSamples;
	
	Out.vColor = saturate(pow(1.f - fOcc, fTotalStrength));
	
	return Out;
}

PS_OUT Pass1_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	int iNumSamples = 9;
	float fTexelSize = 1.f / 1280.f;//(WINCX)
	float fSamplerOffset[9] = { -8.f, -6.f, -4.f, -2.f, 0.f, 2.f, 4.f, 6.f, 8.f };

	float fCompareDepth = tex2D(DepthSampler, In.vTexUV).r;

	float fResult = 0.f;
	float fWeightSum = 0.f;

	for(int i = 0; i < iNumSamples; ++i)
	{
		float2 vSampleOffset = float2(fTexelSize * fSamplerOffset[i], 0.f);
		float2 vSamplePos = In.vTexUV + vSampleOffset;

		float fSampleDepth = tex2D(DepthSampler, In.vTexUV).r;

		float fWeight = 1.f / 0.0001f + abs(fCompareDepth - fSampleDepth);

		fResult += tex2D(BlurSampler, vSamplePos).r * fWeight;

		fWeightSum += fWeight;
	}

	fResult /= fWeightSum;

	Out.vColor = fResult;

	return Out;
}

PS_OUT Pass2_PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vSceneColor = tex2D(SceneSampler, In.vTexUV);
	float4 vSSAOColor = tex2D(BlurSampler, In.vTexUV);

	Out.vColor.rgb = vSceneColor.rgb * vSSAOColor.rgb;
	Out.vColor.a = vSceneColor.a;
	
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
}