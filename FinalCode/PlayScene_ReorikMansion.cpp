#include "StdAfx.h"
#include "PlayScene_ReorikMansion.h"

CPlayScene_ReorikMansion::CPlayScene_ReorikMansion(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_ReorikMansion::~CPlayScene_ReorikMansion()
{
	Release();
}

void CPlayScene_ReorikMansion::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/ReorikMansion.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_ReorikMansion::Update()
{
	return CScene::Update();
}

void CPlayScene_ReorikMansion::Render()
{
	CScene::Render();
}

void CPlayScene_ReorikMansion::Release()
{
	// InputMgr - Disable
	CInputMgr::GetInstance()->Disable();

	// UIMgr - Disable
	CUIMgr::GetInstance()->Disable();

	// RenderMode
	CRenderMgr::GetInstance()->SetRenderMode(0);

	// RemoveBuffer - Monster
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_King"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_OneHand_Blue"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_Shield_Mint"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("SkeletonKing_TeleportShell"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("SkeletonKing_WeaponTrail"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_SwordTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("SkeletonKing_EctoplasmBase"));
}

CScene* CPlayScene_ReorikMansion::UpdateLoad()
{
	// Map
	CMap* pMap = new CMap(NULL, OBJ_TYPE_DYNAMIC, _T("ReorikMansion0"), _T("../Resource/Mesh/Map/ReorikMansion/"), _T("0.X"));
	m_pLayer[LAYER_TYPE_MAP]->AddObject(pMap);
	pMap->Initialize();

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_King"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_King/"), _T("Skeleton_King.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_OneHand_Blue"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_OneHand_Blue/"), _T("Skeleton_OneHand_Blue.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_Shield_Mint"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_Shield_Mint/"), _T("Skeleton_Shield_Mint.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("SkeletonKing_TeleportShell"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/SkeletonKing_TeleportShell/"), _T("SkeletonKing_TeleportShell.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("SkeletonKing_WeaponTrail"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/SkeletonKing_WeaponTrail/"), _T("SkeletonKing_WeaponTrail.X")));
	
	// AddTexture - Effect
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_SwordTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	 	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_SwordTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/skeletonKingGhost_ectoPlasm.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
		CTextureMgr::GetInstance()->AddTexture(_T("SkeletonKing_EctoplasmBase"), pTexture); 

	return CScene::UpdateLoad();
}

CScene* CPlayScene_ReorikMansion::UpdateComplete()
{
	// Dummy
	CCath4FToCath3F_Entrance* pDummy = new CCath4FToCath3F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pDummy);

	CTransformCom* pTransformCom = (CTransformCom*)pDummy->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	pDummy->Initialize();

	// Skeleton_King
	CSkeleton_King* pMonster0 = new CSkeleton_King(_T("Monster"), OBJ_TYPE_DYNAMIC, 70);
	m_pLayer[LAYER_TYPE_MONSTER]->AddObject(pMonster0);
	pTransformCom = (CTransformCom*)pMonster0->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(211.f, 270.f, 1796.f));
	pMonster0->Initialize();
	pMonster0->SetState(new CSkeleton_King_Intro_Idle);

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

	//Water
	CWaterEffect* pWater = new CWaterEffect(NULL, OBJ_TYPE_DYNAMIC, 0.f, -1.5f, _T("Skeletal_Throne_Water"), 1.f);
	m_pLayer[LAYER_TYPE_EFFECT]->AddObject(pWater);
	pTransformCom = (CTransformCom*)pWater->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.f, -4.f, 0.f);
	pWater->Initialize();
	pWater->m_bCheck = true;

	// SceneMessage
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("ÇØ°ñ¿ÕÀÇ ¹¦½Ç"));
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

CScene* CPlayScene_ReorikMansion::UpdatePlay()
{
	return CScene::UpdatePlay();
}