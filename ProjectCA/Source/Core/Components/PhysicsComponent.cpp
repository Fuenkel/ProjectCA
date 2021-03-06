#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\include\Core\Components\TransformComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"
//#include "..\..\..\Include\Core\Components\Collider.h"



PhysicsComponent::PhysicsComponent()
	:m_bGrounded(false), m_bAccel(false), m_bStatic(false),
	m_fSpeed(0.f), m_fMaxSpeed(0.f), m_fXSpeed(0.f), m_fMass(0.f),
	m_fGravity(0.f), m_fJumpForce(0.f), m_fYSpeed(0.f), m_dTimeElapsed(0.f)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

bool PhysicsComponent::PostInit(CEntity* pOwner, float fSpeed, float fMaxSpeed, 
	float fGravity, float fJumpForce, const Types::tstring& strTag)
{

	m_pOwner = pOwner;

	if (fGravity < 0.f)
		return false;

	m_bGrounded				= false;
	m_bAccel					= false;
	m_bStatic					= false;
	m_fMass						= 1.f;
	m_fGravity					= fGravity;
	m_fXSpeed					= 0.f;
	m_fSpeed					= fSpeed;
	m_fMaxSpeed				= fMaxSpeed;
	m_fYSpeed					= 0.f;
	m_fJumpForce				= fJumpForce;
	m_strComponentTag		= strTag;

	m_bActive					= true;

	return true;
}

void PhysicsComponent::Init()
{
	m_fXSpeed			= 0.f;
	m_fYSpeed			= 0.f;
	m_dTimeElapsed	= 0.f;
	m_bActive			= true;
	m_bStatic			= false;
}

void PhysicsComponent::Update(double dDeltaTime)
{
	if (m_bActive)
	{
		m_dTimeElapsed += dDeltaTime;

		if (!m_bStatic)
		{
			Gravity(dDeltaTime);
		}

		if (m_bGrounded)
		{
			m_bGrounded = false;
		}

	}

}
void PhysicsComponent::LateUpdate()
{

}

void PhysicsComponent::SetCurSpeed(float fSpeed)
{
	m_fXSpeed = fSpeed;
}

void PhysicsComponent::SetSpeed(float fSpeed)
{
	if (fSpeed >= 0) 
		m_fSpeed = fSpeed;
}

void PhysicsComponent::SetMass(float fMass)
{
	m_fMass = fMass;
}

void PhysicsComponent::SetGravity(float fGravity)
{
	if (fGravity >= 0.f)
		m_fGravity = fGravity;
}

void PhysicsComponent::SetCurJumpForce(float fJumpForce)
{
	m_fYSpeed = fJumpForce;
}

void PhysicsComponent::SetJumpForce(float fJumpForce)
{
	if (fJumpForce >= 0.f)
		m_fJumpForce = fJumpForce;
}

void PhysicsComponent::SetGrounded(bool bGrounded)
{
	m_bGrounded = bGrounded;
}

void PhysicsComponent::SetAcceled(bool bAccel)
{
	m_bAccel = bAccel;
}

void PhysicsComponent::SetStatic(bool bStatic)
{
	if (bStatic)
	{
		m_fYSpeed = 0.f;
	}
	m_bStatic = bStatic;
}

void PhysicsComponent::AddForceX(float fForce)
{
	m_fXSpeed += fForce;
}

void PhysicsComponent::AddForceY(float fForce)
{
	m_fYSpeed -= fForce;
}

bool PhysicsComponent::IsGrounded() const
{
	return m_bGrounded;
}

bool PhysicsComponent::IsAcceled() const
{
	return m_bAccel;
}

bool PhysicsComponent::IsStatic() const
{
	return m_bStatic;
}

float PhysicsComponent::GetCurSpeed() const
{
	return m_bActive ? m_fXSpeed : 0.f;
}

float PhysicsComponent::GetMaxSpeed() const
{
	return m_bActive ? m_fMaxSpeed : 0.f;
}

float PhysicsComponent::GetSpeed() const
{
	return m_bActive? m_fSpeed : 0.f;
}

float PhysicsComponent::GetMass() const
{
	return m_fMass;
}

float PhysicsComponent::GetCurJumpForce() const
{
	return m_bActive ? m_fYSpeed : 0.f;
}

float PhysicsComponent::GetGravity() const
{
	return m_bActive ? m_fGravity : 0.f;
}

float PhysicsComponent::GetJumpForce() const
{	
	return m_bActive ? m_fJumpForce : 0.f;
}

void PhysicsComponent::Gravity(double dDeltaTime)
{
	if (m_bGrounded)
	{
		m_fYSpeed = 0.f;
	}
	else
	{
		if (m_fYSpeed > -1 * m_fMaxYSpeed)
		{
			m_fYSpeed -= m_fGravity * dDeltaTime;
		}

	}

}
