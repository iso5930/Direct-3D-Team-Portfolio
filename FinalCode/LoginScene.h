#pragma once

#include "Scene.h"

class CIDTextField;
class CPWTextField;
class CBasicButton;
class CWhiteCursor;

class CLoginScene : public CScene
{
private:
	// IDTextField
	CIDTextField* m_pIDTextField;

	// PWTextField
	CPWTextField* m_pPWTextField;

	// AccessButton
	CBasicButton* m_pAccessButton;

	// SettingButton
	CBasicButton* m_pSettingButton;

	// ProducerButton
	CBasicButton* m_pProducerButton;

	// AdviceButton
	CBasicButton* m_pAdviceButton;

	// DestroyButton
	CBasicButton* m_pDestroyButton;

	// WhiteCursor
	CWhiteCursor* m_pWhiteCursor;

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
	explicit CLoginScene(CScene* _pScen);
	virtual ~CLoginScene();
};
