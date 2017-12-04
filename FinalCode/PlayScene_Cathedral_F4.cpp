#include "StdAfx.h"
#include "PlayScene_Cathedral_F4.h"

CPlayScene_Cathedral_F4::CPlayScene_Cathedral_F4(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_Cathedral_F4::~CPlayScene_Cathedral_F4()
{
	Release();
}

void CPlayScene_Cathedral_F4::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/Cathedral_F4.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_Cathedral_F4::Update()
{
	return CScene::Update();
}

void CPlayScene_Cathedral_F4::Render()
{
	CScene::Render();
}

void CPlayScene_Cathedral_F4::Release()
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
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Archer_Brown"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Ghoul"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Summoner_Blue"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Axe_Blue"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("SkeletonSummoner_ArcaneBall"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Ghoul_Scratch_A"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Ghoul_Scratch_B"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Arrow"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_AxeTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_SwordTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_TrailEffect"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonSummoner_SummonSkeleton"));
}

CScene* CPlayScene_Cathedral_F4::UpdateLoad()
{
	// AddNode
	CSeamlessMgr::GetInstance()->AddNode(1, 1); CSeamlessMgr::GetInstance()->AddNode(1, 2); CSeamlessMgr::GetInstance()->AddNode(1, 101);
	CSeamlessMgr::GetInstance()->AddNode(2, 2); CSeamlessMgr::GetInstance()->AddNode(2, 1); CSeamlessMgr::GetInstance()->AddNode(2, 3); CSeamlessMgr::GetInstance()->AddNode(2, 101);
	CSeamlessMgr::GetInstance()->AddNode(3, 3); CSeamlessMgr::GetInstance()->AddNode(3, 2);
	CSeamlessMgr::GetInstance()->AddNode(101, 101); CSeamlessMgr::GetInstance()->AddNode(101, 1); CSeamlessMgr::GetInstance()->AddNode(101, 2); CSeamlessMgr::GetInstance()->AddNode(101, 200); CSeamlessMgr::GetInstance()->AddNode(101, 201); CSeamlessMgr::GetInstance()->AddNode(101, 202);
	CSeamlessMgr::GetInstance()->AddNode(200, 200); CSeamlessMgr::GetInstance()->AddNode(200, 101); CSeamlessMgr::GetInstance()->AddNode(200, 201);
	CSeamlessMgr::GetInstance()->AddNode(201, 201); CSeamlessMgr::GetInstance()->AddNode(201, 101); CSeamlessMgr::GetInstance()->AddNode(201, 200); CSeamlessMgr::GetInstance()->AddNode(201, 202);
	CSeamlessMgr::GetInstance()->AddNode(202, 202); CSeamlessMgr::GetInstance()->AddNode(202, 101); CSeamlessMgr::GetInstance()->AddNode(202, 201); CSeamlessMgr::GetInstance()->AddNode(202, 203); CSeamlessMgr::GetInstance()->AddNode(202, 303);
	CSeamlessMgr::GetInstance()->AddNode(203, 203); CSeamlessMgr::GetInstance()->AddNode(203, 202); CSeamlessMgr::GetInstance()->AddNode(203, 303);
	CSeamlessMgr::GetInstance()->AddNode(303, 303); CSeamlessMgr::GetInstance()->AddNode(303, 202); CSeamlessMgr::GetInstance()->AddNode(303, 203);

	// AddBuffer - StaticProb
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Door"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gate_A/"), _T("trDun_Cath_Gate_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Archer_Brown"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Archer_Brown/"), _T("Skeleton_Archer_Brown.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Ghoul"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Ghoul/"), _T("Ghoul.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Summoner_Blue"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Summoner_Blue/"), _T("Skeleton_Summoner_Blue.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Axe_Blue"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Axe_Blue/"), _T("Skeleton_Axe_Blue.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("SkeletonSummoner_ArcaneBall"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/SkeletonSummoner_ArcaneBall/"), _T("SkeletonSummoner_ArcaneBall.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Ghoul_Scratch_A"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Ghoul_Scratch_A/"), _T("Ghoul_Scratch_A.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Ghoul_Scratch_B"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Ghoul_Scratch_B/"), _T("Ghoul_Scratch_B.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Arrow"), new CStaticMesh(_T("../Resource/Mesh/Effect/Arrow0/"), _T("Arrow.X")));

	// AddBuffer - Texture
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_AxeTrail.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_AxeTrail"), pTexture);
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

CScene* CPlayScene_Cathedral_F4::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// Cathedral_F4_GateWay
	CGateWay* Cathedral_F4_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_CATHEDRAL_F4);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(Cathedral_F4_GateWay);
	pTransformCom = (CTransformCom*)Cathedral_F4_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(4739.69f,-22.0f,4712.99f);
	Cathedral_F4_GateWay->Initialize();

	// Cath4FToCath3F_Entrance
	CCath4FToCath3F_Entrance* pCath4FToCath3F_Entrance = new CCath4FToCath3F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath4FToCath3F_Entrance);
	pCath4FToCath3F_Entrance->Initialize();
	pCath4FToCath3F_Entrance->Event();

	// Cathedral_F3_Gate
	CGate* pCathedral_F3_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 3층"), _T("Cathedral_F3"), &D3DXVECTOR3(1721.0f, -586.0f, 10342.5f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F3);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F3_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F3_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(9810.0f, 43.0f, 2139.0f);
	pCathedral_F3_Gate->SetSize(272.0f, 195.0f, 14.0f);
	pCathedral_F3_Gate->Initialize();

	// Cath4FToRoyalChamber_Entrance
	CCath4FToRoyalChamber_Entrance* pCath4FToRoyalChamber_Entrance = new CCath4FToRoyalChamber_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath4FToRoyalChamber_Entrance);
	pCath4FToRoyalChamber_Entrance->Initialize();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8042.0f, 0.0f, 1817.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7790.0f, 0.0f, 1704.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7473.0f, 0.0f, 1854.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7043.0f, 0.0f, 1663.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6549.0f, 0.0f, 1835.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 40));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4894.0f, 0.0f, 1752.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4368.0f, 3.0f, 1824.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4265.0f, 0.0f, 2119.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4390.0f, 0.0f, 2218.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4318.0f, 0.0f, 2713.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 40));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3609.0f, 3.0f, 4178.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3410.0f, 1.0f, 4394.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3391.0f, 0.0f, 4777.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 40));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3650.0f, 4.0f, 5172.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 40));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4609.0f, 0.0f, 7818.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4593.0f, 0.0f, 8354.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4203.0f, 0.0f, 8369.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3999.0f, 0.0f, 8072.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4006.0f, 0.0f, 7877.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4245.0f, 0.0f, 8050.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 44));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1977.0f, 0.0f, 8173.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1784.0f, 0.0f, 8149.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1582.0f, 0.0f, 8031.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1427.0f, 0.0f, 7821.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1610.0f, 0.0f, 7696.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1894.0f, 0.0f, 7687.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 44));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1693.0f, 0.0f, 8762.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1817.0f, 0.0f, 8876.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 44));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1730.0f, 0.0f, 7281.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1692.0f, 0.0f, 7032.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 44));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1846.0f, 0.0f, 7132.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 44));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(975.0f, 0.0f, 7229.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(954.0f, 0.0f, 7034.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1104.0f, 0.0f, 7209.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 48));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(933.0f, 0.0f, 8869.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1061.0f, 0.0f, 8738.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(498.0f, 86.0f, 8117.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(565.0f, 86.0f, 7695.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 48));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7020.0f, 0.0f, 7944.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7198.0f, 0.0f, 7816.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7520.0f, 0.0f, 7922.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7708.0f, 0.0f, 7931.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7954.0f, 0.0f, 7784.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8382.0f, 0.0f, 8004.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8622.0f, 0.0f, 7807.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_SUMMONER_BLUE, rand() % 5 + 48));	
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9846.0f, 0.0f, 7946.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_GHOUL, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10430.0f, 2.0f, 7920.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_AXE_BLUE, rand() % 5 + 48));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10438.0f, 0.0f, 8666.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ARCHER_BROWN, rand() % 5 + 48));
	
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
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 4층"));
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

CScene* CPlayScene_Cathedral_F4::UpdatePlay()
{
	return CScene::UpdatePlay();
}