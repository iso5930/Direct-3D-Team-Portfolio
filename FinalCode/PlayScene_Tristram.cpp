#include "StdAfx.h"
#include "PlayScene_Tristram.h"

CPlayScene_Tristram::CPlayScene_Tristram(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_Tristram::~CPlayScene_Tristram()
{
	Release();
}

void CPlayScene_Tristram::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/Tristram.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_Tristram::Update()
{
	return CScene::Update();
}

void CPlayScene_Tristram::Render()
{
	CScene::Render();
}

void CPlayScene_Tristram::Release()
{
	// InputMgr - Disable
	CInputMgr::GetInstance()->Disable();

	// UIMgr - Disable
	CUIMgr::GetInstance()->Disable();

	// SeamlessMgr - Disable
	CSeamlessMgr::GetInstance()->Disable();

	// RenderMode
	CRenderMgr::GetInstance()->SetRenderMode(0);

	// RemoveBuffer - NPC - Tristram
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Arghus"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Blacksmith"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Guard"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Jeweler"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Mystic"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("NPC_Tristram_Tashun"));

	// RemoveBuffer - Prob - Tristram
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_Gate_Town"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_Stash"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_Broken_Furniture"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_Wagon_Destroyed"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_BlackSmith_Store"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Tristram_CampFire"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_GateWay"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Prob_Cath_WoodDoor"));

	// RemoveBuffer - Monster
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Stitch"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Female"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Male"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_White"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Red"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Stitch_Spike"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Scratch_A"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Skinny_Male_Scratch_B"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Male_Scratch"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Female_Scratch_A"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Zombie_Female_Scratch_B"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("ZombieFemale_Spit"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("ZombieFemale_PukeBase"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("PukeDecal0"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("PukeDecal1"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("PukeDecal2"));

	// RemoveTexture - SkyBox
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkyBox_SkyBox"));
}

CScene* CPlayScene_Tristram::UpdateLoad()
{
	// AddNode
	//CSeamlessMgr::GetInstance()->AddNode(2, 2);
	CSeamlessMgr::GetInstance()->AddNode(1, 1); CSeamlessMgr::GetInstance()->AddNode(1, 2); CSeamlessMgr::GetInstance()->AddNode(1, 101); CSeamlessMgr::GetInstance()->AddNode(1, 102);
	CSeamlessMgr::GetInstance()->AddNode(2, 1); CSeamlessMgr::GetInstance()->AddNode(2, 2); CSeamlessMgr::GetInstance()->AddNode(2, 101); CSeamlessMgr::GetInstance()->AddNode(2, 102);
	CSeamlessMgr::GetInstance()->AddNode(101, 1); CSeamlessMgr::GetInstance()->AddNode(101, 2); CSeamlessMgr::GetInstance()->AddNode(101, 101); CSeamlessMgr::GetInstance()->AddNode(101, 102); CSeamlessMgr::GetInstance()->AddNode(101, 201); CSeamlessMgr::GetInstance()->AddNode(101, 202);
	CSeamlessMgr::GetInstance()->AddNode(102, 1); CSeamlessMgr::GetInstance()->AddNode(102, 2);   CSeamlessMgr::GetInstance()->AddNode(102, 101); CSeamlessMgr::GetInstance()->AddNode(102, 102); CSeamlessMgr::GetInstance()->AddNode(102, 201); CSeamlessMgr::GetInstance()->AddNode(102, 202);
	CSeamlessMgr::GetInstance()->AddNode(201, 101); CSeamlessMgr::GetInstance()->AddNode(201, 102); CSeamlessMgr::GetInstance()->AddNode(201, 201); CSeamlessMgr::GetInstance()->AddNode(201, 202); CSeamlessMgr::GetInstance()->AddNode(201, 300); CSeamlessMgr::GetInstance()->AddNode(201, 301); CSeamlessMgr::GetInstance()->AddNode(201, 302);
	CSeamlessMgr::GetInstance()->AddNode(202, 101); CSeamlessMgr::GetInstance()->AddNode(202, 102); CSeamlessMgr::GetInstance()->AddNode(202, 201); CSeamlessMgr::GetInstance()->AddNode(202, 202); CSeamlessMgr::GetInstance()->AddNode(202, 301); CSeamlessMgr::GetInstance()->AddNode(202, 302);
	CSeamlessMgr::GetInstance()->AddNode(300, 201); CSeamlessMgr::GetInstance()->AddNode(300, 300); CSeamlessMgr::GetInstance()->AddNode(300, 301); CSeamlessMgr::GetInstance()->AddNode(300, 400); CSeamlessMgr::GetInstance()->AddNode(300, 401);
	CSeamlessMgr::GetInstance()->AddNode(301, 201); CSeamlessMgr::GetInstance()->AddNode(301, 202); CSeamlessMgr::GetInstance()->AddNode(301, 300); CSeamlessMgr::GetInstance()->AddNode(301, 301); CSeamlessMgr::GetInstance()->AddNode(301, 302); CSeamlessMgr::GetInstance()->AddNode(301, 400); CSeamlessMgr::GetInstance()->AddNode(301, 401); CSeamlessMgr::GetInstance()->AddNode(301, 402);
	CSeamlessMgr::GetInstance()->AddNode(302, 201); CSeamlessMgr::GetInstance()->AddNode(302, 202); CSeamlessMgr::GetInstance()->AddNode(302, 301); CSeamlessMgr::GetInstance()->AddNode(302, 302); CSeamlessMgr::GetInstance()->AddNode(302, 401); CSeamlessMgr::GetInstance()->AddNode(302, 402);
	CSeamlessMgr::GetInstance()->AddNode(400, 300); CSeamlessMgr::GetInstance()->AddNode(400, 301); CSeamlessMgr::GetInstance()->AddNode(400, 400); CSeamlessMgr::GetInstance()->AddNode(400, 401); CSeamlessMgr::GetInstance()->AddNode(400, 500); CSeamlessMgr::GetInstance()->AddNode(400, 501);
	CSeamlessMgr::GetInstance()->AddNode(401, 300); CSeamlessMgr::GetInstance()->AddNode(401, 301); CSeamlessMgr::GetInstance()->AddNode(401, 302); CSeamlessMgr::GetInstance()->AddNode(401, 400); CSeamlessMgr::GetInstance()->AddNode(401, 401); CSeamlessMgr::GetInstance()->AddNode(401, 402); CSeamlessMgr::GetInstance()->AddNode(401, 500); CSeamlessMgr::GetInstance()->AddNode(401, 501); CSeamlessMgr::GetInstance()->AddNode(401, 502);
	CSeamlessMgr::GetInstance()->AddNode(402, 301); CSeamlessMgr::GetInstance()->AddNode(402, 302); CSeamlessMgr::GetInstance()->AddNode(402, 401); CSeamlessMgr::GetInstance()->AddNode(402, 402); CSeamlessMgr::GetInstance()->AddNode(402, 501); CSeamlessMgr::GetInstance()->AddNode(402, 502);
	CSeamlessMgr::GetInstance()->AddNode(500, 400); CSeamlessMgr::GetInstance()->AddNode(500, 401); CSeamlessMgr::GetInstance()->AddNode(500, 500); CSeamlessMgr::GetInstance()->AddNode(500, 501); CSeamlessMgr::GetInstance()->AddNode(500, 601);
	CSeamlessMgr::GetInstance()->AddNode(501, 400); CSeamlessMgr::GetInstance()->AddNode(501, 401); CSeamlessMgr::GetInstance()->AddNode(501, 402); CSeamlessMgr::GetInstance()->AddNode(501, 500); CSeamlessMgr::GetInstance()->AddNode(501, 501); CSeamlessMgr::GetInstance()->AddNode(501, 502); CSeamlessMgr::GetInstance()->AddNode(501, 601); CSeamlessMgr::GetInstance()->AddNode(501, 602);
	CSeamlessMgr::GetInstance()->AddNode(502, 401); CSeamlessMgr::GetInstance()->AddNode(502, 402); CSeamlessMgr::GetInstance()->AddNode(502, 501); CSeamlessMgr::GetInstance()->AddNode(502, 502); CSeamlessMgr::GetInstance()->AddNode(502, 601); CSeamlessMgr::GetInstance()->AddNode(502, 602);
	CSeamlessMgr::GetInstance()->AddNode(601, 501); CSeamlessMgr::GetInstance()->AddNode(601, 502); CSeamlessMgr::GetInstance()->AddNode(601, 601); CSeamlessMgr::GetInstance()->AddNode(601, 602); CSeamlessMgr::GetInstance()->AddNode(601, 701); CSeamlessMgr::GetInstance()->AddNode(601, 702);
	CSeamlessMgr::GetInstance()->AddNode(602, 501); CSeamlessMgr::GetInstance()->AddNode(602, 502); CSeamlessMgr::GetInstance()->AddNode(602, 601); CSeamlessMgr::GetInstance()->AddNode(602, 602); CSeamlessMgr::GetInstance()->AddNode(602, 701); CSeamlessMgr::GetInstance()->AddNode(602, 702);
	CSeamlessMgr::GetInstance()->AddNode(701, 601); CSeamlessMgr::GetInstance()->AddNode(701, 602); CSeamlessMgr::GetInstance()->AddNode(701, 701); CSeamlessMgr::GetInstance()->AddNode(701, 702);
	CSeamlessMgr::GetInstance()->AddNode(702, 601); CSeamlessMgr::GetInstance()->AddNode(702, 602); CSeamlessMgr::GetInstance()->AddNode(702, 701); CSeamlessMgr::GetInstance()->AddNode(702, 702);

	// AddBuffer - NPC - Tristram
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Arghus"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Arghus/"), _T("Arghus.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Blacksmith"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Blacksmith/"), _T("Blacksmith.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Guard"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Guard/"), _T("Guard.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Jeweler"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Jeweler/"), _T("Jeweler.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Mystic"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Mystic/"), _T("Mystic.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("NPC_Tristram_Tashun"), new CDynamicMesh(_T("../Resource/Mesh/NPC/Tristram/Tashun/"), _T("Tashun.X")));

	// AddBuffer - Prob - Tristram
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_Gate_Town"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_NewTristram_Gate_Town/"), _T("trOut_NewTristram_Gate_Town.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_Stash"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_NewTristram_Stash/"), _T("trOut_NewTristram_Stash.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_Broken_Furniture"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_NewTristram_broken_furniture_pile/"), _T("trOut_NewTristram_broken_furniture_pile.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_Wagon_Destroyed"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_OldTristram_trOut_OldTristram_Wagon_Destroyed_B/"), _T("trOut_OldTristram_trOut_OldTristram_Wagon_Destroyed_B.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_BlackSmith_Store"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_NewTristram_BlackSmith_Store/"), _T("trOut_NewTristram_BlackSmith_Store.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Tristram_CampFire"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_Exploding_CampFire/"), _T("trOut_Exploding_CampFire.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_WoodDoor"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_WoodDoor_A/"), _T("trDun_Cath_WoodDoor_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Stitch"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Stitch/"), _T("Stitch.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Female"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Zombie_Female/"), _T("Zombie_Female.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Male"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Zombie_Male/"), _T("Zombie_Male.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_White"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Zombie_Skinny_Male_White/"), _T("Zombie_Skinny_Male_White.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Red"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Zombie_Skinny_Male_Red/"), _T("Zombie_Skinny_Male_Red.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("Stitch_Spike"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Stitch_Spike/"), _T("Stitch_Spike.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Scratch_A"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Skinny_Male_Scratch_A/"), _T("Zombie_Skinny_Male_Scratch_A.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Skinny_Male_Scratch_B"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Skinny_Male_Scratch_B/"), _T("Zombie_Skinny_Male_Scratch_B.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Male_Scratch"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Male_Scratch/"), _T("Zombie_Male_Scratch.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Female_Scratch_A"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Female_Scratch_A/"), _T("Zombie_Female_Scratch_A.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Zombie_Female_Scratch_B"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Zombie_Female_Scratch_B/"), _T("Zombie_Female_Scratch_B.X")));

	// AddTexture - Effect
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Spit.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("ZombieFemale_Spit"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Puke_Particle.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("ZombieFemale_PukeBase"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Puke_Drop0.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("PukeDecal0"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Puke_Drop1.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("PukeDecal1"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Puke_Drop2.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("PukeDecal2"), pTexture);

	// AddTexture - SkyBox
	if(FAILED(D3DXCreateCubeTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/SkyBox/SkyBox.dds"), (LPDIRECT3DCUBETEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("SkyBox_SkyBox"), pTexture);

	// SeamlessMgr - Enable
	CSeamlessMgr::GetInstance()->Enable();

	return CScene::UpdateLoad();
}

CScene* CPlayScene_Tristram::UpdateComplete()
{
	// PlaySoundForSystemBGM
	CSoundMgr::GetInstance()->StopSoundForSystemBGM();
	CSoundMgr::GetInstance()->PlaySoundForSystemBGM(_T("BGM2.ogg"));

	CTransformCom* pTransformCom;

	// Tristram_BlackSmith(제작소NPC)
	CTristram_BlackSmith* pTristram_BlackSmith = new CTristram_BlackSmith(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_BlackSmith);
	pTransformCom = (CTransformCom*)pTristram_BlackSmith->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7272.0f, 307.0f, 4486.0f);
	pTristram_BlackSmith->Initialize();
	pTristram_BlackSmith->SetState(new CTristram_BlackSmith_Idle);

	// Tristram_Mystic(퀘스트NPC)
	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST1) == NULL)
	{
		CTristram_Mystic* pTristram_Mystic = new CTristram_Mystic(_T("NPC"), OBJ_TYPE_DYNAMIC);
		m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Mystic);
		pTransformCom = (CTransformCom*)pTristram_Mystic->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(7010.0f, 755.0f, 1945.0f);
		pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
		pTristram_Mystic->Initialize();
		pTristram_Mystic->SetState(new CTristram_Mystic_Idle);
	}

	// Tristram_Arghus(상점NPC)
	CTristram_Arghus* pTristram_Arghus = new CTristram_Arghus(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Arghus);
	pTransformCom = (CTransformCom*)pTristram_Arghus->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6537.0f, 305.0f, 3915.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f);
	pTristram_Arghus->Initialize();
	pTristram_Arghus->SetState(new CTristram_Arghus_Idle);

	// Tristram_Guard1(일반NPC)
	CTristram_Guard* pTristram_Guard1 = new CTristram_Guard(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Guard1);
	pTransformCom = (CTransformCom*)pTristram_Guard1->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8352.0f, 308.0f, 5988.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f);
	pTristram_Guard1->Initialize();
	pTristram_Guard1->SetState(new CTristram_Guard_Idle);
	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST2) != NULL)
		pTristram_Guard1->SetMode(0);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST1) == NULL)
		pTristram_Guard1->SetMode(0);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST1) != NULL)
		pTristram_Guard1->SetMode(1);

	// Tristram_Guard2(일반NPC)
	CTristram_Guard* pTristram_Guard2 = new CTristram_Guard(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Guard2);
	pTransformCom = (CTransformCom*)pTristram_Guard2->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8330.0f, 305.0f, 5734.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f);
	pTristram_Guard2->Initialize();
	pTristram_Guard2->SetState(new CTristram_Guard_Idle);

	// Tristram_Guard3(일반NPC)
	CTristram_Guard* pTristram_Guard3 = new CTristram_Guard(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Guard3);
	pTransformCom = (CTransformCom*)pTristram_Guard3->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8072.0f, 406.0f, 6104.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f);
	pTristram_Guard3->Initialize();
	pTristram_Guard3->SetState(new CTristram_Guard_Idle);

	// Tristram_Guard4(일반NPC)
	CTristram_Guard* pTristram_Guard4 = new CTristram_Guard(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Guard4);
	pTransformCom = (CTransformCom*)pTristram_Guard4->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8072.0f, 406.0f, 5643.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f);
	pTristram_Guard4->Initialize();
	pTristram_Guard4->SetState(new CTristram_Guard_Idle);

	// Tristram_Jeweler(보석방NPC)
	CTristram_Jeweler* pTristram_Jeweler = new CTristram_Jeweler(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Jeweler);
	pTransformCom = (CTransformCom*)pTristram_Jeweler->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7100.0f, 305.0f, 3567.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(-180.0f), 0.0f);
	pTristram_Jeweler->Initialize();
	pTristram_Jeweler->SetState(new CTristram_Jeweler_Idle);

	// Tristram_Tashun(촌장NPC)
	CTristram_Tashun* pTristram_Tashun = new CTristram_Tashun(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pTristram_Tashun);
	pTransformCom = (CTransformCom*)pTristram_Tashun->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7327.0f, 305.0f, 3620.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DXToRadian(135.0f), 0.0f);
	pTristram_Tashun->Initialize();
	pTristram_Tashun->SetState(new CTristram_Tashun_Idle);

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST9) != NULL)
		pTristram_Tashun->SetMode(9);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST8) != NULL)
		pTristram_Tashun->SetMode(8);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST7) != NULL)
		pTristram_Tashun->SetMode(6);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST6) != NULL)
		pTristram_Tashun->SetMode(5);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST5) != NULL)
		pTristram_Tashun->SetMode(4);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST4) != NULL)
		pTristram_Tashun->SetMode(3);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST3) != NULL)
		pTristram_Tashun->SetMode(2);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST2) != NULL)
		pTristram_Tashun->SetMode(1);
	else if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST1) != NULL)
		pTristram_Tashun->SetMode(0);

	// Tristram_Town_Gate(입구)
	CTristram_Gate_Town* pTristram_Gate_Town = new CTristram_Gate_Town(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pTristram_Gate_Town);
	pTransformCom = (CTransformCom*)pTristram_Gate_Town->GetComponent(COM_TYPE_TRANSFORM);
	pTristram_Gate_Town->Initialize();

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST2) != NULL)
		pTristram_Gate_Town->Event();

	// Tristram_Stash(창고)
	CTristram_Stash* pTristram_Stash = new CTristram_Stash(_T("StaticProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_Stash);
	pTransformCom = (CTransformCom*)pTristram_Stash->GetComponent(COM_TYPE_TRANSFORM);
	//pTransformCom->m_vPos = D3DXVECTOR3(6484.0f, 293.0f, 4208.0f);
	pTransformCom->m_vPos = D3DXVECTOR3(6584.0f, 293.0f, 4158.0f);
	pTristram_Stash->Initialize();

	// NPC_Enchantress(요술사)
	CNPC_Enchantress* pNPC_Enchantress = new CNPC_Enchantress(_T("NPC"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_NPC]->AddObject(pNPC_Enchantress);
	pTransformCom = (CTransformCom*)pNPC_Enchantress->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7465.0f, 305.0f, 3850.0f);
	pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f);
	pNPC_Enchantress->Initialize();

	// Tristram_Broken_Furniture
	CTristram_Broken_Furniture* pTristram_Broken_Furniture = new CTristram_Broken_Furniture(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_Broken_Furniture);
	pTransformCom = (CTransformCom*)pTristram_Broken_Furniture->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6256.0f, 307.0f, 3443.0f);
	pTristram_Broken_Furniture->Initialize();

	// Tristram_Wagon_Destroyed
	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST4) == NULL)
	{
		CTristram_Wagon_Destroyed* pTristram_Wagon_Destroyed = new CTristram_Wagon_Destroyed(_T("StaticProb"), OBJ_TYPE_DYNAMIC);
		m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_Wagon_Destroyed);
		pTransformCom = (CTransformCom*)pTristram_Wagon_Destroyed->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(8219.0f, 303.0f, 6284.0f);
		pTristram_Wagon_Destroyed->Initialize();
	}

	// Tristram_BlackSmith_Store
	CTristram_BlackSmith_Store* pTristram_BlackSmith_Store = new CTristram_BlackSmith_Store(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_BlackSmith_Store);
	pTransformCom = (CTransformCom*)pTristram_BlackSmith_Store->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7307.0f, 302.0f, 4766.0f);
	pTristram_BlackSmith_Store->Initialize();

	// Tristram_CampFire1
	CTristram_CampFire* pTristram_CampFire1 = new CTristram_CampFire(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_CampFire1);
	pTransformCom = (CTransformCom*)pTristram_CampFire1->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7483.0f, 302.0f, 6260.0f);
	pTristram_CampFire1->Initialize();

	// Tristram_CampFire2
	CTristram_CampFire* pTristram_CampFire2 = new CTristram_CampFire(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_CampFire2);
	pTransformCom = (CTransformCom*)pTristram_CampFire2->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7564.0f, 302.0f, 6371.0f);
	pTristram_CampFire2->Initialize();

	// Tristram_CampFire3
	CTristram_CampFire* pTristram_CampFire3 = new CTristram_CampFire(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_CampFire3);
	pTransformCom = (CTransformCom*)pTristram_CampFire3->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7670.0f, 302.0f, 6293.0f);
	pTristram_CampFire3->Initialize();

	// TristramToCath1F_Entrance
	CTristramToCath1F_Entrance* pTristramToCath1F_Entrance = new CTristramToCath1F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pTristramToCath1F_Entrance);
	pTristramToCath1F_Entrance->Initialize();

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST9) != NULL)
		pTristramToCath1F_Entrance->Event();

	// Tristram_GateWay
	CGateWay* pTristram_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_TRISTREAM);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristram_GateWay);
	pTransformCom = (CTransformCom*)pTristram_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7072.33f, 338.0f, 4051.0f);
	pTristram_GateWay->Initialize();

	// TristramField_GateWay
	CGateWay* pTristramField_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_TRISTREAM_FIELD);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pTristramField_GateWay);
	pTransformCom = (CTransformCom*)pTristramField_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6475.0f, 547.0f, 16873.0f);
	pTristramField_GateWay->Initialize();

	// Cathedral_F1_Gate
	CGate* pCathedral_F1_Gate = new CGate(_T("StaticProb"), OBJ_TYPE_DYNAMIC, _T("대성당 지하 1층"), _T("Cathedral_F1"), &D3DXVECTOR3(6669.7f, 0.0f, 1789.1f), &D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F1);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F1_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F1_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(5647.0f, 717.0f, 23771.0f);
	pCathedral_F1_Gate->SetSize(268.0f, 11.0f, 272.0f);
	pCathedral_F1_Gate->Initialize();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8241.0f, 754.0f, 2844.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8298.0f, 754.0f, 3023.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8662.0f, 698.0f, 3436.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8712.0f, 685.0f, 3547.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, 1));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7422.0f, 344.0f, 10929.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6719.0f, 345.0f, 10833.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7317.0f, 344.0f, 11443.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7362.0f, 344.0f, 11849.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7154.0f, 346.0f, 10362.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6828.0f, 357.0f, 11366.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6622.0f, 364.0f, 11854.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7087.0f, 365.0f, 12430.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6500.0f, 377.0f, 13099.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5982.0f, 350.0f, 11053.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6287.0f, 344.0f, 11473.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6306.0f, 345.0f, 11977.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5959.0f, 344.0f, 11623.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5848.0f, 350.0f, 11058.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5564.0f, 348.0f, 10970.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5729.0f, 344.0f, 11949.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5997.0f, 344.0f, 12283.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6112.0f, 344.0f, 12713.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5997.0f, 344.0f, 12936.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5669.0f, 344.0f, 13251.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5253.0f, 344.0f, 12907.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5059.0f, 344.0f, 13014.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5296.0f, 346.0f, 13480.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4842.0f, 343.0f, 13378.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4521.0f, 345.0f, 13103.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4549.0f, 344.0f, 13451.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4303.0f, 344.0f, 12585.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4419.0f, 345.0f, 12918.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4572.0f, 344.0f, 12429.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 1));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4817.0f, 344.0f, 12279.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 1));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2211.0f, 344.0f, 11239.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1975.0f, 344.0f, 11495.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1812.0f, 344.0f, 11342.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1770.0f, 344.0f, 11689.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2315.0f, 345.0f, 11643.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2924.0f, 344.0f, 12085.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2659.0f, 344.0f, 12468.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2217.0f, 344.0f, 12361.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(1877.0f, 345.0f, 12533.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2070.0f, 344.0f, 12025.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2544.0f, 345.0f, 13326.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2822.0f, 344.0f, 13432.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2902.0f, 346.0f, 13693.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2641.0f, 344.0f, 14489.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2357.0f, 344.0f, 14258.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2902.0f, 344.0f, 14294.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3111.0f, 344.0f, 14610.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3176.0f, 344.0f, 14994.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2910.0f, 344.0f, 15128.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(2535.0f, 344.0f, 15093.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5097.0f, 510.0f, 15024.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4597.0f, 510.0f, 14378.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4891.0f, 510.0f, 14330.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5417.0f, 510.0f, 14452.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6059.0f, 510.0f, 15163.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6625.0f, 510.0f, 15444.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6691.0f, 510.0f, 15050.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6445.0f, 510.0f, 14817.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6304.0f, 510.0f, 14375.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 3));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5934.0f, 510.0f, 15453.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 3));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5958.0f, 344.0f, 18570.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6021.0f, 344.0f, 18964.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6219.0f, 344.0f, 19378.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6251.0f, 343.0f, 19030.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6205.0f, 344.0f, 18622.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6103.0f, 343.0f, 18789.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8917.0f, 255.0f, 20455.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8676.0f, 255.0f, 20459.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8732.0f, 262.0f, 20169.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8425.0f, 255.0f, 20190.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5252.0f, 703.0f, 22487.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5537.0f, 703.0f, 22007.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5996.0f, 703.0f, 22104.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5715.0f, 703.0f, 22334.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6047.0f, 703.0f, 22525.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6439.0f, 703.0f, 22705.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_FEMALE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6654.0f, 703.0f, 22442.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE, rand() % 5 + 5));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6377.0f, 703.0f, 22137.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_ZOMBIE_MALE, rand() % 5 + 5));


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

	// Light3
	CLight* pLight3 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 3, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7125.0f, 921.0f, 1784.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight3);
	pLight3->Initialize();

	// Light4
	CLight* pLight4 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 4, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8538.0f, 855.0f, 3147.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight4);
	pLight4->Initialize();

	// Light5
	CLight* pLight5 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 5, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8848.0f, 617.0f, 4226.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight5);
	pLight5->Initialize();

	// Light6
	CLight* pLight6 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 6, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8880.0f, 433.0f, 5672.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight6);
	pLight6->Initialize();

	// Light7
	CLight* pLight7 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 7, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8704.0f, 439.0f, 5839.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight7);
	pLight7->Initialize();

	// Light8
	CLight* pLight8 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 8, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8168.0f, 465.0f, 5972.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight8);
	pLight8->Initialize();

	// Light9
	CLight* pLight9 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 9, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(8168.0f, 465.0f, 5718.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight9);
	pLight9->Initialize();

	// Light10
	CLight* pLight10 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 10, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7342.0f, 417.0f, 5639.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight10);
	pLight10->Initialize();

	// Light11
	CLight* pLight11 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 11, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6393.0f, 372.0f, 4814.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight11);
	pLight11->Initialize();

	// Light12
	CLight* pLight12 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 12, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6256.0f, 518.0f, 4674.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight12);
	pLight12->Initialize();

	// Light13
	CLight* pLight13 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 13, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6463.0f, 454.0f, 4207.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight13);
	pLight13->Initialize();

	// Light14
	CLight* pLight14 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 14, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6366.0f, 522.0f, 4021.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight14);
	pLight14->Initialize();

	// Light15
	CLight* pLight15 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 15, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6438.0f, 443.0f, 3874.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight15);
	pLight15->Initialize();

	// Light16
	CLight* pLight16 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 16, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(6335.0f, 400.0f, 3622.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight16);
	pLight16->Initialize();

	// Light17
	CLight* pLight17 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 17, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7051.0f, 433.0f, 3415.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight17);
	pLight17->Initialize();

	// Light18
	CLight* pLight18 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 18, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7526.0f, 433.0f, 3586.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight18);
	pLight18->Initialize();

	// Light19
	CLight* pLight19 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 19, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7671.0f, 450.0f, 4342.0f, 1.0f), NULL, 400.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight19);
	pLight19->Initialize();

	// Light20
	CLight* pLight20 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 20, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7483.0f, 402.0f, 6260.0f, 1.0f), NULL, 200.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight20);
	pLight20->Initialize();

	// Light21
	CLight* pLight21 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 21, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7564.0f, 402.0f, 6371.0f, 1.0f), NULL, 200.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight21);
	pLight21->Initialize();

	// Light22
	CLight* pLight22 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 22, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.1f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7670.0f, 402.0f, 6293.0f, 1.0f), NULL, 200.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight22);
	pLight22->Initialize();

	// Light23
	CLight* pLight23 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 23, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7147.0f, 402.0f, 4022.0f, 1.0f), NULL, 200.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight23);
	pLight23->Initialize();

	// Light24
	CLight* pLight24 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 24, LIGHT_TYPE_POINT, &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(1.0f, 0.7f, 0.1f, 1.0f), &D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), &D3DXVECTOR4(7101.0f, 402.0f, 4319.0f, 1.0f), NULL, 200.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight24);
	pLight24->Initialize();

	// Water
	CWaterEffect* pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("E10_S14_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7741.9f, 59.687f, 7734.f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.75f, 0.75f, 0.75f);
	pWater->Initialize();

	pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("Old_E03_S04_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8322.f, 288.f, 10991.f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.75f, 0.75f, 0.75f);
	pWater->Initialize();

	pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("Old_E03_S03_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(8075.f, 288.f, 13754.f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.75f, 0.75f, 0.75f);
	pWater->Initialize();

	pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("Old_E03_S01_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6120.f, 336.646f, 18360.f);
	pWater->Initialize();
	
	pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("Old_E03_S02_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6120.f, 371.646f, 15300.f);
	pWater->Initialize();

	pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -0.1f, _T("Old_E03_N01_Water"), 4.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6120.f, 336.646f, 21420.f);
	pWater->Initialize();

	// SceneMessage
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("트리스트럼"));
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

CScene* CPlayScene_Tristram::UpdatePlay()
{
	return CScene::UpdatePlay();
}