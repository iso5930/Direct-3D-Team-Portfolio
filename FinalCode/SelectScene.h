#pragma once

#include "Scene.h"

class CBasicButton;
class CCharacterButton;
class CVScroll;
class CModel;
class CBadgeUI;

class CSelectScene : public CScene
{
private:
	// Select
	int m_iSelect;

	// Scroll
	int m_iScroll;

	// MaxScroll
	int m_iMaxScroll;

	// CancelButton
	CBasicButton* m_pCancelButton;

	// CharacterCreateButton
	CBasicButton* m_pCharacterCreateButton;

	// CharacterSelectButton
	CBasicButton* m_pCharacterSelectButton;

	// CharacterDeleteButton
	CBasicButton* m_pCharacterDeleteButton;

	// CharacterButton
	CCharacterButton* m_pCharacterButton[10];

	// ScrollUpButton
	CBasicButton* m_pScrollUpButton;

	// ScrollDownButton
	CBasicButton* m_pScrollDownButton;

	// VScroll
	CVScroll* m_pVScroll;

	// Model
	CModel* m_pModel;

	// BadgeUI
	CBadgeUI* m_pBadgeUI;

public:
	virtual void Initialize();
	virtual CScene* Update();
	virtual void Render();
	virtual void Release();

private:
	virtual CScene* UpdateLoad();
	virtual CScene* UpdateComplete();
	virtual CScene* UpdatePlay();

private:
	// RenewButton
	void RenewButton();

	// RenewModel
	void RenewModelAndBadge();

	// UpdateButton
	void UpdateButton();

	// UpdateScroll
	void UpdateScroll();

public:
	explicit CSelectScene(CScene* _pScene);
	virtual ~CSelectScene();
};
