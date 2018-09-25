#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Actor\CPlayer.h"
#include "..\..\..\Include\Core\Components\PlayerInputComponent.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"



CPlayer::CPlayer()
	:CActor()
{
}

CPlayer::~CPlayer()
{
}

//bool CPlayer::Init(const Types::ActorData &)
//{
//	
//
//	return true;
//}

bool CPlayer::PostInit(const Types::ActorData& data, CGameScene* pScene)
{
	//기본 Actor의 속성 초기화
	if (data.iActorWidth > MAX_ACTOR_SIZE || data.iActorHeight > MAX_ACTOR_SIZE)
		return false;

	if (data.actorPoint.x < 0 || data.actorPoint.x > MAX_WIDTH || 
		data.actorPoint.y < 0 || data.actorPoint.y > MAX_HEIGHT)
		return false;

	m_iActorWidth = data.iActorWidth;
	m_iActorHeight = data.iActorHeight;
	m_actorPoint = m_spawnPoint = data.actorPoint;
	m_actorType = data.actorType;
	m_actorState = data.actorState;
	m_direction = data.direction;
	m_actorID = data.actorID;
	m_strActorTag = data.strActorTag;
	m_bActive = data.bActive;
	
	m_pOwnerScene = pScene;

	//AIComponent (InputComponent) 초기화
	PlayerInputComponent* pAI = new PlayerInputComponent;
	if (!pAI->Init(this))
		return false;

	if (!AddComponent(pAI, pAI->GetComponentTag()))
		return false;

	//PhysicsComponent 초기화
	PhysicsComponent* pPhysics = new PhysicsComponent;
	if (!pPhysics->Init(this, 500.f, 1300.f, -600.f))
		return false;

	if (!AddComponent(pPhysics, pPhysics->GetComponentTag()))
		return false;

	//Collider 초기화
	ColliderBox* pCollider = new ColliderBox;
	if (!pCollider->Init(this))
		return false;

	if (!AddComponent(pCollider, pCollider->GetComponentTag()))
		return false;

	return true;
}

bool CPlayer::Init()
{
	return false;
}

void CPlayer::Update(float fDeltaTime)
{
	CActor::Update(fDeltaTime);
}

void CPlayer::Render(const HDC & hDC)
{
	Rectangle(hDC, m_actorPoint.x, m_actorPoint.y, m_actorPoint.x + m_iActorWidth, m_actorPoint.y + m_iActorHeight);
}

void CPlayer::ActorBehavior()
{
}
