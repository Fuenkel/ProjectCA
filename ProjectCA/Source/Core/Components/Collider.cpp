#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\Collider.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"
#include "..\..\..\Include\Core\CCollisionManager.h"

//������ �� Collider�� Default�� Collision ���⿡ ����.
//Trigger�� ����ϰ� ���� ��� SetUseTrigger�Լ��� �̿��� Trigger�� ��ȯ
Collider::Collider(ColliderType type)
	:m_ColliderType(type), m_CollisionType(COLLISION_IDLE),
	m_pOnCollision(nullptr), m_pOnTrigger(nullptr), 
	m_bCollision(false), m_bUseTrigger(false)
{
}

Collider::~Collider()
{
	puts("Delete Collider");

	CCollisionManager::GetInstance()->DeleteCollider(this);
}

bool Collider::PostInit(CObject * pOwner, const Types::tstring & strTag)
{
	m_pOwner				= pOwner;
	m_strComponentTag = strTag;

	m_bActive = true;

	CCollisionManager::GetInstance()->AddCollider(this);

	return true;
}

void Collider::LateUpdate()
{
}

void Collider::ResolveCollision(CObject* pOther, float fintersectLength)
{
	if (m_bUseTrigger)
	{
		OnTriggered(pOther, fintersectLength);
	}
	else
	{
		OnCollision(pOther, fintersectLength);
	}
}

void Collider::SetColliderType(ColliderType type)
{
	m_ColliderType = type;
}

void Collider::SetCollisionType(CollisionType type)
{
	m_CollisionType = type;
}

void Collider::SetIsCollision(bool bCollision)
{
	m_bCollision = bCollision;
}

void Collider::SetColliderPoint(POSITION position)
{
	m_CurColliderPoint = m_ColliderPoint = position;
}

void Collider::SetColliderPoint(float fx, float fy)
{
	SetColliderPoint(POSITION(fx, fy));
}

void Collider::SetUseTriggered(bool bUseTrigger)
{
	m_bUseTrigger = bUseTrigger;
}

void Collider::SetDelegate(Callback pDelegate)
{
	if (m_bUseTrigger)
	{
		m_pOnTrigger = pDelegate;
	}
	else
	{
		m_pOnCollision = pDelegate;
	}
}

void Collider::SetOnCollision(Callback pCollision)
{
	m_pOnCollision =  pCollision;
}

void Collider::SetOnTrigerr(Callback pTrigger)
{
	m_pOnTrigger = pTrigger;
}

Collider::ColliderType Collider::GetColliderType() const
{
	return m_ColliderType;
}

Collider::CollisionType Collider::GetCollisionType() const
{
	return m_CollisionType;
}

bool Collider::IsCollision() const
{
	return m_bCollision;
}

const Types::Point & Collider::GetColliderPoint() const
{
	return m_CurColliderPoint;
}

bool Collider::IsTriggered() const
{
	return m_bUseTrigger;
}


//Collision�� �Ͼ�ٸ� ȣ���ϰ� �� �޼ҵ�
void Collider::OnCollision(CObject*pOther, float fintersectLength)
{
	if (m_pOnCollision != nullptr)
	{
		m_pOnCollision(pOther, m_CollisionType, fintersectLength);
		m_CollisionType = COLLISION_IDLE;
	}
}

//Trigger������ �� ȣ���� �޼ҵ�
void Collider::OnTriggered(CObject* pOther, float fintersectLength)
{
	if (m_pOnTrigger != nullptr)
	{
		m_pOnTrigger(pOther, m_CollisionType, fintersectLength);
	}
}
