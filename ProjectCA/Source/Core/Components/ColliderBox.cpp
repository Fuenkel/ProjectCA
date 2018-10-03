#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"



ColliderBox::ColliderBox()
	:Collider(CT_BOX), m_BoxSize(0, 0, 0, 0)
{

	//Debug::MessageInfo(TEXT("Create Box!"));
}

//ColliderBox::ColliderBox(CObject * owner, const Types::Rect& rect) :
//	Collider(owner, CT_BOX), m_BoxSize(rect),
//	m_iWidth(rect.right - rect.left), m_iHeight(rect.bottom - rect.top)
//{     
//	//Debug::MessageInfo(TEXT("Create Box2!"));
//	
//}

ColliderBox::~ColliderBox()
{
	//Debug::MessageInfo(TEXT("Bos Destruct"));
}

bool ColliderBox::Init(CActor* pOwner, const Types::tstring& strTag)
{
	auto pActor = std::shared_ptr<CActor>(pOwner);

	//if (point.x < 0.f || point.y < 0.f)
	//	return false;

	//m_ColliderPoint = point;
	m_pOwner = pActor;
	
	//ó�� Init�� �� �⺻������ Object�� �ʺ�, ���̸� ���󰡵��� ��.
	m_iWidth = m_pOwner->GetActorWidth();
	m_iHeight = m_pOwner->GetActorHeight();

	m_BoxSize.left = m_pOwner->GetActorPoint().x;
	m_BoxSize.top = m_pOwner->GetActorPoint().y;
	m_BoxSize.right = m_pOwner->GetActorPoint().x + m_pOwner->GetActorWidth();
	m_BoxSize.bottom = m_pOwner->GetActorPoint().y + m_pOwner->GetActorHeight();

	m_bIsCollision = false;
	m_strComponentTag = strTag;
	//Debug::MessageInfo(TEXT("Box Init"));

	return true;
}

//bool ColliderBox::Init(CActor * owner, const Types::tstring & strTag)
//{
//	//m_Collide
//
//
//	return true;
//}

//��ü�� �����ӿ� ���� CollisionBox�� ��ǥ�� ���� �̵��ؾ���.
//���� Offset���� ���̶� �ϴ� �س���, ���߿� Offset ������ �� ������ ��.(5.31)
void ColliderBox::Update(double fDeltaTime)
{
	//��ü ��ġ�� ���� CollisionBox ��ġ�̵�
	m_BoxSize.left = m_pOwner->GetActorPoint().x;
	m_BoxSize.top = m_pOwner->GetActorPoint().y;
	m_BoxSize.right = m_pOwner->GetActorPoint().x + (float)m_iWidth;
	m_BoxSize.bottom = m_pOwner->GetActorPoint().y + (float)m_iHeight;

	if (m_bIsCollision) {
		//m_bIsCollision = false;
		//PhysicsComponent* physics = static_cast<PhysicsComponent*>(m_pOwner->GetComponent(TEXT("PhysicsPhysicsComponent")));
		//if (physics == nullptr)
		//	return;

		//physics->Update(deltaTime);
	}
	
}

//void ColliderBox::ResolveCollision(Types::ObjectType type, CollisionType collision)
//{
//
//	switch (type) {
//		//case Types::OT_ENEMY:
//
//		//	break;
//	case Types::OT_PROBS:
//		/*
//		NOTE:
//		PROBS Object�� ���鿡 �΋H���Ÿ� �ش� ���������� �̵��� �����ϰ�, -> Object�� ������ IDLE�� �ٲٸ��.
//		���Ʒ��� �΋H�� ��� ���� ���ۿ� ����� ���.
//		*/
//		//if(m_pOwner->GetObjectPoint().x < )
//		switch (collision) {
//		case CollisionType::COLLSION_TOP:		//���κп� �΋H�� ��� �߷� �ʱ�ȭ
//			PhysicsComponent * physics = static_cast<PhysicsComponent*>(
//				m_pOwner->GetComponent(TEXT("PhysicsComponent")));
//			physics->ResetJumpForce();
//			break;
//		case CollisionType::COLLSION_BOT:		//�غκп� �΋H�� ��� Y��Ʒ��� �����ϰ���.
//
//			break;
//		case CollisionType::COLLSION_SIDE:		//���鿡 �΋H�� ��� X����� ������ ����.
//			
//			break;
//		}
//		break;
//		//case Types::OT_PICKUP:
//
//		//	break;
//	}
//
//
//
//}
