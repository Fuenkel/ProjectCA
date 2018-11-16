#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CWorld.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CCollisionManager.h"
#include "..\..\Include\Scene\Actor\CObjectManager.h"
#include "..\..\Include\Core\CResourceManager.h"
#include "..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\Include\Core\Components\PlayerInputComponent.h"
#include "..\..\Include\Core\Components\AIComponent.h"
#include "..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\Include\Core\Components\ColliderBox.h"
#include "..\..\Include\Core\Components\RenderComponent.h"



CWorld::CWorld()
{

}



CWorld::~CWorld()
{
	if (!m_ActorList.empty())
		m_ActorList.clear();

}

bool CWorld::PostInit(std::shared_ptr<CActor> pPlayer)
{
	m_pPlayer = pPlayer;
	m_fWorldGravity = 1000.f;
	
	m_pObjectManager = CObjectManager::GetInstance();

	return BuildWorld();
}

bool CWorld::Init()
{
	
	//m_lastActorID = 0;

	return true;
}

//CWorld Class���� �����ϴ� weak_ptr List�� ����Ű�� �����Ͱ� �Ҹ����� Ȯ��.
void CWorld::Update(double dDeltaTime)
{
	for (auto it = m_ActorList.begin(); it != m_ActorList.end(); ) {
		if ((*it).expired()) {
			it = m_ActorList.erase(it);
		}
		else {
			(*it).lock()->Update(dDeltaTime);
			++it;
		}

	}


}

void CWorld::Render(const HDC & hDC)
{
	for (auto& it : m_ActorList)
	{
		it.lock()->Render(hDC);
	}

}


void CWorld::AddActor(std::shared_ptr<CActor> pActor)
{
	m_ActorList.emplace_back(pActor);

}

//�ش� Actor�� weak_ptr�� ã�� ��� weak_ptr���� ��ȯ�ϰ�, ��ã�� ��� default�����ڰ��� ��ȯ
// -> lock()�޼ҵ� ���� nullptr ��ȯ
std::weak_ptr<CActor>  CWorld::GetActor(Types::ActorID actorID)
{
	for (auto& it : m_ActorList)
		if (it.lock()->GetActorID() == actorID)
			return it;

	return std::weak_ptr<CActor>();
}

bool CWorld::DeleteActor(Types::ActorID actorID)
{
	std::weak_ptr<CActor> pActor = GetActor(actorID);
	if (pActor.lock() == nullptr)	//
		return false;
	
	for (auto it = m_ActorList.begin(); it != m_ActorList.end();) {
		if ((*it).lock() == pActor.lock()) {
			m_ActorList.erase(it);
			return true;
		}
		else
			++it;
	}

	return false;
}

bool CWorld::DeleteActor(std::weak_ptr<CActor> pActor)
{
	for (auto it = m_ActorList.begin(); it != m_ActorList.end();) {
		if ((*it).lock() == pActor.lock()) {
			m_ActorList.erase(it);
			return true;
		}
		else
			++it;
	}
	
	return false;
}

bool CWorld::CollisionUpdate()
{



	return true;
}

bool CWorld::SetWolrdGravity(float fGravity)
{
	if (fGravity < 0.f)
		return false;

	m_fWorldGravity = fGravity;
	
	return true;
}

float CWorld::GetWorldGravity()
{
	return m_fWorldGravity;
}

bool CWorld::BuildWorld()
{


	return true;
}

void CWorld::ResolveCollision()
{



}

void CWorld::SimulWorld()
{
}

bool CWorld::CheckGrounded()
{
	return false;
}

