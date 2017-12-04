#include "StdAfx.h"
#include "CharacterButton.h"

CCharacterButton::CCharacterButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey)
: CButtonUI(_tszObjKey, _eObjType, _tszBackTexKey, _tszOverTexKey, _tszDownTexKey, NULL)
{
	// Name
	ZeroMemory(m_tszName, sizeof(m_tszName));

	// Info
	ZeroMemory(m_tszInfo, sizeof(m_tszInfo));
}

CCharacterButton::~CCharacterButton()
{
	Release();
}

void CCharacterButton::Initialize()
{
	CButtonUI::Initialize();
}

int CCharacterButton::Update()
{
	CButtonUI::Update();

	return 0;
}

void CCharacterButton::Render()
{
	CButtonUI::Render();

	if(Equals(m_pTransformCom->m_vSize.x, 0.0f, MIN_EPSILON) || Equals(m_pTransformCom->m_vSize.y, 0.0f, MIN_EPSILON))
		return;

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 50.0f), long(vPos.y - 15.0f), long(vPos.x + 150.0f), long(vPos.y));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszName, -1, &rcText, DT_LEFT, D3DXCOLOR(0.8f, 0.5f, 0.3f, 1.0f));

	SetRect(&rcText, long(vPos.x - 50.0f), long(vPos.y + 5.0f), long(vPos.x + 150.0f), long(vPos.y + 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(10, 5)->DrawText(NULL, m_tszInfo, -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
}

void CCharacterButton::Release()
{
}

void CCharacterButton::Setup(TCHAR* _tszName, int _iLevel, int _iJob)
{
	// Name
	_tcscpy_s(m_tszName, MIN_STR, _tszName);

	// Info
	TCHAR tszTemp[MIN_STR];
	_itot_s(_iLevel, tszTemp, 10);
	_tcscpy_s(m_tszInfo, MIN_STR, tszTemp);
	_tcscat_s(m_tszInfo, MIN_STR, _T("레벨 "));

	if(_iJob == 0)
		_tcscat_s(m_tszInfo, MIN_STR, _T("야만용사"));
	else if(_iJob == 1)
		_tcscat_s(m_tszInfo, MIN_STR, _T("악마사냥꾼"));
	else if(_iJob == 2)
		_tcscat_s(m_tszInfo, MIN_STR, _T("수도사"));
	else if(_iJob == 3)
		_tcscat_s(m_tszInfo, MIN_STR, _T("부두술사"));
	else if(_iJob == 4)
		_tcscat_s(m_tszInfo, MIN_STR, _T("마법사"));
}