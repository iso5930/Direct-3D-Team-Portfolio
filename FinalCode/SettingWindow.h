#pragma once

#include "WindowUI.h"

class CSettingButton;

class CSettingWindow : public CWindowUI
{
private:
	// Page
	int m_iPage;

	// BlurSelect
	int m_iBlurSelect;

	// ShadowSelect
	int m_iShadowSelect;

	// FogSelect
	int m_iFogSelect;

	// HDRSelect
	int m_iHDRSelect;

	// SSAOSelect
	int m_iSSAOSelect;

	// DistortionSelect
	int m_iDistortionSelect;

	// DebugBufferSelect
	int m_iDebugBufferSelect;

	// NavigationMeshSelect
	int m_iNavigationMeshSelect;

	// CheckSphereSelect
	int m_iCheckSphereSelect;

	// CollisionSphereSelect
	int m_iCollisionSphereSelect;

	// CollisionBoxSelect
	int m_iCollisionBoxSelect;

	// FPSSelect
	int m_iFPSSelect;

	// PointLightSelect
	int m_iPointLightSelect;

	// NPCBoxSelect
	int m_iNPCBoxSelect;

	// ProbBoxSelect
	int m_iProbBoxSelect;

	// SettingButton
	// 0(GraphicSetting), 1(SoundSetting), 2(GameSetting), 3(CheatKeySetting)
	CSettingButton* m_pSettingButton[4];

	// BlurButton
	// 0(None), 1(Radial), 2(Gaussian), 3(Motion)
	CSettingButton* m_pBlurButton[4];

	// ShadowButton
	// 0(None), 1(Normal), 2(Cascade)
	CSettingButton* m_pShadowButton[3];

	// FogButton
	// 0(None), 1(Exponent), 2(Exponent^2), 3(Height)
	CSettingButton* m_pFogButton[4];

	// HDRButton
	// 0(None), 1(HDR)
	CSettingButton* m_pHDRButton[2];

	// SSAOButton
	// 0(None), 1(SSAO)
	CSettingButton* m_pSSAOButton[2];

	// DistortionButton
	// 0(None), 1(Distortion)
	CSettingButton* m_pDistortionButton[2];

	// DebugBufferButton
	// 0(None), 1(Using)
	CSettingButton* m_pDebugBufferButton[2];

	// NavigationMeshButton
	// 0(None), 1(Using)
	CSettingButton* m_pNavigationMeshButton[2];

	// CheckSphereButton
	// 0(None), 1(Using)
	CSettingButton* m_pCheckSphereButton[2];

	// CollisionSphereButton
	// 0(None), 1(Using)
	CSettingButton* m_pCollisionSphereButton[2];

	// CollisionBoxButton
	// 0(None), 1(Using)
	CSettingButton* m_pCollisionBoxButton[2];

	// FPSButton
	// 0(None), 1(Using)
	CSettingButton* m_pFPSButton[2];

	// PointLightButton
	// 0(None), 1(Using)
	CSettingButton* m_pPointLightButton[2];

	// NPCBoxButton
	// 0(None), 1(Using)
	CSettingButton* m_pNPCBoxButton[2];

	// ProbBoxButton
	// 0(None), 1(Using)
	CSettingButton* m_pProbBoxButton[2];

	// CheatKeyButton
	// 0(LevelUpButton), 1(QuestItemButton), 2(NormalItemButton), 3(MagicItemButton), 4(UniqueItemButton)
	// 5(LegendItemButton), 6(SetItemButton), 7(GemItemButton), 8(MaterialItemButton), 9(GoldPlusButton)
	// 10(GoldMinusButton)
	CBasicButton* m_pCheatKeyButton[11];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Renew();

public:
	explicit CSettingWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CSettingWindow();
};
