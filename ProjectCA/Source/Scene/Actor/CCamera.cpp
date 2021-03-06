#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\CEntity.hpp"
#include "..\..\..\Include\Scene\Actor\CCamera.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Core\Components\TransformComponent.h"



CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

bool CCamera::PostInit(std::shared_ptr<CEntity> pOwner, UINT iWidth, UINT iHeight, CAMERA_ID id)
{
	m_bActive = true;
	m_fDestPosition = 0.f;
	m_fCameraCurSpeed = 0.f;
	m_fOwnerCurSpeed = 0.f;
	m_fOwnerCurJumpForce = 0.f;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iCameraID = id;
	m_CameraMode = CM_DEFAULT;
	
	if (pOwner)
	{
		m_pOwner = pOwner;
		auto pPhysics = pOwner->GetComponent<PhysicsComponent>();
		if (pPhysics.expired())
		{
			m_fCameraMaxSpeed = 0.f;
		}
		else
		{
			m_fCameraMaxSpeed = pPhysics.lock()->GetMaxSpeed()*2.f;
		}
		m_CameraPosition			= POSITION(m_pOwner.lock()->GetEntityPosition().x - m_iWidth / 2.f, 0.f);
		m_OwnerScreenPosition = m_pOwner.lock()->GetComponent<TransformComponent>().lock()->GetScreenPosition();
	}
	else
	{
		m_fCameraMaxSpeed		= 0.f;
		m_CameraPosition			= 0.f;
		m_OwnerScreenPosition = 0.f;
	}

	return true;
}

void CCamera::Init()
{
	if (!m_pOwner.expired())
	{
		m_CameraPosition.x = m_pOwner.lock()->GetEntityPosition().x - m_iWidth / 2.f;
		m_OwnerScreenPosition = m_pOwner.lock()->GetComponent<TransformComponent>().lock()->GetScreenPosition();
	}
	m_CameraPosition.y = 0.f;
}

void CCamera::Update(double dDeltaTime)
{
	if (!m_pOwner.expired())
	{
		m_OwnerScreenPosition = m_pOwner.lock()->GetComponent<TransformComponent>().lock()->GetScreenPosition();
	}
	AdjustCameraPosition(dDeltaTime);
}

std::weak_ptr<CEntity> CCamera::GetOwner()
{
	if(m_pOwner.expired())
		return std::weak_ptr<CEntity>();

	return m_pOwner;
}

void CCamera::AdjustCameraPosition(double dDeltaTime)
{
	if (!m_pOwner.expired())
	{
		auto pPhysics = m_pOwner.lock()->GetComponent<PhysicsComponent>();
		if (!pPhysics.expired())
		{
			m_fOwnerCurSpeed = pPhysics.lock()->GetCurSpeed();
			m_fOwnerCurJumpForce = pPhysics.lock()->GetCurJumpForce();
		}
	}

	switch (m_CameraMode)
	{
	case CM_DEFAULT:
		ScrollDefault(dDeltaTime);
		break;
	case CM_SCROLL_HOR:
		ScrollHorizon(dDeltaTime);
		break;
	case CM_SCROLL_HOR_VER:
		ScrollVertical(dDeltaTime);
		break;
	case CM_AUTO:
		ScrollAuto(dDeltaTime);
		break;
	}

}

void CCamera::SetActive(bool bActive)
{
	m_bActive = bActive;
}

void CCamera::SetCameraSize(UINT iWidth, UINT iHeight)
{
	m_iWidth	= iWidth;
	m_iHeight	= iHeight;

}

void CCamera::SetOwner(std::shared_ptr<CEntity> pOwner)
{
	m_pOwner = pOwner;
}

void CCamera::Move(float fx, float fy)
{
	m_CameraPosition.x += fx;
	m_CameraPosition.y -= fy;
}

void CCamera::SetCameraPosition(const POSITION & position)
{
	m_CameraPosition = position;

}

void CCamera::SetCameraPosition(float fx, float fy)
{
	m_CameraPosition.x = fx;
	m_CameraPosition.y = fy;
}

void CCamera::SetCameraPositionX(float fx)
{
	m_CameraPosition.x = fx;
}

void CCamera::SetCameraPositionY(float fy)
{
	m_CameraPosition.y = fy;
}

void CCamera::SetCameraMode(CameraMode mode)
{
	m_CameraMode = mode;
}

//Position Locking
void CCamera::ScrollDefault(double dDeltaTime)
{
	m_CameraPosition.x += (m_fOwnerCurSpeed * dDeltaTime);
	m_CameraPosition.y -= (m_fOwnerCurJumpForce * dDeltaTime);
}

//수직 카메라이동
void CCamera::ScrollHorizon(double dDeltaTime)
{
	float fUnit = m_iWidth * (1.f / 5.f);
	m_fCameraCurSpeed = 0.f;

	if (m_fDestPosition != 0.f)
	{
		if (m_fDestPosition == fUnit * 2.f)
		{
			if (m_OwnerScreenPosition.x >= fUnit * 1.89f)
			{
				m_CameraPosition.x += m_fCameraMaxSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fCameraMaxSpeed;
			}
			else
			{
				m_fDestPosition = 0.f;
			}

		}
		else if (m_fDestPosition == fUnit * 3.f)
		{
			if (m_OwnerScreenPosition.x <= fUnit * 3.11f)
			{
				m_CameraPosition.x -= m_fCameraMaxSpeed * dDeltaTime;
				m_fCameraCurSpeed = -1*m_fCameraMaxSpeed;
			}
			else
			{
				m_fDestPosition = 0.f;
			}

		}

	}
	else
	{
		if (m_fOwnerCurSpeed > 0.f)
		{
			if (m_OwnerScreenPosition.x > fUnit * 4.f)
			{
				m_fDestPosition = fUnit * 2.f;
			}
			else if (m_OwnerScreenPosition.x <= fUnit * 2.f && m_OwnerScreenPosition.x >= fUnit * 1.9f)
			{
				m_CameraPosition.x += m_fOwnerCurSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fOwnerCurSpeed;
			}

		}
		else if (m_fOwnerCurSpeed < 0.f)
		{
			if (m_OwnerScreenPosition.x < fUnit)
			{
				m_fDestPosition = fUnit * 3.f;
			}
			else if (m_OwnerScreenPosition.x >= fUnit * 3.f && m_OwnerScreenPosition.x <= fUnit * 3.1f)
			{
				m_CameraPosition.x += m_fOwnerCurSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fOwnerCurSpeed;
			}

		}
	}
	
}

//수평, 수직 카메라이동
void CCamera::ScrollVertical(double dDeltaTime)
{
	float fUnit = m_iWidth * (1.f / 5.f);
	m_fCameraCurSpeed = 0.f;

	if (m_fDestPosition != 0.f)
	{
		if (m_fDestPosition == fUnit * 2.f)
		{
			if (m_OwnerScreenPosition.x >= fUnit * 1.89f)
			{
				m_CameraPosition.x += m_fCameraMaxSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fCameraMaxSpeed;
			}
			else
			{
				m_fDestPosition = 0.f;
			}

		}
		else if (m_fDestPosition == fUnit * 3.f)
		{
			if (m_OwnerScreenPosition.x <= fUnit * 3.11f)
			{
				m_CameraPosition.x -= m_fCameraMaxSpeed * dDeltaTime;
				m_fCameraCurSpeed = -1 * m_fCameraMaxSpeed;
			}
			else
			{
				m_fDestPosition = 0.f;
			}

		}

	}
	else
	{
		if (m_fOwnerCurSpeed > 0.f)
		{
			if (m_OwnerScreenPosition.x > fUnit * 4.f)
			{
				m_fDestPosition = fUnit * 2.f;
			}
			else if (m_OwnerScreenPosition.x <= fUnit * 2.f && m_OwnerScreenPosition.x >= fUnit * 1.9f)
			{
				m_CameraPosition.x += m_fOwnerCurSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fOwnerCurSpeed;
			}

		}
		else if (m_fOwnerCurSpeed < 0.f)
		{
			if (m_OwnerScreenPosition.x < fUnit)
			{
				m_fDestPosition = fUnit * 3.f;
			}
			else if (m_OwnerScreenPosition.x >= fUnit * 3.f && m_OwnerScreenPosition.x <= fUnit * 3.1f)
			{
				m_CameraPosition.x += m_fOwnerCurSpeed * dDeltaTime;
				m_fCameraCurSpeed = m_fOwnerCurSpeed;
			}

		}
	}

	auto pPhysics = m_pOwner.lock()->GetComponent<PhysicsComponent>().lock();
	POSITION position = m_pOwner.lock()->GetTransform().lock()->GetScreenPosition();
	if (pPhysics->IsGrounded())
	{
		if (position.y < m_iHeight * 0.49f)
		{
			m_CameraPosition.y += pPhysics->GetJumpForce() * dDeltaTime;
		}
		else if (position.y > m_iHeight * 0.51f)
		{
			m_CameraPosition.y -= pPhysics->GetJumpForce() * dDeltaTime;
		}
	}
}

void CCamera::ScrollAuto(double dDeltaTime)
{
}

bool CCamera::IsActive() const
{
	return m_bActive;
}

UINT CCamera::GetCameraWidth() const
{
	return m_iWidth;
}

UINT CCamera::GetCameraHeight() const
{
	return m_iHeight;
}

float CCamera::GetCameraCurSpeed() const
{
	return m_fCameraCurSpeed;
}

Types::CameraID CCamera::GetCameraID() const
{
	return m_iCameraID;
}

const POSITION & CCamera::GetCameraPosition() const
{
	return m_CameraPosition;
}
