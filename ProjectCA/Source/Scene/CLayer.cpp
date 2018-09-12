#include "..\..\Include\Scene\CLayer.h"
//#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\CWorld.h"
//#include "..\..\Include\Scene\Object\CObject.h"


//CLayer::CLayer(int order, const Types::tstring & tag):
//	m_iOrder(order), m_iObjectNumber(0), m_strLayerTag(tag)
//{
//}
CLayer::CLayer() 
{

}

CLayer::~CLayer()
{
	//if(!m_ObjectList.empty())
	//	for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
	//		SAFE_DELETE((*m_it))
	//	}

	//m_ObjectList.clear();

	if (!m_actorList.empty())
		for (auto& it : m_actorList)
			SAFE_DELETE(it)

			m_actorList.clear();
}

//	TODO(08.06) : 
//		ObjectType���� Init���� �޸��������
//	->Init �޼ҵ��� ������ ���� Actor���� �ʱ�ȭ���� ����ϴ� ���� �ƴ� 
//		Layer�� �Ӽ� �� ��ü�� �ʱ�ȭ�ϵ��� ������.(08.14)
bool CLayer::Init(const Types::tstring& strTag, UINT iOrder)
{
	//if (!m_ObjectList.empty())
		//for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
			//switch ((*m_it)->GetObjectType()) {
			//case Types::OT_PLAYER:

			//	break;
			//case Types::OT_PROBS:
			//	
			//	break;
			//case Types::OT_ENEMY:

			//	break;
			//}

		//}
	m_strLayerTag = strTag;
	m_iOrder = iOrder;
	m_iActorNumber = 0;

	return true;
}

//Update ���� : Update -> ResolveCollision -> LateUpdate
//Layer Class�� ������ Rendering���θ� ��������� �� Update������ expired�� weak_ptr�� üũ�ϱ��
void CLayer::Update(float fDeltaTime)
{
	//if (!m_ObjectList.empty())
	//	for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
	//		(*m_it)->Update(fDeltaTime);
	//	}
	
	//if (!m_actorList.empty()) {
	//	for (auto& it : m_actorList)
	//		it->Update(fDeltaTime);

	//	for (auto& it : m_actorList)
	//		it->LateUpdate(fDeltaTime);
	//}

	if (!m_actorList.empty())
		for (auto& it : m_actorList)
			if (it.expired())
				m_actorList.remove(it);	//���߿� erase()�� ��ü�� �� �ְԲ� ��������.

}

void CLayer::Render(const HDC& hDC)
{
	//if (!m_ObjectList.empty())
	//	for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
	//		(*m_it)->Render(hDC);
	//	}

	if (!m_actorList.empty())
		for (auto& it : m_actorList)
			it.lock()->Render(hDC);
}

void CLayer::LateUpdate(float fDeltaTime)
{
	/*for (auto& object : m_ObjectList) {
		object->LateUpdate(fDeltaTime);
	}
*/
}

void CLayer::AddActor(std::shared_ptr<CActor> pActor)
{
	m_actorList.insert(pActor);

}

bool CLayer::DeleteActor(ActorID actorID)
{
	std::weak_ptr<CActor> pActor = FindActor(actorID);
	if (FindActor(actorID).lock() == nullptr)
		return false;

	m_actorList.remove(pActor);

	return true;
}

bool CLayer::DeleteActor(std::shared_ptr<CActor> pActor)
{
	if (FindActor(pActor).lock() == nullptr)
		return false;
	
	m_actorList.remove(pActor);

	return true;
}



std::weak_ptr<CActor> CLayer::FindActor(ActorID actorID)
{
	for (auto& it : m_actorList) {
		if (it.lock()->GetActorID() == actorID)
			return it;
	}

	return std::weak_ptr<CActor>();	//return nullptr
}

std::weak_ptr<CActor> CLayer::FindActor(const std::weak_ptr<CActor>& pActor pActor)
{
	for (auto& it : m_actorList) {
		if (it.lock() == pActor.lock())
			return it;
	}

	return std::weak_ptr<CActor>();	//return nullptr
}

//void CLayer::AddObjectToLayer(CObject * object)
//{
//	m_ObjectList.push_back(object);
//	++m_iObjectNumber;
//}
//
//bool CLayer::DeleteObjectFromLayer(CObject * object)
//{
//	if( !m_ObjectList.empty() )
//		for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
//			if ((*m_it) == object) {
//				SAFE_DELETE((*m_it))
//				m_ObjectList.erase(m_it);
//				--m_iObjectNumber;
//				return true;
//			}
//		}
//
//	return false;
//}
