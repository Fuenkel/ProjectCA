#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\Collider.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"


Collider::Collider(ColliderType type)
	:m_Type(type)
{
	
}

Collider::~Collider()
{
	//Debug::MessageInfo(TEXT("Box Destruct"));
}

//Collision�� ����Ų Object Type���� �ൿ ����
//Collision�� ������ ���� ���۵� ���� �����ؾ���(18.07.04)
void Collider::OnCollision(Types::ObjectType type, Collider::CollisionType collision)
{

	switch (type) {
	//case Types::OT_ENEMY:

	//	break;
	case Types::OT_PROBS:
		/*
			NOTE:
				PROBS Object�� ���鿡 �΋H���Ÿ� �ش� ���������� �̵��� �����ϰ�,
				���Ʒ��� �΋H�� ��� ���� ���ۿ� ����� ���.
		*/
		

		switch (collision) {
		case CollisionType::COLLISION_TOP:		//���κп� �΋H�� ��� �߷� �ʱ�ȭ
			{
				PhysicsComponent * physics = static_cast<PhysicsComponent*>(
					m_pOwner->GetComponent(TEXT("PhysicsComponent")));
				if (physics == nullptr)
					return;
					
				physics->ResetJumpForce();
				//Debug::MessageInfo(TEXT("TOP"));
			}
			break;

		//case CollisionType::COLLISION_BOT:		//�غκп� �΋H�� ��� Y��Ʒ��� �����ϰ���.
		//	break;
		case CollisionType::COLLISION_SIDE:		//���鿡 �΋H�� ��� X����� ������ ����.
			m_pOwner->SetActorDirection(Types::DIR_IDLE);
			//Debug::MessageInfo(TEXT("SIDE"));
			break;
		}
		break;


	//case Types::OT_PICKUP:

	//	break;
	}



}

//�����ε��� ���� ����
void Collider::OnCollision(Types::ObjectType type)
{
	if (m_bIsCollision) {
		ComponentBase* pComponent = nullptr;
		switch (type) {
		case Types::OT_PROBS:
			//m_pOwner->SetObjectState(Types::OS_IDLE);
			pComponent = m_pOwner->GetComponent(TEXT("PhysicsComponent"));
			PhysicsComponent* physics = static_cast<PhysicsComponent*>(pComponent);
			physics->ResetSpeed();
			break;
		}
	}
	//else {
	//	m_pOwner->SetObjectState(Types::OS_MOVE);
	//}
	

}

//void Collider::Init()
//{
//	//m_pOwner = owner;
//
//
//}
//
//void Collider::Update(const double & deltaTime)
//{
//
//
//}
