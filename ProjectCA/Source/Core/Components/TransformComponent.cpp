#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"
#include "..\..\..\Include\Scene\CCameraManager.h"
#include "..\..\..\Include\Scene\Actor\CCamera.h"


TransformComponent::TransformComponent()
	: m_fPivotWidthRatio(0.f), m_fPivotHeightRatio(0.f)
{
}

TransformComponent::~TransformComponent()
{
}

bool TransformComponent::PostInit(CActor * pOwner, const POSITION& position, const TSTRING & strTag)
{
	m_pOwner					= std::shared_ptr<CActor>(pOwner);
	m_Pivot						= m_LastPosition = m_SpawnPosition 
									= m_ScreenPosition = m_Position = position;
	
	m_strComponentTag		= strTag;

	return true;
}

void TransformComponent::Init()
{
	m_Position = m_SpawnPosition;
}

void TransformComponent::Update(double dDeltaTime)
{
	//AdjustScreenPosition();
}

void TransformComponent::LateUpdate(double dDeltaTime)
{
}

void TransformComponent::Move(float fx, float fy)
{
	//Backup Position
	m_LastPosition = m_Position;

	m_Position.x		+= fx;
	m_Position.y	-= fy;

	m_Pivot.x		= m_Position.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
	m_Pivot.y		= m_Position.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;

	//printf("LastPosition : (%f, %f), CurPosition : (%f, %f)\n", m_LastPosition.x, m_LastPosition.y, m_Position.x, m_Position.y);
}

void TransformComponent::SetPosition(const POSITION & position)
{
	//m_LastPosition = m_Position;

	m_Position = position;

	m_Pivot.x = m_Position.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
	m_Pivot.y = m_Position.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;
}

void TransformComponent::SetPosition(float fx, float fy)
{
	SetPosition(POSITION(fx, fy));
}

void TransformComponent::SetPositionX(float fx)
{
	//m_LastPosition		= m_Position;

	m_Position.x			= fx;

	m_Pivot.x			= m_Position.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
}

void TransformComponent::SetPositionY(float fy)
{
	//m_LastPosition		= m_Position;

	m_Position.y		= fy;

	m_Pivot.y			= m_Position.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;
}

void TransformComponent::SetSpawnPosition(const POSITION & position)
{
	m_SpawnPosition = position;
	AdjustScreenPosition();
}

void TransformComponent::SetSpawnPosition(float fx, float fy)
{
	SetSpawnPosition(POSITION(fx, fy));
}

void TransformComponent::SetPivotRatio(float fWidthRatio, float fHeightRatio)
{
	m_fPivotWidthRatio	= fWidthRatio;
	m_fPivotHeightRatio	= fHeightRatio;

	m_Pivot.x				= m_Position.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
	m_Pivot.y				= m_Position.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;
}

void TransformComponent::SetWidthPivotRatio(float fRatio)
{
	m_fPivotWidthRatio	 = fRatio;

	m_Pivot.x				 = m_Position.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
}

void TransformComponent::SetHeightPivotRatio(float fRatio)
{
	m_fPivotHeightRatio	= fRatio;

	m_Pivot.y				= m_Position.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;
}

void TransformComponent::SetScreenPosition(const POSITION & position)
{
	m_ScreenPosition = position;
}

float TransformComponent::GetPivotWidthRatio() const
{
	return m_fPivotWidthRatio;
}

float TransformComponent::GetPivotHeightRatio() const
{
	return m_fPivotHeightRatio;
}

POSITION TransformComponent::GetPosition() const
{
	return m_Position;
}

POSITION TransformComponent::GetSpawnPosition() const
{
	return m_SpawnPosition;
}

POSITION TransformComponent::GetPivot() const
{
	return m_Pivot;
}

POSITION TransformComponent::GetLastPosition() const 
{
	return m_LastPosition;
}

POSITION TransformComponent::GetScreenPosition() const
{
	return m_ScreenPosition;
}

POSITION TransformComponent::GetScreenPivot() const
{
	return m_ScreenPivot;
}

void TransformComponent::AdjustScreenPosition()
{
	POSITION cameraPosition = CCameraManager::GetInstance()->GetMainCamera().lock()->GetCameraPosition();

	m_ScreenPosition.x = m_Position.x - cameraPosition.x;
	m_ScreenPosition.y = m_Position.y + cameraPosition.y;

	m_ScreenPivot.x = m_ScreenPosition.x - m_pOwner->GetActorWidth() * m_fPivotWidthRatio;
	m_ScreenPivot.y = m_ScreenPosition.y - m_pOwner->GetActorHeight() * m_fPivotHeightRatio;
}


