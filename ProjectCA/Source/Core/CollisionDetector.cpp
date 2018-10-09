#include "..\..\stdafx.h"
#include "..\..\Include\Core\CollisionDetector.h"
#include "..\..\Include\Core\Components\Collider.h"
#include "..\..\Include\Core\Components\ColliderBox.h"
#include "..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\Include\Scene\Actor\CActor.h"
//#include "..\..\Include\Core\Components\ColliderCircle.h"



CollisionDetector::CollisionDetector()
{
	
}

CollisionDetector::~CollisionDetector()
{



}

void CollisionDetector::Init()
{



}

void CollisionDetector::Update(Collider * pCollider, Collider * pOther)
{
	if ((pCollider->GetColliderType() == Collider::CT_BOX) && (pOther->GetColliderType() == Collider::CT_BOX))
		BoxAndBox(static_cast<ColliderBox*>(pCollider), static_cast<ColliderBox*>(pOther));


}

void CollisionDetector::Update(std::shared_ptr<CActor> pActor, std::shared_ptr<CActor> pOther)
{
	Collider* collider1 = static_cast<Collider*>(pActor->GetComponent(TEXT("Collider")));
	Collider* collider2 = static_cast<Collider*>(pOther->GetComponent(TEXT("Collider")));

	if (collider1 == nullptr || collider2 == nullptr)
		return;

	if ((collider1->GetColliderType() == Collider::CT_BOX) && (collider2->GetColliderType() == Collider::CT_BOX))
		BoxAndBox(pActor, pOther);


}

//
bool CollisionDetector::BoxAndBox(ColliderBox * pCollider, ColliderBox * pOther)
{
	Types::Rect box1 = pCollider->GetBoxSize();
	Types::Rect box2 = pOther->GetBoxSize();

	if ( (box1.right < box2.left) || (box1.left > box2.right) )
	{
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		return false;
	}
	
	if ((box1.top > box2.bottom) || (box1.bottom < box2.top))
	{
		//Debug::MessageInfo(TEXT("Collision!"));
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		return false;
	}

	
	pCollider->SetIsCollision(true);
	pOther->SetIsCollision(true);
	//collider1->ResolveCollision();
	return true;

}

//��Ŀ������ �ٲ���� �� ������..
bool CollisionDetector::BoxAndBox(std::shared_ptr<CActor> pActor, std::shared_ptr<CActor> pOther)
{
	ColliderBox* collider1 = static_cast<ColliderBox*>(pActor->GetComponent(TEXT("Collider")));
	ColliderBox* collider2 = static_cast<ColliderBox*>(pOther->GetComponent(TEXT("Collider")));
	if (collider1 == nullptr || collider2 == nullptr) // �� �� �ϳ��� Collider�� ���� ���� ����.
		return false;

	PhysicsComponent* pPhysics1 =  static_cast<PhysicsComponent*>(pActor->GetComponent(TEXT("PhysicsComponent")));
	PhysicsComponent* pPhysics2 = static_cast<PhysicsComponent*>(pOther->GetComponent(TEXT("PhysicsComponent")));

	const Types::Rect& box1 = collider1->GetBoxSize();
	const Types::Rect& box2 = collider2->GetBoxSize();

	//bool isCollision = false;

	//Collider::CollisionType collisionType = Collider::COLLISION_TOP;

	//�浹�� �ƴ� ����̴�.
	//�ϴ� �׽�Ʈ������ �浹�� ���� ��� ������ grounded�� false�� �����ϰԲ� ��. -> ���߿� �ݵ�� ����
	if ((box1.right < box2.left) || (box1.left > box2.right))
	{
		collider1->SetIsCollision(false);
		collider2->SetIsCollision(false);
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
		collider1->SetIsCollision(false);
		collider2->SetIsCollision(false);
		if (pPhysics1 != nullptr)
			pPhysics1->SetGrounded(false);
		if (pPhysics2 != nullptr)
			pPhysics2->SetGrounded(false);

		return false;
	}


	//������� ������ �浹�� �Ͼ ����̴�.
	//Collision�� �Ͼ���� ������ Collider Component�� �˸���, OnCollision �޼ҵ带 �����Ͽ� �浹 �� ���� ó��.
	collider1->SetIsCollision(true);
	collider2->SetIsCollision(true);
	collider1->OnCollision(pOther);
	collider2->OnCollision(pActor);

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
