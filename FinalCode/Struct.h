#pragma once

struct TStrCompare
{
	TCHAR* tszKey;

	TStrCompare(TCHAR* _tszKey) : tszKey(_tszKey) { }
	template<typename T> bool operator()(T _t) { return !_tcscmp(_t.first, tszKey); }
};

struct Vertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR3 vTexUV;

	Vertex()
	{
		ZeroMemory(&vPos, sizeof(D3DXVECTOR3));
		ZeroMemory(&vNormal, sizeof(D3DXVECTOR3));
		ZeroMemory(&vTexUV, sizeof(D3DXVECTOR3));
	}
};

struct Index
{
	DWORD _1;
	DWORD _2;
	DWORD _3;

	Index()
	{
		_1 = 0;
		_2 = 0;
		_3 = 0;
	}
};

struct Particle
{
	D3DXVECTOR3 vPos;
	float		fSize;

	Particle()
	{
		ZeroMemory(&vPos, sizeof(D3DXVECTOR3));
		fSize = 10.f;
	}
};

struct ParticleValue
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVelocity;
	float		fTime;
	float		fAccTime;
	float		fSize;
	bool		bAlive;
};

struct Ray
{
	D3DXVECTOR3 vSrc;
	D3DXVECTOR3 vDir;

	Ray()
	{
		ZeroMemory(&vSrc, sizeof(D3DXVECTOR3));
		ZeroMemory(&vDir, sizeof(D3DXVECTOR3));
	}
};

struct MeshFrame : public D3DXFRAME
{
	D3DXMATRIX mCombinedMatrix;
};

struct MeshContainer : public D3DXMESHCONTAINER 
{
	LPDIRECT3DTEXTURE9* ppDiffuseTexture;
	LPDIRECT3DTEXTURE9* ppNormalTexture;
	LPDIRECT3DTEXTURE9* ppSpecularTexture;
	LPD3DXMESH pMesh;
	D3DXMATRIX* pOffsetMatrix;
	D3DXMATRIX** ppCombinedMatrix;
	D3DXMATRIX* pResultMatrix;
	LPD3DXBUFFER pCombinationBuf;
	DWORD dwMaxVertexInfl;
};

struct SkinningVTF
{
	DWORD dwNumMaterials;
	LPDIRECT3DTEXTURE9* ppCurVTF;
	LPDIRECT3DTEXTURE9* ppPreVTF;
	SkinningVTF* pFirstChild;
	SkinningVTF* pSibling;

	SkinningVTF()
	{
		dwNumMaterials = 0;
		ppCurVTF = NULL;
		ppPreVTF = NULL;
		pFirstChild = NULL;
		pSibling = NULL;
	}

	~SkinningVTF()
	{
		if(ppCurVTF != NULL)
		{
			for(DWORD i = 0; i < dwNumMaterials; ++i)
				ppCurVTF[i]->Release();

			delete[] ppCurVTF;
		}

		if(ppPreVTF != NULL)
		{
			for(DWORD i = 0; i < dwNumMaterials; ++i)
				ppPreVTF[i]->Release();

			delete[] ppPreVTF;
		}

		if(pFirstChild != NULL)
			delete pFirstChild;

		if(pSibling != NULL)
			delete pSibling;
	}
};

struct Info
{
	TCHAR tszMapKey[MIN_STR];
	TCHAR tszName[MIN_STR];
	int iGender;
	int iJob;

	Info()
	{
		ZeroMemory(tszMapKey, sizeof(tszMapKey));
		ZeroMemory(tszName, sizeof(tszName));
		iGender = 0;
		iJob = 0;
	}
};

struct Stat
{
	int iLevel;
	int iStrength;
	int iAgility;
	int iIntelligence;
	int iVitality;
	int iControl, iMaxControl;
	int iEffort, iMaxEffort;
	int iHate, iMaxHate;
	int iLife, iMaxLife;
	int iMana, iMaxMana;
	int iRage, iMaxRage;
	int iVision, iMaxVision;
	int iExp, iMaxExp;
	
	Stat()
	{
		iLevel = 0;
		iStrength = 0;
		iAgility = 0;
		iIntelligence = 0;
		iVitality = 0;
		iControl = 0, iMaxControl = 0;
		iEffort = 0, iMaxEffort = 0;
		iHate = 0, iMaxHate = 0;
		iLife = 0, iMaxLife = 0;
		iMana = 0, iMaxMana = 0;
		iRage = 0, iMaxRage = 0;
		iVision = 0, iMaxVision = 0;
		iExp = 0, iMaxExp = 0;
	}
};

struct MainStat
{
	int iStrength;							// 힘
	int iAgility;							// 민첩
	int iIntelligence;						// 지능
	int iVitality;							// 활력

	MainStat()
	{
		iStrength = 0;
		iAgility = 0;
		iIntelligence = 0;
		iVitality = 0;
	}

	MainStat(int _iStrength, int _iAgility, int _iIntelligence, int _iVitality)
	{
		iStrength = _iStrength;
		iAgility = _iAgility;
		iIntelligence = _iIntelligence;
		iVitality = _iVitality;
	}
};

struct AttackStat
{
	float fReducedCooldownTime;				// 재사용대기시간 감소
	float fCriticalProbability;				// 극대화 확률
	float fCriticalDamage;					// 극대화 피해

	AttackStat()
	{
		fReducedCooldownTime = 0.0f;
		fCriticalProbability = 0.0f;
		fCriticalDamage = 0.0f;
	}

	AttackStat(float _fReducedCooldownTime, float _fCriticalProbability, float _fCriticalDamage)
	{
		fReducedCooldownTime = _fReducedCooldownTime;
		fCriticalProbability = _fCriticalProbability;
		fCriticalDamage = _fCriticalProbability;
	}
};

struct DefenseStat
{
	int iPhysicalResistance;				// 물리저항
	int iColdResistance;					// 냉기저항
	int iFlameResistance;					// 화염저항
	int iLightningResistance;				// 번개저항
	int iPoisonResistance;					// 독저항
	int iHolyResistance;					// 신성저항
	float fReducedNearDamage;				// 근접피해감소
	float fReducedFarDamage;				// 투사체피해감소

	DefenseStat()
	{
		iPhysicalResistance = 0;
		iColdResistance = 0;
		iFlameResistance = 0;
		iLightningResistance = 0;
		iPoisonResistance = 0;
		iHolyResistance = 0;
		fReducedNearDamage = 0.0f;
		fReducedFarDamage = 0.0f;	
	}

	DefenseStat(int _iPhysicalResistance, int _iColdResistance, int _iFlameResistance, int _iLightningResistance, int _iPoisonResistance, int _iHolyResistance, float _fReducedNearDamage, float _fReducedFarDamage)
	{
		iPhysicalResistance = _iPhysicalResistance;
		iColdResistance = _iColdResistance;	
		iFlameResistance = _iFlameResistance;	
		iLightningResistance = _iLightningResistance;
		iPoisonResistance = _iPoisonResistance;	
		iHolyResistance = _iHolyResistance;	
		fReducedNearDamage = _fReducedNearDamage;
		fReducedFarDamage = _fReducedFarDamage;
	}
};

struct LifeStat
{
	float fRestoresBonus;					// 전체 생명력 보너스
	int iLifeRecoveryOfSecond;				// 초당 생명력 회복량
	int iLifeRecoveryOfHit;					// 적중당 생명력 회복량

	LifeStat()
	{
		fRestoresBonus = 0.0f;
		iLifeRecoveryOfSecond = 0;
		iLifeRecoveryOfHit = 0;
	}

	LifeStat(float _fRestoresBonus, int _iLifeRecoveryOfSecond, int _iLifeRecoveryOfHit)
	{
		fRestoresBonus = _fRestoresBonus;
		iLifeRecoveryOfSecond = _iLifeRecoveryOfSecond;
		iLifeRecoveryOfHit = _iLifeRecoveryOfHit;
	}
};

struct ResourceStat
{
	int iControlRecoveryOfSecond;			// 절제 회복량/초
	int iEffortRecoveryOfSecond;			// 공력 회복량/초
	int iHateRecoveryOfSecond;				// 증오 회복량/초
	int iManaRecoveryOfSecond;				// 마나 회복량/초
	int iRageRecoveryOfSecond;				// 분노 회복량/초
	int iVisionRecoveryOfSecond;			// 비전력 회복량/초
	float fReducedControlConsumption;		// 절제 소모량 감소
	float fReducedEffortConsumption;		// 공력 소모량 감소
	float fReducedHateConsumption;			// 증오 소모량 감소
	float fReducedManaConsumption;			// 마나 소모량 감소
	float fReducedRageConsumption;			// 분노 소모량 감소
	float fReducedVisionConsumption;		// 비전력 소모량 감소

	ResourceStat()
	{
		iControlRecoveryOfSecond = 0;
		iEffortRecoveryOfSecond = 0;
		iHateRecoveryOfSecond = 0;
		iManaRecoveryOfSecond = 0;
		iRageRecoveryOfSecond = 0;		
		iVisionRecoveryOfSecond = 0;
		fReducedControlConsumption = 0.0f;
		fReducedEffortConsumption = 0.0f;
		fReducedHateConsumption = 0.0f;
		fReducedManaConsumption = 0.0f;
		fReducedRageConsumption = 0.0f;
		fReducedVisionConsumption = 0.0f;
	}

	ResourceStat(int _iControlRecoveryOfSecond, int _iEffortRecoveryOfSecond, int _iHateRecoveryOfSecond, int _iManaRecoveryOfSecond, int _iRageRecoveryOfSecond, int _iVisionRecoveryOfSecond,
		float _fReducedControlConsumption, float _fReducedEffortConsumption, float _fReducedHateConsumption, float _fReducedManaConsumption, float _fReducedRageConsumption, float _fReducedVisionConsumption)
	{
		iControlRecoveryOfSecond = _iControlRecoveryOfSecond;
		iEffortRecoveryOfSecond = _iEffortRecoveryOfSecond;
		iHateRecoveryOfSecond = _iHateRecoveryOfSecond;
		iManaRecoveryOfSecond = _iManaRecoveryOfSecond;
		iRageRecoveryOfSecond = _iRageRecoveryOfSecond;		
		iVisionRecoveryOfSecond = _iVisionRecoveryOfSecond;
		fReducedControlConsumption = _fReducedControlConsumption;
		fReducedEffortConsumption = _fReducedEffortConsumption;
		fReducedHateConsumption = _fReducedHateConsumption;
		fReducedManaConsumption = _fReducedManaConsumption;
		fReducedRageConsumption = _fReducedRageConsumption;
		fReducedVisionConsumption = _fReducedVisionConsumption;
	}
};

struct AdventureStat
{
	float fExperience;						// 추가경험치
	float fMagicItemsFound;					// 마법아이템발견
	float fDiscoveryOfGoldCoins;			// 금화발견

	AdventureStat()
	{
		fExperience = 0.0f;
		fMagicItemsFound = 0.0f;
		fDiscoveryOfGoldCoins = 0.0f;
	}
};

struct Item
{
	TCHAR tszName[MIN_STR];
	TCHAR tszTexKey[MIN_STR];
	TCHAR tszBufKey[MIN_STR];
	DWORD dwItemClass;
	DWORD dwItemType;
	DWORD dwItemID;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
	int iGender;
	int iLevel;
	int iValue;
	int iNum;
	int iAtt;
	int iDef;
	MainStat tMainStat;
	AttackStat tAttackStat;
	DefenseStat tDefenseStat;
	LifeStat tLifeStat;
	ResourceStat tResourceStat;
	AdventureStat tAdventureStat;
	int iSockNum;
	int iSockCnt;
	Item* SockArr[3];

	Item()
	{
		ZeroMemory(tszName, sizeof(tszName));
		ZeroMemory(tszTexKey, sizeof(tszTexKey));
		ZeroMemory(tszBufKey, sizeof(tszBufKey));
		dwItemClass = 0;
		dwItemType = 0;
		dwItemID = 0;
		iPosX = 0;
		iPosY = 0;
		iWidth = 0;
		iHeight = 0;
		iGender = 0;
		iLevel = 0;
		iValue = 0;
		iNum = 1;
		iAtt = 0;
		iDef = 0;
		iSockNum = 0;
		iSockCnt = 0;
		ZeroMemory(SockArr, sizeof(SockArr));
	}

	Item(TCHAR* _tszName, TCHAR* _tszTexKey, TCHAR* _tszBufKey, DWORD _dwItemClass, DWORD _dwItemType, DWORD _dwItemID, int _iPosX, int _iPosY, int _iWidth, int _iHeight, int _iGender, int _iLevel, int _iValue, int _iNum, int _iAtt, int _iDef)
	{
		ZeroMemory(tszName, sizeof(tszName));		if(_tszName != NULL && _tcscmp(_tszName, _T("")) != 0) { _tcscpy_s(tszName, MIN_STR, _tszName); }
		ZeroMemory(tszTexKey, sizeof(tszTexKey));	if(_tszTexKey != NULL && _tcscmp(_tszTexKey, _T("")) != 0) { _tcscpy_s(tszTexKey, MIN_STR, _tszTexKey); }
		ZeroMemory(tszBufKey, sizeof(tszBufKey));	if(_tszBufKey != NULL && _tcscmp(_tszBufKey, _T("")) != 0) { _tcscpy_s(tszBufKey, MIN_STR, _tszBufKey); }
		dwItemClass = _dwItemClass;
		dwItemType = _dwItemType;
		dwItemID = _dwItemID;
		iPosX = _iPosX;
		iPosY = _iPosY;
		iWidth = _iWidth;
		iHeight = _iHeight;
		iGender = _iGender;
		iLevel = _iLevel;
		iValue = _iValue;
		iNum = _iNum;
		iAtt = _iAtt;
		iDef = _iDef;
		iSockNum = 0;
		iSockCnt = 0;
		ZeroMemory(SockArr, sizeof(SockArr));
	}

	Item(Item* _pItem)
	{
		ZeroMemory(tszName, sizeof(tszName));		if(_tcscmp(_pItem->tszName, _T("")) != 0) { _tcscpy_s(tszName, MIN_STR, _pItem->tszName); }
		ZeroMemory(tszTexKey, sizeof(tszTexKey));	if(_tcscmp(_pItem->tszTexKey, _T("")) != 0) { _tcscpy_s(tszTexKey, MIN_STR, _pItem->tszTexKey); }
		ZeroMemory(tszBufKey, sizeof(tszBufKey));	if(_tcscmp(_pItem->tszBufKey, _T("")) != 0) { _tcscpy_s(tszBufKey, MIN_STR, _pItem->tszBufKey); }
		dwItemClass = _pItem->dwItemClass;
		dwItemType = _pItem->dwItemType;
		dwItemID = _pItem->dwItemID;
		iPosX = _pItem->iPosX;
		iPosY = _pItem->iPosY;
		iWidth = _pItem->iWidth;
		iHeight = _pItem->iHeight;
		iGender = _pItem->iGender;
		iLevel = _pItem->iLevel;
		iValue = _pItem->iValue;
		iNum = _pItem->iNum;
		iAtt = _pItem->iAtt;
		iDef = _pItem->iDef;
		memcpy_s(&tMainStat, sizeof(MainStat), &_pItem->tMainStat, sizeof(MainStat));
		memcpy_s(&tAttackStat, sizeof(AttackStat), &_pItem->tAttackStat, sizeof(AttackStat));
		memcpy_s(&tDefenseStat, sizeof(DefenseStat), &_pItem->tDefenseStat, sizeof(DefenseStat));
		memcpy_s(&tLifeStat, sizeof(LifeStat), &_pItem->tLifeStat, sizeof(LifeStat));
		memcpy_s(&tResourceStat, sizeof(ResourceStat), &_pItem->tResourceStat, sizeof(ResourceStat));
		memcpy_s(&tAdventureStat, sizeof(AdventureStat), &_pItem->tAdventureStat, sizeof(AdventureStat));
		iSockNum = _pItem->iSockNum;
		iSockCnt = _pItem->iSockCnt;
		ZeroMemory(SockArr, sizeof(SockArr));
		for(int i = 0; i < iSockCnt; ++i)
			SockArr[i] = new Item(_pItem->SockArr[i]);
	}

	~Item()
	{
		for(int i = 0; i < 3; ++i)
		{
			if(SockArr[i] != NULL)
			{
				delete SockArr[i];
				SockArr[i] = NULL;
			}
		}
	}

	int Item::GetStrength()
	{
		int iTemp = tMainStat.iStrength;
		for(int i = 0; i < iSockCnt; ++i)
			iTemp += SockArr[i]->tMainStat.iStrength;
		return iTemp;
	}

	int Item::GetAgility()
	{
		int iTemp = tMainStat.iAgility;
		for(int i = 0; i < iSockCnt; ++i)
			iTemp += SockArr[i]->tMainStat.iAgility;
		return iTemp;
	}

	int Item::GetIntelligence()
	{
		int iTemp = tMainStat.iIntelligence;
		for(int i = 0; i < iSockCnt; ++i)
			iTemp += SockArr[i]->tMainStat.iIntelligence;
		return iTemp;
	}

	int Item::GetVitality()
	{
		int iTemp = tMainStat.iVitality;
		for(int i = 0; i < iSockCnt; ++i)
			iTemp += SockArr[i]->tMainStat.iVitality;
		return iTemp;
	}
};

struct Formula
{
	Item* pItem;
	int iIronNum;
	int iCrystalNum;
	int iPatternsNum;
	int iDiamondNum;
	int iManaSourceNum;
	int iAdamantiumNum;
	int iMetalStainNum;

	int iTopazNum1;
	int iTopazNum2;
	int iTopazNum3;
	int iTopazNum4;
	int iTopazNum5;

	int iSapphireNum1;
	int iSapphireNum2;
	int iSapphireNum3;
	int iSapphireNum4;
	int iSapphireNum5;

	int iRubyNum1;
	int iRubyNum2;
	int iRubyNum3;
	int iRubyNum4;
	int iRubyNum5;

	int iEmeraldNum1;
	int iEmeraldNum2;
	int iEmeraldNum3;
	int iEmeraldNum4;
	int iEmeraldNum5;

	int iDiamondNum1;
	int iDiamondNum2;
	int iDiamondNum3;
	int iDiamondNum4;
	int iDiamondNum5;

	int iAmethystNum1;
	int iAmethystNum2;
	int iAmethystNum3;
	int iAmethystNum4;
	int iAmethystNum5;

	Formula()
	{
		pItem = NULL;

		iIronNum = 0;
		iCrystalNum = 0;
		iPatternsNum = 0;
		iDiamondNum = 0;
		iManaSourceNum = 0;
		iAdamantiumNum = 0;
		iMetalStainNum = 0;

		iTopazNum1 = 0;
		iTopazNum2 = 0;
		iTopazNum3 = 0;
		iTopazNum4 = 0;
		iTopazNum5 = 0;

		iSapphireNum1 = 0;
		iSapphireNum2 = 0;
		iSapphireNum3 = 0;
		iSapphireNum4 = 0;
		iSapphireNum5 = 0;

		iRubyNum1 = 0;
		iRubyNum2 = 0;
		iRubyNum3 = 0;
		iRubyNum4 = 0;
		iRubyNum5 = 0;

		iEmeraldNum1 = 0;
		iEmeraldNum2 = 0;
		iEmeraldNum3 = 0;
		iEmeraldNum4 = 0;
		iEmeraldNum5 = 0;

		iDiamondNum1 = 0;
		iDiamondNum2 = 0;
		iDiamondNum3 = 0;
		iDiamondNum4 = 0;
		iDiamondNum5 = 0;

		iAmethystNum1 = 0;
		iAmethystNum2 = 0;
		iAmethystNum3 = 0;
		iAmethystNum4 = 0;
		iAmethystNum5 = 0;
	}

	Formula(Item* _pItem)
	{
		pItem = _pItem;

		iIronNum = 0;
		iCrystalNum = 0;
		iPatternsNum = 0;
		iDiamondNum = 0;
		iManaSourceNum = 0;
		iAdamantiumNum = 0;
		iMetalStainNum = 0;

		iTopazNum1 = 0;
		iTopazNum2 = 0;
		iTopazNum3 = 0;
		iTopazNum4 = 0;
		iTopazNum5 = 0;

		iSapphireNum1 = 0;
		iSapphireNum2 = 0;
		iSapphireNum3 = 0;
		iSapphireNum4 = 0;
		iSapphireNum5 = 0;

		iRubyNum1 = 0;
		iRubyNum2 = 0;
		iRubyNum3 = 0;
		iRubyNum4 = 0;
		iRubyNum5 = 0;

		iEmeraldNum1 = 0;
		iEmeraldNum2 = 0;
		iEmeraldNum3 = 0;
		iEmeraldNum4 = 0;
		iEmeraldNum5 = 0;

		iDiamondNum1 = 0;
		iDiamondNum2 = 0;
		iDiamondNum3 = 0;
		iDiamondNum4 = 0;
		iDiamondNum5 = 0;

		iAmethystNum1 = 0;
		iAmethystNum2 = 0;
		iAmethystNum3 = 0;
		iAmethystNum4 = 0;
		iAmethystNum5 = 0;
	}

	void SetMaterial(int _iIronNum, int _iCrystalNum, int _iPatternsNum, int _iDiamondNum, int _iManaSourceNum, int _iAdamantiumNum, int _iMetalStainNum)
	{
		iIronNum = _iIronNum;
		iCrystalNum = _iCrystalNum;
		iPatternsNum = _iPatternsNum;
		iDiamondNum = _iDiamondNum;
		iManaSourceNum = _iManaSourceNum;
		iAdamantiumNum = _iAdamantiumNum;
		iMetalStainNum = _iMetalStainNum;
	}

	void SetTopaz(int _iTopazNum1, int _iTopazNum2, int _iTopazNum3, int _iTopazNum4, int _iTopazNum5)
	{
		iTopazNum1 = _iTopazNum1;
		iTopazNum2 = _iTopazNum2;
		iTopazNum3 = _iTopazNum3;
		iTopazNum4 = _iTopazNum4;
		iTopazNum5 = _iTopazNum5;
	}

	void SetSapphire(int _iSapphireNum1, int _iSapphireNum2, int _iSapphireNum3, int _iSapphireNum4, int _iSapphireNum5)
	{
		iSapphireNum1 = _iSapphireNum1;
		iSapphireNum2 = _iSapphireNum2;
		iSapphireNum3 = _iSapphireNum3;
		iSapphireNum4 = _iSapphireNum4;
		iSapphireNum5 = _iSapphireNum5;
	}

	void SetRuby(int _iRubyNum1, int _iRubyNum2, int _iRubyNum3, int _iRubyNum4, int _iRubyNum5)
	{
		iRubyNum1 = _iRubyNum1;
		iRubyNum2 = _iRubyNum2;
		iRubyNum3 = _iRubyNum3;
		iRubyNum4 = _iRubyNum4;
		iRubyNum5 = _iRubyNum5;
	}

	void SetEmerald(int _iEmeraldNum1, int _iEmeraldNum2, int _iEmeraldNum3, int _iEmeraldNum4, int _iEmeraldNum5)
	{
		iEmeraldNum1 = _iEmeraldNum1;
		iEmeraldNum2 = _iEmeraldNum2;
		iEmeraldNum3 = _iEmeraldNum3;
		iEmeraldNum4 = _iEmeraldNum4;
		iEmeraldNum5 = _iEmeraldNum5;
	}

	void SetDiamond(int _iDiamondNum1, int _iDiamondNum2, int _iDiamondNum3, int _iDiamondNum4, int _iDiamondNum5)
	{
		iDiamondNum1 = _iDiamondNum1;
		iDiamondNum2 = _iDiamondNum2;
		iDiamondNum3 = _iDiamondNum3;
		iDiamondNum4 = _iDiamondNum4;
		iDiamondNum5 = _iDiamondNum5;
	}

	void SetAmethyst(int _iAmethystNum1, int _iAmethystNum2, int _iAmethystNum3, int _iAmethystNum4, int _iAmethystNum5)
	{
		iAmethystNum1 = _iAmethystNum1;
		iAmethystNum2 = _iAmethystNum2;
		iAmethystNum3 = _iAmethystNum3;
		iAmethystNum4 = _iAmethystNum4;
		iAmethystNum5 = _iAmethystNum5;
	}

	~Formula()
	{
		if(pItem != NULL)
		{
			delete pItem;
			pItem = NULL;
		}
	}
};

struct Quest
{
	QUEST_TYPE eQuestType;
	int iStep;

	Quest()
	{
		eQuestType = QUEST_TYPE_END;
		iStep = 0;
	}

	Quest(QUEST_TYPE _eQuestType, int _iStep)
	{
		eQuestType = _eQuestType;
		iStep = _iStep;
	}

	Quest(Quest* _pQuest)
	{
		eQuestType = _pQuest->eQuestType;
		iStep = _pQuest->iStep;
	}
};

struct Achieve
{
	ACHIEVE_TYPE eAchieveType;

	Achieve()
	{
		eAchieveType = ACHIEVE_TYPE_END;
	}

	Achieve(ACHIEVE_TYPE _eAchieveType)
	{
		eAchieveType = _eAchieveType;
	}

	Achieve(Achieve* _pAchieve)
	{
		eAchieveType = _pAchieve->eAchieveType;
	}
};

struct FollowerInfo
{
	FOLLOWER_TYPE eFollowerType;
	Stat stat;

	FollowerInfo()
	{
		// FollowerType
		eFollowerType = FOLLOWER_TYPE_END;

		// Stat
		ZeroMemory(&stat, sizeof(stat));
	}
};

struct Account 
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vAngle;
	D3DXVECTOR3 vSize;
	SLOT_TYPE eSlotType[7];
	SLOT_ID eSlotID[7];
	Info info;
	Stat stat;

	// Item
	int iItemNum;
	vector<Item*> ItemVec;
	
	// Equip
	int iEquipNum;
	vector<int> EquipIndexVec;
	vector<Item*> EquipVec;

	// Storage
	int iStorageNum[5];
	vector<Item*> StorageVec[5];
	
	// Quest
	int iQuestNum;
	vector<Quest*> QuestVec;

	// Achieve
	int iAchieveNum;
	vector<Achieve*> AchieveVec;

	// HaveFollower
	bool bHaveFollower;

	// FollowerInfo
	FollowerInfo followerInfo;

	D3DXVECTOR3 vFollowerPos;
	D3DXVECTOR3 vFollowerAngle;
	D3DXVECTOR3 vFollowerSize;

	// FollowerEquip
	int iFollowerEquipNum;
	vector<int> FollowerEquipIndexVec;
	vector<Item*> FollowerEquipVec;

	// GateWayNum
	int iGateWayNum;
	vector<int> GateWayVec;

	Account()
	{
		// Pos
		ZeroMemory(&vPos, sizeof(D3DXVECTOR3));

		// Angle
		ZeroMemory(&vAngle, sizeof(D3DXVECTOR3));

		// Size
		vSize.x = 1.0f, vSize.y = 1.0f, vSize.z = 1.0f;

		// Slot
		for(int i = 0; i < 7; ++i)
		{
			eSlotType[i] = SLOT_TYPE_END;
			eSlotID[i] = SLOT_ID_END;
		}

		// ItemNum
		iItemNum = 0;

		// EquipNum
		iEquipNum = 0;

		// StorageNum
		for(int i = 0; i < 5; ++i)
			iStorageNum[i] = 0;

		// QuestNum
		iQuestNum = 0;

		// AchieveNum
		iAchieveNum = 0;

		// HaveFollower
		bHaveFollower = false;

		// FollowerPos
		ZeroMemory(&vFollowerPos, sizeof(D3DXVECTOR3));

		// FollowerAngle
		ZeroMemory(&vFollowerAngle, sizeof(D3DXVECTOR3));

		// FollowerSize
		vFollowerSize.x = 1.0f, vFollowerSize.y = 1.0f, vFollowerSize.z = 1.0f;

		// FollowerEquipNum
		iFollowerEquipNum = 0;

		// GateWayNum
		iGateWayNum = 0;
	}

	~Account()
	{
		// ItemVec
		for(int i = 0; i < iItemNum; ++i)
		{
			delete ItemVec[i];
			ItemVec[i] = NULL;
		}
		ItemVec.clear();

		// EquipVec
		for(int i = 0; i < iEquipNum; ++i)
		{
			delete EquipVec[i];
			EquipVec[i] = NULL;
		}
		EquipVec.clear();

		// StorageVec
		for(int i = 0; i < 5; ++i)
		{
			for(size_t j = 0; j < StorageVec[i].size(); ++j)
			{
				delete StorageVec[i][j];
				StorageVec[i][j] = NULL;
			}
			StorageVec[i].clear();
		}

		// QuestVec
		for(int i = 0; i < iQuestNum; ++i)
		{
			delete QuestVec[i];
			QuestVec[i] = NULL;
		}
		QuestVec.clear();

		// AchieveVec
		for(int i = 0; i < iAchieveNum; ++i)
		{
			delete AchieveVec[i];
			AchieveVec[i] = NULL;
		}
		AchieveVec.clear();

		// FollowerEquipVec
		for(int i = 0; i < iFollowerEquipNum; ++i)
		{
			delete FollowerEquipVec[i];
			FollowerEquipVec[i] = NULL;
		}
		FollowerEquipVec.clear();
	}
};

struct IntersectInfo
{
	BOOL bHit;
	float u, v, dist;
	DWORD dwFaceIndex, dwCountOfHits;
	LPD3DXBUFFER pBuffer;

	IntersectInfo()
	{
		bHit = FALSE;
		u = 0.0f, v = 0.0f, dist = 0.0f;
		dwFaceIndex = 0, dwCountOfHits = 0;
		pBuffer = NULL;
	}
};

struct Collision
{
	D3DXVECTOR3 vAxisX;
	D3DXVECTOR3 vAxisY;
	D3DXVECTOR3 vAxisZ;
	DWORD dwType;
	D3DXMATRIX* pMatrix;
	D3DXVECTOR3 vCenter;
	float fWidth;
	float fHeight;
	float fDepth;
	vector<void*> ExceptVec;

	Collision(DWORD _dwType, D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pCenter, float _fWidth, float _fHeight, float _fDepth)
	{
		ZeroMemory(&vAxisX, sizeof(D3DXVECTOR3));
		ZeroMemory(&vAxisY, sizeof(D3DXVECTOR3));
		ZeroMemory(&vAxisZ, sizeof(D3DXVECTOR3));
		dwType = _dwType;
		pMatrix = _pMatrix;
		vCenter = (*_pCenter);
		fWidth = _fWidth;
		fHeight = _fHeight;
		fDepth = _fDepth;
	}
};

struct Sphere
{
	D3DXMATRIX* pMatrix;
	D3DXVECTOR3 vCenter;
	float fRadius;
	vector<void*> ExceptVec;

	Sphere(D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pCenter, float _fRadius)
	{
		pMatrix = _pMatrix;
		vCenter = (*_pCenter);
		fRadius = _fRadius;
	}
};

struct Bone
{
	MeshFrame* pFrame;
	D3DXMATRIX mWorld;

	Bone()
	{
		pFrame = NULL;
		D3DXMatrixIdentity(&mWorld);
	}
};

struct Frame
{
	int iStart;
	int iEnd;
	int iCur;
	float fFrameTime;
	float fAccTime;

	Frame() 
	{
		iStart = 0;
		iEnd = 0;
		iCur = 0;
		fFrameTime = 0.0f;
		fAccTime = 0.0f;
	}
};

struct Buff
{
	BUFF_TYPE eBuffType;
	float fAccTime;
	float fFrameTime;

	Buff(BUFF_TYPE _eBuffType, float _fFrameTime)
	{
		eBuffType = _eBuffType;
		fAccTime = 0.0f;
		fFrameTime = _fFrameTime;
	}
};

struct Mez
{
	SKILL_TYPE eSkillType;
	float fAccTime;
	float fFrameTime;

	Mez(SKILL_TYPE _eSkillType, float _fFrameTime)
	{
		eSkillType = _eSkillType;
		fAccTime = 0.0f;
		fFrameTime = _fFrameTime;
	}
};

struct MonsterSpawn
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vAngle;
	D3DXVECTOR3 vSize;
	MONSTER_TYPE eMonsterType;
	int iLevel;

	MonsterSpawn(D3DXVECTOR3* _pPos, D3DXVECTOR3* _pAngle, D3DXVECTOR3* _pSize, MONSTER_TYPE _eMonsterType, int _iLevel)
	{
		vPos = *_pPos;
		vAngle = *_pAngle;
		vSize = *_pSize;
		eMonsterType = _eMonsterType;
		iLevel = _iLevel;
	}
};