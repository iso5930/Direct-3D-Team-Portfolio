#pragma once

#include "Scene.h"

class CBasicButton;
class CNameTextField;
class CWhiteCursor;
class CModel;
class CProfileUI;

class CCreateScene : public CScene
{
private:
	// GenderSelect
	int m_iGenderSelect;

	// JobSelect
	int m_iJobSelect;

	// GenderButton
	CBasicButton* m_pGenderButton[2];

	// JobButton
	CBasicButton* m_pJobButton[5];

	// BackButton
	CBasicButton* m_pBackButton;

	// CreateButton
	CBasicButton* m_pCreateButton;

	// NameTextField
	CNameTextField* m_pNameTextField;

	// WhiteCursor
	CWhiteCursor* m_pWhiteCursor;

	// Model
	CModel* m_pModel;

	// Profile
	CProfileUI* m_pProfileUI;

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
	explicit CCreateScene(CScene* _pScene);
	virtual ~CCreateScene();
};
