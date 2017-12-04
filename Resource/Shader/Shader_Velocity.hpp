float4x4 g_mCurWorld;
float4x4 g_mPreWorld;
float4x4 g_mCurViewProj;
float4x4 g_mPreViewProj;

int g_iInfluenceMax;

texture g_CurSkinningTexture;
sampler CurSkinningSampler = sampler_state
{
	texture	= g_CurSkinningTexture;
};

texture g_PreSkinningTexture;
sampler PreSkinningSampler = sampler_state
{
	texture	= g_PreSkinningTexture;
};

float4x4 GetCurSkinMatrix(int idx)
{
	float4 uvCol = float4(((float)((idx % 16) * 4) + 0.5f) / 64.0f, ((float)((idx / 16)) + 0.5f) / 64.0f, 0.0f, 0.0f);

	float4x4 mat = { tex2Dlod(CurSkinningSampler, uvCol),
		tex2Dlod(CurSkinningSampler, uvCol + float4(1.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(CurSkinningSampler, uvCol + float4(2.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(CurSkinningSampler, uvCol + float4(3.0f / 64.0f, 0, 0, 0)) };

	return mat;
}

float4x4 GetPreSkinMatrix(int idx)
{
	float4 uvCol = float4(((float)((idx % 16) * 4) + 0.5f) / 64.0f, ((float)((idx / 16)) + 0.5f) / 64.0f, 0.0f, 0.0f);

	float4x4 mat = { tex2Dlod(PreSkinningSampler, uvCol),
		tex2Dlod(PreSkinningSampler, uvCol + float4(1.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(PreSkinningSampler, uvCol + float4(2.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(PreSkinningSampler, uvCol + float4(3.0f / 64.0f, 0, 0, 0)) };

	return mat;
}

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_INPUT
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
};

struct Pass0_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vVeloUV : TEXCOORD1;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	float4 vCurPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 vPrePosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float3 vNormal = float3(0.0f, 0.0f, 0.0f);

	// To World
	vCurPosition = mul(Input.vPosition, g_mCurWorld);
	vPrePosition = mul(Input.vPosition, g_mPreWorld);
	float4 vWorldVelo = vCurPosition - vPrePosition;
	float3 vWorldNormal = mul(Input.vNormal, (float3x3)g_mCurWorld);

	// To Proj
	vCurPosition = mul(vCurPosition, g_mCurViewProj);
	vPrePosition = mul(vPrePosition, g_mPreViewProj);

	// Position
	if(dot(vWorldNormal, vWorldVelo.xyz) >= 0.0f)
		Output.vPosition = vCurPosition;
	else
		Output.vPosition = vPrePosition;

	// VeloUV
	Output.vVeloUV.xy = vCurPosition.xy / vCurPosition.w - vPrePosition.xy / vCurPosition.w;
	Output.vVeloUV.x *= 0.5f;
	Output.vVeloUV.y *= -0.5f;
	Output.vVeloUV.z = Output.vPosition.z;
	Output.vVeloUV.w = Output.vPosition.w;

	return Output;
}

struct Pass0_PS_INPUT
{
	float4 vVeloUV : TEXCOORD1;
};

float4 Pass0_PS_MAIN(Pass0_PS_INPUT Input) : COLOR
{
	return Input.vVeloUV;
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_INPUT
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float4 vWeights : BLENDWEIGHT0;
	int4 vIndices : BLENDINDICES0;
};

struct Pass1_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vVeloUV : TEXCOORD1;
};

Pass1_VS_OUTPUT Pass1_VS_MAIN(Pass1_VS_INPUT Input)
{
	Pass1_VS_OUTPUT Output;

	float4 vCurPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 vPrePosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float3 vNormal = float3(0.0f, 0.0f, 0.0f);
	float lastWeight = 0.0f;
	int n = g_iInfluenceMax - 1;

	for(int i = 0; i < n; ++i)
	{
		lastWeight += Input.vWeights[i];
		vCurPosition += Input.vWeights[i] * mul(Input.vPosition, GetCurSkinMatrix(Input.vIndices[i]));
		vPrePosition += Input.vWeights[i] * mul(Input.vPosition, GetPreSkinMatrix(Input.vIndices[i]));
		vNormal += Input.vWeights[i] * mul(Input.vNormal, (float3x3)GetCurSkinMatrix(Input.vIndices[i]));
	}

	lastWeight = 1.0f - lastWeight;
	vCurPosition += lastWeight * mul(Input.vPosition, GetCurSkinMatrix(Input.vIndices[n]));
	vPrePosition += lastWeight * mul(Input.vPosition, GetPreSkinMatrix(Input.vIndices[n]));
	vNormal += lastWeight * mul(Input.vNormal, (float3x3)GetCurSkinMatrix(Input.vIndices[n]));
	vCurPosition.w = 1.0f;
	vPrePosition.w = 1.0f;

	// To World
	vCurPosition = mul(vCurPosition, g_mCurWorld);
	vPrePosition = mul(vPrePosition, g_mPreWorld);
	float4 vWorldVelo = vCurPosition - vPrePosition;
	float3 vWorldNormal = mul(vNormal, (float3x3)g_mCurWorld);

	// To Proj
	vCurPosition = mul(vCurPosition, g_mCurViewProj);
	vPrePosition = mul(vPrePosition, g_mPreViewProj);

	// Position
	if(dot(vWorldNormal, vWorldVelo.xyz) >= 0.0f)
		Output.vPosition = vCurPosition;
	else
		Output.vPosition = vPrePosition;

	// VeloUV
	Output.vVeloUV.xy = vCurPosition.xy / vCurPosition.w - vPrePosition.xy / vCurPosition.w;
	Output.vVeloUV.x *= 0.5f;
	Output.vVeloUV.y *= -0.5f;
	Output.vVeloUV.z = Output.vPosition.z;
	Output.vVeloUV.w = Output.vPosition.w;

	return Output;
}

struct Pass1_PS_INPUT
{
	float4 vVeloUV : TEXCOORD1;
};

float4 Pass1_PS_MAIN(Pass1_PS_INPUT Input) : COLOR
{
	return Input.vVeloUV;
}

////////////////////////////////////////////////////////////////////////// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

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

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}
};