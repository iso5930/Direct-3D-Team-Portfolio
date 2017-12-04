#include "Header.h"

#define MIN_STR 64

struct MainStat
{
	int iStrength;							// ��
	int iAgility;							// ��ø
	int iIntelligence;						// ����
	int iVitality;							// Ȱ��

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
	float fReducedCooldownTime;				// ������ð� ����
	float fCriticalProbability;				// �ش�ȭ Ȯ��
	float fCriticalDamage;					// �ش�ȭ ����

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
	int iPhysicalResistance;				// ��������
	int iColdResistance;					// �ñ�����
	int iFlameResistance;					// ȭ������
	int iLightningResistance;				// ��������
	int iPoisonResistance;					// ������
	int iHolyResistance;					// �ż�����
	float fReducedNearDamage;				// �������ذ���
	float fReducedFarDamage;				// ����ü���ذ���

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
	float fRestoresBonus;					// ��ü ����� ���ʽ�
	int iLifeRecoveryOfSecond;				// �ʴ� ����� ȸ����
	int iLifeRecoveryOfHit;					// ���ߴ� ����� ȸ����

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
	int iControlRecoveryOfSecond;			// ���� ȸ����/��
	int iEffortRecoveryOfSecond;			// ���� ȸ����/��
	int iHateRecoveryOfSecond;				// ���� ȸ����/��
	int iManaRecoveryOfSecond;				// ���� ȸ����/��
	int iRageRecoveryOfSecond;				// �г� ȸ����/��
	int iVisionRecoveryOfSecond;			// ������ ȸ����/��
	float fReducedControlConsumption;		// ���� �Ҹ� ����
	float fReducedEffortConsumption;		// ���� �Ҹ� ����
	float fReducedHateConsumption;			// ���� �Ҹ� ����
	float fReducedManaConsumption;			// ���� �Ҹ� ����
	float fReducedRageConsumption;			// �г� �Ҹ� ����
	float fReducedVisionConsumption;		// ������ �Ҹ� ����

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
	float fExperience;						// �߰�����ġ
	float fMagicItemsFound;					// ���������۹߰�
	float fDiscoveryOfGoldCoins;			// ��ȭ�߰�

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
};

void BinaryToTxt()
{
	// ofs
	ofstream ofs("../Data/NaviMesh/Tristram.txt");

	// File
	HANDLE hFile = CreateFile(_T("../Data/NaviMesh/Tristram.dat"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;

	// Data
	char szData[256];

	// Size
	int iSize;
	ReadFile(hFile, &iSize, sizeof(int), &dwByte, NULL);
	itoa(iSize, szData, 10);
	ofs << iSize << endl;

	// Point
	D3DXVECTOR3 vPoint;

	for(int i = 0; i < iSize; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			ReadFile(hFile, &vPoint, sizeof(D3DXVECTOR3), &dwByte, NULL);

			gcvt(double(vPoint.x), 8, szData);
			ofs << szData << endl;

			gcvt(double(vPoint.y), 8, szData);
			ofs << szData << endl;

			gcvt(double(vPoint.z), 8, szData);
			ofs << szData << endl;
		}

		itoa(0, szData, 10);
		ofs << szData << endl;
	}

	ofs.close();
	CloseHandle(hFile);
}

void TxtToBinary()
{
	// ifs
	ifstream ifs("../Data/NaviMesh/Cathedral_F1.txt");

	// File
	HANDLE hFile = CreateFile(_T("../Data/NaviMesh/Cathedral_F1.dat"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;

	// Data
	char szData[256];

	// Size
	ifs >> szData;
	int iSize = atoi(szData);
	WriteFile(hFile, &iSize, sizeof(int), &dwByte, NULL);

	// Point
	D3DXVECTOR3 vPoint;

	// Type
	DWORD dwType;

	for(int i = 0; i < iSize; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			ifs >> szData;
			vPoint.x = float(atof(szData));
			ifs >> szData;
			vPoint.y = float(atof(szData));
			ifs >> szData;
			vPoint.z = float(atof(szData));

			WriteFile(hFile, &vPoint, sizeof(D3DXVECTOR3), &dwByte, NULL);
		}

		ifs >> szData;
		dwType = atoi(szData);
		WriteFile(hFile, &dwByte, sizeof(DWORD), &dwByte, NULL);
	}

	ifs.close();
	CloseHandle(hFile);
}

int main()
{
	TxtToBinary();

	return 0;
}