#include "StdAfx.h"
#include "PlayScene_RoyalChamber.h"

CPlayScene_RoyalChamber::CPlayScene_RoyalChamber(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene_RoyalChamber::~CPlayScene_RoyalChamber()
{
	Release();
}

void CPlayScene_RoyalChamber::Initialize()
{
	// LoadBack
	m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
	m_pLoadBack->Initialize();

	// PathFindMgr - LoadNaviMesh
	CPathFindMgr::GetInstance()->LoadNaviMesh(_T("../Data/NaviMesh/RoyalChamber.dat"));

	CScene::Initialize();
}

CScene* CPlayScene_RoyalChamber::Update()
{
	return CScene::Update();
}

void CPlayScene_RoyalChamber::Render()
{
	CScene::Render();
}

void CPlayScene_RoyalChamber::Release()
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
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Stitch"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Triune_Berserker"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Skeleton_OneHand_Brown"));
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Warden"));

	// RemoveBuffer - Effect
	CBufferMgr::GetInstance()->RemoveBuffer(_T("Stitch_Spike"));

	// RemoveTexture - Effect
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_AxeTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Skeleton_SwordTrail"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire0"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire1"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire2"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire3"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire4"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire5"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire6"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire7"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire8"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire9"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire10"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire11"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire12"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire13"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire14"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire15"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire16"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire17"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire18"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire19"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire20"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire21"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire22"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire23"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire24"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire25"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire26"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire27"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire28"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire29"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire30"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire31"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire32"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire33"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire34"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire35"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire36"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire37"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire38"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire39"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire40"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire41"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire42"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire43"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire44"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire45"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire46"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire47"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire48"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire49"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire50"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire51"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire52"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire53"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire54"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire55"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire56"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire57"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire58"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire59"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire60"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire61"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire62"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire63"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire64"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire65"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire66"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire67"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire68"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire69"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire70"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("WardenFire71"));
	CTextureMgr::GetInstance()->RemoveTexture(_T("Warden_Entangle"));
}

CScene* CPlayScene_RoyalChamber::UpdateLoad()
{
	// AddNode
	CSeamlessMgr::GetInstance()->AddNode(0, 0); CSeamlessMgr::GetInstance()->AddNode(0, 1);
	CSeamlessMgr::GetInstance()->AddNode(1, 1); CSeamlessMgr::GetInstance()->AddNode(1, 0); CSeamlessMgr::GetInstance()->AddNode(1, 2);
	CSeamlessMgr::GetInstance()->AddNode(2, 2); CSeamlessMgr::GetInstance()->AddNode(2, 1); CSeamlessMgr::GetInstance()->AddNode(2, 102);
	CSeamlessMgr::GetInstance()->AddNode(102, 102); CSeamlessMgr::GetInstance()->AddNode(102, 1); CSeamlessMgr::GetInstance()->AddNode(102, 2); CSeamlessMgr::GetInstance()->AddNode(102, 201); CSeamlessMgr::GetInstance()->AddNode(102, 202); CSeamlessMgr::GetInstance()->AddNode(102, 203);
	CSeamlessMgr::GetInstance()->AddNode(201, 201); CSeamlessMgr::GetInstance()->AddNode(201, 102); CSeamlessMgr::GetInstance()->AddNode(201, 202); CSeamlessMgr::GetInstance()->AddNode(201, 302);
	CSeamlessMgr::GetInstance()->AddNode(202, 202); CSeamlessMgr::GetInstance()->AddNode(202, 102); CSeamlessMgr::GetInstance()->AddNode(202, 201); CSeamlessMgr::GetInstance()->AddNode(202, 203); CSeamlessMgr::GetInstance()->AddNode(202, 302);
	CSeamlessMgr::GetInstance()->AddNode(203, 203); CSeamlessMgr::GetInstance()->AddNode(203, 102); CSeamlessMgr::GetInstance()->AddNode(203, 202); CSeamlessMgr::GetInstance()->AddNode(203, 302);
	CSeamlessMgr::GetInstance()->AddNode(302, 302); CSeamlessMgr::GetInstance()->AddNode(302, 201); CSeamlessMgr::GetInstance()->AddNode(302, 202); CSeamlessMgr::GetInstance()->AddNode(302, 203); CSeamlessMgr::GetInstance()->AddNode(302, 402); CSeamlessMgr::GetInstance()->AddNode(302, 403);
	CSeamlessMgr::GetInstance()->AddNode(402, 402); CSeamlessMgr::GetInstance()->AddNode(402, 302); CSeamlessMgr::GetInstance()->AddNode(402, 403); CSeamlessMgr::GetInstance()->AddNode(402, 503);
	CSeamlessMgr::GetInstance()->AddNode(403, 403); CSeamlessMgr::GetInstance()->AddNode(403, 302); CSeamlessMgr::GetInstance()->AddNode(403, 402); CSeamlessMgr::GetInstance()->AddNode(403, 503);
	CSeamlessMgr::GetInstance()->AddNode(503, 503); CSeamlessMgr::GetInstance()->AddNode(503, 402); CSeamlessMgr::GetInstance()->AddNode(503, 403); CSeamlessMgr::GetInstance()->AddNode(503, 602); CSeamlessMgr::GetInstance()->AddNode(503, 603);
	CSeamlessMgr::GetInstance()->AddNode(602, 602); CSeamlessMgr::GetInstance()->AddNode(602, 503); CSeamlessMgr::GetInstance()->AddNode(602, 603); CSeamlessMgr::GetInstance()->AddNode(602, 702);
	CSeamlessMgr::GetInstance()->AddNode(603, 603); CSeamlessMgr::GetInstance()->AddNode(603, 503); CSeamlessMgr::GetInstance()->AddNode(603, 602); CSeamlessMgr::GetInstance()->AddNode(603, 702);
	CSeamlessMgr::GetInstance()->AddNode(702, 702); CSeamlessMgr::GetInstance()->AddNode(702, 602); CSeamlessMgr::GetInstance()->AddNode(702, 603); CSeamlessMgr::GetInstance()->AddNode(702, 802);
	CSeamlessMgr::GetInstance()->AddNode(802, 802);	CSeamlessMgr::GetInstance()->AddNode(802, 702);

	// AddBuffer - StaticProb
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_GateWay"), new CStaticMesh(_T("../Resource/Mesh/Prob/Tristram/trOut_WaypointA_Subscene/"), _T("trOut_WaypointA_Subscene.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Prob_Cath_Door"), new CDynamicMesh(_T("../Resource/Mesh/Prob/Cathedral/trDun_Cath_Gate_A/"), _T("trDun_Cath_Gate_A.X")));

	// AddBuffer - Monster
	CBufferMgr::GetInstance()->AddBuffer(_T("Stitch"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Stitch/"), _T("Stitch.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Triune_Berserker"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Triune_Berserker/"), _T("Triune_Berserker.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Skeleton_OneHand_Brown"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Skeleton_OneHand_Brown/"), _T("Skeleton_OneHand_Brown.X")));
	CBufferMgr::GetInstance()->AddBuffer(_T("Warden"), new CDynamicMesh(_T("../Resource/Mesh/Monster/Warden/"), _T("Warden.X")));

	// AddBuffer - Effect
	CBufferMgr::GetInstance()->AddBuffer(_T("Stitch_Spike"), new CStaticMesh(_T("../Resource/Mesh/Effect/Monster/Stitch_Spike/"), _T("Stitch_Spike.X")));	

	// AddBuffer - Texture
	LPDIRECT3DBASETEXTURE9 pTexture;
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_SwordTrail.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_SwordTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Skeleton_AxeTrail.dds"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Skeleton_AxeTrail"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire0.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire0"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire1.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire1"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire2.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire2"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire3.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire3"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire4.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire4"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire5.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire5"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire6.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire6"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire7.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire7"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire8.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire8"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire9.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire9"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire10.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire10"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire11.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire11"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire12.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire12"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire13.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire13"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire14.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire14"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire15.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire15"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire16.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire16"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire17.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire17"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire18.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire18"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire19.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire19"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire20.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire20"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire21.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire21"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire22.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire22"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire23.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire23"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire24.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire24"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire25.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire25"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire26.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire26"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire27.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire27"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire28.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire28"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire29.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire29"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire30.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire30"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire31.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire31"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire32.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire32"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire33.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire33"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire34.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire34"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire35.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire35"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire36.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire36"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire37.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire37"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire38.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire38"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire39.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire39"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire40.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire40"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire41.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire41"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire42.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire42"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire43.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire43"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire44.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire44"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire45.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire45"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire46.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire46"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire47.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire47"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire48.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire48"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire49.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire49"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire50.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire50"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire51.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire51"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire52.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire52"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire53.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire53"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire54.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire54"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire55.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire55"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire56.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire56"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire57.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire57"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire58.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire58"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire59.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire59"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire60.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire60"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire61.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire61"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire62.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire62"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire63.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire63"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire64.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire64"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire65.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire65"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire66.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire66"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire67.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire67"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire68.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire68"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire69.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire69"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire70.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire70"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/WardenFire/WardenFire71.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("WardenFire71"), pTexture);
	if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), _T("../Resource/Texture/Effect/Entangle.png"), (LPDIRECT3DTEXTURE9*)&pTexture))) { cout << "D3DXCreateTextureFromFile() Failed!" << endl; }
	CTextureMgr::GetInstance()->AddTexture(_T("Warden_Entangle"), pTexture);

	// SeamlessMgr - Enable
	CSeamlessMgr::GetInstance()->Enable();

	return CScene::UpdateLoad();
}

CScene* CPlayScene_RoyalChamber::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// RoyalChamber_GateWay
	CGateWay* pRoyalChamber_GateWay = new CGateWay(_T("StaticProb"), OBJ_TYPE_DYNAMIC, GATE_WAY_TYPE_ROYAL_CHAMBER);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pRoyalChamber_GateWay);
	pTransformCom = (CTransformCom*)pRoyalChamber_GateWay->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(10464.0f, 24.0f, 14011.0f);
	pRoyalChamber_GateWay->Initialize();

	// RoyalChamberToCath4F_Entrance
	CRoyalChamberToCath4F_Entrance* pRoyalChamberToCath4F_Entrance = new CRoyalChamberToCath4F_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pRoyalChamberToCath4F_Entrance);
	pRoyalChamberToCath4F_Entrance->Initialize();
	pRoyalChamberToCath4F_Entrance->Event();

	// Cathedral_F4_Gate
	CGate* pCathedral_F4_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("´ë¼º´ç ÁöÇÏ 4Ãþ"), _T("Cathedral_F4"), &D3DXVECTOR3(10457.9f, 0.0f, 9811.19f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F4);
	m_pLayer[LAYER_TYPE_STATIC_PROB]->AddObject(pCathedral_F4_Gate);
	pTransformCom = (CTransformCom*)pCathedral_F4_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(1904.15f, 14.4608f, 1766.73f);
	pCathedral_F4_Gate->SetSize(14.0f, 195.0f, 272.0f);
	pCathedral_F4_Gate->Initialize();

	// RoyalChamberToReorikMansion_Entrance
	CRoyalChamberToReorikMansion_Entrance* pRoyalChamberToReorikMansion_Entrance = new CRoyalChamberToReorikMansion_Entrance(_T("DynamicProb"), OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_DYNAMIC_PROB]->AddObject(pRoyalChamberToReorikMansion_Entrance);
	pRoyalChamberToReorikMansion_Entrance->Initialize();

	// MonsterSpawnTrigger1
	CMonsterSpawnTrigger* pMonsterSpawnTrigger1 = new CMonsterSpawnTrigger(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_TRIGGER]->AddObject(pMonsterSpawnTrigger1);
	pMonsterSpawnTrigger1->Initialize();

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3366.f, 0.f, 1653.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3425.f, 0.f, 2300.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3828.f, 0.f, 2336.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4187.f, 0.f, 2278.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(3988.f, 0.f, 1789.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(4251.f, 0.f, 1721.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5033.f, 1.f, 2333.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5285.f, 0.f, 2288.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5229.f, -11.f, 1760.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(5945.f, 0.f, 1788.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7098.f, 1.f, 1800.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7322.f, 2.f, 2063.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7501.f, 0.f, 2033.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7500.f, 0.f, 1703.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7019.f, -9.f, 906.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7434.f, 9.f, 835.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8283.f, -11.f, 950.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8335.f, 0.f, 1377.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8254.f, 2.f, 1528.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8273.f, 3.f, 2367.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7471.f, 3.f, 2282.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7317.f, 3.f, 2485.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7453.f, -0.f, 2955.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7281.f, 1.f, 3277.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7461.f, -11.f, 4194.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7238.f, 0.f, 4662.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7417.f, 1.f, 4795.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7619.f, -9.f, 4686.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7717.f, 5.f, 5430.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7409.f, 1.f, 5655.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 50));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7407.f, 4.f, 6341.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 50));
		
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7270.f, -7.f, 7107.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7616.f, 0.f, 7083.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8191.f, 0.f, 7119.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8194.f, 6.f, 7484.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8234.f, 6.f, 8131.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8147.f, 4.f, 8675.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7800.f, 4.f, 8651.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7068.f, 6.f, 8682.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6688.f, -6.f, 8523.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(6560.f, 5.f, 7934.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7147.f, -57.f, 7668.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7533.f, -57.f, 7652.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7663.f, -57.f, 8080.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7283.f, -56.f, 8176.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7435.f, 1.f, 10444.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7271.f, 0.f, 10697.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7534.f, 2.f, 10879.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7508.f, 0.f, 11314.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7522.f, 3.f, 13606.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7298.f, 2.f, 13842.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7399.f, 4.f, 14145.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7819.f, -7.f, 14025.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));

	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10498.f, 0.f, 15285.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10359.f, 1.f, 15431.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10503.f, 1.f, 15613.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10282.f, 0.f, 16153.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 54));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10732.f, -1.f, 16228.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 54));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10279.f, 0.f, 16864.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10660.f, 0.f, 16948.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10559.f, 1.f, 17221.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10688.f, -9.f, 17775.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10452.f, 0.f, 18420.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
		
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11169.f, 4.f, 19268.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11380.f, 0.f, 19053.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11543.f, -11.f, 19235.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11589.f, -11.f, 19796.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(11592.f, 0.f, 20231.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10391.f, 5.f, 20114.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(10122.f, 4.f, 20252.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9604.f, 3.f, 20149.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(9225.f, 4.f, 20247.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8758.f, 0.f, 20299.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(8239.f, 0.f, 20215.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 58));
	
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7478.f, 0.f, 21936.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7278.f, 0.f, 22237.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7480.f, 0.f, 22648.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7269.f, 0.f, 22977.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7556.f, 2.f, 23140.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), MONSTER_TYPE_SKELETON_ONEHAND_BROWN, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7650.f, 5.f, 23768.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7407.f, 1.f, 24092.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7415.f, 0.f, 24444.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_STITCH, rand() % 5 + 58));
	pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7326.f, 2.f, 24928.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.8f, 0.8f, 0.8f), MONSTER_TYPE_TRIUNE_BERSERKER, rand() % 5 + 58));

	//pMonsterSpawnTrigger1->AddMonsterSpawn(new MonsterSpawn(&D3DXVECTOR3(7394.f, 9.f, 26458.f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(2.0f, 2.0f, 2.0f), MONSTER_TYPE_WARDEN, rand() % 20 + 5));

	// Warden
	CWarden* pMonster0 = new CWarden(_T("Monster"), OBJ_TYPE_DYNAMIC, 70);
	m_pLayer[LAYER_TYPE_MONSTER]->AddObject(pMonster0);
	pTransformCom = (CTransformCom*)pMonster0->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(7394.f, 9.f, 26458.f);
	pTransformCom->m_vSize = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
	pMonster0->Initialize();
	pMonster0->SetState(new CWarden_Idle(0));
	
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
	CSceneMessage* pSceneMessage = new CSceneMessage(NULL, OBJ_TYPE_DYNAMIC, _T("¿Õ°¡ÀÇ ¹¦½Ç"));
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

CScene* CPlayScene_RoyalChamber::UpdatePlay()
{
	return CScene::UpdatePlay();
}