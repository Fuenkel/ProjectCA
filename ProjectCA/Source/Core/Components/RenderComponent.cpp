#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\RenderComponent.h"
#include	"..\..\..\Include\Core\CResourceManager.h"
#include "..\..\..\Include\Core\Graphic\CSprite.h"
#include "..\..\..\Include\Core\Graphic\CAnim.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"



RenderComponent::RenderComponent()
	:m_bVisible(true), m_bChangeAnim(false)
{
}

RenderComponent::~RenderComponent()
{
	if (m_hBrush)
		DeleteObject(m_hBrush);
	
	m_animationTable.clear();

}

bool RenderComponent::Init(CActor * pOwner, const Types::tstring & strTag)
{
	std::shared_ptr<CActor> pActor = std::shared_ptr<CActor>(pOwner);
	m_pOwner = pActor;

	m_strComponentTag = strTag;
	
	m_ownerState = m_pOwner->GetActorState();
	m_ownerJumpState = m_pOwner->GetActorJumpState();
	m_ownerDirection = m_pOwner->GetActorDirection();

	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	return true;
}

void RenderComponent::Update(double dDeltaTime)
{
	if (m_ownerState != m_pOwner->GetActorState()
		|| m_ownerDirection != m_pOwner->GetActorDirection()
		|| m_ownerJumpState != m_pOwner->GetActorJumpState())
	{
		m_ownerState = m_pOwner->GetActorState();
		m_ownerDirection = m_pOwner->GetActorDirection();
		m_ownerJumpState = m_pOwner->GetActorJumpState();

		//if (m_bChangeAnim)
		//{
		ChangeAnimationCilp();
		//	m_bChangeAnim = false;
		//}
	}
	m_pWeakCurAnim.lock()->Update(dDeltaTime);
	//for (auto& it : m_animationTable) {
	//	it.second->Update(fDeltaTime);
	//}

	//m_dTimeElapsed += fDeltaTime;
}

//DC�ڵ鰪�� BackBuffer�� DC�� �޾ƿ;� �Ѵ�.
void RenderComponent::Draw(const HDC & hDC)
{
	if (m_bVisible) 
	{
		m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);
		//m_animTable[m_ownerState]->Draw(hDC, hMemDC);
		m_pWeakCurAnim.lock()->Draw(hDC);

		Rectangle(hDC, m_pOwner->GetActorPoint().x, m_pOwner->GetActorPoint().y,
			m_pOwner->GetActorPoint().x + m_pOwner->GetActorWidth(),
			m_pOwner->GetActorPoint().y + m_pOwner->GetActorHeight());
		m_hBrush = (HBRUSH)SelectObject(hDC, m_hOldBrush);
	
	}		

}

//bool RenderComponent::AddSprite(Types::ObjectState state, const Types::tstring & strSpriteName)
//{
//	m_pWeakSprite = CResourceManager::GetInstance()->GetWeakSprtiePtr(strSpriteName);
//
//	//�ش� Sprite�� ���� ���
//	if(m_pWeakSprite.expired())
//		return false;
//	
//	if (m_spriteTable.find(state) != m_spriteTable.end()) { //���̺� �ȿ� �ش� Key���� ����� vector�� �ִ� ���
//		for (auto& it : m_spriteTable[state]) {		//vector�� �̹� �����ϴ� Sprite�� false return
//			if (it.lock() == m_pWeakSprite.lock())
//				return false;
//		}
//		m_spriteTable[state].emplace_back(m_pWeakSprite);		//vector�� ������ �ش� Sprite �߰�
//	}
//	else {	//���̺� �ȿ� �ش� Key���� ����� vector�� ���� ���
//		//�ش� Key���� ����� Vector�� ������ ��, Sprite �߰�
//		m_spriteTable.insert(std::make_pair(state, WeakSpritePtrList()));
//		m_spriteTable[state].emplace_back(m_pWeakSprite);
//	}	
//	
//	return true;
//}

//bool RenderComponent::AddAnim(double dPlayTime, Types::ObjectState state, const Types::tstring & strSpriteName, 
//	const Types::tstring& strAnimTag)
//{
//	std::shared_ptr<CAnim> pAnim = std::make_shared<CAnim>();
//
//	if (!pAnim->Init(m_pOwner, strSpriteName, dPlayTime, strAnimTag))
//		return false;
//
//	if (m_animTable.find(state) != m_animTable.end()) { //���̺� �ȿ� �ش� Key���� ����� vector�� �ִ� ���
//		m_animTable[state] = pAnim;
//	}
//	else {	//���̺� �ȿ� �ش� Key���� ����� vector�� ���� ���
//			//�ش� Key���� ����� Vector�� ������ ��, Anim �߰�
//		m_animTable.insert(std::make_pair(state, pAnim));
//	}
//
//	return true;
//}


bool RenderComponent::AddAnim(double dPlayTime, const Types::tstring & strSpriteName,
	UINT iWidth, UINT iHeight,	bool bLoop, bool bAnimate, const Types::tstring & strAnimTag)
{
	std::shared_ptr<CAnim> pAnim = std::make_shared<CAnim>();

	if (!pAnim->Init(m_pOwner, strSpriteName, iWidth, iHeight, dPlayTime, bLoop, bAnimate, strAnimTag))
		return false;

	if (m_pWeakCurAnim.expired())
		m_pWeakCurAnim = pAnim;

	//���̺� �ȿ� �ش� Key���� ����� vector�� �ִ� ���
	if (m_animationTable.find(strAnimTag) != m_animationTable.end())
	{ 
		m_animationTable[strAnimTag] = pAnim;
	}
	else 
	{	
		//���̺� �ȿ� �ش� Key���� ����� vector�� ���� ���
		//�ش� Key���� ����� Vector�� ������ ��, Anim �߰�
		m_animationTable.insert(std::make_pair(strAnimTag, pAnim));
	}

	return true;
}

bool RenderComponent::ChangeAnimation(const Types::tstring & strAnimTag)
{
	auto it = m_animationTable.find(strAnimTag);
	if ( it == m_animationTable.end())
		return false;

	if ((*it).second == nullptr)
		return false;

	if (!m_pWeakCurAnim.expired()) {
		if (m_pWeakCurAnim.lock()->GetAnimTag() == strAnimTag)
			return true;

		m_pWeakCurAnim.lock()->ClearEleapsedTime();
	}
	m_pWeakCurAnim = (*it).second;

	return true;
}

bool RenderComponent::SetAnimationPlaySpeed(double dSpeed)
{
	return m_pWeakCurAnim.lock()->SetPlaySpeed(dSpeed);
}

void RenderComponent::ChangeAnimationCilp()
{

	//switch (m_ownerState) {
	//case Types::OS_IDLE:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		if(m_pOwner->GetActorJumpState() == Types::JS_JUMP)
	//			ChangeAnimation(TEXT("JumpLeft"));
	//		else if(m_pOwner->GetActorJumpState() == Types::JS_FALL)
	//			ChangeAnimation(TEXT("FalldownLeft"));
	//		else
	//			ChangeAnimation(TEXT("IdleLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		if (m_pOwner->GetActorJumpState() == Types::JS_JUMP)
	//			ChangeAnimation(TEXT("JumpRight"));
	//		else if (m_pOwner->GetActorJumpState() == Types::JS_FALL)
	//			ChangeAnimation(TEXT("FalldownRight"));
	//		else
	//			ChangeAnimation(TEXT("IdleRight"));
	//	break;
	//case Types::OS_WALK:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		if (m_pOwner->GetActorJumpState() == Types::JS_JUMP)
	//			ChangeAnimation(TEXT("JumpLeft"));
	//		else if (m_pOwner->GetActorJumpState() == Types::JS_FALL)
	//			ChangeAnimation(TEXT("FalldownLeft"));
	//		else
	//			ChangeAnimation(TEXT("WalkLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		if (m_pOwner->GetActorJumpState() == Types::JS_JUMP) {
	//			ChangeAnimation(TEXT("JumpRight"));
	//			puts("JUMPLEFT");
	//		}
	//		else if (m_pOwner->GetActorJumpState() == Types::JS_FALL)
	//			ChangeAnimation(TEXT("FalldownRight"));
	//		else
	//			ChangeAnimation(TEXT("WalkRight"));
	//	break;
	//case Types::OS_RUN:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		if (m_pOwner->GetActorJumpState() != Types::JS_IDLE)
	//			ChangeAnimation(TEXT("RunJumpLeft"));
	//		else
	//			ChangeAnimation(TEXT("RunLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		if (m_pOwner->GetActorJumpState() != Types::JS_IDLE)
	//			ChangeAnimation(TEXT("RunJumpRight"));
	//		else
	//			ChangeAnimation(TEXT("RunRight"));
	//	break;
	//case Types::OS_LOOKUP:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		ChangeAnimation(TEXT("LookupLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		ChangeAnimation(TEXT("LookupRight"));
	//	break;
	//case Types::OS_SITDOWN:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		ChangeAnimation(TEXT("SitdownLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		ChangeAnimation(TEXT("SitdownRight"));
	//	break;
	//case Types::OS_ATTACK:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		ChangeAnimation(TEXT("AttackLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		ChangeAnimation(TEXT("AttackRight"));
	//	break;
	//case Types::OS_DAMAGED:
	//	if (m_ownerDirection == Types::DIR_LEFT)
	//		ChangeAnimation(TEXT("DamagedLeft"));
	//	else if (m_ownerDirection == Types::DIR_RIGHT)
	//		ChangeAnimation(TEXT("DamagedRight"));
	//	break;

	//}

	//if (m_ownerState == Types::OS_RUN)
	//	puts("RUN");

	if (m_ownerJumpState == Types::JS_JUMP) {
		switch (m_ownerState) {
		case Types::OS_IDLE:
		case Types::OS_WALK:
		case Types::OS_LOOKUP:
			if (m_ownerDirection == Types::DIR_LEFT)
			{
				ChangeAnimation(TEXT("JumpLeft"));
				//puts("JUMPLEFT");
			}
			else if (m_ownerDirection == Types::DIR_RIGHT)
			{
				ChangeAnimation(TEXT("JumpRight"));
				//puts("JUMPRIGHT");
			}
			break;
		case Types::OS_RUN:
			if (m_ownerDirection == Types::DIR_LEFT)
			{
				ChangeAnimation(TEXT("RunJumpLeft"));
			}
			else if (m_ownerDirection == Types::DIR_RIGHT)
			{
				ChangeAnimation(TEXT("RunJumpRight"));
			}
			break;
		case Types::OS_ATTACK:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("AttackLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("AttackRight"));
			break;
		case Types::OS_DAMAGED:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("DamagedLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("DamagedRight"));
			break;
		}

	}
	else if (m_ownerJumpState == Types::JS_FALL) {
		switch (m_ownerState) {
		case Types::OS_IDLE:
		case Types::OS_WALK:
		case Types::OS_LOOKUP:
			if (m_ownerDirection == Types::DIR_LEFT)
			{
				ChangeAnimation(TEXT("FalldownLeft"));
				//puts("FALLLEFT");
			}
			else if (m_ownerDirection == Types::DIR_RIGHT)
			{
				ChangeAnimation(TEXT("FalldownRight"));
				//puts("FALLRIGHT");
			}
			break;
		case Types::OS_RUN:
			if (m_ownerDirection == Types::DIR_LEFT) 
			{
				ChangeAnimation(TEXT("RunJumpLeft"));
			}
			else if (m_ownerDirection == Types::DIR_RIGHT) 
			{	
				ChangeAnimation(TEXT("RunJumpRight"));
			}
			break;
		case Types::OS_ATTACK:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("AttackLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("AttackRight"));
			break;
		case Types::OS_DAMAGED:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("DamagedLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("DamagedRight"));
			break;
		}
	}
	else {
		switch (m_ownerState) {
		case Types::OS_IDLE:
			//puts("ChangeIDLE");
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("IdleLeft"));
			else if(m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("IdleRight"));
			break;
		case Types::OS_WALK:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("WalkLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("WalkRight"));
			break;
		case Types::OS_RUN:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("RunLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("RunRight"));
			break;
		case Types::OS_LOOKUP:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("LookupLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("LookupRight"));
			break;
		case Types::OS_SITDOWN:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("SitdownLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("SitdownRight"));
			break;
		case Types::OS_ATTACK:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("AttackLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("AttackRight"));
			break;
		case Types::OS_DAMAGED:
			if (m_ownerDirection == Types::DIR_LEFT)
				ChangeAnimation(TEXT("DamagedLeft"));
			else if (m_ownerDirection == Types::DIR_RIGHT)
				ChangeAnimation(TEXT("DamagedRight"));
			break;

		}

	}



}
