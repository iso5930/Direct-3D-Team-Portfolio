float4 g_vViewRightTop;
//float4 g_vFog = float4(0.33f, 8000.f, 1000.f, 0.f);  //지수, 지수 제곱 안개
float4 g_vFog = float4(0.05f, 8000.f, 1000.f, 0.f);  //높이 안개
//float4 g_vColorFog = float4(0.25f, 0.25f, 0.5f, 0.5f);
float4 g_vColorFog = float4(0.25f, 0.25f, 0.5f, 0.2f);

float4 g_vCameraPos;

float4x4 g_mInvView;

texture	g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
	minfilter = linear;
	magfilter = linear;
};

texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture = g_SceneTexture;
	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Output;

	Output.vPosition = In.vPosition;
	Output.vTexUV = In.vTexUV;
	Output.vClipPosition = In.vPosition;

	return Output;
}

struct PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct PS_OUT
{
	float4 vColor : COLOR0;
};

PS_OUT PS_MAIN_EXPONENT_FOG(PS_IN In)
{
	PS_OUT Out;
	
	//DepthUV 
	float2 vDepthUV = In.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	//Depth
	float fDepth = tex2D(NormalSampler, vDepthUV).w;

	//ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	float4 vViewPos = float4(vViewRay * fDepth, 1.f);

	//Fog
	float fDensity = g_vFog.x;
	float fFogEnd = g_vFog.y;

	float fDist = vViewPos.z / fFogEnd * 10.f;

	float f = exp(-fDist * fDensity);
	
	float4 vColor = tex2D(SceneSampler, In.vTexUV);

	Out.vColor = lerp(g_vColorFog, vColor, f);

	return Out;	
}

PS_OUT PS_MAIN_EXPONENT_SQUARE_FOG(PS_IN In)
{
 	PS_OUT Out;
 
 	//DepthUV 
 	float2 vDepthUV = In.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
 
 	//Depth
 	float fDepth = tex2D(NormalSampler, vDepthUV).w;
 
 	//ViewRay
 	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);
 
 	float4 vViewPos = float4(vViewRay * fDepth, 1.f);
 
 	float fDensity = g_vFog.x;
 	float fFogEnd = g_vFog.y;
 	
 	//float fDistance = distance(vViewPos, g_vCameraPos);
 
 	float fDist = vViewPos.z / fFogEnd * 10.f;
 
 	float f = exp(-(fDist * fDensity) * (fDist * fDensity));
 
 	float4 vColor = tex2D(SceneSampler, In.vTexUV);
 
 	Out.vColor = lerp(g_vColorFog, vColor, f);
 
 	return Out;
}

PS_OUT PS_MAIN_LAYER_FOG(PS_IN In)
{
	PS_OUT Out;

	//DepthUV 
	float2 vDepthUV = In.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	//Depth
	float fDepth = tex2D(NormalSampler, vDepthUV).w;

	//ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	//ViewPos
	float4 vViewPos = float4(vViewRay * fDepth, 1.f);

	//WorldPos
	float4 vWorldPos = mul(vViewPos, g_mInvView);

	float fFogEnd = g_vFog.y; //End 값
	float fFogTop = g_vFog.z; //높이 상수 값

	float fFogRange = g_vFog.z;

	float4 vCameraProj, vWorldProj;

	vCameraProj = g_vCameraPos;
	vCameraProj.y = 0.f;

	vWorldProj = vWorldPos;
	vWorldProj.y = 0.f;

	float fDeltaD = distance(vCameraProj, vWorldProj) / fFogEnd * 2.f;
	
	float fDeltaY, fDensityIntegral = 0.f;

	if(g_vCameraPos.y >= fFogTop) //카메라의 상단이 안개 상단보다 높을때
	{
		if(vWorldPos.y < fFogTop) //월드 정점이 안개 상단보다 낮을때
		{
			fDeltaY = (fFogTop - vWorldPos.y) / fFogRange * 2.f;
			fDensityIntegral = (fDeltaY * fDeltaY * g_vFog.x);
		}
		else
		{
			fDeltaY = 0.f;
			fDensityIntegral = 0.f;
		}
	}
	else //월드 정점이 안개의 상단보다 낮을때.
	{
		if(vWorldPos.y < fFogTop)
		{
			float fDeltaA = (fFogTop - g_vCameraPos.y) / fFogRange * 2.f;
			float fDeltaB = (fFogTop - vWorldPos.y) / fFogRange * 2.f;

			fDeltaY = abs(fDeltaA - fDeltaB);

			fDensityIntegral = abs((fDeltaA * fDeltaA * g_vFog.x) - (fDeltaB * fDeltaB * g_vFog.x));
		}
		else
		{
			fDeltaY = abs(fFogTop - g_vCameraPos.y) / fFogRange * 2.f;
			fDensityIntegral = abs(fDeltaY * fDeltaY * g_vFog.x);
		}
	}

	float fDensity = 0.f;

	if(fDeltaY != 0.f)
	{
		fDensity = sqrt((1.f + ((fDeltaD / fDeltaY) * (fDeltaD / fDeltaY)))) * fDensityIntegral;
	}
	
	float f = exp(-fDensity);

	float4 vColor = tex2D(SceneSampler, In.vTexUV);

	Out.vColor = lerp(g_vColorFog, vColor, f);
	
	return Out;
}

technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_EXPONENT_FOG();
	}

	pass Pass1
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_EXPONENT_SQUARE_FOG();
	}

	pass Pass2
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x00000080;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_LAYER_FOG();
	}
};