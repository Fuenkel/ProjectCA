#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Actor\CProb.h" 
#include "..\..\..\Include\Core\Components\AIComponent.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"


CProb::CProb()
	:CActor()
{
}

CProb::~CProb()
{
}

bool CProb::PostInit(const Types::ActorData & data, CGameScene* pScene)
{
	//�⺻ Actor�� �Ӽ� �ʱ�ȭ
	if (data.iActorWidth > MAX_ACTOR_SIZE || data.iActorHeight > MAX_ACTOR_SIZE)
		return false;

	if (data.actorPoint.x < 0 || data.actorPoint.x > MAX_WIDTH ||
		data.actorPoint.y < 0 || data.actorPoint.y > MAX_HEIGHT)
		return false;

	m_iActorWidth = data.iActorWidth;
	m_iActorHeight = data.iActorHeight;
	m_actorPoint = m_spawnPoint = data.actorPoint;
	m_actorType = data.actorType;
	m_actorCurState = m_actorPreState = data.actorState;
	m_actorCurVerticalState = m_actorPreVerticalState = data.verticalState;
	m_actorHorizonalState = data.horizonalState;
	m_direction = data.direction;
	m_actorVector = data.vector;
	m_actorID = data.actorID;
	m_strActorTag = data.strActorTag;
	m_bActive = data.bActive;

	m_pOwnerScene = pScene;

	//AIComponent (InputComponent) �ʱ�ȭ
	AIComponent* pAI = new AIComponent;
	if (!pAI->Init(this))
		return false;

	if (!AddComponent(pAI, pAI->GetComponentTag()))
		return false;

	//PhysicsComponent �ʱ�ȭ
	PhysicsComponent* pPhysics = new PhysicsComponent;
	if (!pPhysics->Init(this, 0.f, 0.f, 0.f, 0.f))
		return false;

	if (!AddComponent(pPhysics, pPhysics->GetComponentTag()))
		return false;

	//Collider �ʱ�ȭ
	ColliderBox* pCollider = new ColliderBox;
	if (!pCollider->Init(this))
		return false;

	if (!AddComponent(pCollider, pCollider->GetComponentTag()))
		return false;
	

	return true;
}

bool CProb::Init()
{
	return true;
}

void CProb::Update(double fDeltaTime)
{
	CActor::Update(fDeltaTime);
}

void CProb::Render(const HDC & hDC)
{
	Rectangle(hDC, m_actorPoint.x, m_actorPoint.y, m_actorPoint.x + m_iActorWidth, m_actorPoint.y + m_iActorHeight);

}

void CProb::ActorBehavior()
{
}
