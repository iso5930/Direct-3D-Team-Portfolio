float g_fFar;

float4 g_vColor;
float4 g_vRimColor;
float4 g_vCameraPos;

float4x4 g_mWorld;
float4x4 g_mViewProj;

int g_iInfluenceMax;

texture	g_DiffuseTexture;
sampler DiffuseSampler = sampler_state
{
	texture	= g_DiffuseTexture;
};

texture g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture	= g_NormalTexture;
};

texture g_SpecularTexture;
sampler SpecularSampler = sampler_state
{
	texture	= g_SpecularTexture;
};

texture g_SkinningTexture;
sampler SkinningSampler = sampler_state
{
	texture	= g_SkinningTexture;
};

float4x4 GetSkinMatrix(int idx)
{
	float4 uvCol = float4(((float)((idx % 16) * 4) + 0.5f) / 64.0f, ((float)((idx / 16)) + 0.5f) / 64.0f, 0.0f, 0.0f);

	float4x4 mat = { tex2Dlod(SkinningSampler, uvCol),
		tex2Dlod(SkinningSampler, uvCol + float4(1.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(SkinningSampler, uvCol + float4(2.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(SkinningSampler, uvCol + float4(3.0f / 64.0f, 0, 0, 0)) };

	return mat;
}

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_INPUT
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float3 vTangent : TANGENT;
	float3 vBinormal : BINORMAL;
	float2 vTexUV : TEXCOORD0;
};

struct Pass0_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float3 T : TEXCOORD1;
	float3 B : TEXCOORD2;
	float3 N : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
	float4 vWorldPosition : TEXCOORD5;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vWorldPosition = Output.vPosition;
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// TBN
	Output.T = mul(Input.vTangent, (float3x3)g_mWorld);
	Output.B = mul(Input.vBinormal, (float3x3)g_mWorld);
	Output.N = mul(Input.vNormal, (float3x3)g_mWorld);

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass0_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float3 T : TEXCOORD1;
	float3 B : TEXCOORD2;
	float3 N : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
	float4 vWorldPosition : TEXCOORD5;
};

struct Pass0_PS_OUTPUT
{
	float4 vAlbedo : COLOR0;
	float4 vNormal : COLOR1;
	float4 vSpecular : COLOR2;
	float4 vDepth : COLOR3;
};

Pass0_PS_OUTPUT Pass0_PS_MAIN(Pass0_PS_INPUT Input)
{
	Pass0_PS_OUTPUT Output;

	// Depth
	float depth = Input.vClipPosition.z / g_fFar;
	Output.vDepth = float4(depth.xxx, 0.0f);

	// Albedo
	Output.vAlbedo = tex2D(DiffuseSampler, Input.vTexUV) * g_vColor;

	// Normal
	float3 vTangentNormal = tex2D(NormalSampler, Input.vTexUV).xyz;
	vTangentNormal = normalize(vTangentNormal * 2.0f - 1.0f);

	// TBN
	float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));

	// Normal
	Output.vNormal = float4(mul(vTangentNormal, TBN) * 0.5f + 0.5f, depth);

	// Specular
	Output.vSpecular = float4(tex2D(SpecularSampler, Input.vTexUV).rgb, 0.0f);

	//Rim

	float4 vWorldPos = Input.vWorldPosition;
	float4 vViewDir = normalize(g_vCameraPos - vWorldPos);

	half rim = 1.0 - saturate(dot(vViewDir, Input.N));
	float4 Emission = g_vRimColor * pow(rim, 2.f);

	Output.vAlbedo.rgb += Emission.rgb;

	//Rim

	return Output;
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_IN
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float3 vTangent : TANGENT;
	float3 vBinormal : BINORMAL;
	float2 vTexUV : TEXCOORD0;
	float4 vWeights : BLENDWEIGHT0;
	int4 vIndices : BLENDINDICES0;
};

struct Pass1_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float3 T : TEXCOORD1;
	float3 B : TEXCOORD2;
	float3 N : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
	float4 vWorldPosition : TEXCOORD5;
};

Pass1_VS_OUT Pass1_VS_MAIN(Pass1_VS_IN Input)
{
	Pass1_VS_OUT Output;

	float4 vPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float3 vTangent = float3(0.0f, 0.0f, 0.0f);
	float3 vBinormal = float3(0.0f, 0.0f, 0.0f);
	float3 vNormal = float3(0.0f, 0.0f, 0.0f);
	float lastWeight = 0.0f;
	int n = g_iInfluenceMax - 1;

	for(int i = 0; i < n; ++i)
	{
		lastWeight += Input.vWeights[i];
		vPosition += Input.vWeights[i] * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[i]));
		vTangent += Input.vWeights[i] * mul(Input.vTangent, (float3x3)GetSkinMatrix(Input.vIndices[i]));
		vBinormal += Input.vWeights[i] * mul(Input.vBinormal, (float3x3)GetSkinMatrix(Input.vIndices[i]));
		vNormal += Input.vWeights[i] * mul(Input.vNormal, (float3x3)GetSkinMatrix(Input.vIndices[i]));
	}

	lastWeight = 1.0f - lastWeight;
	vPosition += lastWeight * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[n]));
	vTangent += lastWeight * mul(Input.vTangent, (float3x3)GetSkinMatrix(Input.vIndices[n]));
	vBinormal += lastWeight * mul(Input.vBinormal, (float3x3)GetSkinMatrix(Input.vIndices[n]));
	vNormal += lastWeight * mul(Input.vNormal, (float3x3)GetSkinMatrix(Input.vIndices[n]));
	vPosition.w = 1.0f;

	// Position
	Output.vPosition = mul(vPosition, g_mWorld);
	Output.vWorldPosition = Output.vPosition;
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// TBN
	Output.T = mul(vTangent, (float3x3)g_mWorld);
	Output.B = mul(vBinormal, (float3x3)g_mWorld);
	Output.N = mul(vNormal, (float3x3)g_mWorld);

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass1_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float3 T : TEXCOORD1;
	float3 B : TEXCOORD2;
	float3 N : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
	float4 vWorldPosition : TEXCOORD5;
};

struct Pass1_PS_OUTPUT
{
	float4 vAlbedo : COLOR0;
	float4 vNormal : COLOR1;
	float4 vSpecular : COLOR2;
};

Pass1_PS_OUTPUT Pass1_PS_MAIN(Pass1_PS_INPUT Input)
{
	Pass1_PS_OUTPUT Output;

	// Depth
	float depth = Input.vClipPosition.z / g_fFar;

	// Albedo
	Output.vAlbedo = tex2D(DiffuseSampler, Input.vTexUV) * g_vColor;

	// Normal
	float3 vTangentNormal = tex2D(NormalSampler, Input.vTexUV).xyz;
	vTangentNormal = normalize(vTangentNormal * 2.0f - 1.0f);

	// TBN
	float3x3 TBN = float3x3(Input.T, Input.B, Input.N);
	//TBN = transpose(TBN);

	// Normal
	Output.vNormal = float4(mul(vTangentNormal, TBN) * 0.5f + 0.5f, depth);

	// Specular
	Output.vSpecular = float4(tex2D(SpecularSampler, Input.vTexUV).rgb, 0.0f);

	//Rim

	float4 vWorldPos = Input.vWorldPosition;
	float4 vViewDir = normalize(g_vCameraPos - vWorldPos);

	half rim = 1.0 - saturate(dot(vViewDir, Input.N));
	float4 Emission = g_vRimColor * pow(rim, 2.f);

	Output.vAlbedo.rgb += Emission.rgb;

	//Rim

	return Output;
}

// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0x000000e0;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}

	pass Pass1
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0x000000d0;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}
};