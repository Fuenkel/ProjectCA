#include "..\..\stdafx.h"
#include "..\..\Include\Core\CCollisionManager.h"
#include "..\..\Include\Core\Components\Collider.h"
#include "..\..\Include\Core\Components\ColliderBox.h"
#include "..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\Include\Scene\Actor\CActor.h"
//#include "..\..\Include\Core\Components\ColliderCircle.h"



CCollisionManager::CCollisionManager()
{
	
}

CCollisionManager::~CCollisionManager()
{



}

void CCollisionManager::Init()
{



}

void CCollisionManager::Update(Collider * pCollider, Collider * pOther)
{
	if ((pCollider->GetColliderType() == Collider::CT_BOX) && (pOther->GetColliderType() == Collider::CT_BOX))
		BoxAndBox(static_cast<ColliderBox*>(pCollider), static_cast<ColliderBox*>(pOther));


}

void CCollisionManager::Update(std::shared_ptr<CActor> pActor, std::shared_ptr<CActor> pOther)
{
	Collider* collider1 = static_cast<Collider*>(pActor->GetComponent(TEXT("Collider")));
	Collider* collider2 = static_cast<Collider*>(pOther->GetComponent(TEXT("Collider")));

	if (collider1 == nullptr || collider2 == nullptr)
		return;

	if ((collider1->GetColliderType() == Collider::CT_BOX) && (collider2->GetColliderType() == Collider::CT_BOX))
		BoxAndBox(pActor, pOther);


}

//
bool CCollisionManager::BoxAndBox(ColliderBox * pCollider, ColliderBox * pOther)
{
	Types::Rect box1 = pCollider->GetRect();
	Types::Rect box2 = pOther->GetRect();

	//��, �Ʒ� �浹�˻�
	if ( box1.right > box2.left && box1.left < box2.right)
	{
		if (box1.bottom <= box2.top && box1.bottom > box2.bottom)
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(COLLISION_BOT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(COLLISION_TOP);
		}
		else if(box1.top >= box2.bottom && box1.top < box2.top )
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(COLLISION_TOP);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(COLLISION_BOT);
		}
		
	}
	else if (box1.bottom < box2.top && box1.top > box2.bottom)	//���̵� �浹 �˻�
	{
		if (box1.right >= box2.left && box1.right < box2.right)
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(COLLISION_RIGHT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(COLLISION_LEFT);
		}
		else if (box1.left <= box2.right && box1.left > box2.left)
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(COLLISION_LEFT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(COLLISION_RIGHT);
		}

	}

	
	pCollider->SetIsCollision(false);
	pOther->SetIsCollision(false);
	//collider1->ResolveCollision();
	return false;

}


bool CCollisionManager::BoxAndBox(std::shared_ptr<CActor> pActor, std::shared_ptr<CActor> pOtherActor)
{
	ColliderBox* pCollider = static_cast<ColliderBox*>(pActor->GetComponent(TEXT("Collider")));
	ColliderBox* pOther = static_cast<ColliderBox*>(pOtherActor->GetComponent(TEXT("Collider")));
	if (pCollider == nullptr || pOther == nullptr) // �� �� �ϳ��� Collider�� ���� ���� ���� ���
		return false;

	//PhysicsComponent* pPhysics1 =  static_cast<PhysicsComponent*>(pActor->GetComponent(TEXT("PhysicsComponent")));
	//PhysicsComponent* pPhysics2 = static_cast<PhysicsComponent*>(pOtherActor->GetComponent(TEXT("PhysicsComponent")));

	const Types::Rect& box1 = pCollider->GetRect();
	const Types::Rect& box2 = pOther->GetRect();

	////��, �Ʒ� �浹�˻�
	//if (box1.bottom > box2.top && box1.top < box2.bottom)	//���̵� �浹 �˻�
	//{
	//	//puts("Collision2..");
	//	if (box1.right >= box2.left && box1.right < box2.right)
	//	{
	//		pCollider->SetIsCollision(true);
	//		pCollider->SetCollisionType(COLLISION_RIGHT);

	//		pOther->SetIsCollision(true);
	//		pOther->SetCollisionType(COLLISION_LEFT);

	//		pCollider->OnCollision(pOtherActor);
	//		pOther->OnCollision(pActor);
	//	}
	//	else if (box1.left <= box2.right && box1.left > box2.left)
	//	{
	//		pCollider->SetIsCollision(true);
	//		pCollider->SetCollisionType(COLLISION_LEFT);

	//		pOther->SetIsCollision(true);
	//		pOther->SetCollisionType(COLLISION_RIGHT);

	//		pCollider->OnCollision(pOtherActor);
	//		pOther->OnCollision(pActor);
	//	}

	//}
	//else if (box1.right > box2.left && box1.left < box2.right)
	//{
	//	if (box1.bottom >= box2.top && box1.bottom < box2.bottom)
	//	{
	//		puts("player");
	//		pCollider->SetIsCollision(true);
	//		pCollider->SetCollisionType(COLLISION_BOT);

	//		pOther->SetIsCollision(true);
	//		pOther->SetCollisionType(COLLISION_TOP);

	//		pCollider->OnCollision(pOtherActor);
	//		pOther->OnCollision(pActor);
	//	}
	//	else if (box1.top <= box2.bottom && box1.top > box2.top)
	//	{
	//		pCollider->SetIsCollision(true);
	//		pCollider->SetCollisionType(COLLISION_TOP);

	//		pOther->SetIsCollision(true);
	//		pOther->SetCollisionType(COLLISION_BOT);

	//		pCollider->OnCollision(pOtherActor);
	//		pOther->OnCollision(pActor);
	//	}

	//}

	//pCollider->SetIsCollision(false);
	//pOther->SetIsCollision(false);

	//return false;

	////bool isCollision = false;

	////Collider::CollisionType collisionType = Collider::COLLISION_TOP;

	//�浹�� �ƴ� ����̴�.
	//�ϴ� �׽�Ʈ������ �浹�� ���� ��� ������ grounded�� false�� �����ϰԲ� ��. -> ���߿� �ݵ�� ����
	if ((box1.right < box2.left) || (box1.left > box2.right))
	{
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		pCollider->SetCollisionType(COLLISION_IDLE);
		pOther->SetCollisionType(COLLISION_IDLE);
		//if (pPhysics1 != nullptr)
		//	pPhysics1->SetGrounded(false);
		//if (pPhysics2 != nullptr)
		//	pPhysics2->SetGrounded(false);
		//
		return false;
	}

	if ((box1.top > box2.bottom) || (box1.bottom < box2.top))
	{
		//Debug::MessageInfo(TEXT("Collision!"));
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		pCollider->SetCollisionType(COLLISION_IDLE);
		pOther->SetCollisionType(COLLISION_IDLE);
		//if (pPhysics1 != nullptr)
		//	pPhysics1->SetGrounded(false);
		//if (pPhysics2 != nullptr)
		//	pPhysics2->SetGrounded(false);

		return false;
	}


	//������� ������ �浹�� �Ͼ ����̴�.
	//Collision�� �Ͼ���� ������ Collider Component�� �˸���, OnCollision �޼ҵ带 �����Ͽ� �浹 �� ���� ó��.
	//BUG : ������ Ƣ�°� ������ �˻��� �� �հ����������� -> �ڷ��� �ȸ����༭ �׷���
	//			
	//��, ��
	if (box1.top < box2.bottom && box1.bottom > box2.top)
	{
		if (box1.left < box2.left)
		{
			if (pCollider->GetCollisionType() == COLLISION_TOP)
				puts("TOP");
			pCollider->SetCollisionType(COLLISION_RIGHT);
			pOther->SetCollisionType(COLLISION_LEFT);

			pCollider->SetIsCollision(true);
			pOther->SetIsCollision(true);
			pCollider->OnCollision(pOtherActor);
			pOther->OnCollision(pActor);

			return true;
		}
		else if (box1.right > box2.right)
		{
			pCollider->SetCollisionType(COLLISION_LEFT);
			pOther->SetCollisionType(COLLISION_RIGHT);

			pCollider->SetIsCollision(true);
			pOther->SetIsCollision(true);
			pCollider->OnCollision(pOtherActor);
			pOther->OnCollision(pActor);

			return true;
		}

	}

	//��, ��
	if (box1.right >= box2.left && box1.left <= box2.right)
	{
		if (box1.bottom < box2.bottom)
		{
			pCollider->SetCollisionType(COLLISION_BOT);
			pOther->SetCollisionType(COLLISION_TOP);
		
			pCollider->SetIsCollision(true);
			pOther->SetIsCollision(true);
			pCollider->OnCollision(pOtherActor);
			pOther->OnCollision(pActor);

			return true;

		}
		else if (box1.top > box2.top)
		{
			//if(pActor->GetActorType() == Types::AT_PLAYER)
			//puts("TOP");

			pCollider->SetCollisionType(COLLISION_TOP);
			pOther->SetCollisionType(COLLISION_BOT);

			pCollider->SetIsCollision(true);
			pOther->SetIsCollision(true);
			pCollider->OnCollision(pOtherActor);
			pOther->OnCollision(pActor);

			return true;
		}

	}



	pCollider->SetIsCollision(true);
	pOther->SetIsCollision(true);
	pCollider->OnCollision(pOtherActor);
	pOther->OnCollision(pActor);

	return true;



}








//bool CollisionDetector::BoxAndCircle(ColliderBox * collider1, ColliderCircle * colldier2)
//{
//	return false;
//}
//
//bool CollisionDetector::CircleToCircle(ColliderCircle * collider1, ColliderCircle * colldier2)
//{
//	return false;
//}
