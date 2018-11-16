#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CObject.h"
#include "..\..\Include\Core\Components\ComponentBase.h"
#include "..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\Include\Scene\CCameraManager.h"
#include "..\..\Include\Scene\CLayer.h"


CObject::CObject()
{
}

CObject::~CObject()
{
	m_ComponentTable.clear();
}

bool CObject::PostInit(const OBJECT_DATA & objectData, CScene* pScene)
{
	//Object �Ӽ� �ʱ�ȭ �� Transform ������Ʈ �߰�
	//Pivot ratio�� �ܺο��� ���� �������� ��.
	m_bActive				= true;
	m_iObjectWidth		= objectData.m_iObjectWidth;
	m_iObjectHeight		= objectData.m_iObjectHeight;
	m_strObjectName		= objectData.m_strObjectName;
	m_strLayerTag			= TEXT("default");
	m_pOwnerScene		= pScene;

	auto pTransform = std::make_shared<TransformComponent>();
	if (!pTransform->PostInit(this, objectData.m_ObjectPoint))
		return false;

	if (!AddComponent(pTransform, pTransform->GetComponentTag()))
		return false;

	return true;
}

void CObject::Init()
{
	for (const auto& component : m_ComponentTable)
	{
		component.second->Init();
	}
	
}


void CObject::Update(double dDeltaTime)
{
	for (const auto& component : m_ComponentTable)
	{
		component.second->Update(dDeltaTime);
	}
}

void CObject::LateUpdate()
{
	if (CCameraManager::GetInstance()->GetMainCamera().expired())
		return;
	GetTransform().lock()->AdjustScreenPosition();
}


std::weak_ptr<ComponentBase> CObject::GetComponent(const TSTRING& strTag)
{
	auto it = m_ComponentTable.find(strTag);

	if (it == m_ComponentTable.end())
		return std::weak_ptr<ComponentBase>();

	return it->second;
}

bool CObject::AddComponent(std::shared_ptr<ComponentBase> pComponent, const TSTRING& strTag)
{
	return m_ComponentTable.insert(std::make_pair(strTag, pComponent)).second;
}

bool CObject::DeleteComponent(const TSTRING & strTag)
{
	ComponentTable::iterator it = m_ComponentTable.find(strTag);

	if (it == m_ComponentTable.end())
		return false;

	m_ComponentTable.erase(strTag);

	return true;
}

CObject * CObject::Clone()
{
	CObject* pClone(this);

	return pClone;
}

void CObject::SetActive(bool bActive)
{
	m_bActive = bActive;
}

void CObject::SetObjectSize(UINT iWidth, UINT iHeight)
{
	m_iObjectWidth = iWidth;
	m_iObjectHeight = iHeight;
}

void CObject::SetObjectWidth(UINT iWidth)
{
	m_iObjectWidth = iWidth;
}

void CObject::SetObjectHeight(UINT iHeight)
{
	m_iObjectHeight = iHeight;
}

void CObject::SetObjectPosition(POSITION position)
{
	GetComponent<TransformComponent>().lock()->SetPosition(position);
}

void CObject::SetObjectPosition(float fx, float fy)
{
	GetComponent<TransformComponent>().lock()->SetPosition(fx, fy);
}

void CObject::SetObjectName(const TSTRING & strName)
{
	m_strObjectName = strName;
}

void CObject::SetOwnerLayer(CLayer * pLayer)
{
	m_pOwnerLayer = pLayer;
	if (pLayer)
	{
		m_strLayerTag = pLayer->GetLayerTag();
	}
	else
	{
		m_strLayerTag = TEXT("Default");
	}
}

void CObject::SetOwnerScene(CScene * pScene)
{
	m_pOwnerScene = pScene;
}

bool CObject::IsActive()
{
	return m_bActive;
}

UINT CObject::GetObjectWidth() const
{
	return m_iObjectWidth;
}

UINT CObject::GetObjectHeight() const
{
	return m_iObjectHeight;
}

POSITION CObject::GetObjectPosition()
{
	return GetTransform().lock()->GetPosition();
}

CLayer * const CObject::GetOwnerLayer() const
{
	return m_pOwnerLayer;
}

CScene * const CObject::GetOwnerScene() const
{
	return m_pOwnerScene;
}

const TSTRING & CObject::GetObjectName()
{
	return m_strObjectName;
}

std::weak_ptr<TransformComponent> CObject::GetTransform()
{
	return GetComponent<TransformComponent>();
}