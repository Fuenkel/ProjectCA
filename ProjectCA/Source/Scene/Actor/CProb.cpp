#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Actor\CProp.h" 
#include "..\..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\..\Include\Core\Components\ImageRender.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"


CProp::CProp()
{
}

CProp::~CProp()
{
}

bool CProp::PostInit(const OBJECT_DATA& data, CScene* pScene)
{
	//기본 Actor의 속성 초기화
	CObject::PostInit(data, pScene);

	GetTransform().lock()->SetPivotRatio(0.5f, 1.f);

	//Collider 초기화
	std::shared_ptr<ColliderBox> pCollider = std::make_shared<ColliderBox>();
	if (!pCollider->PostInit(this))
		return false;
	
	if (!AddComponent(pCollider, pCollider->GetComponentTag()))
		return false;
	


	return true;
}

