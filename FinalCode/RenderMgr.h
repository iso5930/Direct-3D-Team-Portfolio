#pragma once

class CRenderCom;

class CRenderMgr
{
private:
	// RenderMode
	DWORD m_dwRenderMode;

	// Screen
	CBuffer* m_pScreen;

	// ShaderArr
	CShader* m_pShaderArr[SHADER_TYPE_END];

	// TargetArr
	CRenderTarget* m_pTargetArr[TARGET_TYPE_END];

	// ObjectVec
	vector<CObject*> m_ObjectVec[RENDER_TYPE_END];

	// Blur
	float m_fBlurWidth;
	float m_fKernelSize;

	// FPS
	float m_fTime;
	TCHAR m_tszFPS[MID_STR];
	DWORD m_dwFPS;

	// Temp
	CTransformCom* m_pTransformCom;
	CBufferCom* m_pBufferCom;
	CRenderCom* m_pRenderCom;
	CMaterialCom* m_pMaterialCom;
	CStaticMesh* m_pStaticMesh;
	CDynamicMesh* m_pDynamicMesh;

	//Fog
	float m_fFogHeight;

	//HDR + Bloom
	float m_fBrightThreshold;
	float m_fGaussMultiplier;
	float m_fGaussMean;
	float m_fGaussStdDev;
	float m_fExposure;
	float m_fBloom_w;
	float m_fBloom_h;
	float m_fBloomWeight_X[9];
	float m_fBloomOffset_X[9];
	float m_fBloomWeight_Y[9];
	float m_fBloomOffset_Y[9];

	//OffSet
	D3DXVECTOR4 m_vLuminanceOffset[5][9];
	D3DXVECTOR4 m_vLuminanceOffset_LV6[4];
	D3DXVECTOR4 m_vDownSamplerOffset[16];

	float		m_fShadowBais;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	void CreateShadowMap();
	void CreateVelocityMap();
	void BlurBegin();
	void FogBegin();
	void HDR_Begin();
	void SSAO_Begin();
	void Effect_Begin();
	void Shadow_Begin();
	void RenderBack();
	void RenderSkyBox();
	void RenderDeffered();
	void RenderLight();
	void RenderBlend();
	void Shadow_End();
	void Effect_End();
	void SSAO_End();
	void HDR_End();
	void FogEnd();
	void BlurEnd();
	void RenderUI();
	void RenderMouse();
	void RenderNPCBox();
	void RenderProbBox();
	void RenderFPS();

private:
	void RenderShadowFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF);
	void RenderShadowContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);

	void RenderVelocityFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF);
	void RenderVelocityContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);

	void RenderFrame(CShader* _pShader, MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF);
	void RenderContainer(CShader* _pShader, MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);

	void RenderAfterImageFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF);
	void RenderAfterImageContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);

	void RenderDynamicEffectFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF);
	void RenderDynamicEffectContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);

public:
	void SetRenderMode(DWORD _dwRenderMode) { m_dwRenderMode = _dwRenderMode; }

	void AddObject(RENDER_TYPE _eRenderType, CObject* _pObject);
	void RemoveObject(RENDER_TYPE _eRenderType, CObject* _pObject);
	
public:
	float ComputeGaussianValue(float fX, float fMean, float fStd_Deviation);
	void  HDR_Offset(void);

private:
	DECLARE_SINGLETON(CRenderMgr)

private:
	explicit CRenderMgr();
	~CRenderMgr();
};

inline bool RenderCompare(CObject* _pLeft, CObject* _pRight)
{
	return ((CRenderCom*)_pLeft->GetComponent(COM_TYPE_RENDER))->m_dwPriority > ((CRenderCom*)_pRight->GetComponent(COM_TYPE_RENDER))->m_dwPriority;
}