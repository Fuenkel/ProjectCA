#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CWorld.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CollisionDetector.h"



CWorld::CWorld()
	:m_pCollisionDetector(nullptr)
{

}



CWorld::~CWorld()
{
	if (!m_actorList.empty())
		m_actorList.clear();

}

bool CWorld::Init()
{
	m_pCollisionDetector = std::make_unique<CollisionDetector>();

	//m_lastActorID = 0;

	return true;
}

//CWorld Class���� �����ϴ� weak_ptr List�� ����Ű�� �����Ͱ� �Ҹ����� Ȯ��.
void CWorld::Update(float fDeltaTime)
{
	for (auto it = m_actorList.begin(); it != m_actorList.end(); ) {
		if ((*it).expired()) {
			it = m_actorList.erase(it);
		}
		else {
			++it;
		}

	}
	

}
void CWorld::AddActor(std::shared_ptr<CActor> pActor)
{
	m_actorList.emplace_back(std::weak_ptr<CActor>(pActor));

}

//�ش� Actor�� weak_ptr�� ã�� ��� weak_ptr���� ��ȯ�ϰ�, ��ã�� ��� default�����ڰ��� ��ȯ
// -> lock()�޼ҵ� ���� nullptr ��ȯ
std::weak_ptr<CActor>  CWorld::GetActor(ActorID actorID)
{
	for (auto& it : m_actorList)
		if (it.lock()->GetActorID() == actorID)
			return it;

	return std::weak_ptr<CActor>();
}

bool CWorld::DeleteActor(ActorID actorID)
{
	std::weak_ptr<CActor> pActor = GetActor(actorID);
	if (pActor.lock() == nullptr)	//
		return false;
	
	for (auto it = m_actorList.begin(); it != m_actorList.end();) {
		if ((*it).lock() == pActor.lock()) {
			m_actorList.erase(it);
			return true;
		}
		else
			++it;
	}

	return false;
}

bool CWorld::DeleteActor(std::weak_ptr<CActor> pActor)
{
	for (auto it = m_actorList.begin(); it != m_actorList.end();) {
		if ((*it).lock() == pActor.lock()) {
			m_actorList.erase(it);
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

void CWorld::ResolveCollision()
{



}

void CWorld::SimulWorld()
{
}

