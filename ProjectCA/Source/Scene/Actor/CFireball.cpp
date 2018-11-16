#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Actor\CFireball.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"
#include "..\..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"
#include "..\..\..\Include\Core\Components\AnimationRender.h"
#include "..\..\..\Include\Scene\CCameraManager.h"
#include "..\..\..\Include\Scene\Actor\CCamera.h"


CFireball::CFireball()
	:CActor()
{
}

CFireball::~CFireball()
{
}

bool CFireball::PostInit(const Types::ActorData & data, CGameScene* pScene)
{
	if (!CActor::PostInit(data, pScene))
		return false;

	//Physics �߰�
	auto pPhysics = std::make_shared<PhysicsComponent>();
	if (!pPhysics->PostInit(this, 600.f, 600.f, 1000.f, 500.f))
		return false;
	//pPhysics->SetCurSpeed(pPhysics->GetSpeed());
	if (!AddComponent(pPhysics, pPhysics->GetComponentTag()))
		return false;


	//Collider �߰�
	auto pCollider = std::make_shared<ColliderBox>();
	if (!pCollider->PostInit(this))
		return false;
	pCollider->SetSize(m_iObjectWidth * 0.23f, m_iObjectHeight * 0.23f);

	auto onCollision = [&](CObject* pOther, Collider::CollisionType type, float fIntersectLength)->void {

		CActor* pOtherActor = static_cast<CActor*>(pOther);

		switch (pOtherActor->GetActorType())
		{
		case Types::AT_ENEMY:
			pOtherActor->SetActorState(Types::AS_DAMAGED);
			pOtherActor->GetComponent<PhysicsComponent>().lock()->SetCurSpeed(0.f);
			pOtherActor->GetComponent<ColliderBox>().lock()->SetCurRectHeight(pOtherActor->GetComponent<ColliderBox>().lock()->GetHeight());
			SetActive(false);
			break;
		case Types::AT_PROB:
			switch (type)
			{
			case Collider::COLLISION_BOT:
				GetComponent<PhysicsComponent>().lock()->SetGrounded(true);
				GetComponent<PhysicsComponent>().lock()->SetCurJumpForce(GetComponent<PhysicsComponent>().lock()->GetJumpForce());
				break;
			default:
				SetActive(false);
				break;
			}
			break;
		}

	};
	pCollider->SetOnCollision(onCollision);
	if (!AddComponent(pCollider, pCollider->GetComponentTag()))
		return false;


	//Render �߰�
	auto pRender = std::make_shared<AnimationRender>();
	if (!pRender->PostInit(this))
		return false;
	if (!pRender->AddAnimation(0.3f, TEXT("Default"), TEXT("FireballRight"), m_iObjectWidth, m_iObjectHeight, true, TEXT("AttackRight")))
		return false;
	if (!pRender->AddAnimation(0.3f, TEXT("Default"), TEXT("FireballLeft"), m_iObjectWidth, m_iObjectHeight, true, TEXT("AttackLeft")))
		return false;
	if (!AddComponent(pRender, pRender->GetAnimTag()))
		return false;

	m_bActive = false;

	return true;
}

void CFireball::Init()
{
	CActor::Init();
	m_bActive = false;
}

void CFireball::Update(double dDeltaTime)
{
	if (!m_bActive)
	{
		GetTransform().lock()->SetPosition(m_pOwnerActor->GetObjectPosition().x, m_pOwnerActor->GetObjectPosition().y - m_pOwnerActor->GetObjectHeight() / 2.f);
	}
	else
	{
		ActorBehavior(dDeltaTime);
		for (auto& component : m_ComponentTable)
		{
			component.second->Update(dDeltaTime);
		}
	}

}

void CFireball::Render(const HDC & hDC)
{
	if (m_bActive)
	{
		auto pRender = GetComponent<AnimationRender>();
		if (!pRender.expired())
			pRender.lock()->Draw(hDC);
	}
}

void CFireball::SetFireballActive()
{
	m_Direction = m_pOwnerActor->GetActorDirection();
	
	auto pPhysics = GetComponent<PhysicsComponent>().lock();
	float fWalkSpeed = pPhysics->GetSpeed();

	if (m_Direction == Types::DIR_LEFT)
	{
		pPhysics->SetCurSpeed(-1 * fWalkSpeed);
	}
	else if (m_Direction == Types::DIR_RIGHT)
	{
		pPhysics->SetCurSpeed(fWalkSpeed);
	}
	SetActive(true);

}


void CFireball::ActorBehavior(double dDeltaTime)
{
	auto pPhysics = GetComponent<PhysicsComponent>().lock();
	auto pCamera = CCameraManager::GetInstance()->GetMainCamera().lock();
	auto screenPosition = GetTransform().lock()->GetScreenPosition();

	if (screenPosition.x < 0.f || screenPosition.x >(float)pCamera->GetCameraWidth())
	{
		m_bActive = false;
		return;
	}
	if (screenPosition.y < 0.f || screenPosition.y >(float)pCamera->GetCameraHeight())
	{
		m_bActive = false;
		return;
	}

	GetTransform().lock()->Move(pPhysics->GetCurSpeed() * dDeltaTime, pPhysics->GetCurJumpForce() * dDeltaTime);


}
