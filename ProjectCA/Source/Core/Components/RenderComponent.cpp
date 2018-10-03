#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Core\Components\RenderComponent.h"
#include	"..\..\..\Include\Core\CResourceManager.h"
#include "..\..\..\Include\Core\Graphic\CSprite.h"
#include "..\..\..\Include\Core\Graphic\CAnim.h"
#include "..\..\..\Include\Scene\Actor\CActor.h"


RenderComponent::RenderComponent()
	:m_iFrame(0), m_dTimeElapsed(0.0f), m_bVisible(true)
{
}

RenderComponent::~RenderComponent()
{
		
}

bool RenderComponent::Init(CActor * pOwner, const Types::tstring & strTag)
{
	//m_pWeakSprite = CResourceManager::GetInstance()->GetWeakSprtiePtr(strSpriteName);
	//if (m_pWeakSprite.lock() == nullptr)
	//	return false;

	std::shared_ptr<CActor> pActor = std::shared_ptr<CActor>(pOwner);
	m_pOwner = pActor;

	m_strComponentTag = strTag;
	//m_ownerState = m_pOwner->GetActorState();

	//if (!AddSprite(Types::OS_IDLE, TEXT("PlayerIdle")))
	//	return false;

	//if (!AddSprite(Types::OS_MOVE, TEXT("PlayerMove")))
	//	return false;


	//For Test Code
	//����� �۵��ϸ� Actor�ܿ��� �߰��ϵ��� �����ؾ���.
	//if (!AddAnim(0.2f, Types::OS_IDLE, TEXT("PlayerIdle"), TEXT("Idle")))
	//	return false;

	//if (!AddAnim(0.2f, Types::OS_MOVE, TEXT("PlayerMove"), TEXT("Move")))
	//	return false;

	return true;
}

void RenderComponent::Update(double fDeltaTime)
{
	//if (m_pWeakSprite.expired())
	//	m_pWeakSprite.reset();

	//if (m_ownerState != m_pOwner->GetActorState())
	//	m_ownerState = m_pOwner->GetActorState();

	for (auto& it : m_animationTable) {
		it.second->Update(fDeltaTime);
	}

	m_dTimeElapsed += fDeltaTime;

}

//DC�ڵ鰪�� BackBuffer�� DC�� �޾ƿ;� �Ѵ�.
void RenderComponent::Draw(const HDC & hDC)
{
	if (m_bVisible) {
		//m_animTable[m_ownerState]->Draw(hDC, hMemDC);
		m_pWeakCurAnim.lock()->Draw(hDC);

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


bool RenderComponent::AddAnim(double dPlayTime, const Types::tstring & strSpriteName
	, bool bAnimate, const Types::tstring & strAnimTag)
{
	std::shared_ptr<CAnim> pAnim = std::make_shared<CAnim>();

	if (!pAnim->Init(m_pOwner, strSpriteName, dPlayTime, bAnimate, strAnimTag))
		return false;

	if (m_pWeakCurAnim.expired())
		m_pWeakCurAnim = pAnim;

	if (m_animationTable.find(strAnimTag) != m_animationTable.end()) { //���̺� �ȿ� �ش� Key���� ����� vector�� �ִ� ���
		m_animationTable[strAnimTag] = pAnim;
	}
	else {	//���̺� �ȿ� �ش� Key���� ����� vector�� ���� ���
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
