#include "..\..\Include\Scene\CScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Scene\CObject.h"


CScene::CScene(Types::SceneType type):
	m_SceneType(type)
{

}

CScene::~CScene()
{
	if(!m_LayerList.empty())
		for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
			SAFE_DELETE((*m_it))
		}

	m_LayerList.clear();

	//m_ObjectPtrList.clear();
}

bool CScene::Init()
{
	//if (!m_LayerList.empty())
	//	for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
	//		(*m_it)->Init();

	//	}

	return true;
}

void CScene::Update(double deltaTime)
{
	if (!m_LayerList.empty())
		for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
			(*m_it)->Update(deltaTime);

		}

}

void CScene::Render(const HDC& hDC)
{
	if (!m_LayerList.empty())
		for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
			(*m_it)->Render(hDC);
			
		}
}

//CLayer Ŭ������ friend �޼ҵ�.
//CreateLayer�޼ҵ带 ���ؼ��� Layer ������ �����ϰԲ� �����.
bool CScene::CreateLayer(const Types::tstring & tag, int order)
{
	if (FindLayer(tag))
		return false;

	CLayer* pLayer = new CLayer;
	pLayer->Init(tag, order);

	m_LayerList.emplace_back(pLayer);
	SortLayer();

	return true;
}

bool CScene::DeleteLayer(const Types::tstring & tag)
{
	if (!FindLayer(tag))
		return false;

	SAFE_DELETE((*m_it));
	m_LayerList.erase(m_it);

	return true;
}

CLayer * CScene::FindLayer(const Types::tstring & tag)
{
	for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
		if (!(*m_it)->GetLayerTag().compare( tag))
			return (*m_it);
	}

	return nullptr;
}

//�ش� Scene�� ������ �� ȣ���ϴ� �޼ҵ�.

void CScene::ResetScene()
{
	////ResetŰ �˻�
	//if (KEY_DOWN(VK_BACK)) {

	//	Init();
	//}

	for (const auto& actor : m_ObjectPtrList) {
		actor->Init();
	}

}

//LayerOrder�� Ŭ���� ���� ��µ�.
bool CScene::CompareLayer(CLayer * first, CLayer * second)
{
	return (first->GetLayerOrder() > second->GetLayerOrder()); 
}
