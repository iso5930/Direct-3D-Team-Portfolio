float g_fFar;
float g_fAlpha;
float g_fTime;
float g_iInfluenceMax;
float g_fX;
float g_fY;
float g_fDetail;

float g_flameTime;
float3 g_vScrollSpeed = float3(1.3f, 2.1f, 2.3f);
float3 g_vScale = float3(1.f, 2.f, 3.f);

float2 g_vDir1 = float2(0.1f, 0.2f);
float2 g_vDir2 = float2(0.1f, 0.3f);
float2 g_vDir3 = float2(0.1f, 0.1f);

float g_vDirScale = 0.8f;
float g_vDirBias = 0.5f;

float4x4 g_mWorld;
float4x4 g_mViewProj;
float4x4 g_mProj;
float4x4 g_mInvView;
float4x4 g_mInvWorld;
float4x4 g_mView;

float4 g_vViewRightTop;
float4 g_vViewPosition;
float4 g_vLightPosition;

texture g_BaseTexture;
sampler BaseSampler = sampler_state
{
	texture	= g_BaseTexture;
};

texture g_DepthTexture;
sampler DepthSampler = sampler_state
{
	texture	= g_DepthTexture;
};

texture g_NormalDepthTexture;
sampler NormalDepthSampler = sampler_state
{
	texture	= g_NormalDepthTexture;
};

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

texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture = g_SceneTexture;
};

texture g_DistortionTexture;
sampler DistortionSampler = sampler_state
{
	texture = g_DistortionTexture;
};

texture g_EffectTexture;
sampler EffectSampler = sampler_state
{
	texture = g_EffectTexture;
};

texture g_AlphaTexture;
sampler AlphaSampler = sampler_state
{
	texture = g_AlphaTexture;
};

texture g_BlendTexture;
sampler BlendSampler = sampler_state
{
	texture = g_BlendTexture;
};

texture g_RefractionTexture;
sampler RefractionSampler = sampler_state
{
	texture = g_RefractionTexture;
};

texture g_FireTexture;
sampler FireSampler = sampler_state
{
	texture = g_FireTexture;
	AddressU = Clamp;
	AddressV = Clamp;
};
texture g_FireAlphaTexture;
sampler FireAlphaSampler = sampler_state
{
	texture = g_FireAlphaTexture;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_NoiseTexture;
sampler NoiseSampler = sampler_state
{
	texture = g_NoiseTexture;
	AddressU = Wrap;
	AddressV = Wrap;
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
	float3 vLightDir : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
	float3 T : TEXCOORD3;
	float3 B : TEXCOORD4;
	float3 N : TEXCOORD5;
	float4 vClipPosition : TEXCOORD6;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// LightDir
	Output.vLightDir = vWorldPosition.xyz - g_vLightPosition.xyz;

	// ViewDir
	Output.vViewDir = normalize(vWorldPosition.xyz - g_vViewPosition.xyz);

	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
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
	float3 vLightDir : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
	float3 T : TEXCOORD3;
	float3 B : TEXCOORD4;
	float3 N : TEXCOORD5;
	float4 vClipPosition : TEXCOORD6;
};

float4 Pass0_PS_MAIN(Pass0_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// TangentNormal
	float3 vTangentNormal = tex2D(NormalSampler, Input.vTexUV).xyz;
	vTangentNormal = normalize(vTangentNormal * 2.0f - 1.0f);

	// TBN
	float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
	TBN = transpose(TBN);

	// WorldNormal
	float3 vWorldNormal = mul(TBN, vTangentNormal);

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV);

	// Diffuse
	float3 vLightDir = normalize(Input.vLightDir);
	float3 Diffuse = saturate(dot(vWorldNormal, -vLightDir));
	Diffuse = Albedo.rgb * Diffuse;

	// Specular
	float3 Specular;
	if(Diffuse.x > 0.0f)
	{
		float3 vReflection = reflect(vLightDir, vWorldNormal);
		float3 vViewDir = normalize(Input.vViewDir);
		Specular = saturate(dot(vReflection, -vViewDir));
		Specular = pow(Specular, 20.0f);
		Specular *= tex2D(SpecularSampler, Input.vTexUV).rgb;
	}

	// Ambient
	float3 Ambient = float3(0.5f, 0.5f, 0.5f) * Albedo.rgb;

	return float4(Ambient + Diffuse + Specular, Albedo.a);
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass1_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass1_VS_OUT Pass1_VS_MAIN(Pass1_VS_IN Input)
{
	Pass1_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass1_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass1_PS_OUT
{
	float4 vDiffuse : COLOR0;
	float4 vDistortion : COLOR1;
};

Pass1_PS_OUT Pass1_PS_MAIN(Pass1_PS_IN Input)
{
	Pass1_PS_OUT Out = (Pass1_PS_OUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		Out.vDiffuse = float4(0.f, 0.f, 0.f, 0.f);
		Out.vDistortion = float4(0.f, 0.f, 0.f, 0.f);

		return Out;
	}

	Out.vDiffuse = tex2D(BaseSampler, Input.vTexUV);
	Out.vDistortion = tex2D(BaseSampler, Input.vTexUV);

	return Out;
}

////////////////////////////////////////////////////////////////////////// Pass2
struct Pass2_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass2_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass2_VS_OUT Pass2_VS_MAIN(Pass2_VS_IN Input)
{
	Pass2_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass2_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass2_PS_OUT
{
	float4 vDiffuse : COLOR0;
};

Pass2_PS_OUT Pass2_PS_MAIN(Pass2_PS_IN Input)
{
	Pass2_PS_OUT Out = (Pass2_PS_OUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		Out.vDiffuse = float4(0.f, 0.f, 0.f, 0.f);

		return Out;
	}

	Out.vDiffuse = tex2D(BaseSampler, Input.vTexUV);

	return Out;
}

struct Pass3_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass3_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass3_VS_OUT Pass3_VS_MAIN(Pass3_VS_IN Input)
{
	Pass2_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass3_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass3_PS_MAIN(Pass3_PS_IN Input) : COLOR
{
	float4 vOut = float4(0.f, 0.f, 0.f, 0.f);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return vOut;
	}

	vOut = tex2D(BaseSampler, Input.vTexUV);

	return vOut;
}

struct Pass4_VS_IN
{
	float4 vPosition : POSITION;
};

struct Pass4_VS_OUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD1;
};

Pass4_VS_OUT Pass4_VS_MAIN(Pass4_VS_IN Input)
{
	Pass4_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass4_PS_IN
{
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass4_PS_MAIN(Pass4_PS_IN Input) : COLOR0
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// Depth
	float fDepth = tex2D(DepthSampler, vDepthUV).r;

	// 1번
	// ViewRay : 여기서 vScreenPos를 쓰는 이유가 뭐지? 지금 vScreenPos의 범위는 -1~1의 범위를 가진다.
	// 근데, Lerp 함수에 -값도 들어감? 왜 들어가려고하지? z가 RightTop의 z인 이유는 먼 평면에 붙이기 위함인거 같다.
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	// 여기도 왜 이렇게 하는건지 모르게떠..
	float4 vViewPos = float4(vViewRay * fDepth, 1.0f);

	// To Proj
	float4 vProjPos = mul(vViewPos, g_mProj);
	if(tex2D(NormalDepthSampler, vDepthUV).w < vProjPos.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// To Local
	float4 vLocalPos = mul(vViewPos, g_mInvView);
	vLocalPos = mul(vLocalPos, g_mInvWorld);

	// Abs
	float3 vAbsLocalPos = abs(vLocalPos.xyz);
	clip(0.5f - vAbsLocalPos.xyz);

	float2 vTexUV = vLocalPos.xz + 0.5f;
	float4 vColor = tex2D(BaseSampler, vTexUV);
	vColor *= (1.0f - max((vAbsLocalPos.z - 0.25f) / 0.25f, 0.0f));

	return vColor;
}

struct Pass5_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass5_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass5_VS_OUT Pass5_VS_MAIN(Pass5_VS_IN Input)
{
	Pass5_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass5_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass5_PS_MAIN(Pass5_PS_IN Input) : COLOR
{
	float4 vOut = float4(0.f, 0.f, 0.f, 0.f);

	vOut = tex2D(BaseSampler, Input.vTexUV);

	return vOut;
}

struct Pass6_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass6_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass6_VS_OUT Pass6_VS_MAIN(Pass6_VS_IN Input)
{
	Pass6_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass6_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass6_PS_OUT
{
	float4 vDiffuse : COLOR0;
	float4 vDistortion : COLOR1;
};

Pass6_PS_OUT Pass6_PS_MAIN(Pass6_PS_IN Input)
{
	Pass6_PS_OUT Out = (Pass6_PS_OUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		Out.vDiffuse = float4(0.f, 0.f, 0.f, 0.f);
		Out.vDistortion = float4(0.f, 0.f, 0.f, 0.f);

		return Out;
	}

	Out.vDiffuse = tex2D(BaseSampler, Input.vTexUV);
	Out.vDistortion = tex2D(BaseSampler, Input.vTexUV);

	Out.vDiffuse.a -= g_fAlpha;
	Out.vDistortion.a -= g_fAlpha;

	return Out;
}

struct Pass7_VS_IN
{
	float4 vPosition : POSITION;
};

struct Pass7_VS_OUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD1;
};

Pass7_VS_OUT Pass7_VS_MAIN(Pass7_VS_IN Input)
{
	Pass7_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass7_PS_IN
{
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass7_PS_MAIN(Pass7_PS_IN Input) : COLOR0
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// Depth
	float fDepth = tex2D(DepthSampler, vDepthUV).r;

	// 1번
	// ViewRay : 여기서 vScreenPos를 쓰는 이유가 뭐지? 지금 vScreenPos의 범위는 -1~1의 범위를 가진다.
	// 근데, Lerp 함수에 -값도 들어감? 왜 들어가려고하지? z가 RightTop의 z인 이유는 먼 평면에 붙이기 위함인거 같다.
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	// 여기도 왜 이렇게 하는건지 모르게떠..
	float4 vViewPos = float4(vViewRay * fDepth, 1.0f);

	// To Proj
	float4 vProjPos = mul(vViewPos, g_mProj);
	if(tex2D(NormalDepthSampler, vDepthUV).w < vProjPos.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// To Local
	float4 vLocalPos = mul(vViewPos, g_mInvView);
	vLocalPos = mul(vLocalPos, g_mInvWorld);

	// Abs
	float3 vAbsLocalPos = abs(vLocalPos.xyz);
	clip(0.5f - vAbsLocalPos.xyz);

	float2 vTexUV = vLocalPos.xz + 0.5f;
	float4 vColor = tex2D(BaseSampler, vTexUV);
	vColor *= (1.0f - max((vAbsLocalPos.z - 0.25f) / 0.25f, 0.0f));

	vColor.a -= g_fAlpha;

	return vColor;
}


struct Pass8_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass8_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass8_VS_OUT Pass8_VS_MAIN(Pass8_VS_IN Input)
{
	Pass8_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass8_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass8_PS_MAIN(Pass8_PS_IN Input) : COLOR
{
	float4 vOut = float4(0.f, 0.f, 0.f, 0.f);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return vOut;
	}

	vOut = tex2D(BaseSampler, Input.vTexUV);
	vOut.a -= g_fAlpha;

	return vOut;
}

struct Pass9_VS_INPUT
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float3 vTangent : TANGENT;
	float3 vBinormal : BINORMAL;
	float2 vTexUV : TEXCOORD0;
};

struct Pass9_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float3 vLightDir : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
	float3 T : TEXCOORD3;
	float3 B : TEXCOORD4;
	float3 N : TEXCOORD5;
	float4 vClipPosition : TEXCOORD6;
};

Pass9_VS_OUTPUT Pass9_VS_MAIN(Pass9_VS_INPUT Input)
{
	Pass9_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// LightDir
	Output.vLightDir = vWorldPosition.xyz - g_vLightPosition.xyz;

	// ViewDir
	Output.vViewDir = normalize(vWorldPosition.xyz - g_vViewPosition.xyz);

	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV - float2(g_fTime * 0.75f, 0.f);

	// TBN
	Output.T = mul(Input.vTangent, (float3x3)g_mWorld);
	Output.B = mul(Input.vBinormal, (float3x3)g_mWorld);
	Output.N = mul(Input.vNormal, (float3x3)g_mWorld);

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass9_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float3 vLightDir : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
	float3 T : TEXCOORD3;
	float3 B : TEXCOORD4;
	float3 N : TEXCOORD5;
	float4 vClipPosition : TEXCOORD6;
};

float4 Pass9_PS_MAIN(Pass9_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// TangentNormal
	float3 vTangentNormal = tex2D(NormalSampler, Input.vTexUV).xyz;
	vTangentNormal = normalize(vTangentNormal * 2.0f - 1.0f);

	// TBN
	float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
	TBN = transpose(TBN);

	// WorldNormal
	float3 vWorldNormal = mul(TBN, vTangentNormal);

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV);

	// Diffuse
	float3 vLightDir = normalize(Input.vLightDir);
	float3 Diffuse = saturate(dot(vWorldNormal, -vLightDir));
	Diffuse = Albedo.rgb * Diffuse;

	// Specular
	float3 Specular;
	if(Diffuse.x > 0.0f)
	{
		float3 vReflection = reflect(vLightDir, vWorldNormal);
		float3 vViewDir = normalize(Input.vViewDir);
		Specular = saturate(dot(vReflection, -vViewDir));
		Specular = pow(Specular, 20.0f);
		Specular *= tex2D(SpecularSampler, Input.vTexUV).rgb;
	}

	// Ambient
	float3 Ambient = float3(0.5f, 0.5f, 0.5f) * Albedo.rgb;

	return float4(Ambient + Diffuse + Specular, Albedo.a);
}

struct Pass10_VS_IN
{
	float4 vPosition : POSITION;
	float4 vWeights : BLENDWEIGHT0;
	int4 vIndices : BLENDINDICES0;
};

struct Pass10_VS_OUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD0;
};

Pass10_VS_OUT Pass10_VS_MAIN(Pass10_VS_IN Input)
{
	Pass10_VS_OUT Output;

	float4 vPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);

	float lastWeight = 0.0f;
	int n = g_iInfluenceMax - 1;

	for(int i = 0; i < n; ++i)
	{
		lastWeight += Input.vWeights[i];
		vPosition += Input.vWeights[i] * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[i]));
	}

	lastWeight = 1.0f - lastWeight;
	vPosition += lastWeight * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[n]));
	vPosition.w = 1.0f;

	// Position
	Output.vPosition = mul(vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass10_PS_INPUT	
{
	float4 vClipPosition : TEXCOORD0;
};

struct Pass10_PS_OUTPUT
{
	float4 vAlbedo : COLOR0;
};

Pass10_PS_OUTPUT Pass10_PS_MAIN(Pass10_PS_INPUT Input)
{
	Pass10_PS_OUTPUT Output = (Pass10_PS_OUTPUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return Output;
	}

	Output.vAlbedo = float4(0.5f, 0.1f, 0.1f, 0.7f);

	return Output;
}


Pass10_PS_OUTPUT Pass11_PS_MAIN(Pass10_PS_INPUT Input)
{
	Pass10_PS_OUTPUT Output = (Pass10_PS_OUTPUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return Output;
	}

	Output.vAlbedo = float4(0.f, 0.f, 0.f, 1.f);

	return Output;
}

struct Pass12_VS_INPUT
{
	float4 vPosition : POSITION;
};

struct Pass12_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD0;
};

Pass12_VS_OUTPUT Pass12_VS_MAIN(Pass12_VS_INPUT Input)
{
	Pass12_VS_OUTPUT Output;
	
	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass12_PS_INPUT
{
	float4 vClipPosition : TEXCOORD0;
};

float4 Pass12_PS_MAIN(Pass12_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	return float4(0.f, 0.f, 0.f, 1.f);
}

struct Pass13_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV	: TEXCOORD0;
};

struct Pass13_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass13_VS_OUT Pass13_VS_MAIN(Pass13_VS_IN Input)
{
	Pass13_VS_OUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass13_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass13_PS_OUT
{
	float4 vDiffuse : COLOR0;
	float4 vDistortion : COLOR1;
	float4 vRefraction	: COLOR2;
};

Pass13_PS_OUT Pass13_PS_MAIN(Pass13_PS_IN Input)
{
	Pass13_PS_OUT Out = (Pass13_PS_OUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return Out;
	}

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV + float2(0.f, g_fTime * -0.25f));

	Out.vDiffuse = float4(Albedo.rgb, Albedo.a - g_fAlpha);
	Out.vRefraction = Albedo;
	
	return Out;
}

struct Pass14_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass14_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass14_VS_OUTPUT Pass14_VS_MAIN(Pass14_VS_INPUT Input)
{
	Pass14_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass14_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass14_PS_MAIN(Pass14_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV);

	return float4(Albedo.rgb, Albedo.a - g_fAlpha);
}

struct Pass15_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass15_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass15_VS_OUT Pass15_VS_MAIN(Pass15_VS_IN Input)
{
	Pass15_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;

	// TexUV
	Output.vTexUV = Input.vTexUV - float2(0.f, g_fTime * 1.5f);

	return Output;
}

struct Pass15_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass15_PS_MAIN(Pass15_PS_IN Input) : COLOR
{
	float4 vOut = float4(0.f, 0.f, 0.f, 0.f);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return vOut;
	}

	vOut = tex2D(BaseSampler, Input.vTexUV);

	return vOut;
}

struct Pass16_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vWeights : BLENDWEIGHT0;
	int4 vIndices : BLENDINDICES0;
};

struct Pass16_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD4;
};

Pass16_VS_OUT Pass16_VS_MAIN(Pass16_VS_IN Input)
{
	Pass16_VS_OUT Output;

	float4 vPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float lastWeight = 0.0f;
	int n = g_iInfluenceMax - 1;

	for(int i = 0; i < n; ++i)
	{
		lastWeight += Input.vWeights[i];
		vPosition += Input.vWeights[i] * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[i]));
	}

	lastWeight = 1.0f - lastWeight;
	vPosition += lastWeight * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[n]));
	vPosition.w = 1.0f;

	// Position
	Output.vPosition = mul(vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass16_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD4;
};

struct Pass16_PS_OUTPUT
{
	float4 vAlbedo : COLOR0;
};

Pass16_PS_OUTPUT Pass16_PS_MAIN(Pass16_PS_INPUT Input)
{
	Pass16_PS_OUTPUT Output;
	Output.vAlbedo = float4(0.f, 0.f, 0.f, 0.f);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return Output;

	// Albedo
	Output.vAlbedo = tex2D(DiffuseSampler, Input.vTexUV);

	return Output;
}

struct Pass17_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass17_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass17_VS_OUTPUT Pass17_VS_MAIN(Pass17_VS_INPUT Input)
{
	Pass17_VS_OUTPUT Output;

	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass17_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass17_PS_MAIN(Pass17_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV);
	float4 Alpha = tex2D(AlphaSampler, Input.vTexUV);

	return float4(Albedo.rgb, Alpha.a);
}

struct Pass18_VS_INPUT
{
	float4 vPosition	: POSITION;
	float2 vTexUV		: TEXCOORD0;
	float	fPointSize	: PSIZE;
};

struct Pass18_VS_OUTPUT
{
	float4	vPosition	: POSITION;
	float2	vTexUV		: TEXCOORD0;
	float4	vClipPosition : TEXCOORD1;
	float	fPointSize	: PSIZE;
};

Pass18_VS_OUTPUT Pass18_VS_MAIN(Pass18_VS_INPUT Input)
{
	Pass18_VS_OUTPUT Out = (Pass18_VS_OUTPUT)0;

	Out.vPosition = mul(Input.vPosition, g_mWorld);
	Out.vPosition = mul(Out.vPosition, g_mViewProj);

	Out.vTexUV = Input.vTexUV;

	Out.fPointSize = 5.f;

	// ClipPosition
	Out.vClipPosition = Out.vPosition;
	
	return Out;
}

struct Pass18_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass18_PS_OUTPUT
{
	float4 vColor : COLOR0;
};

Pass18_PS_OUTPUT Pass18_PS_MAIN(Pass18_PS_INPUT Input)
{
	Pass18_PS_OUTPUT Out = (Pass18_PS_OUTPUT)0;

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		Out.vColor = float4(0.f, 0.f, 0.f, 0.f);

		return Out;
	}

	Out.vColor = tex2D(DiffuseSampler, Input.vTexUV);
	
	return Out;
}

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass19_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass19_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass19_VS_OUTPUT Pass19_VS_MAIN(Pass19_VS_INPUT Input)
{
	Pass19_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass19_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass19_PS_MAIN(Pass19_PS_INPUT Input) : COLOR0
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 vColor = tex2D(DiffuseSampler, Input.vTexUV);

	vColor.a -= g_fAlpha;

	return vColor;
}

struct Pass20_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass20_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass20_VS_OUT Pass20_VS_MAIN(Pass20_VS_IN Input)
{
	Pass20_VS_OUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;

	// TexUV
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass20_PS_IN
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass20_PS_MAIN(Pass20_PS_IN Input) : COLOR
{
	float4 vOut = float4(0.f, 0.f, 0.f, 0.f);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
	{
		return vOut;
	}

	float4 vDiffuse = tex2D(DiffuseSampler, Input.vTexUV * 4.f);
	float4 vBlend = tex2D(BlendSampler, Input.vTexUV);

	vOut = float4(vDiffuse.rgb, vBlend.a) * vBlend;

	return vOut;
}


struct Pass21_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass21_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass21_VS_OUTPUT Pass21_VS_MAIN(Pass21_VS_INPUT Input)
{
	Pass21_VS_OUTPUT Output;

	// Position
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass21_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass21_PS_MAIN(Pass21_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Albedo
	float4 Albedo = tex2D(DiffuseSampler, Input.vTexUV);

	float4 Alpha = tex2D(AlphaSampler, Input.vTexUV + float2(g_fTime * 2.f, g_fTime * 2.f));

	float fAlpha = Albedo.a * Alpha.a;

	return float4(Albedo.rgb, fAlpha);
}

struct Pass22_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass22_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass22_VS_OUTPUT Pass22_VS_MAIN(Pass22_VS_INPUT Input)
{
	Pass22_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass22_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass22_PS_MAIN(Pass22_PS_INPUT Input) : COLOR
{
	float2 vUV = Input.vTexUV * g_fDetail;
	vUV = vUV + float2(g_fTime * g_fX, g_fTime * g_fY);

	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.f, 0.f, 0.f, 0.0f);

	return tex2D(DiffuseSampler, vUV);	
}

struct Pass23_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass23_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float2 vTexUV1 : TEXCOORD1;
	float2 vTexUV2 : TEXCOORD2;
	float2 vTexUV3 : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
};

Pass23_VS_OUTPUT Pass23_VS_MAIN(Pass23_VS_INPUT Input)
{
	Pass23_VS_OUTPUT Output;

	// WorldPosition
	float4 vWorldPosition = mul(Input.vPosition, g_mWorld);

	// Position
	Output.vPosition = mul(vWorldPosition, g_mViewProj);

	// TexUV
	Output.vTexUV = Input.vTexUV;

	// ClipPosition
	Output.vClipPosition = Output.vPosition;

	Output.vTexUV1 = Input.vTexUV * g_vScale.x;
	Output.vTexUV1.y = Output.vTexUV1.y + (g_fTime * g_vScrollSpeed.x);

	Output.vTexUV2 = Input.vTexUV * g_vScale.y;
	Output.vTexUV2.y = Output.vTexUV2.y + (g_fTime * g_vScrollSpeed.y);

	Output.vTexUV3 = Input.vTexUV * g_vScale.z;
	Output.vTexUV3.y = Output.vTexUV3.y + (g_fTime * g_vScrollSpeed.z);

	return Output;
}

struct Pass23_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float2 vTexUV1 : TEXCOORD1;
	float2 vTexUV2 : TEXCOORD2;
	float2 vTexUV3 : TEXCOORD3;
	float4 vClipPosition : TEXCOORD4;
};

float4 Pass23_PS_MAIN(Pass23_PS_INPUT Input) : COLOR
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.f, 0.f, 0.f, 0.0f);

	float4 vNoisc1 = tex2D(NoiseSampler, Input.vTexUV1);
	float4 vNoisc2 = tex2D(NoiseSampler, Input.vTexUV2);
	float4 vNoisc3 = tex2D(NoiseSampler, Input.vTexUV3);
	
	vNoisc1 = (vNoisc1 - 0.5f) * 2.f;
	vNoisc2 = (vNoisc2 - 0.5f) * 2.f;
	vNoisc3 = (vNoisc3 - 0.5f) * 2.f;

	vNoisc1.xy = vNoisc1.xy * g_vDir1.xy;
	vNoisc2.xy = vNoisc2.xy * g_vDir2.xy;
	vNoisc3.xy = vNoisc3.xy * g_vDir3.xy;

	float4 vFinalNoise = vNoisc1 + vNoisc2 + vNoisc3;

	float fPerturb = ((1.f - Input.vTexUV.y) * g_vDirScale) + g_vDirBias;
	
	float2 vNoiseCoord = (vFinalNoise.xy * fPerturb) + Input.vTexUV.xy;

	float4 vFireColor = tex2D(FireSampler, vNoiseCoord);
	float4 vAlphaColor = tex2D(FireAlphaSampler, vNoiseCoord);

	vFireColor.a = vAlphaColor.a;

	return vFireColor;
}

////////////////////////////////////////////////////////////////////////// PassBlend
struct BLEND_VS_IN
{
	float4 vPosition	: POSITION;
	float2 vTexUV		: TEXCOORD0;
};

struct BLEND_VS_OUT
{
	float4 vPosition		: POSITION;
	float2 vTexUV			: TEXCOORD0;
	float4 vClipPosition	: TEXCOORD1;
};

BLEND_VS_OUT BLEND_VS_MAIN(BLEND_VS_IN Input)
{
	BLEND_VS_OUT Out = (BLEND_VS_OUT)0;
	
	Out.vPosition = Input.vPosition;
	Out.vTexUV = Input.vTexUV;
	Out.vClipPosition = Input.vPosition;

	return Out;
}

struct BLEND_PS_IN
{
	float2 vTexUV			: TEXCOORD0;
	float4 vClipPosition	: TEXCOORD1;
};

float4 BLEND_PS_MAIN(BLEND_PS_IN Input) : COLOR0
{
	float2 vInputUV = Input.vTexUV + (float2(1.f / 1280.f, 1.f / 720.f) / 2.f);
	
	float2 vTrans = vInputUV + 0.001f;

	float4 vNoise = tex2D(DistortionSampler, vTrans);

	float4 vRefraction = tex2D(RefractionSampler, vInputUV);

	float2 vUV = vInputUV + vNoise.xy * 0.05f;

	float4 vOri = float4(0.f, 0.f, 0.f, 0.f);

	vOri = tex2D(SceneSampler, vUV); //원본값 or 왜곡이 적용된 녀석...

	if(vRefraction.a != 0)
	{
		float4 vRefractionColor = tex2D(SceneSampler, vInputUV + vRefraction.r * 0.01f);

		vOri = vRefractionColor;
	}

	return vOri;
}

// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}//매쉬 이펙트

	pass Pass1
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	} //왜곡 이펙트

	pass Pass2
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass2_VS_MAIN();
		PixelShader = compile ps_3_0 Pass2_PS_MAIN();
	}

	pass Pass3
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass3_VS_MAIN();
		PixelShader = compile ps_3_0 Pass3_PS_MAIN();
	}

	pass Pass4
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass4_VS_MAIN();
		PixelShader = compile ps_3_0 Pass4_PS_MAIN();
	}

	pass Pass5
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass5_VS_MAIN();
		PixelShader = compile ps_3_0 Pass5_PS_MAIN();
	}

	pass Pass6
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass6_VS_MAIN();
		PixelShader = compile ps_3_0 Pass6_PS_MAIN();
	}

	pass Pass7
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass7_VS_MAIN();
		PixelShader = compile ps_3_0 Pass7_PS_MAIN();
	}

	pass Pass8
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass8_VS_MAIN();
		PixelShader = compile ps_3_0 Pass8_PS_MAIN();
	}

	pass Pass9
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x0000009f;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass9_VS_MAIN();
		PixelShader = compile ps_3_0 Pass9_PS_MAIN();
	}//매쉬 이펙트 + 알파테스트 + UV 애니메이션 예정

	pass Pass10
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass10_VS_MAIN();
		PixelShader = compile ps_3_0 Pass10_PS_MAIN();
	}//매쉬 이펙트

	pass Pass11
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass10_VS_MAIN();
		PixelShader = compile ps_3_0 Pass11_PS_MAIN();
	}//매쉬 이펙트

	pass Pass12
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass12_VS_MAIN();
		PixelShader = compile ps_3_0 Pass12_PS_MAIN();
	}//매쉬 이펙트

	pass Pass13
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass13_VS_MAIN();
		PixelShader = compile ps_3_0 Pass13_PS_MAIN();
	} //왜곡 이펙트

	pass Pass14
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass14_VS_MAIN();
		PixelShader = compile ps_3_0 Pass14_PS_MAIN();
	}//매쉬 이펙트

	pass Pass15
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass15_VS_MAIN();
		PixelShader = compile ps_3_0 Pass15_PS_MAIN();
	}

	pass Pass16
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
// 		alphafunc = greater;
// 		alpharef = 0x00000000;
		cullmode = none;
		VertexShader = compile vs_3_0 Pass16_VS_MAIN();
		PixelShader = compile ps_3_0 Pass16_PS_MAIN();
	}

	pass Pass17
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass17_VS_MAIN();
		PixelShader = compile ps_3_0 Pass17_PS_MAIN();
	}

	pass Pass18
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = ccw;

		PointSpriteEnable = true;

		VertexShader = compile vs_3_0 Pass18_VS_MAIN();
		PixelShader = compile ps_3_0 Pass18_PS_MAIN();
	}

	pass Pass19
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		PointSpriteEnable = false;

		VertexShader = compile vs_3_0 Pass19_VS_MAIN();
		PixelShader = compile ps_3_0 Pass19_PS_MAIN();
	}

	pass Pass20
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		PointSpriteEnable = false;

		VertexShader = compile vs_3_0 Pass20_VS_MAIN();
		PixelShader = compile ps_3_0 Pass20_PS_MAIN();
	}

	pass Pass21
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass21_VS_MAIN();
		PixelShader = compile ps_3_0 Pass21_PS_MAIN();
	}

	pass Pass22
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x000000d0;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass22_VS_MAIN();
		PixelShader = compile ps_3_0 Pass22_PS_MAIN();
	}

	pass Pass23
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = true;
		zwriteenable = false;

		alphatestenable = false;
		//alphafunc = greater;
		//alpharef = 0x00000088;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass23_VS_MAIN();
		PixelShader = compile ps_3_0 Pass23_PS_MAIN();
	}

	pass Pass_Blend
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0x00000020;
		cullmode = ccw;

		VertexShader = compile vs_3_0 BLEND_VS_MAIN();
		PixelShader = compile ps_3_0 BLEND_PS_MAIN();
	} //블렌딩.
};