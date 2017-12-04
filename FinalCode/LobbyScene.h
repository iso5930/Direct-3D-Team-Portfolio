#pragma once

#include "Scene.h"

class CBasicButton;

class CLobbyScene : public CScene
{
private:
	// BackButton
	CBasicButton* m_pBackButton;

	// SettingButton
	CBasicButton* m_pSettingButton;

	// GameContinueButton
	CBasicButton* m_pGameContinueButton;

	// CharacterChangeButton
	CBasicButton* m_pCharacterChangeButton;

	// Model
	CModel* m_pModel;

public:
	virtual void Initialize();
	virtual CScene* Update();
	virtual void Render();
	virtual void Release();

private:
	virtual CScene* UpdateLoad();
	virtual CScene* UpdateComplete();
	virtual CScene* UpdatePlay();

public:
	explicit CLobbyScene(CScene* _pScene);
	virtual ~CLobbyScene();
};
