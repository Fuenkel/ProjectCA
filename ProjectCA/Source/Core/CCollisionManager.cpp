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

bool CCollisionManager::Init()
{


	return true;
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

bool CCollisionManager::CheckCollision(std::shared_ptr<CActor> pActor, std::shared_ptr<CActor> pOther)
{
	Collider* collider1 = static_cast<Collider*>(pActor->GetComponent(TEXT("Collider")));
	Collider* collider2 = static_cast<Collider*>(pOther->GetComponent(TEXT("Collider")));
	bool		bIsCollision = false;

	if (collider1 == nullptr || collider2 == nullptr)
		return bIsCollision;

	if ((collider1->GetColliderType() == Collider::CT_BOX) && (collider2->GetColliderType() == Collider::CT_BOX))
		bIsCollision = BoxAndBox(pActor, pOther);

	return bIsCollision;
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
			pCollider->SetCollisionType(Collider::COLLISION_BOT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(Collider::COLLISION_TOP);
		}
		else if(box1.top >= box2.bottom && box1.top < box2.top )
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(Collider::COLLISION_TOP);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(Collider::COLLISION_BOT);
		}
		
	}
	else if (box1.bottom < box2.top && box1.top > box2.bottom)	//���̵� �浹 �˻�
	{
		if (box1.right >= box2.left && box1.right < box2.right)
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(Collider::COLLISION_RIGHT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(Collider::COLLISION_LEFT);
		}
		else if (box1.left <= box2.right && box1.left > box2.left)
		{
			pCollider->SetIsCollision(true);
			pCollider->SetCollisionType(Collider::COLLISION_LEFT);

			pOther->SetIsCollision(true);
			pOther->SetCollisionType(Collider::COLLISION_RIGHT);
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

	const Types::Rect& box1 = pCollider->GetRect();
	const Types::Rect& box2 = pOther->GetRect();

	//�浹�� �ƴ� ����̴�.
	if ((box1.right < box2.left) || (box1.left > box2.right))
	{
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		pCollider->SetCollisionType(Collider::COLLISION_IDLE);
		pOther->SetCollisionType(Collider::COLLISION_IDLE);
		return false;
	}

	if ((box1.top > box2.bottom) || (box1.bottom < box2.top))
	{
		pCollider->SetIsCollision(false);
		pOther->SetIsCollision(false);
		pCollider->SetCollisionType(Collider::COLLISION_IDLE);
		pOther->SetCollisionType(Collider::COLLISION_IDLE);

		return false;
	}

	//������� ������ �浹�� �Ͼ ����̴�.
	//Collision�� �Ͼ���� ������ Collider Component�� �˸���, OnCollision �޼ҵ带 �����Ͽ� �浹 �� ���� ó��.
	float fIntersecRectWidth = 0.f;
	float fIntersecRectHeight = 0.f;

	//box1 : Left, Box2 : Right
	if (box1.right < box2.right)
	{
		if (box1.left < box2.left)
		{
			fIntersecRectWidth = box1.right - box2.left;
			if (box1.top < box2.top && box1.bottom >= box2.top)		//��
			{
				fIntersecRectHeight = box1.bottom - box2.top;
				if (fIntersecRectHeight > fIntersecRectWidth)
				{
					pCollider->SetCollisionType(Collider::COLLISION_RIGHT);
					pOther->SetCollisionType(Collider::COLLISION_LEFT);
				}
				else
				{
					pCollider->SetCollisionType(Collider::COLLISION_BOT);
					pOther->SetCollisionType(Collider::COLLISION_TOP);
				}
			}
			else if (box1.top < box2.bottom && box1.bottom > box2.bottom)	//�Ʒ�
			{
				fIntersecRectHeight = box2.bottom - box1.top;
				if (fIntersecRectHeight > fIntersecRectWidth)
				{
					pCollider->SetCollisionType(Collider::COLLISION_RIGHT);
					pOther->SetCollisionType(Collider::COLLISION_LEFT);
				}
				else
				{
					pCollider->SetCollisionType(Collider::COLLISION_TOP);
					pOther->SetCollisionType(Collider::COLLISION_BOT);
				}
			}
			else   //�߰�
			{
				pCollider->SetCollisionType(Collider::COLLISION_RIGHT);
				pOther->SetCollisionType(Collider::COLLISION_LEFT);
			}
		}
		else
		{
			if (box1.bottom >= box2.top && box1.bottom < box2.bottom)
			{
				pCollider->SetCollisionType(Collider::COLLISION_BOT);
				pOther->SetCollisionType(Collider::COLLISION_TOP);
			}
			else if(box1.top <= box2.bottom && box1.top > box2.top)
			{
				pCollider->SetCollisionType(Collider::COLLISION_TOP);
				pOther->SetCollisionType(Collider::COLLISION_BOT);
			}
		}
	}
	//box1 : Right, box2 : Left
	else if (box1.left > box2.left)
	{
		if (box1.right > box2.right)
		{
			fIntersecRectWidth = box2.right - box1.left;
			if (box1.top < box2.top && box1.bottom >= box2.top)		//��
			{
				fIntersecRectHeight = box1.bottom - box2.top;
				if (fIntersecRectHeight > fIntersecRectWidth)
				{
					pCollider->SetCollisionType(Collider::COLLISION_LEFT);
					pOther->SetCollisionType(Collider::COLLISION_RIGHT);
				}
				else
				{
					pCollider->SetCollisionType(Collider::COLLISION_BOT);
					pOther->SetCollisionType(Collider::COLLISION_TOP);
				}
			}
			else if (box1.top < box2.bottom && box1.bottom > box2.bottom)	//�Ʒ�
			{
				fIntersecRectHeight = box2.bottom - box1.top;
				if (fIntersecRectHeight > fIntersecRectWidth)
				{
					pCollider->SetCollisionType(Collider::COLLISION_LEFT);
					pOther->SetCollisionType(Collider::COLLISION_RIGHT);
				}
				else
				{
					pCollider->SetCollisionType(Collider::COLLISION_TOP);
					pOther->SetCollisionType(Collider::COLLISION_BOT);
				}
			}
			else   //�߰�
			{
				pCollider->SetCollisionType(Collider::COLLISION_RIGHT);
				pOther->SetCollisionType(Collider::COLLISION_LEFT);
			}
		}
		else
		{
			if (box1.bottom >= box2.top && box1.bottom < box2.bottom)
			{
				pCollider->SetCollisionType(Collider::COLLISION_BOT);
				pOther->SetCollisionType(Collider::COLLISION_TOP);
			}
			else if (box1.top <= box2.bottom && box1.top > box2.top)
			{
				pCollider->SetCollisionType(Collider::COLLISION_TOP);
				pOther->SetCollisionType(Collider::COLLISION_BOT);
			}
		}
	}

	pCollider->SetIsCollision(true);
	pOther->SetIsCollision(true);
	pCollider->ResolveCollision(pOtherActor);
	pOther->ResolveCollision(pActor);

	return true;
	////��, ��
	//if (box1.top < box2.bottom && box1.bottom > box2.top)
	//{
	//	if (box1.left < box2.left)
	//	{
	//		pCollider->SetCollisionType(Collider::COLLISION_RIGHT);
	//		pOther->SetCollisionType(Collider::COLLISION_LEFT);

	//		pCollider->SetIsCollision(true);
	//		pOther->SetIsCollision(true);
	//		pCollider->ResolveCollision(pOtherActor);
	//		pOther->ResolveCollision(pActor);

	//		return true;
	//	}
	//	else if (box1.right > box2.right)
	//	{
	//		pCollider->SetCollisionType(Collider::COLLISION_LEFT);
	//		pOther->SetCollisionType(Collider::COLLISION_RIGHT);

	//		pCollider->SetIsCollision(true);
	//		pOther->SetIsCollision(true);
	//		pCollider->ResolveCollision(pOtherActor);
	//		pOther->ResolveCollision(pActor);

	//		return true;
	//	}

	//}

	////��, ��
	//if (box1.right >= box2.left && box1.left <= box2.right)
	//{
	//	if (box1.bottom < box2.bottom)
	//	{
	//		pCollider->SetCollisionType(Collider::COLLISION_BOT);
	//		pOther->SetCollisionType(Collider::COLLISION_TOP);
	//	
	//		pCollider->SetIsCollision(true);
	//		pOther->SetIsCollision(true);
	//		pCollider->ResolveCollision(pOtherActor);
	//		pOther->ResolveCollision(pActor);

	//		return true;
	//	}
	//	else if (box1.top > box2.top)
	//	{
	//		pCollider->SetCollisionType(Collider::COLLISION_TOP);
	//		pOther->SetCollisionType(Collider::COLLISION_BOT);

	//		pCollider->SetIsCollision(true);
	//		pOther->SetIsCollision(true);
	//		pCollider->ResolveCollision(pOtherActor);
	//		pOther->ResolveCollision(pActor);

	//		return true;
	//	}

	//}



	//pCollider->SetIsCollision(true);
	//pOther->SetIsCollision(true);
	//pCollider->ResolveCollision(pOtherActor);
	//pOther->ResolveCollision(pActor);

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
