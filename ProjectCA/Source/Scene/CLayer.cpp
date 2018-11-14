#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Scene\CObject.h"
#include "..\..\Include\Scene\Actor\CActor.h"
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

	//if (!m_ObjectList.empty())
	//	for (auto& it : m_ObjectList)
	//		SAFE_DELETE(it)

	Destroy();
	m_ObjectList.clear();

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
void CLayer::Update(double fDeltaTime)
{
	//if (!m_ObjectList.empty())
	//	for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
	//		(*m_it)->Update(fDeltaTime);
	//	}
	
	//if (!m_ObjectList.empty()) {
	//	for (auto& it : m_ObjectList)
	//		it->Update(fDeltaTime);

	//	for (auto& it : m_ObjectList)
	//		it->LateUpdate(fDeltaTime);
	//}

	if (!m_ObjectList.empty())
		for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it) {
			if ((*it).expired()) {
				m_ObjectList.erase(it);
				break;
			}
		}
}

void CLayer::Render(const HDC& hDC)
{
	//if (!m_ObjectList.empty())
	//	for (m_it = m_ObjectList.begin(); m_it != m_ObjectList.end(); ++m_it) {
	//		(*m_it)->Render(hDC);
	//	}

	if (!m_ObjectList.empty())
	{
		for (auto& it : m_ObjectList)
		{
			if (it.lock()->IsActive())
			{
				it.lock()->Render(hDC);
			}
		}
	}
}

void CLayer::Destroy()
{
	for(auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
	{
		if (!it->expired())
		{
			it->lock()->SetOwnerLayer(nullptr);
		}
			
	}
}

void CLayer::AddActor(std::shared_ptr<CObject> pObject)
{

	m_ObjectList.emplace_back(pObject);

}

//bool CLayer::DeleteActor(Types::ActorID actorID)
//{
//	std::weak_ptr<CActor> pActor = FindObject(actorID);
//	if (FindObject(actorID).lock() == nullptr)
//		return false;
//
//	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ) {
//		if ((*it).lock() == pActor.lock()) {
//			m_ObjectList.erase(it);
//			break;
//		}
//		else
//			++it;
//	}
//
//	return true;
//}

bool CLayer::DeleteActor(std::shared_ptr<CObject>& pObject)
{
	if (FindObject(pObject).lock() == nullptr)
		return false;

	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ) {
		if (it->lock() == pObject) {
			m_ObjectList.erase(it);
			break;
		}
		else
			++it;
	}


	//auto func = [&](std::shared_ptr<CActor> strongPtr)->bool {
	//	if (ptr == strongPtr)
	//		return true;
	//	return false;
	//};
	//
	//m_ObjectList.remove_if(func);

	return true;
}


//
//std::weak_ptr<CObject> CLayer::FindObject(Types::ActorID actorID)
//{
//	for (const auto& it : m_ObjectList) {
//		if (it.lock()->GetActorID() == actorID)
//			return it;
//	}
//
//	return std::weak_ptr<CActor>();	//return nullptr
//}

std::weak_ptr<CObject> CLayer::FindObject(const std::shared_ptr<CObject>& pObject)
{
	for (const auto& it : m_ObjectList) {
		if (it.lock() == pObject)
			return it;
	}

	return std::weak_ptr<CActor>();	//return nullptr
}

const std::list<std::weak_ptr<CObject>>& CLayer::GetActorList() const
{
	return m_ObjectList;
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
