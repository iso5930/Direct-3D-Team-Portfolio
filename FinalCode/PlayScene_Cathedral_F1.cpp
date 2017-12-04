#include "StdAfx.h"
#include "PlayScene_Cathedral_F1.h"

CPlayScene_Cathedral_F1::CPlayScene_Cathedral_F1(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_Cathedral_F1::~CPlayScene_Cathedral_F1()
{
	Release();
}

void CPlayScene_Cathedral_F1::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/Cathedral_F1.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_Cathedral_F1::Update()
{
	return CScene::Update();
}

void CPlayScene_Cathedral_F1::Render()
{
	CScene::Render();
}

void CPlayScene_Cathedral_F1::Release()
{
	// InputMgr - Disable
	CInputMgr::GetInstance()->Disable();

	// UIMgr - Disable
	CUIMgr::GetInstance()->Disable();

	// SeamlessMgr - Disable
	CSeamlessMgr::GetInstance()->Disable();

	// RenderMode
	CRenderMgr::GetInstance()->SetRenderMode(0);

	// RemoveBuffer - StaticProb
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_GateWay"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Cath_Death_Guard"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Cath_Door"));

	// RemoveBuffer - Monster
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_OneHand_Mint"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Shield_Brown"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Archer_Mint"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Summoner_Brown"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("SkeletonSummoner_ArcaneBall"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Arrow"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Stitch_Spike"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_SwordTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_TrailEffect"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_SummonSkeleton"));
}

CScene* CPlayScene_Cathedral_F1::UpdateLoad()
{
	// AddNode
	CSeamlessMgr::GetInstance()->AddNode(2, 2); CSeamlessMgr::GetInstance()->AddNode(2, 102);
	CSeamlessMgr::GetInstance()->AddNode(102, 2); CSeamlessMgr::GetInstance()->AddNode(102, 102); CSeamlessMgr::GetInstance()->AddNode(102, 202);
	CSeamlessMgr::GetInstance()->AddNode(202, 102); CSeamlessMgr::GetInstance()->AddNode(202, 202); CSeamlessMgr::GetInstance()->AddNode(202, 201);
	CSeamlessMgr::GetInstance()->AddNode(201, 200); CSeamlessMgr::GetInstance()->AddNode(201, 201); CSeamlessMgr::GetInstance()->AddNode(201, 202);
	CSeamlessMgr::GetInstance()->AddNode(200, 201); CSeamlessMgr::GetInstance()->AddNode(200, 200); CSeamlessMgr::GetInstance()->AddNode(200, 300);
	CSeamlessMgr::GetInstance()->AddNode(300, 300); CSeamlessMgr::GetInstance()->AddNode(300, 200); CSeamlessMgr::GetInstance()->AddNode(300, 201); CSeamlessMgr::GetInstance()->AddNode(300, 400);
	CSeamlessMgr::GetInstance()->AddNode(400, 300); CSeamlessMgr::GetInstance()->AddNode(400, 400);

	// AddBuffer - StaticProb
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Death_Guard"), new CStaticMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gore_H/"), _T("trDun_Cath_Gore_H.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Door"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gate_A/"), _T("trDun_Cath_Gate_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_OneHand_Mint"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_OneHand_Mint/"), _T("Skeleton_OneHand_Mint.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Shield_Brown"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Shield_Brown/"), _T("Skeleton_Shield_Brown.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Archer_Mint"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Archer_Mint/"), _T("Skeleton_Archer_Mint.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Summoner_Brown"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Summoner_Brown/"), _T("Skeleton_Summoner_Brown.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("SkeletonSummoner_ArcaneBall"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/SkeletonSummoner_ArcaneBall/"), _T("SkeletonSummoner_ArcaneBall.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Arrow"), new CStaticMesh(_T("../Resource/Mesh/Effect/Arrow0/"), _T("Arrow.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Stitch_Spike"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Stitch_Spike/"), _T("Stitch_Spike.X")));

	// AddTexture - Effect
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_SwordTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_SwordTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/SkeletonSummoner_SummonTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("SkeletonSummoner_TrailEffect"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Arcane_galaxy_Blend.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("SkeletonSummoner_SummonSkeleton"), pTexture);

	// SeamlessMgr - Enable
	CSeamlessMgr::GetInstance()->Enable();

	return CScene::UpdateLoad();
}

CScene* CPlayScene_Cathedral_F1::UpdateComplete()
{
	// PlaySoundForSystemBGM
	CSoundMgr::GetInstance()->StopSoundForSystemBGM();
	CSoundMgr::GetInstance()->PlaySoundForSystemBGM(_T("BGM3.ogg"));

	// TransformCom
	CTransformCom* pTransformCom;

	// Cathedral_Death_Guard
	CCathedral_Death_Guard* pCathedral_Death_Guard = new CCathedral_Death_Guard(_T("StaticProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_Death_Guard);
	pCathedral_Death_Guard->Initialize();

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST10) != NULL)
		pCathedral_Death_Guard->EventEnd();

	// Cathedral_F1_GateWay
	CGateWay* pCathedral_F1_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_CATHEDRAL_F1);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F1_GateWay);
	pTransformCom = (CTransformCom*)pCathedral_F1_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6692.91f, 354.0f, 8659.0f);
	pCathedral_F1_GateWay->Initialize();

	// Cath1FToTristram_Entrance
	CCath1FToTristram_Entrance* pCath1FToTristram_Entrance = new CCath1FToTristram_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath1FToTristram_Entrance);
	pCath1FToTristram_Entrance->Initialize();
	pCath1FToTristram_Entrance->Event();

	// Cath1FToCath2_Entrance
	CCath1FToCath2F_Entrance* pCath1FToCath2F_Entrance = new CCath1FToCath2F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath1FToCath2F_Entrance);
	pCath1FToCath2F_Entrance->Initialize();

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST10) != NULL)
		pCath1FToCath2F_Entrance->Event();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7539.0f, 0.0f, 3540.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7392.0f, 0.0f, 3799.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7530.0f, 0.0f, 4181.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7282.0f, 0.0f, 4417.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7047.0f, 63.0f, 4782.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6738.0f, 63.0f, 4653.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6617.0f, 63.0f, 4828.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6608.0f, 68.0f, 5153.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6864.0f, 63.0f, 5190.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7659.0f, 63.0f, 4851.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7526.0f, 0.0f, 6122.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7274.0f, 0.0f, 6357.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7443.0f, 0.0f, 6637.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7914.0f, -314.0f, 6945.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7777.0f, -318.0f, 7101.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7886.0f, -318.0f, 7289.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8086.0f, -318.0f, 7407.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8065.0f, -318.0f, 7209.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8173.0f, -318.0f, 7006.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8414.0f, -318.0f, 6917.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7914.0f, -314.0f, 6945.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7777.0f, -318.0f, 7101.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7886.0f, -318.0f, 7289.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8086.0f, -318.0f, 7407.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8065.0f, -318.0f, 7209.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8173.0f, -318.0f, 7006.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 10));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8414.0f, -318.0f, 6917.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 10));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8523.0f, 318.0f, 8731.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8511.0f, 318.0f, 8936.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8176.0f, 318.0f, 8851.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7923.0f, 318.0f, 8956.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7816.0f, 318.0f, 8752.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7480.0f, 320.0f, 8825.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6552.0f, 0.0f, 7792.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6180.0f, 0.0f, 7785.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6142.0f, 0.0f, 8039.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5722.0f, 0.0f, 7820.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5014.0f, 0.0f, 8470.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4419.0f, 0.0f, 8414.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3727.0f, 0.0f, 8469.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3606.0f, 2.0f, 7879.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4100.0f, 0.0f, 7773.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4580.0f, 2.0f, 7892.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5095.0f, 2.0f, 7896.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1755.0f, 4.0f, 7446.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1456.0f, 0.0f, 7311.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1338.0f, 0.0f, 7025.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1548.0f, 4.0f, 6957.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1764.0f, 4.0f, 7032.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1576.0f, 4.0f, 7175.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(483.0f, 296.0f, 7986.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(472.0f, 299.0f, 8345.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(383.0f, 299.0f, 8697.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(482.0f, 299.0f, 8955.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 14));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1386.0f, 0.0f, 8893.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1614.0f, 1.0f, 8955.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1825.0f, 1.0f, 8807.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1637.0f, 0.0f, 8667.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1403.0f, 0.0f, 8632.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1491.0f, 0.0f, 8480.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1759.0f, 4.0f, 8446.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(582.0f, 63.0f, 10871.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(505.0f, 63.0f, 11193.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(699.0f, 63.0f, 11297.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(767.0f, 63.0f, 11085.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(998.0f, 63.0f, 11034.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1249.0f, 0.0f, 11478.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1429.0f, 0.0f, 11910.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1266.0f, 0.0f, 12282.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1347.0f, 0.0f, 13099.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1163.0f, 0.0f, 13384.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1619.0f, -293.0f, 14536), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1705.0f, -296.0f, 13956), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1871.0f, -291.0f, 14138), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2061.0f, -293.0f, 14620), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2320.0f, -296.0f, 14710), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_BROWN, rand() % 5 + 18));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2369.0f, -296.0f, 14388), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_MINT, rand() % 5 + 18));

	// Light0
	CLight* pLight0 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 0, LIGHT_TYPE_SHADOW, NULL, NULL, NULL, NULL, NULL, 0.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight0);
	pLight0->SetView(1500.f, &D3DXVECTOR3(D3DX_PI / 4.0f, D3DX_PI / 2.0f, 0.0f));
	pLight0->SetProj(D3DXToRadian(90.0f), 1.0f, 1.0f, 3000.f);
	pLight0->Initialize();

	// Light1
	CLight* pLight1 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 1, LIGHT_TYPE_DIRECTION, &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), &D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f), NULL, &D3DXVECTOR4(0.0f, -1.0f, 1.0f, 0.0f), 0.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight1);
	pLight1->Initialize();

	// Light2
	CLight* pLight2 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 2, LIGHT_TYPE_POINT, &D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f), &D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight2);
	pLight2->Initialize();

	// SceneMessage
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 1층"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(pSceneMessage);
	pSceneMessage->Initialize();

	// InputMgr - Enable
	CInputMgr::GetInstance()->Enable();

	// UIMgr - Enable
	CUIMgr::GetInstance()->Enable();

	// LightMgr - Enable
	CLightMgr::GetInstance()->Enable(0);

	// RenderMgr - RenderMode
	CRenderMgr::GetInstance()->SetRenderMode(0xFFFFFFFF);

	return CScene::UpdateComplete();
}

CScene* CPlayScene_Cathedral_F1::UpdatePlay()
{
	return CScene::UpdatePlay();
}