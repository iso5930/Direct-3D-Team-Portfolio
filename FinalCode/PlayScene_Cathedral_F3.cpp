#include "StdAfx.h"
#include "PlayScene_Cathedral_F3.h"

CPlayScene_Cathedral_F3::CPlayScene_Cathedral_F3(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_Cathedral_F3::~CPlayScene_Cathedral_F3()
{
	Release();
}

void CPlayScene_Cathedral_F3::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/Cathedral_F3.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_Cathedral_F3::Update()
{
	return CScene::Update();
}

void CPlayScene_Cathedral_F3::Render()
{
	CScene::Render();
}

void CPlayScene_Cathedral_F3::Release()
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
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Vessel"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Possessed"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Cultists"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Red"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Scratch_A"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Scratch_B"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Possessed_Scratch_A"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Possessed_Scratch_B"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Vessel_Transform0"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Vessel_Transform1"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Vessel_Transform2"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Vessel_Transform3"));
}

CScene* CPlayScene_Cathedral_F3::UpdateLoad()
{
	// AddNode
	CSeamlessMgr::GetInstance()->AddNode(0, 0); CSeamlessMgr::GetInstance()->AddNode(0, 100); CSeamlessMgr::GetInstance()->AddNode(0, 101);
	CSeamlessMgr::GetInstance()->AddNode(100, 100); CSeamlessMgr::GetInstance()->AddNode(100, 0); CSeamlessMgr::GetInstance()->AddNode(100, 101); CSeamlessMgr::GetInstance()->AddNode(100, 102); CSeamlessMgr::GetInstance()->AddNode(100, 200);
	CSeamlessMgr::GetInstance()->AddNode(101, 101); CSeamlessMgr::GetInstance()->AddNode(101, 0); CSeamlessMgr::GetInstance()->AddNode(101, 100); CSeamlessMgr::GetInstance()->AddNode(101, 102); CSeamlessMgr::GetInstance()->AddNode(101, 200);
	CSeamlessMgr::GetInstance()->AddNode(102, 102); CSeamlessMgr::GetInstance()->AddNode(102, 0); CSeamlessMgr::GetInstance()->AddNode(102, 100); CSeamlessMgr::GetInstance()->AddNode(102, 101);
	CSeamlessMgr::GetInstance()->AddNode(200, 200); CSeamlessMgr::GetInstance()->AddNode(200, 100); CSeamlessMgr::GetInstance()->AddNode(200, 101); CSeamlessMgr::GetInstance()->AddNode(200, 300);
	CSeamlessMgr::GetInstance()->AddNode(300, 300); CSeamlessMgr::GetInstance()->AddNode(300, 200);

	// AddBuffer - StaticProb
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Door"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gate_A/"), _T("trDun_Cath_Gate_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Vessel"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Triune_Vessel/"), _T("Triune_Vessel.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Possessed"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Triune_Possessed/"), _T("Triune_Possessed.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Cultists"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Triune_Cultists/"), _T("Triune_Cultists.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Zombie_Skinny_Male_Red/"), _T("Zombie_Skinny_Male_Red.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Scratch_A"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Skinny_Male_Scratch_A/"), _T("Zombie_Skinny_Male_Scratch_A.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Scratch_B"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Skinny_Male_Scratch_B/"), _T("Zombie_Skinny_Male_Scratch_B.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Possessed_Scratch_A"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Triune_Possessed_Scratch_A/"), _T("Triune_Possessed_Scratch_A.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Possessed_Scratch_B"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Triune_Possessed_Scratch_B/"), _T("Triune_Possessed_Scratch_B.X")));

	// AddBuffer - Texture
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Vessel_Transform0.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Vessel_Transform0"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Vessel_Transform1.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Vessel_Transform1"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Vessel_Transform2.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Vessel_Transform2"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Vessel_Transform3.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Vessel_Transform3"), pTexture);

	// SeamlessMgr - Enable
	CSeamlessMgr::GetInstance()->Enable();

	return CScene::UpdateLoad();
}

CScene* CPlayScene_Cathedral_F3::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// Cathedral_F3_GateWay
	CGateWay* Cathedral_F3_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_CATHEDRAL_F3);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(Cathedral_F3_GateWay);
	pTransformCom = (CTransformCom*)Cathedral_F3_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(490.429f,321.0f,4845.03f);
	Cathedral_F3_GateWay->Initialize();

	// Cath3FToCath2F_Entrance
	CCath3FToCath2F_Entrance* pCath3FToCath2F_Entrance = new CCath3FToCath2F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath3FToCath2F_Entrance);
	pCath3FToCath2F_Entrance->Initialize();
	pCath3FToCath2F_Entrance->Event();

	// Cathedral_F2_Gate
	CGate* pCathedral_F2_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 2층"), _T("Cathedral_F2"), &D3DXVECTOR3(1665.0f, -631.0f, 13603.4f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F2);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F2_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F2_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6733.0f, 51.0f, 5215.0f);
	pCathedral_F2_Gate->SetSize(272.0f, 195.0f, 14.0f);
	pCathedral_F2_Gate->Initialize();

	// Cath3FToCath4F_Entrance
	CCath3FToCath4F_Entrance* pCath3FToCath4F_Entrance = new CCath3FToCath4F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pCath3FToCath4F_Entrance);
	pCath3FToCath4F_Entrance->Initialize();
	pCath3FToCath4F_Entrance->Event();

	// Cathedral_F4_Gate
	CGate* pCathedral_F4_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 4층"), _T("Cathedral_F4"), &D3DXVECTOR3(9790.0f, 17.0f, 1904.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F4);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F4_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F4_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(1539.0f, -582.0f, 10334.0f);
	pCathedral_F4_Gate->SetSize(14.0f, 195.0f, 272.0f);
	pCathedral_F4_Gate->Initialize();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2682.0f, 0.0f, 4970.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2440.0f, 0.0f, 4792.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1973.0f, 4.0f, 4955.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1722.0f, 4.0f, 4847.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1338.0f, 4.0f, 4505.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1294.0f, 0.0f, 4229.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1360.0f, 0.0f, 3992.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1188.0f, 0.0f, 3753.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1243.0f, 0.0f, 3380.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(624.0f, -296.0f, 2512.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(824.0f, -296.0f, 2555.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(813.0f, -296.0f, 2294.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1036.0f, -296.0f, 2216.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1164.0f, -296.0f, 2424.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1243.0f, -296.0f, 2317.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1405.0f, -296.0f, 2435.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1569.0f, -285.0f, 2402.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1630.0f, -296.0f, 2222.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1774.0f, -296.0f, 2443.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1943.0f, -296.0f, 2540.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 30));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1333.0f, 0.0f, 5391.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1384.0f, 0.0f, 5809.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_POSSESSED, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1245.0f, 0.0f, 5911.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1305.0f, 2.0f, 6604.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1182.0f, 0.0f, 6925.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1543.0f, -47.0f, 7039.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1737.0f, -47.0f, 7431.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1592.0f, -47.0f, 7716.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1197.0f, 2.0f, 7721.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(596.0f, 3.0f, 7244.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(346.0f, 1.0f, 7448.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(368.0f, 0.0f, 8196.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 34));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(672.0f, 4.0f, 8293.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_POSSESSED, rand() % 5 + 34));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1286.0f, 0.0f, 9102.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1158.0f, 0.0f, 9410.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1379.0f, 0.0f, 9654.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1185.0f, 0.0f, 9834.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1307.0f, 0.0f, 9927.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1285.0f, 0.0f, 10299.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 38));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1588.0f, -296.0f, 11389.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1734.0f, -296.0f, 10987.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1951.0f, -296.0f, 11221.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_TRIUNE_VESSEL, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2188.0f, -293.0f, 11523.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2364.0f, -296.0f, 11306.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_CULTISTS, rand() % 5 + 38));

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
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 3층"));
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

CScene* CPlayScene_Cathedral_F3::UpdatePlay()
{
	return CScene::UpdatePlay();
}