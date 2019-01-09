#include "..\..\Include\Scene\CScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Scene\CObject.h"
#include "..\..\Include\Scene\CCameraManager.h"
#include "..\..\Include\Scene\Actor\CObjectManager.hpp"


CScene::CScene(Types::SceneType type):
	m_SceneType(type)
{
}

CScene::~CScene()
{
	if(!m_LayerList.empty())
		for (auto it = m_LayerList.begin(); it != m_LayerList.end(); ++it) {
			SAFE_DELETE((*it))
		}

	m_LayerList.clear();
	m_EntityPtrList.clear();
	CObjectManager::GetInstance()->Clear();
}


void CScene::StartScene()
{
	CCameraManager::GetInstance()->ChangeMainCamera(m_pMainCameraPtr.lock());
}

bool CScene::Init()
{
	//Default ���̾� ����.
	//��� Entity���� ������ �⺻������ DefaultLayer�� ���Ե�.
	if (!CreateLayer(TEXT("Default"), 0))
	{
		return false;
	}

	return true;
}

void CScene::Update(double dDeltaTime)
{
	if (!m_LayerList.empty())
	{
		for (const auto& layer : m_LayerList)
		{
			layer->Update(dDeltaTime);
		}
	}
}

void CScene::Render(const HDC& hDC)
{
	if (!m_LayerList.empty())
	{
		for (const auto& layer : m_LayerList)
		{
			layer->Render(hDC);
		}
	}
}

//CLayer Ŭ������ friend �޼ҵ�.
//CreateLayer�޼ҵ带 ���ؼ��� Layer ������ �����ϰԲ� �����.
bool CScene::CreateLayer(const TSTRING & strTag, int order)
{
	if (FindLayer(strTag))
		return false;

	CLayer* pLayer = new CLayer;
	pLayer->Init(strTag, order);

	m_LayerList.emplace_back(pLayer);
	SortLayer();

	return true;
}

bool CScene::DeleteLayer(const TSTRING & strTag)
{
	for (auto it = m_LayerList.cbegin(); it != m_LayerList.cend(); ++it)
	{
		if((*it)->GetLayerTag() == strTag)
		{
			m_LayerList.erase(it);
			return true;
		}
	}
	
	return false;
}

CLayer * CScene::FindLayer(const TSTRING & strTag)
{
	for (const auto& layer : m_LayerList)
	{
		if (!layer->GetLayerTag().compare(strTag))
		{
			return layer;
		}
	}

	return nullptr;
}

//Entity�� �����Ǿ� Scene�� �־��� �� Default Layer�� ��.
void CScene::AddEntityToScene(CEntity * pEntity)
{
	m_EntityPtrList.emplace_back(pEntity);
	FindLayer(TEXT("Default"))->AddActor(FindEntityFromScene(pEntity->GetEntityID()).lock());
}

//Entity�� �����Ǿ� Scene�� �־��� �� Default Layer�� ��.
void CScene::AddEntityToScene(std::shared_ptr<CEntity> pEntity)
{
	m_EntityPtrList.push_back(pEntity);
	FindLayer(TEXT("Default"))->AddActor(pEntity);
}

WeakEntityPtr CScene::FindEntityFromScene(CEntity * pEntity)
{
	for (const auto& obj : m_EntityPtrList)
	{
		if (obj.get() == pEntity)
		{
			return obj;
		}
	}

	return WeakEntityPtr();
}

WeakEntityPtr CScene::FindEntityFromScene(const TSTRING & strEntityName)
{
	for (const auto& obj : m_EntityPtrList)
	{
		if (obj->GetEntityName() == strEntityName)
		{
			return obj;
		}
	}

	return WeakEntityPtr();
}

WeakEntityPtr CScene::FindInactiveEntityFromScene(CEntity * pEntity)
{
	for (const auto& obj : m_EntityPtrList)
	{
		if (obj.get() == pEntity)
		{
			return obj;
		}
	}

	return WeakEntityPtr();
}

WeakEntityPtr CScene::FindInactiveEntityFromScene(const TSTRING & strEntityName)
{
	for (const auto& obj : m_EntityPtrList)
	{
		if (obj->GetEntityName() == strEntityName)
		{
			return obj;
		}
	}
	

	return WeakEntityPtr();
}

void CScene::SetSceneMainCamera(std::shared_ptr<CCamera> pCamera)
{
	m_pMainCameraPtr = pCamera;
}

WeakEntityPtr CScene::FindEntityFromScene(UINT entityID)
{
	for (const auto& obj : m_EntityPtrList)
	{
		if (obj->GetEntityID() == entityID)
		{
			return obj;
		}

	}

	return WeakEntityPtr();
}

bool CScene::DeleteEntityFromScene(CEntity * pEntity)
{
	for (auto it = m_EntityPtrList.cbegin(); it != m_EntityPtrList.cend(); ++it)
	{
		if (it->get() == pEntity)
		{
			m_EntityPtrList.erase(it);
			return true;
		}
	}

	return false;
}

bool CScene::DeleteEntityFromScene(UINT entityID)
{
	for (auto it = m_EntityPtrList.cbegin(); it != m_EntityPtrList.cend(); ++it)
	{
		if ((*it)->GetEntityID() == entityID)
		{
			m_EntityPtrList.erase(it);
			return true;
		}
	}

	return false;
}

//�ش� Scene�� ������ �� ȣ���ϴ� �޼ҵ�.
void CScene::ResetScene()
{
	for (const auto& actor : m_EntityPtrList) {
		actor->Init();
	}

	CCameraManager::GetInstance()->ResetCameraList();
}

//LayerOrder�� Ŭ���� ���� ��µ�.
bool CScene::CompareLayer(CLayer * first, CLayer * second)
{
	return (first->GetLayerOrder() > second->GetLayerOrder()); 
}

void CScene::CheckGarbage()
{
	for (auto it = m_EntityPtrList.cbegin(); it != m_EntityPtrList.cend(); )
	{
		if ((*it) == nullptr)
		{
			it = m_EntityPtrList.erase(it);
		}
		else
		{
			++it;
		}
	}

}
