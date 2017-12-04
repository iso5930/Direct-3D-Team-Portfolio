#pragma once

#include "WindowUI.h"

class CEnchantButton;
class CFormulaButton;
class CVScroll;

class CEnchantWindow : public CWindowUI
{
private:
	// Texture
	LPDIRECT3DBASETEXTURE9 m_pTexture[3];

	// Page
	int m_iPage;

	// Scroll
	int m_iScroll;

	// MaxScroll
	int m_iMaxScroll;

	// FormulaType
	int m_iFormulaType;

	// FormulaSelect
	int m_iFormulaSelect;

	// DisenchantType
	int m_iDisenchantType;

	// DisenchantSelect
	int m_iDisenchatSelect;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// EnchantButton
	CEnchantButton* m_pEnchantButton[3];

	// GemFormula
	// 0(Topaz), 1(Sapphire), 2(Ruby), 3(Emerald), 4(Diamond), 5(Amethyst)
	vector<Formula*> m_GemFormula[6];

	// AccessoryFormula
	// 0(Amulet), 1(Ring)
	vector<Formula*> m_AccessoryFormula[2];

	// GemCategoryButton
	CCategoryButton* m_pGemCategoryButton[6];

	// AccessoryCategoryButton
	CCategoryButton* m_pAccessoryCategoryButton[2];

	// GemFormulaButton
	vector<CFormulaButton*> m_GemFormulaButton[6];

	// AccessoryFormulaButton
	vector<CFormulaButton*> m_AccessoryFormulaButton[2];

	// GemItemSign
	vector<CItemSign*> m_GemItemSign;

	// AccessoryItemSign
	vector<CItemSign*> m_AccessoryItemSign;

	// DisenchantItemSign
	CItemSign* m_pDisenchantItemSign;

	// VScroll
	CVScroll* m_pVScroll;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Renew();

public: ////////////////////////////////////////////////////////////////////////// Add
	void AddTopaz(Formula* _pFormula) { m_GemFormula[0].push_back(_pFormula); }
	void AddSapphire(Formula* _pFormula) { m_GemFormula[1].push_back(_pFormula); }
	void AddRuby(Formula* _pFormula) { m_GemFormula[2].push_back(_pFormula); }
	void AddEmerald(Formula* _pFormula) { m_GemFormula[3].push_back(_pFormula); }
	void AddDiamond(Formula* _pFormula) { m_GemFormula[4].push_back(_pFormula); }
	void AddAmethyst(Formula* _pFormula) { m_GemFormula[5].push_back(_pFormula); }

	void AddAmulet(Formula* _pFormula) { m_AccessoryFormula[0].push_back(_pFormula); }
	void AddRing(Formula* _pFormula) { m_AccessoryFormula[1].push_back(_pFormula); }

public: ////////////////////////////////////////////////////////////////////////// Category
	// OpenGemCategory
	void OpenGemCategory(int _iIndex);

	// CloseGemCategory
	void CloseGemCategory(int _iIndex);

	// OpenAccessoryCategory
	void OpenAccessoryCategory(int _iIndex);

	// CloseAccessoryCategory
	void CloseAccessoryCategory(int _iIndex);

	// UpdateScroll
	void UpdateScroll();

	// UpdateGemCategory
	void UpdateGemCategory();

	// UpdateAccessoryCategory
	void UpdateAccessoryCategory();

	// CreateGemFormula
	void CreateGemFormula();

	// CreateAccessoryFormula
	void CreateAccessoryFormula();

	// MakeGem
	void MakeGem();

	// MakeAccessory
	void MakeAccessory();

private:
	////////////////////////////////////////////////////////////////////////// Pick
	void UpdateNonePick();
	void UpdatePick();
	void UpdateInventoryPick();
	void UpdateEquipmentPick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateInventoryPickIn();
	void UpdateEquipmentPickIn();

	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateInventoryPickOut();
	void UpdateEquipmentPickOut();

	////////////////////////////////////////////////////////////////////////// InEnchant
	void UpdateInEnchant();
	void UpdateNonePickInEnchant();
	void UpdatePickInEnchant();
	void UpdateInventoryPickInEnchant();
	void UpdateEquipmentPickInEnchant();

public:
	explicit CEnchantWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CEnchantWindow();
};
