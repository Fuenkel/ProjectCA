#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CWorld.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CCollisionManager.h"



CWorld::CWorld()
{

}



CWorld::~CWorld()
{
	if (!m_actorList.empty())
		m_actorList.clear();

}

bool CWorld::PostInit()
{
	return false;
}

bool CWorld::Init()
{
	
	//m_lastActorID = 0;

	return true;
}

//CWorld Class���� �����ϴ� weak_ptr List�� ����Ű�� �����Ͱ� �Ҹ����� Ȯ��.
void CWorld::Update(double dDeltaTime)
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

void CWorld::Render(const HDC & hDC)
{
}


void CWorld::AddActor(std::shared_ptr<CActor> pActor)
{
	m_actorList.emplace_back(std::weak_ptr<CActor>(pActor));

}

//�ش� Actor�� weak_ptr�� ã�� ��� weak_ptr���� ��ȯ�ϰ�, ��ã�� ��� default�����ڰ��� ��ȯ
// -> lock()�޼ҵ� ���� nullptr ��ȯ
std::weak_ptr<CActor>  CWorld::GetActor(Types::ActorID actorID)
{
	for (auto& it : m_actorList)
		if (it.lock()->GetActorID() == actorID)
			return it;

	return std::weak_ptr<CActor>();
}

bool CWorld::DeleteActor(Types::ActorID actorID)
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

