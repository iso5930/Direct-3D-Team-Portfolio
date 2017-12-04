#include "StdAfx.h"
#include "PlayScene_Cathedral_F2.h"

CPlayScene_Cathedral_F2::CPlayScene_Cathedral_F2(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_Cathedral_F2::~CPlayScene_Cathedral_F2()
{
	Release();
}

void CPlayScene_Cathedral_F2::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/Cathedral_F2.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_Cathedral_F2::Update()
{
	return CScene::Update();
}

void CPlayScene_Cathedral_F2::Render()
{
	CScene::Render();
}

void CPlayScene_Cathedral_F2::Release()
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
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Cath_Door"));

	// RemoveBuffer - Monster
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Archer_Red"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Shield_Red"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Summoner_Red"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Axe_Red"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("SkeletonSummoner_ArcaneBall"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Arrow"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_SwordTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_AxeTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_TrailEffect"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_SummonSkeleton"));
}

CScene* CPlayScene_Cathedral_F2::UpdateLoad()
{
	// AddNode
	CSeamlessMgr::GetInstance()->AddNode(3, 3); CSeamlessMgr::GetInstance()->AddNode(3, 103);
	CSeamlessMgr::GetInstance()->AddNode(103, 103); CSeamlessMgr::GetInstance()->AddNode(103, 3); CSeamlessMgr::GetInstance()->AddNode(103, 203);
	CSeamlessMgr::GetInstance()->AddNode(202, 202); CSeamlessMgr::GetInstance()->AddNode(202, 203); CSeamlessMgr::GetInstance()->AddNode(202, 103); CSeamlessMgr::GetInstance()->AddNode(202, 302);
	CSeamlessMgr::GetInstance()->AddNode(203, 203); CSeamlessMgr::GetInstance()->AddNode(203, 103); CSeamlessMgr::GetInstance()->AddNode(203, 202); CSeamlessMgr::GetInstance()->AddNode(203, 204); CSeamlessMgr::GetInstance()->AddNode(203, 302);
	CSeamlessMgr::GetInstance()->AddNode(204, 204); CSeamlessMgr::GetInstance()->AddNode(204, 103); CSeamlessMgr::GetInstance()->AddNode(204, 203);
	CSeamlessMgr::GetInstance()->AddNode(302, 302); CSeamlessMgr::GetInstance()->AddNode(302, 202); CSeamlessMgr::GetInstance()->AddNode(302, 203); CSeamlessMgr::GetInstance()->AddNode(302, 401); CSeamlessMgr::GetInstance()->AddNode(302, 402);
	CSeamlessMgr::GetInstance()->AddNode(402, 402); CSeamlessMgr::GetInstance()->AddNode(402, 302); CSeamlessMgr::GetInstance()->AddNode(402, 401);
	CSeamlessMgr::GetInstance()->AddNode(401, 401); CSeamlessMgr::GetInstance()->AddNode(401, 302); CSeamlessMgr::GetInstance()->AddNode(401, 400); CSeamlessMgr::GetInstance()->AddNode(401, 402);
	CSeamlessMgr::GetInstance()->AddNode(400, 400); CSeamlessMgr::GetInstance()->AddNode(400, 401);

	// AddBuffer - StaticProb
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Door"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gate_A/"), _T("trDun_Cath_Gate_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Archer_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Archer_Red/"), _T("Skeleton_Archer_Red.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Shield_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Shield_Red/"), _T("Skeleton_Shield_Red.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Summoner_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Summoner_Red/"), _T("Skeleton_Summoner_Red.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Axe_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Axe_Red/"), _T("Skeleton_Axe_Red.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Arrow"), new CStaticMesh(_T("../Resource/Mesh/Effect/Arrow0/"), _T("Arrow.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("SkeletonSummoner_ArcaneBall"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/SkeletonSummoner_ArcaneBall/"), _T("SkeletonSummoner_ArcaneBall.X")));

	// AddTexture - Effect
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_SwordTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_SwordTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_AxeTrail.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_AxeTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/SkeletonSummoner_SummonTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("SkeletonSummoner_TrailEffect"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Arcane_galaxy_Blend.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("SkeletonSummoner_SummonSkeleton"), pTexture);

	// SeamlessMgr - Enable
	CSeamlessMgr::GetInstance()->Enable();

	return CScene::UpdateLoad();
}

CScene* CPlayScene_Cathedral_F2::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// Cathedral_F2_GateWay
	CGateWay* pCathedral_F2_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_CATHEDRAL_F2);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F2_GateWay);
	pTransformCom = (CTransformCom*)pCathedral_F2_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6695.3f,352.0f,14781.0f);
	pCathedral_F2_GateWay->Initialize();

	// Cath2FToCath1F_Entrance
	CCath2FToCath1F_Entrance* pCath2FToCath1F_Entrance = new CCath2FToCath1F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath2FToCath1F_Entrance );
	pCath2FToCath1F_Entrance ->Initialize();
	pCath2FToCath1F_Entrance ->Event();

	// Cathedral_F1_Gate
	CGate* pCathedral_F1_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 1층"), _T("Cathedral_F1"), &D3DXVECTOR3(1741.0f, -583.0f, 13400.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F1);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F1_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F1_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(12862.0f, 40.0f, 8265.0f);
	pCathedral_F1_Gate->SetSize(272.0f, 195.0f, 14.0f);
	pCathedral_F1_Gate->Initialize();

	// Cath2FToCath3F_Entrance
	CCath2FToCath3F_Entrance* pCath2FToCath3F_Entrance = new CCath2FToCath3F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath2FToCath3F_Entrance );
	pCath2FToCath3F_Entrance ->Initialize();
	pCath2FToCath3F_Entrance ->Event();

	// Cathedral_F3_Gate
	CGate* pCathedral_F3_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 3층"), _T("Cathedral_F3"), &D3DXVECTOR3(6734.0f, 22.0f, 5001.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F3);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F3_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F3_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(1666.0f, -628.0f, 13760.0f);
	pCathedral_F3_Gate->SetSize(272.0f, 195.0f, 14.0f);
	pCathedral_F3_Gate->Initialize();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11207.0f, 0.0f, 7765.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10737.0f, 0.0f, 8008.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10115.0f, 2.0f, 7778.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9505.0f, 0.0f, 7985.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9606.0f, 2.0f, 8421.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10415.0f, 0.0f, 8466.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11265.0f, 2.0f, 8452.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10401.0f, 0.0f, 6171.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10556.0f, 0.0f, 5990.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10551.0f, 0.0f, 5561.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10495.0f, 0.0f, 5312.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10337.0f, 0.0f, 4379.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10560.0f, 0.0f, 4055.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10503.0f, 0.0f, 3638.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10469.0f, 3.0f, 3295.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10401.0f, 0.0f, 6171.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10556.0f, 0.0f, 5990.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10551.0f, 0.0f, 5561.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10495.0f, 0.0f, 5312.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10337.0f, 0.0f, 4379.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10560.0f, 0.0f, 4055.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10503.0f, 0.0f, 3638.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10469.0f, 3.0f, 3295.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10469.0f, 3.0f, 3295.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10957.0f, -296.0f, 2221.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11066.0f, -296.0f, 2545.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10802.0f, -296.0f, 2547.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10671.0f, -296.0f, 2201.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10487.0f, -296.0f, 2281.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10334.0f, -296.0f, 2521.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10201.0f, -296.0f, 2204.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10022.0f, -296.0f, 2338.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9780.0f, -296.0f, 2518.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_RED, rand() % 5 + 20));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7935.0f, 4.0f, 7425.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7729.0f, 4.0f, 7365.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7421.0f, 3.0f, 7249.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7672.0f, 4.0f, 7087.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7502.0f, 2.0f, 6948.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 20));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7894.0f, 4.0f, 7006.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 20));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6641.0f, 299.0f, 7478.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6486.0f, 296.0f, 7750.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6671.0f, 296.0f, 8010.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6528.0f, 299.0f, 8265.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6674.0f, 296.0f, 8618.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7505.0f, 0.0f, 8516.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7532.0f, 0.0f, 8809.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7765.0f, 1.0f, 8953.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7944.0f, 1.0f, 8946.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7946.0f, 1.0f, 8739.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7884.0f, 0.0f, 8543.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7700.0f, 0.0f, 8669.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7060.0f, 63.0f, 10889.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6745.0f, 63.0f, 10800.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6632.0f, 63.0f, 11090.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6817.0f, 63.0f, 11297.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7065.0f, 63.0f, 11134.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7698.0f, 63.0f, 11080.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7670.0f, 63.0f, 10874.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8522.0f, -316.0f, 13014.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8379.0f, -318.0f, 13246.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8242.0f, -318.0f, 13053.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7971.0f, -318.0f, 13030.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7956.0f, -318.0f, 13257.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7756.0f, -318.0f, 13296.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7862.0f, -318.0f, 13518.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8174.0f, -314.0f, 13536.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));	
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7487.0f, 318.0f, 14130.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7667.0f, 318.0f, 14390.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 24));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7790.0f, 318.0f, 14186.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 24));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8533.0f, 318.0f, 14888.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8322.0f, 318.0f, 15069.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8126.0f, 318.0f, 14932.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7926.0f, 318.0f, 15086.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7890.0f, 320.0f, 14842.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7699.0f, 318.0f, 14824.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7494.0f, 320.0f, 14995.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6595.0f, 0.0f, 13918.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6195.0f, 0.0f, 14131.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6097.0f, 0.0f, 13960.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5826.0f, 0.0f, 14066.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5626.0f, 0.0f, 13934.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5331.0f, 0.0f, 14035.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5034.0f, 0.0f, 13905.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4741.0f, 0.0f, 14118.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4345.0f, 0.0f, 13955.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3979.0f, 0.0f, 14067.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3838.0f, 2.0f, 13942.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3467.0f, 0.0f, 14070.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1245.0f, 0.0f, 14083.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1302.0f, 0.0f, 14306.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1524.0f, 0.0f, 14034.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1588.0f, 0.0f, 14282.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1522.0f, 0.0f, 14883.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1358.0f, 0.0f, 14905.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(666.0f, 0.0f, 15026.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(352.0f, 0.0f, 15041.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(231.0f, 0.0f, 14742.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(446.0f, 0.0f, 14659.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SHIELD_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(678.0f, 0.0f, 14470.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(396.0f, 0.0f, 14300.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(384.0f, 0.0f, 14139.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_RED, rand() % 5 + 28));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(718.0f, 0.0f, 14095.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_RED, rand() % 5 + 28));

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
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 2층"));
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

CScene* CPlayScene_Cathedral_F2::UpdatePlay()
{
	return CScene::UpdatePlay();
}