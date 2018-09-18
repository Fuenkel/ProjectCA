#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"
//#include "..\..\..\Include\Core\Components\Collider.h"



PhysicsComponent::PhysicsComponent() 
	//,m_fSpeed(200.f), m_fGravity(1300.f), m_fJumpForce(-350.f)
{
	
}

PhysicsComponent::~PhysicsComponent()
{
	//m_pOwner.reset();
}

bool PhysicsComponent::Init(std::shared_ptr<CActor> pOwner, float fSpeed, float fGravity, 
	float fJumpForce, const Types::tstring& strTag)
{
	m_pOwner = pOwner;
	m_lastActorPoint = m_pOwner->GetActorPoint();

	if (fSpeed < 0.f || fGravity < 0.f)
		return false;

	m_fSpeed = fSpeed;
	m_fGravity = fGravity;
	m_fJumpForce = fJumpForce;
	//m_pOwner = owner;

	m_strComponentTag = strTag;

	return true;
}

void PhysicsComponent::Update(float ffDeltaTime)
{

	m_lastActorPoint = m_pOwner->GetActorPoint();
	Move(ffDeltaTime);
	//Gravity(fDeltaTime);

}

void PhysicsComponent::RestoreActorPoint()
{
	m_pOwner->SetActorPoint(m_lastActorPoint.x, m_lastActorPoint.y);

}

//NOTE(07.30) : ���� �浹�ν��� �� �ǰ�������, �׿� ���� ������ ����� �ȵǴ� ��Ȳ. ��ġ��
void PhysicsComponent::Move(float fDeltaTime)
{
	switch (m_pOwner->GetActorDirection()) {
	case Types::DIR_LEFT:
		//MessageBox(NULL, TEXT("LEFT"), TEXT("Info"), MB_ICONINFORMATION);
		if (m_pOwner->GetActorPoint().x > 0)
			m_pOwner->SetActorPoint(m_pOwner->GetActorPoint().x - m_fSpeed * fDeltaTime, m_pOwner->GetActorPoint().y);
		break;
	case Types::DIR_RIGHT:
		//MessageBox(NULL, TEXT("RIGHT"), TEXT("Info"), MB_ICONINFORMATION);
		if (m_pOwner->GetActorPoint().x < MAX_WIDTH)
			m_pOwner->SetActorPoint(m_pOwner->GetActorPoint().x + m_fSpeed * fDeltaTime, m_pOwner->GetActorPoint().y);
		break;
	case Types::DIR_UP:
		if (m_pOwner->GetActorPoint().y > 0)
			m_pOwner->SetActorPoint(m_pOwner->GetActorPoint().x, m_pOwner->GetActorPoint().y - m_fSpeed * fDeltaTime);
		break;
	case Types::DIR_DOWN:
		if (m_pOwner->GetActorPoint().y < MAX_HEIGHT)
			m_pOwner->SetActorPoint(m_pOwner->GetActorPoint().x, m_pOwner->GetActorPoint().y + m_fSpeed * fDeltaTime);
		break;
		//case Types::DIR_IDLE:

		//	break;
	}
	

}


void PhysicsComponent::Gravity(float fDeltaTime)
{
	//�������� ��� ����ũ���� �� ��ŭ �ش� Object�� ���� ���Ѵ�.
	//if (m_pOwner->GetObjectState() == Types::OS_JUMP){
		//m_pOwner->SetObjectPointY(0.5f * m_fGravity *fDeltaTime * fDeltaTime
	m_pOwner->SetActorPoint(m_pOwner->GetActorPoint().x, m_pOwner->GetActorPoint().y + m_fJumpForce*fDeltaTime);

	if(m_fJumpForce < 500.f)
		m_fJumpForce += m_fGravity * fDeltaTime*0.75;


	//		
	//}
	//else {	
	//if (m_pOwner->GetObjectPoint().y > 400) {
	//	m_pOwner->SetObjectPointY(400.f);
	//	m_fJumpForce = -350.f;
	//}

	
	////���⼭ ��� prob�� �浹�� ���� ������Ʈ�� �ؾ��ϴµ�, �̷��� �ѹ��ۿ� ���Ѵ�.
	//Collider* collider = static_cast<Collider*>(m_pOwner->GetComponent(TEXT("Collider")));
	//if (collider->GetIsCollision()) {
	//	//m_fJumpForce += m_fGravity;
	//	m_fJumpForce = -350.f;
	//}


	//if (m_pOwner->GetObjectPoint().y < 300) {
	//	m_pOwner->SetObjectPointY(m_pOwner->GetObjectPoint().y + m_fGravity * ffDeltaTime);
	//	m_fJumpForce += m_fGravity;
	//}
}
