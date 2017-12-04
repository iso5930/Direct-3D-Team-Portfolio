#include "StdAfx.h"
#include "Skeleton_King.h"

CSkeleton_King::CSkeleton_King(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("해골 왕"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = 49000000;
	m_stat.iStrength = 7000;

	// CollisionCom
	/*m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 60.0f, 0.0f), 30.0f, 70.0f, 30.0f));
	AddComponent(m_pCollisionCom);*/

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 120.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Skeleton_King"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	m_LeftHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_index2");
	m_CenterBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spine2");
	m_CenterTopBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spine3");
}

CSkeleton_King::~CSkeleton_King()
{
	Release();
}

void CSkeleton_King::Initialize()
{
	CMonster::Initialize();
	
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-90.f);
}

int CSkeleton_King::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_CenterBone.mWorld = m_CenterBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_CenterTopBone.mWorld = m_CenterTopBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	
	return 0;
}

void CSkeleton_King::Render()
{
	CMonster::Render();
}

void CSkeleton_King::Release()
{
}

void CSkeleton_King::CreateAttack()
{
	CCollisionCom* pCollisionCom = (CCollisionCom*)m_pComponent[COM_TYPE_COLLISION];

	if(pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_SKELETON_KING_ATTACK1:
		pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, -20.f), 40.f, 40.f, 40.f));
		break;
	case STATE_TYPE_SKELETON_KING_DEATH:
		break;
	case STATE_TYPE_SKELETON_KING_IDLE :
		break;
	case STATE_TYPE_SKELETON_KING_INTRO :
		break;
	case STATE_TYPE_SKELETON_KING_INTRO_IDLE :
		break;
	case STATE_TYPE_SKELETON_KING_SUMMON :
		break;
	case STATE_TYPE_SKELETON_KING_TAUNT :
		break;
	case STATE_TYPE_SKELETON_KING_TELEPORT :
		break;
	case STATE_TYPE_SKELETON_KING_TELEPORT_ATTACK :
		pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, -20.f), 40.f, 40.f, 40.f));
		break;
	case STATE_TYPE_SKELETON_KING_TELEPORT_BACK :
		break;
	case STATE_TYPE_SKELETON_KING_TELEPORT_BACK_POSE :
		break;
	case STATE_TYPE_SKELETON_KING_WALK :
		break;
	case STATE_TYPE_SKELETON_KING_WHIRLWIND_END :
		break;
	case STATE_TYPE_SKELETON_KING_WHIRLWIND_LOOP :
		pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, -20.f), 40.f, 40.f, 40.f));
		break;
	case STATE_TYPE_SKELETON_KING_WHIRLWIND_START :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CSkeleton_King::Damage(CPlayer* _pPlayer)
{
	// Damage
	CMonster::Damage(_pPlayer);

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ONEHAND_BLUE_DEATH)
	{
		// Cath1FToTristram_Gate
		CGate* pCath1FToTristram_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("트리스트럼"), _T("Tristram"), &D3DXVECTOR3(5605.6f, 695.88f, 23559.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_TRISTRAM);
		m_pLayer->AddObject(pCath1FToTristram_Gate, LAYER_TYPE_STATIC_PROB);
		
		CTransformCom* pTransformCom = (CTransformCom*)pCath1FToTristram_Gate->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(52.0f, 203.0f, 1772.0f);
		
		pCath1FToTristram_Gate->SetSize(100.0f, 192.0f, 100.0f);
		pCath1FToTristram_Gate->Initialize();

		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트11 : 엔딩"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST11));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 11;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
			{
				pNPC->SetMode(2);
				break;
			}
		}

		SetState(new CSkeleton_King_Death);
		return;
	}
}

void CSkeleton_King::Damage(CEffect* _pEffect)
{
	// Damage
	CMonster::Damage(_pEffect);

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ONEHAND_BLUE_DEATH)
	{
		// Cath1FToTristram_Gate
		CGate* pCath1FToTristram_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("트리스트럼"), _T("Tristram"), &D3DXVECTOR3(5605.6f, 695.88f, 23559.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_TRISTRAM);
		m_pLayer->AddObject(pCath1FToTristram_Gate, LAYER_TYPE_STATIC_PROB);
		
		CTransformCom* pTransformCom = (CTransformCom*)pCath1FToTristram_Gate->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(52.0f, 203.0f, 1772.0f);
		
		pCath1FToTristram_Gate->SetSize(100.0f, 192.0f, 100.0f);
		pCath1FToTristram_Gate->Initialize();

		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트11 : 엔딩"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();
		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST11));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 11;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
			{
				pNPC->SetMode(10);
				break;
			}
		}

		SetState(new CSkeleton_King_Death);
		return;
	}
}