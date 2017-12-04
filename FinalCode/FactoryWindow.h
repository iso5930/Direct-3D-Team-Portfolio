#pragma once

#include "WindowUI.h"

class CFactoryButton;
class CCategoryButton;
class CFormulaButton;
class CVScroll;

class CFactoryWindow : public CWindowUI
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

	// Type
	int m_iType;

	// Select
	int m_iSelect;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// FactoryButton
	CFactoryButton* m_pFactoryButton[3];

	// WeaponFormula
	// 0(Axe), 1(Bow), 2(CeremonialDagger), 3(Fist), 4(HandXBow), 5(Mace), 6(Polearm), 7(Quiver), 8(Mighty1H), 9(Mighty2H)
	// 10(Shield), 11(Spear), 12(Staff), 13(Sword), 14(TwoHandAxe), 15(TwoHandMace), 16(TwoHandSword), 17(Wand), 18(Mojo)
	// 19(CrossBow), 20(Orb)
	vector<Formula*> m_WeaponFormula[21];

	// ArmorFormula
	// 0(Helms), 1(Shoulders), 2(ChestArmor), 3(Bracers), 4(Gloves), 5(Belt), 6(Pants), 7(Boots)
	vector<Formula*> m_ArmorFormula[8];

	// WeaponCategoryButton
	CCategoryButton* m_pWeaponCategoryButton[21];

	// ArmorCategoryButton
	CCategoryButton* m_pArmorCategoryButton[8];

	// WeaponFormulaButton
	vector<CFormulaButton*> m_WeaponFormulaButton[21];

	// ArmorFormulaButton
	vector<CFormulaButton*> m_ArmorFormulaButton[8];

	// WeaponItemSign
	vector<CItemSign*> m_WeaponItemSign;

	// ArmorItemSign
	vector<CItemSign*> m_ArmorItemSign;

	// DecomposeItem
	vector<Item*> m_DecomposeItem;

	// DecomposeItemSign
	vector<CItemSign*> m_DecomposeItemSign;

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
	void AddAxeFormula(Formula* _pFormula)				{ m_WeaponFormula[0].push_back(_pFormula); }
	void AddBowFormula(Formula* _pFormula)				{ m_WeaponFormula[1].push_back(_pFormula); }
	void AddCeremonialDaggerFormula(Formula* _pFormula)	{ m_WeaponFormula[2].push_back(_pFormula); }
	void AddFistFormula(Formula* _pFormula)				{ m_WeaponFormula[3].push_back(_pFormula); }
	void AddHandXBowFormula(Formula* _pFormula)			{ m_WeaponFormula[4].push_back(_pFormula); }
	void AddMaceFormula(Formula* _pFormula)				{ m_WeaponFormula[5].push_back(_pFormula); }
	void AddPolearmFormula(Formula* _pFormula)			{ m_WeaponFormula[6].push_back(_pFormula); }
	void AddQuiverFormula(Formula* _pFormula)			{ m_WeaponFormula[7].push_back(_pFormula); }
	void AddMighty1HFormula(Formula* _pFormula)			{ m_WeaponFormula[8].push_back(_pFormula); }
	void AddMighty2HFormula(Formula* _pFormula)			{ m_WeaponFormula[9].push_back(_pFormula); }
	void AddShieldFormula(Formula* _pFormula)			{ m_WeaponFormula[10].push_back(_pFormula); }
	void AddSpearFormula(Formula* _pFormula)			{ m_WeaponFormula[11].push_back(_pFormula); }
	void AddStaffFormula(Formula* _pFormula)			{ m_WeaponFormula[12].push_back(_pFormula); }
	void AddSwordFormula(Formula* _pFormula)			{ m_WeaponFormula[13].push_back(_pFormula); }
	void AddTwoHandAxeFormula(Formula* _pFormula)		{ m_WeaponFormula[14].push_back(_pFormula); }
	void AddTwoHandMaceFormula(Formula* _pFormula)		{ m_WeaponFormula[15].push_back(_pFormula); }
	void AddTwoHandSwordFormula(Formula* _pFormula)		{ m_WeaponFormula[16].push_back(_pFormula); }
	void AddWandFormula(Formula* _pFormula)				{ m_WeaponFormula[17].push_back(_pFormula); }
	void AddMojoFormula(Formula* _pFormula)				{ m_WeaponFormula[18].push_back(_pFormula); }
	void AddCrossBowFormula(Formula* _pFormula)			{ m_WeaponFormula[19].push_back(_pFormula); }
	void AddOrbFormula(Formula* _pFormula)				{ m_WeaponFormula[20].push_back(_pFormula); }

	void AddHelmsFormula(Formula* _pFormula)			{ m_ArmorFormula[0].push_back(_pFormula); }
	void AddShouldersFormula(Formula* _pFormula)		{ m_ArmorFormula[1].push_back(_pFormula); }
	void AddChestArmorFormula(Formula* _pFormula)		{ m_ArmorFormula[2].push_back(_pFormula); }
	void AddBracersFormula(Formula* _pFormula)			{ m_ArmorFormula[3].push_back(_pFormula); }
	void AddGlovesFormula(Formula* _pFormula)			{ m_ArmorFormula[4].push_back(_pFormula); }
	void AddBeltFormula(Formula* _pFormula)				{ m_ArmorFormula[5].push_back(_pFormula); }
	void AddPantsFormula(Formula* _pFormula)			{ m_ArmorFormula[6].push_back(_pFormula); }
	void AddBootsFormula(Formula* _pFormula)			{ m_ArmorFormula[7].push_back(_pFormula); }

public: ////////////////////////////////////////////////////////////////////////// Category
	// OpenWeaponCategory
	void OpenWeaponCategory(int _iIndex);

	// CloseWeaponCategory
	void CloseWeaponCategory(int _iIndex);

	// OpenArmorCategory
	void OpenArmorCategory(int _iIndex);

	// CloseArmorCategory
	void CloseArmorCategory(int _iIndex);

	// UpdateScroll
	void UpdateScroll();

	// UpdateWeaponCategory
	void UpdateWeaponCategory();

	// UpdateArmorCategory
	void UpdateArmorCategory();

	// CreateWeaponFormula
	void CreateWeaponFormula();

	// CreateArmorFormula
	void CreateArmorFormula();

	// MakeWeapon
	void MakeWeapon();

	// MakeArmor
	void MakeArmor();

public: ////////////////////////////////////////////////////////////////////////// Decompose
	// Decompose
	Item* Decompose(DWORD _dwItemClass);
	
	// DecomposeInInven
	bool DecomposeInInven(int _iIndex);

	// DecomposeInEquip
	bool DecomposeInEquip(int _iIndex);

	// DecomposeAll
	bool DecomposeAll(DWORD _dwItemClass);

private:
	////////////////////////////////////////////////////////////////////////// Pick
	void UpdateNonePick();
	void UpdatePick();
	void UpdateDecomposePick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateDecomposePickIn();
	
	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateDecomposePickOut();

	////////////////////////////////////////////////////////////////////////// InFactory
	void UpdateInFactory();
	void UpdateNonePickInFactory();
	void UpdatePickInFactory();
	void UpdateDecomposePickInFactory();

public:
	explicit CFactoryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CFactoryWindow();
};
